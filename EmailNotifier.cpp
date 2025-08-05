#include "EmailNotifier.h"
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

EmailNotifier::EmailNotifier() {}

void EmailNotifier::sendLowStockAlert(const vector<Medicine> &medicines, const vector<string> &emails)
{
    if (medicines.empty() || emails.empty())
    {
        cout << "No low stock medicines or no email recipients." << endl;
        return;
    }
    ostringstream oss;
    oss << "Low Stock Alert for the following medicines:\n";
    for (const auto &med : medicines)
    {
        oss << "- " << med.getName() << " (Quantity: " << med.getQuantity() << ")\n";
    }
    sendEmail(oss.str(), "Low Stock Alert", emails);
}

void EmailNotifier::sendExpiryAlert(const vector<Medicine> &medicines, const vector<string> &emails)
{
    if (medicines.empty() || emails.empty())
    {
        cout << "No expiring medicines or no email recipients." << endl;
        return;
    }
    ostringstream oss;
    oss << "Expiry Alert for the following medicines:\n";
    for (const auto &med : medicines)
    {
        oss << "- " << med.getName() << " (Expiry Date: " << med.getExpiryDate() << ")\n";
    }
    sendEmail(oss.str(), "Expiry Alert", emails);
}

void EmailNotifier::sendEmail(const string &message, const string &subject, const vector<string> &emails)
{
    ostringstream cmd;
    cmd << "python3 send_email.py \"" << escapeForCommand(message) << "\" \"" << escapeForCommand(subject) << "\"";
    for (const auto &email : emails)
    {
        cmd << " " << email;
    }

    string finalCommand = cmd.str();
    cout << "Executing command: " << finalCommand << endl;

    int ret = system(finalCommand.c_str());
    if (ret != 0)
    {
        cerr << "Failed to send email alerts." << endl;
    }
}
string EmailNotifier::escapeForCommand(const string &input)
{
    string escaped;
    for (char c : input)
    {
        switch (c)
        {
        case '\"':
            escaped += "\\\"";
            break;
        case '\n':
            escaped += "\\n";
            break;
        default:
            escaped += c;
            break;
        }
    }
    return escaped;
}
