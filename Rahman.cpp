#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <iomanip>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Function to enable ANSI escape codes on Windows
void enableAnsiSupport() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

// Function to display a colorful welcome message
void displayWelcomeMessage() {
    cout << "\033[1;34m"; // Blue color, bold
    cout << "\n============================================\n";
    cout << "   Welcome to Smart Task Organizer! \n";
    cout << "============================================\n";
    cout << "\033[1;36m"; // Cyan color, bold\
    cout << "Manage tasks and employees with ease.\n";
    cout << "Built to explore C++ OOP concepts.\n";
    cout << "\033[0m"; // Reset color
    cout << "\nLet's get started! 😊\n\n";
    cout << flush; // Ensure output is flushed
    // Debug output to confirm function is called
    cout << "[DEBUG] Welcome message displayed.\n" << flush;
}

class Task {
protected:
    string description;
    int taskId;
    string priority;
    int employeeId;
public:
    Task(string desc, int id, string prio, int empId) : description(desc), taskId(id), priority(prio), employeeId(empId) {}
    virtual void display() const = 0;
    virtual ~Task() {}
    int getId() const { return taskId; }
    string getDescription() const { return description; }
    string getPriority() const { return priority; }
    int getEmployeeId() const { return employeeId; }
};

class DevelopmentTask : public Task {
private:
    bool isCompleted;
public:
    DevelopmentTask(string desc, int id, string prio, int empId) 
        : Task(desc, id, prio, empId), isCompleted(false) {}
    void display() const override {
        cout << "\tTask ID: " << setw(4) << taskId 
             << "\tDescription: " << description 
             << "\tPriority: " << priority 
             << "\tEmployee ID: " << employeeId 
             << "\tStatus: " << (isCompleted ? "Completed" : "Pending") << endl;
    }
    void markCompleted() { isCompleted = true; }
    bool getStatus() const { return isCompleted; }
};

class Employee {
private:
    string name;
    int empId;
    vector<int> assignedTasks;
public:
    Employee(string n, int id) : name(n), empId(id) {}
    void assignTask(int taskId) {
        for (int id : assignedTasks) {
            if (id == taskId) return;
        }
        assignedTasks.push_back(taskId);
        cout << "\t" << name << " assigned task ID " << taskId << endl;
    }
    void removeTask(int taskId) {
        for (auto it = assignedTasks.begin(); it != assignedTasks.end(); ++it) {
            if (*it == taskId) {
                assignedTasks.erase(it);
                cout << "\t" << name << " removed task ID " << taskId << endl;
                return;
            }
        }
        cout << "\tTask ID " << taskId << " not found for " << name << endl;
    }
    void display() const {
        cout << "\tEmployee ID: " << setw(4) << empId << "\tName: " << name 
             << "\tAssigned Tasks: ";
        if (assignedTasks.empty()) {
            cout << "None";
        } else {
            for (int id : assignedTasks) cout << id << " ";
        }
        cout << endl;
    }
    int getId() const { return empId; }
    string getName() const { return name; }
};

class TaskManager {
private:
    vector<DevelopmentTask> tasks;
    vector<Employee> employees;
    bool isTaskIdUnique(int taskId) const {
        for (const auto& task : tasks) {
            if (task.getId() == taskId) return false;
        }
        return true;
    }
    bool isEmployeeIdUnique(int empId) const {
        for (const auto& emp : employees) {
            if (emp.getId() == empId) return false;
        }
        return true;
    }
    bool isEmployeeIdExists(int empId) const {
        for (const auto& emp : employees) {
            if (emp.getId() == empId) return true;
        }
        return false;
    }
public:
    size_t getEmployeeCount() const { return employees.size(); }
    void addTask(const DevelopmentTask& task) {
        if (!isTaskIdUnique(task.getId())) {
            cout << "\tError: Task ID " << task.getId() << " already exists." << endl;
            return;
        }
        if (task.getDescription().empty()) {
            cout << "\tError: Task description cannot be empty." << endl;
            return;
        }
        if (!isEmployeeIdExists(task.getEmployeeId())) {
            cout << "\tError: Employee ID " << task.getEmployeeId() << " does not exist." << endl;
            return;
        }
        tasks.push_back(task);
        assignTaskToEmployee(task.getId(), task.getEmployeeId());
        cout << "\tAdded task: " << task.getDescription() << endl;
    }
    void addEmployee(const Employee& emp) {
        if (!isEmployeeIdUnique(emp.getId())) {
            cout << "\tError: Employee ID " << emp.getId() << " already exists." << endl;
            return;
        }
        if (emp.getName().empty()) {
            cout << "\tError: Employee name cannot be empty." << endl;
            return;
        }
        employees.push_back(emp);
        cout << "\tAdded employee: " << emp.getName() << endl;
    }
    void assignTaskToEmployee(int taskId, int empId) {
        bool taskFound = false;
        for (auto& task : tasks) {
            if (task.getId() == taskId) {
                taskFound = true;
                if (task.getStatus()) {
                    cout << "\tError: Task ID " << taskId << " is already completed." << endl;
                    return;
                }
                for (auto& emp : employees) {
                    if (emp.getId() == empId) {
                        emp.assignTask(taskId);
                        cout << "\tTask ID " << taskId << " successfully assigned to " << emp.getName() << endl;
                        return;
                    }
                }
                cout << "\tError: Employee ID " << empId << " not found." << endl;
                return;
            }
        }
        if (!taskFound) cout << "\tError: Task ID " << taskId << " not found." << endl;
    }
    void displayTasks() const {
        cout << "\nAll Tasks:\n";
        if (tasks.empty()) cout << "\tNo tasks available." << endl;
        else for (const auto& task : tasks) task.display();
    }
    void displayEmployees() const {
        cout << "\nAll Employees:\n";
        if (employees.empty()) cout << "\tNo employees available." << endl;
        else for (const auto& emp : employees) emp.display();
    }
    void completeTask(int taskId) {
        for (auto& task : tasks) {
            if (task.getId() == taskId) {
                if (task.getStatus()) {
                    cout << "\tError: Task ID " << taskId << " is already completed." << endl;
                    return;
                }
                task.markCompleted();
                cout << "\tTask ID " << taskId << " marked as completed." << endl;
                for (auto& emp : employees) {
                    if (emp.getId() == task.getEmployeeId()) {
                        emp.removeTask(taskId);
                        break;
                    }
                }
                return;
            }
        }
        cout << "\tError: Task ID " << taskId << " not found." << endl;
    }
};

