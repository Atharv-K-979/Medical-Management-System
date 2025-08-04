#include "Inventory.h"
#include <iostream>
#include <algorithm>

using namespace std;

Inventory::Inventory() {}

void Inventory::addMedicine(const Medicine& med) {
    medicines.push_back(med);
}

bool Inventory::deleteMedicine(const string& name) {
    for (auto it = medicines.begin(); it != medicines.end(); ++it) {
        if (it->getName() == name) {
            medicines.erase(it);
            return true;
        }
    }
    return false;
}

bool Inventory::updateStock(const string& name, int deltaQty) {
    for (auto& med : medicines) {
        if (med.getName() == name) {
            int newQty = med.getQuantity() + deltaQty;
            if (newQty < 0) {
                return false; // Cannot have negative stock
            }
            med.setQuantity(newQty);
            return true;
        }
    }
    return false;
}

void Inventory::displayAllMedicines() const {
    if (medicines.empty()) {
        cout << "No medicines in inventory." << endl;
        return;
    }
    for (const auto& med : medicines) {
        med.displayInfo();
        cout << "------------------------" << endl;
    }
}

vector<Medicine> Inventory::getLowStockMedicines(int threshold) const {
    vector<Medicine> lowStockMeds;
    for (const auto& med : medicines) {
        if (med.isLowStock(threshold)) {
            lowStockMeds.push_back(med);
        }
    }
    return lowStockMeds;
}

vector<Medicine> Inventory::getExpiringMedicines() const {
    vector<Medicine> expiringMeds;
    for (const auto& med : medicines) {
        if (med.isNearExpiry()) {
            expiringMeds.push_back(med);
        }
    }
    return expiringMeds;
}

void Inventory::removeExpiredMedicines() {
    medicines.erase(
        remove_if(medicines.begin(), medicines.end(),
                       [](const Medicine& med) { return med.isExpired(); }),
        medicines.end());
}
