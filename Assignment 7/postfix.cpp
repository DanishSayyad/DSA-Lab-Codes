#include <iostream>
#include <string>
using namespace std;

enum TYPE {NUM, OP, BRAC_OPEN, BRAC_CLOSE};

union part {
    int val;
    char op;
};

struct term {
    short type;
    part value;
    term *next;
};

class Stack {
    private:
        term *head;

    public:
        Stack();
        ~Stack();
        void push(short t, part v);
        term pop();
        term peek();
        bool isEmpty();
        void print();
        void inToPost();
        int solve();
    
    friend void fillData(Stack&, const string&);
};

string removeSpaces(const string &);
void fillData(Stack &, const string &);
int precedence(char);

int main() {
    string expression;
    cout << "Enter the infix expression: ";
    getline(cin, expression);

    Stack exp;

    expression = removeSpaces(expression);
    fillData(exp, expression);

    exp.inToPost();
    cout << "The postfix expression is: ";
    exp.print();

    cout << "Answer: " << exp.solve() << endl;

    return 0;
}

Stack::Stack() {
    head = NULL;
}

void Stack::push(short t, part v) {
    term *node = new term;
    node->type = t;
    node->value = v;
    node->next = head;
    head = node;
}

term Stack::pop() {
    if (!head) {
        cerr << "Stack is empty!" << endl;
        exit(1);
    }
    term temp = *head;
    term *old = head;
    head = head->next;
    delete old;
    return temp;
}

term Stack::peek() {
    if (!head) {
        cerr << "Stack is empty!" << endl;
        exit(1);
    }
    return *head;
}

bool Stack::isEmpty() {
    return head == NULL;
}

void fillData(Stack &st, const string &expr) {
    for (int i = expr.size() - 1; i >= 0; ) {
        char c = expr[i];
        part temp;

        if (isdigit(c)) {
            int num = 0, place = 1;
            while (i >= 0 && isdigit(expr[i])) {
                num += (expr[i] - '0') * place;
                place *= 10;
                i--;
            }
            temp.val = num;
            st.push(NUM, temp);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            temp.op = c;
            st.push(OP, temp);
            i--;
        }
        else if (c == '(') {
            temp.op = c;
            st.push(BRAC_OPEN, temp);
            i--;
        }
        else if (c == ')') {
            temp.op = c;
            st.push(BRAC_CLOSE, temp);
            i--;
        }
        else {
            i--;
        }
    }
}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

void Stack::inToPost() {
    Stack temp;
    Stack output;

    while (!isEmpty()) {
        term t = pop();

        if (t.type == NUM) {
            output.push(NUM, t.value);
        }
        else if (t.type == OP) {
            while (!temp.isEmpty() && temp.peek().type == OP &&
                   precedence(temp.peek().value.op) >= precedence(t.value.op)) {
                term op = temp.pop();
                output.push(op.type, op.value);
            }
            temp.push(OP, t.value);
        }
        else if (t.type == BRAC_OPEN) {
            temp.push(BRAC_OPEN, t.value);
        }
        else if (t.type == BRAC_CLOSE) {
            while (!temp.isEmpty() && temp.peek().type != BRAC_OPEN) {
                term op = temp.pop();
                output.push(op.type, op.value);
            }
            if (!temp.isEmpty() && temp.peek().type == BRAC_OPEN) {
                temp.pop();
            }
        }
    }

    while (!temp.isEmpty()) {
        term op = temp.pop();
        output.push(op.type, op.value);
    }

    // Store postfix
    while (!isEmpty()) pop();
    while(!output.isEmpty()) {
        term t = output.pop();
        push(t.type, t.value);
    }
}

int Stack :: solve() {
    int answer;
    Stack copy, temp;

    // Lifting the stack
    while(!isEmpty()) {
        term t = pop();
        temp.push(t.type, t.value);
    }
    
    // Making two stacks when putting down
    while(!temp.isEmpty()) {
        term t = temp.pop();
        copy.push(t. type, t.value);
        push(t. type, t.value);
    }

    Stack numbers;
    while(!copy.isEmpty()) {
        term t = copy.pop();
        if(t.type == NUM) {
            numbers.push(t.type, t.value);
        }
        else {
            if(numbers.isEmpty()) {
                cout << "Evluation error!\nExit code: ";
                return -1;
            }
            int a = numbers.pop().value.val, b = numbers.pop().value.val;
            term v;
            switch(t.value.op) {
                case '+':
                    v.value.val = a + b;
                    break;
                case '-':
                    v.value.val = b - a;
                    break;
                case '*':
                    v.value.val = a * b;
                    break;
                case '/':
                    v.value.val = b / a;
                    break;
            }
            numbers.push(NUM, v.value);
        }
    }

    return numbers.pop().value.val;
}

void Stack::print() {
    Stack temp;
    while(!isEmpty()) {
        term t = pop();
        if(t.type == NUM) {
            cout << t.value.val << " ";
        }
        else
            cout << t.value.op << " ";
        temp.push(t.type, t.value);
    }
    cout << endl;

    while(!temp.isEmpty()) {
        term t = temp.pop();
        push(t.type, t.value);
    }
}

string removeSpaces(const string &s) {
    string result;
    for (char c : s) {
        if (c != ' ') result += c;
    }
    return result;
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}
