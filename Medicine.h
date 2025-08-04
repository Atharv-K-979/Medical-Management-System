#ifndef MEDICINE_H
#define MEDICINE_H

#include <string>
#include <iostream>
#include <ctime>

class Medicine {
private:
    std::string name;
    int quantity;
    std::string expiryDate; // YYYY-MM-DD
    std::string pros;
    std::string cons;
    std::string dosage;
    std::string manufacturer;

    bool parseDate(const std::string& dateStr, std::tm& tm_date) const;
    bool isDateWithinDays(const std::string& dateStr, int days) const;
    bool isDatePastOrToday(const std::string& dateStr) const;

public:
    Medicine();
    Medicine(const std::string& name, int quantity, const std::string& expiryDate,
             const std::string& pros, const std::string& cons,
             const std::string& dosage, const std::string& manufacturer);

    // Getters
    std::string getName() const;
    int getQuantity() const;
    std::string getExpiryDate() const;
    std::string getPros() const;
    std::string getCons() const;
    std::string getDosage() const;
    std::string getManufacturer() const;

    // Setters
    void setName(const std::string& name);
    void setQuantity(int quantity);
    void setExpiryDate(const std::string& expiryDate);
    void setPros(const std::string& pros);
    void setCons(const std::string& cons);
    void setDosage(const std::string& dosage);
    void setManufacturer(const std::string& manufacturer);

    void displayInfo() const;
    bool isLowStock(int threshold = 10) const;
    bool isNearExpiry() const;
    bool isExpired() const;
};

#endif // MEDICINE_H
