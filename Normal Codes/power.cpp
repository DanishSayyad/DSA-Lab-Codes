#include <iostream>
using namespace std;

struct node {
    int data;
    node *next;
    node(int d) {
        data = d;
        next = NULL;
    }
};

class Stack {
private:
    node *top;
public:
    Stack() { top = NULL; }
    ~Stack() {
        while (top) {
            node *temp = top;
            top = top->next;
            delete temp;
        }
    }
    void push(int d) {
        node *nn = new node(d);
        nn->next = top;
        top = nn;
    }
    int pop() {
        if (!top) throw runtime_error("Stack underflow");
        int d = top->data;
        node *temp = top;
        top = top->next;
        delete temp;
        return d;
    }
    int peek() {
        if (!top) throw runtime_error("Empty stack");
        return top->data;
    }
    bool isEmpty() {
        return top == NULL;
    }
};

int powerNonRecursive(int x, int n) {
    Stack st;
    int result = 1;
    for (int i = n; i > 0; i--) st.push(x);
    while (!st.isEmpty()) result *= st.pop();
    return result;
}

int main() {
    int x, n;
    cout << "Enter base: ";
    cin >> x;
    cout << "Enter exponent: ";
    cin >> n;
    cout << x << "^" << n << " = " << powerNonRecursive(x, n) << endl;
    return 0;
}
