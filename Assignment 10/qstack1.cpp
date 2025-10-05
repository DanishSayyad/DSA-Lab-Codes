#include <iostream>
#include <climits>
using namespace std;

struct node {
    int data;
    node *next;
    node(int num) {
        data = num;
        next = NULL;
    }
};

class QStack {
private:
    node *head, *tail;
    void enqueue(int);
    int dequeue();
    bool isEmpty();

public:
    QStack();
    void push(int);
    int pop();
};

QStack::QStack() {
    head = tail = NULL;
}

void QStack::enqueue(int num) {
    node *nn = new node(num);
    if (!head) {
        head = tail = nn;
    } else {
        tail->next = nn;
        tail = nn;
    }
}

int QStack::dequeue() {
    if (!head) return INT_MIN;
    int num = head->data;
    node *temp = head;
    head = head->next;
    if (!head) tail = NULL;
    delete temp;
    return num;
}

bool QStack::isEmpty() {
    return head == NULL;
}

void QStack::push(int num) {
    enqueue(num); // O(1)
}

int QStack::pop() {
    if (isEmpty()) return INT_MIN;

    QStack tempQueue;

    // Move all elements except the last one to tempQueue
    while (head && head->next) {
        tempQueue.enqueue(dequeue());
    }

    // The last dequeued element is the top of the stack
    int popped = dequeue();

    // Restore the elements back
    while (!tempQueue.isEmpty()) {
        enqueue(tempQueue.dequeue());
    }

    return popped;
}

int main() {
    QStack s;
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.push(50);

    for (int i = 0; i < 5; i++) {
        cout << s.pop() << endl;
    }

    return 0;
}
