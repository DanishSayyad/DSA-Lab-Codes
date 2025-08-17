#include<iostream>
#include<cstring>
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
		short freq[5];
	public:
		TaskManager() {
			head = NULL;
			tail = NULL;
			for(int i = 0; i < 5; i++) freq[i] = 0;
		}
		void addTask(string, short, int);
		void displayTasks();
		bool removeTask(int);
		void priorityCount();
		void markOff();
		void totalTime();
		void searchTask(string);
		void updateTask(int);
	};
	
void showChoice() {
	cout << "1. Add a task\n";
	cout << "2. Remove a task\n";
	cout << "3. Display all tasks\n";
	cout << "4. Update a task\n";
	cout << "5. Search a task\n";
	cout << "6. Mark off a task\n";
	cout << "7. Task count by priority\n";
	cout << "8. Total time required.\n";
	cout << "9. Quit\n";
	return;
}

enum choice {
	None,
	ADD,
	REMOVE,
	DISPLAY,
	UPDATE,
	SEARCH,
	MARK,
	INFO,
	COUNT,
	QUIT
};

int main() {
	TaskManager T1;
	
	int choice, t;
	short p;
	string n;
	
	T1.addTask("Daily cleaning.", 2, 30);
	T1.addTask("DSA Homework.", 3, 50);
	T1.addTask("Machine learning course.", 3, 60);
	T1.addTask("Paying back Jay.", 4, 10);
	T1.addTask("Taking ACM membership.", 5, 15);
	T1.addTask("Buying a chocolate.", 1, 20);
	
	while(choice != QUIT) {
		showChoice();
		cout << "Enter your choice: ";
		cin >> choice;
		cout << endl;
		switch(choice) {
			case ADD:
				cout << "Enter task name to add: ";
				cin.ignore();
				getline(cin, n);
				cout << "Enter task priority: ";
				cin >> p;
				cout << "Enter task time: ";
				cin >> t;
				T1.addTask(n, p, t);
				break;
				
			case REMOVE:
				int num;
				cout << "Enter task number to remove: ";
				cin >> num;
				if(T1.removeTask(num)) cout << "Task removed successfully!\n";
				else cout << "Could not find the task!\n";
				break;
			
			case UPDATE:
				int upos;
				cout << "Enter task number to update: ";
				cin >> upos;
				T1.updateTask(upos);
				break;
				
			case DISPLAY:
				T1.displayTasks();
				break;
				
			case MARK:
				T1.markOff();
				break;
				
			case INFO:
				cout << "Task count by priority:\nPriority\tCount\n";
				T1.priorityCount();
				break;

			case COUNT:
				T1.totalTime();
				break;
			
			case SEARCH:
				cout << "Enter task name to search: ";
				cin.ignore();
				getline(cin, n);
				T1.searchTask(n);
				break;

			case QUIT:
				cout << "Quitting program.";
				break;
		}
		cout << endl;
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
	freq[priority - 1]++;
	
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
	int num = 1;
	
	if(!head) {
		cout << "No Task To Be Done!\n";
		return;
	}
	
	cout << "\tPriority - Name (time)\n";
	
	while(ptr) {
		cout << num++ << ")\t" << ptr->priority << "\t" << ptr->name << " (" << ptr->time << ")\n";
		ptr = ptr->next;
	}
	
	return;
}

bool TaskManager :: removeTask(int n) {
	if(!head) return false;
	node *ptr = head, *p2 = NULL;
	while(ptr) {
		if(!(--n))
			break;
		p2 = ptr;
		ptr = ptr->next;
	}
	if(n) return false;
	if(ptr == head) head = head->next;
	else p2->next = ptr->next;
	if(tail == ptr) tail = p2;
	freq[ptr->priority - 1]--;
	delete ptr;
	return true;
}

void TaskManager :: markOff() {
	if(!head) {
		cout << "No task to be marked off\n";
		return;
	}
	else if(head->next == NULL) {
		removeTask(1);
		return;
	}
	else {
		node *temp = head->next, *ptr = head;
		int num = 1, num_t = 2;
		while(temp) {
			if(temp->priority == ptr->priority) {
				if(temp->time < ptr->time)
					ptr = temp;
					num = num_t;
			}
			else break;
			temp = temp->next;
			num_t++;
		}
		removeTask(num);
	}
	return;
}

void TaskManager :: priorityCount() {
	for(int i = 0; i < 5; i++)
		cout << "(" << i + 1 << ")\t\t" << freq[i] << endl;
	return;
}

void TaskManager :: totalTime() {
	if(!head) {
		cout << "No tasks pending.\n";
		return;
	}

	node *ptr = head;
	int time = 0, count = 0;
	while(ptr) {
		count++;
		time += ptr->time;
		ptr = ptr->next;
	}

	cout << "It'll take " << time << " minutes to complete " << count << " tasks.\n";
	return;
}

void TaskManager :: searchTask(string taskName) {
    if (!head) {
        cout << "No tasks to be searched.\n";
        return;
    }
    node *ptr = head;
    int pos = 1;
    bool found = false;
    while (ptr) {
        if (ptr->name == taskName) {
            cout << "Task found at position: " << pos << endl;
            found = true;
            break;
        }
        ptr = ptr->next;
        pos++;
    }
    if (!found) {
        cout << "Not found\n";
    }
    return;
}

void TaskManager :: updateTask(int num) {
	node *ptr = head;
    int pos = 1;
    while (ptr && pos < num) {
        ptr = ptr->next;
        pos++;
    }
    if (!ptr) {
        cout << "No task at position " << num << endl;
        return;
    }

	removeTask(num);

    string name;
    short priority;
    int time;
    cout << "Enter new task name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter new task priority: ";
    cin >> priority;
    cout << "Enter new task time: ";
    cin >> time;
    addTask(name, priority, time);
    cout << "Task updated successfully!\n";
    return;
}
