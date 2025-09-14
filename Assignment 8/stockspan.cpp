#include <iostream>
#include <climits>

using namespace std;

struct node {
    int data;
    node *next;
    node(int &d) {
        data = d;
        next = NULL;
    }
};

class Stack {
    private:
        node *top;
    
    public:
        Stack();
        ~Stack();
        void push(int);
        int pop();
        int peek();
        bool isEmpty();
    
    friend void display(Stack&);
    friend void stockSpan(Stack&);
};

void display(Stack&);
void stockSpan(Stack&);

int main() {
    Stack stock;

    stock.push(100);
    stock.push(80);
    stock.push(60);
    stock.push(70);
    stock.push(60);
    stock.push(75);
    stock.push(85);

    cout << "The Stock prices:\n";
    display(stock);

    cout << endl;
    stockSpan(stock);

    return 0;
}

void display(Stack &s) {
    if(s.isEmpty()) return;

    int temp = s.pop();
    cout << temp << endl;
    display(s);
    s.push(temp);

    return;
}

void stockSpan(Stack &s) {
    Stack temp;
    int day = 0;
    
    while(!s.isEmpty()) temp.push(s.pop());
    s.push(temp.pop());

    cout << "Daywise  Stock Spans are:\n";
    while(!temp.isEmpty()) {
        int span = 1, num = temp.peek();
        Stack t;
        cout << "Day " << ++day << ": ";
        while(!s.isEmpty() && s.peek() < num) {
            t.push(s.pop());
            span++;
        }
        while(!t.isEmpty()) s.push(t.pop());
        s.push(temp.pop());
        cout << span << endl;
    }

    return;
}

Stack :: Stack() {
    top = NULL;
}

void Stack :: push(int num) {
    node *nn = new node(num);
    if(!nn) {
        cout << "Stack Overflow!";
        return;
    }

    nn->next = top;
    top = nn;
    return;
}

int Stack :: pop() {
    if(isEmpty()) {
        cout << "Stack is empty!";
        return INT_MIN;
    }

    node *ptr = top;
    top = top->next;
    int ans = ptr->data;
    delete ptr;
    return ans;
}

int Stack :: peek() {
    if(isEmpty()) {
        cout << "Stack is empty!";
        return INT_MIN;
    }

    return top->data;
}

bool Stack :: isEmpty() {
    if(!top) return true;
    return false;
}

Stack :: ~Stack() {
    while(!isEmpty()) pop();
    return;
}
