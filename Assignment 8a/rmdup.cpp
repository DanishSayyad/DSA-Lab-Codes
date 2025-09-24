#include <iostream>

using namespace std;

struct node {
    string data;
    node *next;
    node(string &d) {
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
        void push(string);
        string pop();
        string peek();
        bool isEmpty();
    
    friend void display(Stack&);
    friend void removeDuplicates(Stack&);
};

void display(Stack &);
void removeDuplicates(Stack&);

int main() {
    Stack list;
    list.push("Danish");
    list.push("Danish");
    list.push("Jay");
    list.push("Sneha");
    list.push("Sneha");
    list.push("Khushi");
    list.push("Khushi");
    list.push("Khushi");

    cout << "Stack with dusplicates:\n";
    display(list);
    
    removeDuplicates(list);
    cout << "\nStack after removing dusplicates:\n";
    display(list);
    return 0;
}

void display(Stack &s) {
    if(s.isEmpty()) return;

    string temp = s.pop();
    cout << temp << endl;
    display(s);
    s.push(temp);

    return;
}

void removeDuplicates(Stack &s) {
    if(s.isEmpty()) return;

    string str = s.pop();
    removeDuplicates(s);

    if(s.isEmpty()) s.push(str);

    if(s.peek() == str) return;
    s.push(str);

    return;
}

Stack :: Stack() {
    top = NULL;
}

void Stack :: push(string str) {
    node *nn = new node(str);
    if(!nn) {
        cout << "Stack Overflow!";
        return;
    }

    nn->next = top;
    top = nn;
    return;
}

string Stack :: pop() {
    if(isEmpty()) {
        cout << "Stack is empty!";
        return "\0";
    }

    node *ptr = top;
    top = top->next;
    string ans = ptr->data;
    delete ptr;
    return ans;
}

string Stack :: peek() {
    if(isEmpty()) {
        cout << "Stack is empty!";
        return "\0";
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
