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

// push() O(n): we enqueue element and then rotate all previous ones behind it
void QStack::push(int num) {
    enqueue(num);

    // Rotate previous elements behind the new one
    int size = 0;
    for (node *ptr = head; ptr != NULL; ptr = ptr->next)
        size++;

    for (int i = 0; i < size - 1; i++) {
        enqueue(dequeue());
    }
}

// pop() O(1): just dequeue
int QStack::pop() {
    if (isEmpty()) return INT_MIN;
    return dequeue();
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
