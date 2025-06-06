#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Task {
    string description;
    bool completed;
};

vector<Task> taskList;

void showMenu() {
    cout << "\n--- TO-DO LIST MANAGER ---\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Remove Task\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

void addTask() {
    string taskDesc;
    cout << "Enter task description: ";
    cin.ignore(); 
    getline(cin, taskDesc);
    taskList.push_back({taskDesc, false});
    cout << "Task added successfully!\n";
}

void viewTasks() {
    if (taskList.empty()) {
        cout << "No tasks available.\n";
        return;
    }

    cout << "\n--- Your Tasks ---\n";
    for (size_t i = 0; i < taskList.size(); ++i) {
        cout << i + 1 << ". " << taskList[i].description
             << " [" << (taskList[i].completed ? "Completed" : "Pending") << "]\n";
    }
}

void markTaskCompleted() {
    viewTasks();
    if (taskList.empty()) return;

    int index;
    cout << "Enter task number to mark as completed: ";
    cin >> index;

    if (index < 1 || index > taskList.size()) {
        cout << "Invalid task number.\n";
    } else if (taskList[index - 1].completed) {
        cout << "Task is already marked as completed.\n";
    } else {
        taskList[index - 1].completed = true;
        cout << "Task marked as completed.\n";
    }
}

void removeTask() {
    viewTasks();
    if (taskList.empty()) return;

    int index;
    cout << "Enter task number to remove: ";
    cin >> index;

    if (index < 1 || index > taskList.size()) {
        cout << "Invalid task number.\n";
    } else {
        taskList.erase(taskList.begin() + index - 1);
        cout << "Task removed successfully.\n";
    }
}

int main() {
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3:
                markTaskCompleted();
                break;
            case 4:
                removeTask();
                break;
            case 5:
                cout << "Exiting To-Do List Manager. Goodbye!\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
