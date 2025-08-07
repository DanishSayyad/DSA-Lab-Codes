#include<iostream>
#include<string>

using namespace std;

struct node {
	string name;
	short priority;
	int time;
	node *next;
};

class TaskManager {
	private:
		node *head, *tail;
	public:
		TaskManager() {
			head = NULL;
			tail = NULL;
		}
		void addTask(string, short, int);
		void displayTasks();
		void removeTask();
};

void showChoice() {
	cout << "1. Add a task\n";
	cout << "2. Display all tasks\n";
	cout << "3. Quit\n";
	return;
}

int main() {
	TaskManager T1;
	
	int choice, t;
	short p;
	string n;
	
	while(choice != 3) {
		showChoice();
		cout << "Enter your choice: ";
		cin >> choice;
		cout << endl;
		switch(choice) {
			case 1:
                cout << "Enter task name: ";
                cin.ignore();
				getline(cin, n);
				cout << "Enter task priority: ";
				cin >> p;
				cout << "Enter task time: ";
				cin >> t;
				T1.addTask(n, p, t);
                cout << endl;
				break;
			case 2:
				T1.displayTasks();
				break;
			case 3:
				break;
		}
	}
	
	return 0;
}

void TaskManager :: addTask(string name, short priority, int time) {
	if(priority > 5 || priority < 1) {
		cout << "Invalid priority!\n";
		return;
	}

	node *temp = new node;
	
	if(!temp) {
		cout << "Failed to add task!\n";
		return;
	}
	
	temp->name = name;
	temp->priority = priority;
	temp->time = time;
	
	if(!head) {
		head = temp;
		temp->next = NULL;
		tail = temp;
	}
	else {
		if(priority == 5 || head->priority <= priority) {
			temp->next = head;
			head = temp;
		}
		else if(priority == 1 || tail->priority >= priority) {
			temp->next = NULL;
			tail->next = temp;
			tail = temp;
		}
		else{
			node *ptr = head, *p2 = NULL;
			while(ptr) {
				if(ptr->next->priority <= priority)
					break;
				ptr = ptr->next;
			}
			temp->next = ptr->next;
			ptr->next = temp;
		}
	}
	
	return;
}

void TaskManager :: displayTasks() {
	node *ptr = head;
	
	if(!head) {
		cout << "No Task To Be Done!\n";
		return;
	}
	
	while(ptr) {
		cout << ptr->priority << "\t" << ptr->name << " (" << ptr->time << ")\n";
		ptr = ptr->next;
	}
	
	cout << endl;
	
	return;
}