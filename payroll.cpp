#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

const int MAX_EMPLOYEES = 100;

class Employee {
protected:
    string id;
    string name;
    double salary;

public:
    Employee(string id, string name, double salary) : id(id), name(name), salary(salary) {}
    double calculateSalary() { return 0; }
    void display() {}
    string getId() { return id; }
};

class FullTimeEmployee : public Employee {
public:
    FullTimeEmployee(string id, string name, double salary) : Employee(id, name, salary) {}
    double calculateSalary() { return salary; }
    void display() {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Fixed Monthly Salary: $" << salary << "\n";
    }
};

class PartTimeEmployee : public Employee {
private:
    int hoursWorked;
public:
    PartTimeEmployee(string id, string name, double salary, int hoursWorked) 
        : Employee(id, name, salary), hoursWorked(hoursWorked) {}
    double calculateSalary() { return salary * hoursWorked; }
    void display() {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Hourly Wage: $" << salary << "\n";
        cout << "Hours Worked: " << hoursWorked << "\n";
        cout << "Total Salary: $" << calculateSalary() << "\n";
    }
};

class ContractualEmployee : public Employee {
private:
    int projectsCompleted;
public:
    ContractualEmployee(string id, string name, double salary, int projectsCompleted) 
        : Employee(id, name, salary), projectsCompleted(projectsCompleted) {}
    double calculateSalary() { return salary * projectsCompleted; }
    void display() {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Contract Payment Per Project: $" << salary << "\n";
        cout << "Projects Completed: " << projectsCompleted << "\n";
        cout << "Total Salary: $" << calculateSalary() << "\n";
    }
};

void displayMenu() {
    cout << "\nMenu\n";
    cout << "1 - Full-time Employee\n";
    cout << "2 - Part-time Employee\n";
    cout << "3 - Contractual Employee\n";
    cout << "4 - Display Payroll Report\n";
    cout << "5 - Exit\n";
    cout << "Choose an option: ";
}

bool isValidId(const string& id) {
    if (id.empty()) return false;
    for (char c : id) {
        if (!isalnum(c)) return false;
    }
    return true;
}

bool isValidNumber(double num) {
    return num >= 0;
}

int findEmployee(Employee* employees[], int count, const string& id) {
    for (int i = 0; i < count; i++) {
        if (employees[i]->getId() == id) return i;
    }
    return -1;
}

int main() {
    Employee* employees[MAX_EMPLOYEES];
    int employeeCount = 0;
    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        if (choice >= 1 && choice <= 3) {
            string id, name;
            double salary;
            
            do {
                cout << "Enter Employee ID (Alphanumeric, Case Sensitive): ";
                getline(cin, id);
                if (!isValidId(id)) {
                    cout << "Invalid ID! Only alphanumeric characters allowed. Try again.\n";
                } else if (findEmployee(employees, employeeCount, id) != -1) {
                    cout << "Duplicate ID! Try again.\n";
                }
            } while (!isValidId(id) || findEmployee(employees, employeeCount, id) != -1);

            cout << "Enter Name: ";
            getline(cin, name);
            
            do {
                cout << "Enter Salary: ";
                cin >> salary;
                if (!isValidNumber(salary)) {
                    cout << "Invalid input! Salary cannot be negative. Try again.\n";
                }
            } while (!isValidNumber(salary));
            
            cin.ignore();

            if (choice == 1) {
                employees[employeeCount++] = new FullTimeEmployee(id, name, salary);
            } else if (choice == 2) {
                int hours;
                do {
                    cout << "Enter Hours Worked: ";
                    cin >> hours;
                    if (!isValidNumber(hours)) {
                        cout << "Invalid input! Hours worked cannot be negative. Try again.\n";
                    }
                } while (!isValidNumber(hours));
                employees[employeeCount++] = new PartTimeEmployee(id, name, salary, hours);
            } else if (choice == 3) {
                int projects;
                do {
                    cout << "Enter Projects Completed: ";
                    cin >> projects;
                    if (!isValidNumber(projects)) {
                        cout << "Invalid input! Projects completed cannot be negative. Try again.\n";
                    }
                } while (!isValidNumber(projects));
                employees[employeeCount++] = new ContractualEmployee(id, name, salary, projects);
            }
        }
        else if (choice == 4) {
            cout << "\n------ Employee Payroll Report ------\n";
            for (int i = 0; i < employeeCount; i++) {
                employees[i]->display();
                cout << "\n";
            }
        }
    } while (choice != 5);

    for (int i = 0; i < employeeCount; i++) {
        delete employees[i];
    }

    return 0;
}
