Smart Task Organizer 🚀
Project Description 📝
The Smart Task Organizer is a console-based C++ application designed to manage tasks and employees within an organization. This project was created to learn and demonstrate Object-Oriented Programming (OOP) concepts in C++ from scratch. It focuses on applying key OOP principles such as encapsulation 🔒, inheritance 🌳, polymorphism 🔄, and abstraction 🧠 to build a robust and extensible system. The application allows users to add tasks and employees, assign tasks to employees, mark tasks as completed, and display task and employee information. 🎯
The system is built with modularity in mind, making it easy to extend with additional features or task types. It includes input validation to ensure data integrity and provides a user-friendly command-line interface with colorful output for interaction. 💻
Learning Objectives 🎓
This project was developed to:

Understand and implement core OOP concepts in C++. 🛠️
Practice class design, inheritance, and polymorphism. 📚
Work with dynamic data structures like std::vector. 📊
Implement input validation and error handling. ✅
Gain experience in managing relationships between objects (e.g., tasks and employees). 🤝

Features ✨

Task Management:
Add new development tasks with a description, ID, priority, and assigned employee. 📋
Mark tasks as completed, automatically removing them from the assigned employee's task list. ✔️
Display all tasks with their details (ID, description, priority, employee ID, and status). 🖥️


Employee Management:
Add new employees with a name and ID. 👷
Assign tasks to employees and track their assigned tasks. 📌
Remove tasks from employees when completed. 🗑️
Display all employees with their details and assigned task IDs. 🧑‍💼


Input Validation:
Ensures unique task and employee IDs. 🔍
Validates task priority (Low, Medium, High). 🎚️
Checks for valid positive integer IDs. 🔢
Prevents empty descriptions or names. 🚫


User Interface:
Interactive menu-driven console interface with colorful prompts and error messages. 🖱️
Clear error messages for invalid inputs. ⚠️



Classes and Functions 🧩
Below is a summary of the classes and their key functions used in the project:
Class: Task 🗒️
An abstract base class representing a generic task.

Data Members:
description (string): Task description. 📜
taskId (int): Unique task identifier. 🆔
priority (string): Task priority (Low, Medium, High). 🎯
employeeId (int): ID of the employee assigned to the task. 👤


Member Functions:
Task(string desc, int id, string prio, int empId): Constructor to initialize a task. 🏗️
virtual void display() const = 0: Pure virtual function to display task details. 🖨️
virtual ~Task(): Virtual destructor for proper cleanup in derived classes. 🧹
int getId() const: Returns the task ID. 🔢
string getDescription() const: Returns the task description. 📝
string getPriority() const: Returns the task priority. 🎚️
int getEmployeeId() const: Returns the employee ID. 👤



Class: DevelopmentTask (inherits from Task) 🛠️
Represents a specific type of task with completion status.

Data Members:
isCompleted (bool): Tracks whether the task is completed. ✅


Member Functions:
DevelopmentTask(string desc, int id, string prio, int empId): Constructor to initialize a development task. 🏗️
void display() const override: Displays task details, including completion status. 🖥️
void markCompleted(): Marks the task as completed. ✔️
bool getStatus() const: Returns the task's completion status. ❓



Class: Employee 👷
Represents an employee who can be assigned tasks.

Data Members:
name (string): Employee's name. 🧑
empId (int): Unique employee identifier. 🆔
assignedTasks (vector): List of task IDs assigned to the employee. 📋


Member Functions:
Employee(string n, int id): Constructor to initialize an employee. 🏗️
void assignTask(int taskId): Assigns a task to the employee. 📌
void removeTask(int taskId): Removes a task from the employee's assigned tasks. 🗑️
void display() const: Displays employee details and assigned task IDs. 🖥️
int getId() const: Returns the employee ID. 🔢
string getName() const: Returns the employee's name. 🧑



Class: TaskManager 🧑‍💼
Manages tasks and employees, serving as the core system controller.

Data Members:
tasks (vector): List of all tasks. 📋
employees (vector): List of all employees. 👥


Member Functions:
size_t getEmployeeCount() const: Returns the number of employees. 🔢
void addTask(const DevelopmentTask& task): Adds a new task with validation. ➕
void addEmployee(const Employee& emp): Adds a new employee with validation. ➕
void assignTaskToEmployee(int taskId, int empId): Assigns a task to an employee. 📌
void displayTasks() const: Displays all tasks. 🖥️
void displayEmployees() const: Displays all employees. 🖥️
void completeTask(int taskId): Marks a task as completed and removes it from the assigned employee. ✔️
bool isTaskIdUnique(int taskId) const: Checks if a task ID is unique. 🔍
bool isEmployeeIdUnique(int empId) const: Checks if an employee ID is unique. 🔍
bool isEmployeeIdExists(int empId) const: Checks if an employee ID exists. 🔍



Helper Functions 🛠️

bool isValidPriority(string prio): Validates if the priority is "Low," "Medium," or "High." 🎚️
bool isValidId(string input, int& id): Validates if the input is a positive integer ID. 🔢
int getUserChoice(): Displays the menu and retrieves the user's choice. 📋
void displayWelcomeMessage(): Displays a colorful welcome message at program start. 🚀
void enableAnsiSupport(): Enables ANSI escape codes for Windows terminals. 🖥️
int main(): Entry point, runs the interactive menu loop. 🚪

Dependencies 📦

C++ Standard Library:
<iostream>: For input/output operations. 🖨️
<string>: For string manipulation. 📝
<vector>: For dynamic arrays of tasks and employees. 📊
<cctype>: For character handling (used in tolower). 🔡
<algorithm>: For string transformations (e.g., transform). 🔄
<iomanip>: For formatted output (e.g., setw). 📏


Windows-specific:
<windows.h>: For enabling ANSI escape code support on Windows. 🖥️



How to Run 🏃

Clone the repository from GitHub. 📥
Compile the code using a C++ compiler (e.g., g++):g++ -o smart_task_organizer main.cpp


Run the executable:./smart_task_organizer


Follow the interactive menu to manage tasks and employees. 🖱️

Usage 🎮

Select options 1–6 from the menu to perform actions. 🔢
Enter valid task and employee IDs (positive integers). 🆔
Ensure task priorities are "Low," "Medium," or "High" (case-insensitive). 🎚️
Add employees before assigning tasks, as tasks require an existing employee ID. 👷

Future Improvements 🚀

Add support for multiple task types (e.g., BugFixTask, DesignTask). 🛠️
Implement file I/O to save and load tasks/employees. 💾
Add task deadlines and sorting by priority or deadline. ⏰
Enhance the user interface (e.g., GUI or better console formatting). 🖼️

License 📜
This project is licensed under the MIT License. 🗳️