bool isValidPriority(string prio) {
    string lowerPrio = prio;
    transform(lowerPrio.begin(), lowerPrio.end(), lowerPrio.begin(), ::tolower);
    return lowerPrio == "low" || lowerPrio == "medium" || lowerPrio == "high";
}

bool isValidId(string input, int& id) {
    try {
        size_t pos;
        id = stoi(input);
        return id > 0;
    } catch (...) {
        return false;
    }
}

int getUserChoice() {
    string input;
    int choice;
    cout << "\n\033[1;33mSmart Task Organizer:\033[0m\n"; // Yellow color for menu header
    cout << "\t1. Add Task\n";
    cout << "\t2. Add Employee\n";
    cout << "\t3. Mark Task as Completed\n";
    cout << "\t4. Display All Tasks\n";
    cout << "\t5. Display All Employees\n";
    cout << "\t6. Exit\n";
    cout << "\t\033[1;32mEnter your choice (1-6): \033[0m"; // Green color for prompt
    getline(cin, input);
    if (!isValidId(input, choice) || choice < 1 || choice > 6) {
        cout << "\t\033[1;31mInvalid choice. Please enter a number between 1 and 6.\033[0m" << endl; // Red color for error
        return 0;
    }
    return choice;
}

int main() {
    enableAnsiSupport(); // Enable ANSI support for Windows
    displayWelcomeMessage(); // Show welcome message at start
    TaskManager manager;
    while (true) {
        int choice = getUserChoice();
        if (choice == 0) continue;
        if (choice == 6) {
            cout << "\033[1;35m\n====================================\n"; // Magenta color
            cout << "Thank you for using our System! \n";
            cout << "Goodbye! 👋\n";
            cout << "====================================\033[0m\n";
            break;
        }
        switch (choice) {
            case 1: {
                string desc, priority, idInput, empIdInput;
                int id, empId;
                if (manager.getEmployeeCount() == 0) {
                    cout << "\t\033[1;31mError: No employees exist. Add an employee first.\033[0m" << endl; // Red color
                    break;
                }
                cout << "\t\033[1;36mEnter task description: \033[0m"; // Cyan color
                getline(cin, desc);
                cout << "\t\033[1;36mEnter task ID: \033[0m";
                getline(cin, idInput);
                if (!isValidId(idInput, id)) {
                    cout << "\t\033[1;31mError: Task ID must be a positive integer.\033[0m" << endl;
                    break;
                }
                cout << "\t\033[1;36mEnter priority (Low/Medium/High): \033[0m";
                getline(cin, priority);
                if (!isValidPriority(priority)) {
                    cout << "\t\033[1;31mError: Priority must be Low, Medium, or High.\033[0m" << endl;
                    break;
                }
                cout << "\t\033[1;36mEnter employee ID: \033[0m";
                getline(cin, empIdInput);
                if (!isValidId(empIdInput, empId)) {
                    cout << "\t\033[1;31mError: Employee ID must be a positive integer.\033[0m" << endl;
                    break;
                }
                DevelopmentTask task(desc, id, priority, empId);
                manager.addTask(task);
                break;
            }
            case 2: {
                string name, idInput;
                int id;
                cout << "\t\033[1;36mEnter employee name: \033[0m";
                getline(cin, name);
                cout << "\t\033[1;36mEnter employee ID: \033[0m";
                getline(cin, idInput);
                if (!isValidId(idInput, id)) {
                    cout << "\t\033[1;31mError: Employee ID must be a positive integer.\033[0m" << endl;
                    break;
                }
                Employee emp(name, id);
                manager.addEmployee(emp);
                break;
            }
            case 3: {
                string taskIdInput;
                int taskId;
                cout << "\t\033[1;36mEnter task ID to mark as completed: \033[0m";
                getline(cin, taskIdInput);
                if (!isValidId(taskIdInput, taskId)) {
                    cout << "\t\033[1;31mError: Task ID must be a positive integer.\033[0m" << endl;
                    break;
                }
                manager.completeTask(taskId);
                break;
            }
            case 4:
                manager.displayTasks();
                break;
            case 5:
                manager.displayEmployees();
                break;
        }
    }
    return 0;
}