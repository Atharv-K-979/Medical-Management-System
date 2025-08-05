#ifndef EMAILNOTIFIER_H
#define EMAILNOTIFIER_H

#include <vector>
#include <string>
#include "Medicine.h"

class EmailNotifier {
public:
    EmailNotifier();

    void sendLowStockAlert(const std::vector<Medicine>& medicines, const std::vector<std::string>& emails);
    void sendExpiryAlert(const std::vector<Medicine>& medicines, const std::vector<std::string>& emails);

private:
    void sendEmail(const std::string& message, const std::string& subject, const std::vector<std::string>& emails);
    std::string escapeForCommand(const std::string& input);
};

#endif 
