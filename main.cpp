#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Medicine.h"
#include "Inventory.h"
#include "EmailNotifier.h"

using namespace std;

struct User {
    string username;
    string password;
    string role;
};

unordered_map<string, User> loadUsers(const string& filename) {
    unordered_map<string, User> users;
    ifstream file(filename);
    if (!file) {
        cerr << "Failed to open users file." << endl;
        return users;
    }
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        User user;
        if (iss >> user.username >> user.password >> user.role) {
            users[user.username] = user;
        }
    }
    return users;
}

bool authenticate(const unordered_map<string, User>& users, const string& username, const string& password, string& role) {
    auto it = users.find(username);
    if (it != users.end() && it->second.password == password) {
        role = it->second.role;
        return true;
    }
    return false;
}

void adminMenu(Inventory& inventory, EmailNotifier& notifier);
void userMenu(Inventory& inventory);

void addMedicine(Inventory& inventory) {
    string name, expiryDate, pros, cons, dosage, manufacturer;
    int quantity;

    cout << "Enter medicine name: ";
    getline(cin, name);
    cout << "Enter quantity: ";
    cin >> quantity;
    cin.ignore();
    cout << "Enter expiry date (YYYY-MM-DD): ";
    getline(cin, expiryDate);
    cout << "Enter pros: ";
    getline(cin, pros);
    cout << "Enter cons: ";
    getline(cin, cons);
    cout << "Enter dosage: ";
    getline(cin, dosage);
    cout << "Enter manufacturer: ";
    getline(cin, manufacturer);

    Medicine med(name, quantity, expiryDate, pros, cons, dosage, manufacturer);
    inventory.addMedicine(med);
    cout << "Medicine added successfully." << endl;
}

void deleteMedicine(Inventory& inventory) {
    string name;
    cout << "Enter medicine name to delete: ";
    getline(cin, name);
    if (inventory.deleteMedicine(name)) {
        cout << "Medicine deleted successfully." << endl;
    } else {
        cout << "Medicine not found." << endl;
    }
}

void updateStock(Inventory& inventory) {
    string name;
    int delta;
    cout << "Enter medicine name to update stock: ";
    getline(cin, name);
    cout << "Enter quantity change (positive or negative): ";
    cin >> delta;
    cin.ignore();
    if (inventory.updateStock(name, delta)) {
        cout << "Stock updated successfully." << endl;
    } else {
        cout << "Failed to update stock. Check medicine name or quantity." << endl;
    }
}

void viewLowStock(Inventory& inventory) {
    auto lowStockMeds = inventory.getLowStockMedicines();
    if (lowStockMeds.empty()) {
        cout << "No low stock medicines." << endl;
    } else {
        cout << "Low stock medicines:" << endl;
        for (const auto& med : lowStockMeds) {
            med.displayInfo();
            cout << "------------------------" << endl;
        }
    }
}

void viewExpiringSoon(Inventory& inventory) {
    auto expiringMeds = inventory.getExpiringMedicines();
    if (expiringMeds.empty()) {
        cout << "No medicines expiring soon." << endl;
    } else {
        cout << "Medicines expiring soon:" << endl;
        for (const auto& med : expiringMeds) {
            med.displayInfo();
            cout << "------------------------" << endl;
        }
    }
}

void sendEmailAlerts(Inventory& inventory, EmailNotifier& notifier) {
    auto lowStockMeds = inventory.getLowStockMedicines();
    auto expiringMeds = inventory.getExpiringMedicines();

    vector<string> emails;
    string email;
    cout << "Enter email addresses to send alerts (enter empty line to finish):" << endl;
    while (true) {
        getline(cin, email);
        if (email.empty()) break;
        emails.push_back(email);
    }

    if (!lowStockMeds.empty()) {
        notifier.sendLowStockAlert(lowStockMeds, emails);
    }
    if (!expiringMeds.empty()) {
        notifier.sendExpiryAlert(expiringMeds, emails);
    }
    if (lowStockMeds.empty() && expiringMeds.empty()) {
        cout << "No alerts to send." << endl;
    }
}

void removeExpiredMedicines(Inventory& inventory) {
    inventory.removeExpiredMedicines();
    cout << "Expired medicines removed." << endl;
}

void adminMenu(Inventory& inventory, EmailNotifier& notifier) {
    while (true) {
        cout << "\nADMIN Menu:\n"
             << "1. Add Medicine\n"
             << "2. Delete Medicine\n"
             << "3. Update Stock\n"
             << "4. View All Medicines\n"
             << "5. View Low Stock\n"
             << "6. View Expiring Soon\n"
             << "7. Remove Expired Medicines\n"
             << "8. Send Email Alerts\n"
             << "9. Logout\n"
             << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: addMedicine(inventory); break;
            case 2: deleteMedicine(inventory); break;
            case 3: updateStock(inventory); break;
            case 4: inventory.displayAllMedicines(); break;
            case 5: viewLowStock(inventory); break;
            case 6: viewExpiringSoon(inventory); break;
            case 7: removeExpiredMedicines(inventory); break;
            case 8: sendEmailAlerts(inventory, notifier); break;
            case 9: return;
            default: cout << "Invalid choice. Try again." << endl;
        }
    }
}

void userMenu(Inventory& inventory) {
    while (true) {
        cout << "\nUSER Menu:\n"
             << "1. View All Medicines\n"
             << "2. View Low Stock\n"
             << "3. View Expiring Soon\n"
             << "4. Logout\n"
             << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: inventory.displayAllMedicines(); break;
            case 2: viewLowStock(inventory); break;
            case 3: viewExpiringSoon(inventory); break;
            case 4: return;
            default: cout << "Invalid choice. Try again." << endl;
        }
    }
}

int main() {
    auto users = loadUsers("users.txt");
    if (users.empty()) {
        cerr << "No users loaded. Exiting." << endl;
        return 1;
    }

    Inventory inventory;
    EmailNotifier notifier;

    while (true) {
        string username, password, role;
        cout << "Login\nUsername: ";
        getline(cin, username);
        cout << "Password: ";
        getline(cin, password);

        if (authenticate(users, username, password, role)) {
            cout << "Login successful. Role: " << role << endl;
            if (role == "ADMIN") {
                adminMenu(inventory, notifier);
            } else if (role == "USER") {
                userMenu(inventory);
            } else {
                cout << "Unknown role. Access denied." << endl;
            }
        } else {
            cout << "Invalid credentials. Try again." << endl;
        }
    }

    return 0;
}
