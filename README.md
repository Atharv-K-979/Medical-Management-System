# Medical-Management-System

## 📌 Project Description

Medical Management System is a simple **Command-Line Interface (CLI) application** designed to manage medical inventory, users, and notifications efficiently. It supports basic CRUD operations for medicines and users, as well as features such as inventory tracking and email notifications. Developed using C++ and Python, the project demonstrates Object-Oriented Programming (OOP) practices and real-world integration.

<!-- ![Project Banner](images/banner.png) -->

## 🚀 Features

- **Inventory Management:** Add, update, and delete medicines with details.
- **User Management:** Handle user roles and access.
- **Email Notifications:** Automated email alerts for low stock or other events.
- **Billing/Order:** Track and generate bills for medical purchases.
- **File Storage:** Save and retrieve records from files.
- **Simple CLI Interface:** User-friendly console menus and prompts.

<!-- ![CLI Screenshot](images/cli.png) -->
## IMAGES 

## Images

![Add Medicine Screenshot](OP_IMAGES/addmed.jpeg)




## 🛠 Technologies Used

- **C++**: Core application logic (OOP concepts, file handling)
- **Python**: Email notification support
- **Makefile**: Automated build process

## 📌 How to Run the Project

1. Clone the repository
   - **git clone https://github.com/Atharv-K-979/Medical-Management-System.git**

2. Move to the project directory
   - **cd Medical-Management-System**

3. Compile the program using Makefile
   - **make**

   OR manually:
   - **g++ main.cpp Inventory.cpp Medicine.cpp EmailNotifier.cpp -o MedicalManagementSystem**

4. (Optional) For email notifications, ensure Python is installed
   - **python --version**
   - **pip install smtplib**

5. Run the program
   - **./MedicalManagementSystem**


## 📖 Usage Instructions

- Launch the executable.
- Navigate using the CLI menu to:
  - Manage medicines
  - Add new medicines or users
  - Search, update, or delete records
  - Trigger inventory alerts and send email notifications (Python script)
- Exit when finished.

<!-- ![Main Menu](images/menu.png) -->

## 🏗 Future Improvements

- Integrate a database (e.g., SQLite) for persistent data.
- Add a GUI version for better usability.
- Advanced reporting and analytics.
- Multi-user authentication and access control.
- REST APIs for integration with web/mobile apps.

---

*Developed by: Atharv Kulkarni*

<!-- ![Logo](images/logo.png) -->


