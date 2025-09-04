#include <iostream>
#include <climits>

using namespace std;

class Stack {
  private:
    int *a, top, size;
  public:
    Stack(int);
    ~Stack();
    void push(int);
    int pop();
    int peek();
    bool isEmpty();
    bool isFull();
};

int main() {
  return 0;
}

Stack :: Stack(int s) {
  size = s;
  a = new int[s];
  top = -1;
}

Stack :: ~Stack() {
  delete[] a;
}

void Stack :: push(int num) {
  if(isFull()) {
    cout << "Stack is full!";
    return;
  }
  a[++top] = num;
  return;
}

int Stack :: pop() {
  if(isEmpty()) return INT_MIN;
  return a[top--];
}

bool Stack :: isEmpty() {
  if(top == -1) return true;
  return false;
}

bool Stack :: isFull() {
  if(top == size - 1) return true;
  return false;
}

