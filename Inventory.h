#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include "Medicine.h"

class Inventory {
private:
    std::vector<Medicine> medicines;

public:
    Inventory();

    void addMedicine(const Medicine& med);
    bool deleteMedicine(const std::string& name);
    bool updateStock(const std::string& name, int deltaQty);
    void displayAllMedicines() const;
    std::vector<Medicine> getLowStockMedicines(int threshold = 10) const;
    std::vector<Medicine> getExpiringMedicines() const;
    void removeExpiredMedicines();
};

#endif // INVENTORY_H
