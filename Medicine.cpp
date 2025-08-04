#include "Medicine.h"
#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;

Medicine::Medicine() : quantity(0) {}

Medicine::Medicine(const string& name, int quantity, const string& expiryDate,
                   const string& pros, const string& cons,
                   const string& dosage, const string& manufacturer)
    : name(name), quantity(quantity), expiryDate(expiryDate),
      pros(pros), cons(cons), dosage(dosage), manufacturer(manufacturer) {}

string Medicine::getName() const { return name; }
int Medicine::getQuantity() const { return quantity; }
string Medicine::getExpiryDate() const { return expiryDate; }
string Medicine::getPros() const { return pros; }
string Medicine::getCons() const { return cons; }
string Medicine::getDosage() const { return dosage; }
string Medicine::getManufacturer() const { return manufacturer; }

void Medicine::setName(const string& name) { this->name = name; }
void Medicine::setQuantity(int quantity) { this->quantity = quantity; }
void Medicine::setExpiryDate(const string& expiryDate) { this->expiryDate = expiryDate; }
void Medicine::setPros(const string& pros) { this->pros = pros; }
void Medicine::setCons(const string& cons) { this->cons = cons; }
void Medicine::setDosage(const string& dosage) { this->dosage = dosage; }
void Medicine::setManufacturer(const string& manufacturer) { this->manufacturer = manufacturer; }

void Medicine::displayInfo() const {
    cout << "Name: " << name << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Expiry Date: " << expiryDate << endl;
    cout << "Pros: " << pros << endl;
    cout << "Cons: " << cons << endl;
    cout << "Dosage: " << dosage << endl;
    cout << "Manufacturer: " << manufacturer << endl;
}

bool Medicine::isLowStock(int threshold) const {
    return quantity < threshold;
}

bool Medicine::parseDate(const string& dateStr, tm& tm_date) const {
    if (dateStr.size() != 10) return false;
    try {
        tm_date.tm_year = stoi(dateStr.substr(0,4)) - 1900;
        tm_date.tm_mon = stoi(dateStr.substr(5,2)) - 1;
        tm_date.tm_mday = stoi(dateStr.substr(8,2));
        tm_date.tm_hour = 0;
        tm_date.tm_min = 0;
        tm_date.tm_sec = 0;
        tm_date.tm_isdst = -1;
        return true;
    } catch (...) {
        return false;
    }
}

bool Medicine::isDateWithinDays(const string& dateStr, int days) const {
    tm tm_expiry = {};
    if (!parseDate(dateStr, tm_expiry)) {
        return false;
    }
    time_t expiry_time = mktime(&tm_expiry);
    time_t now = time(nullptr);
    double diff = difftime(expiry_time, now);
    return diff >= 0 && diff <= days * 24 * 60 * 60;
}

bool Medicine::isNearExpiry() const {
    return isDateWithinDays(expiryDate, 30);
}

bool Medicine::isDatePastOrToday(const string& dateStr) const {
    tm tm_expiry = {};
    if (!parseDate(dateStr, tm_expiry)) {
        return false;
    }
    time_t expiry_time = mktime(&tm_expiry);
    time_t now = time(nullptr);
    return expiry_time <= now;
}

bool Medicine::isExpired() const {
    return isDatePastOrToday(expiryDate);
}
