#include <iostream>
#include <climits>
using namespace std;

struct Frame {
    int n;
    char from, to, aux;
    int state;
};

struct node {
    Frame data;
    node *next;
    node(Frame d) {
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
    void push(Frame d) {
        node *nn = new node(d);
        nn->next = top;
        top = nn;
    }
    Frame pop() {
        if (!top) throw runtime_error("Stack underflow");
        Frame d = top->data;
        node *temp = top;
        top = top->next;
        delete temp;
        return d;
    }
    Frame peek() {
        if (!top) return {INT_MIN, 0, 0, 0, 0};
        return top->data;
    }
    bool isEmpty() {
        return top == NULL;
    }
};

void hanoiNonRecursive(int n, char from, char to, char aux) {
    Stack st;
    st.push({n, from, to, aux, 0});
    while (!st.isEmpty()) {
        Frame cur = st.pop();
        if (cur.n == 1) {
            cout << "Move disk 1 from " << cur.from << " to " << cur.to << endl;
            continue;
        }
        if (cur.state == 0) {
            cur.state = 1;
            st.push(cur);
            st.push({cur.n - 1, cur.from, cur.aux, cur.to, 0});
        } else {
            cout << "Move disk " << cur.n << " from " << cur.from << " to " << cur.to << endl;
            st.push({cur.n - 1, cur.aux, cur.to, cur.from, 0});
        }
    }
}

int main() {
    int n;
    cout << "Enter number of disks: ";
    cin >> n;
    hanoiNonRecursive(n, 'A', 'C', 'B');
    return 0;
}
