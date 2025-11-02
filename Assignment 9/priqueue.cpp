#include <iostream>
#include <string>
using namespace std;

struct Process {
    string name;
    int priority;
    int burstTime;
};

class PriorityQueue {
    Process arr[100];
    int size;
public:
    PriorityQueue() { size = 0; }

    void push(Process p) {
        arr[size++] = p;
        for (int i = size - 1; i > 0; i--) {
            if (arr[i].priority > arr[i - 1].priority) {
                Process temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
            }
        }
    }

    Process pop() {
        if (size == 0) {
            Process empty = {"", -1, 0};
            return empty;
        }
        return arr[--size];
    }

    bool empty() {
        return size == 0;
    }

    Process top() {
        return arr[size - 1];
    }

    int getSize() {
        return size;
    }
};

int main() {
    PriorityQueue pq;
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        Process p;
        cout << "Enter process name: ";
        cin >> p.name;
        cout << "Enter priority (higher = important): ";
        cin >> p.priority;
        cout << "Enter burst time: ";
        cin >> p.burstTime;
        pq.push(p);
        cout << endl;
    }

    cout << "\nCPU Scheduling Order:\n";
    int time = 0;
    while (!pq.empty()) {
        Process p = pq.pop();
        cout << "Running " << p.name << " | Priority: " << p.priority
             << " | Burst: " << p.burstTime << endl;
        time += p.burstTime;
        cout << "Time elapsed: " << time << endl << endl;
    }

    cout << "All processes completed in " << time << " units.\n";
    return 0;
}
