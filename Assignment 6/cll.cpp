#include <iostream>

using namespace std;

struct node {
    int data;
    node *next, *prev;
};

class CLL {
    private:
        node *head, *tail;
    public:
        CLL();
        void addNode(int);
        void display();
        void deleteNode(int);
        void searchNode(int);
};

int main() {
    CLL c1;
    c1.display();
    c1.addNode(10);
    c1.addNode(20);
    c1.addNode(40);
    c1.addNode(50);
    c1.display();
    c1.deleteNode(20);
    c1.display();
    c1.searchNode(40);
    c1.searchNode(100);
    return 0;
}

CLL::CLL() {
    head = NULL;
    tail = NULL;
}

void CLL :: addNode(int val) {
    node *newNode = new node;
    if(!newNode) {
        cout << "Memory allocation failed" << endl;
        return;
    }
    newNode->data = val;
    if (!head) {
        head = newNode;
        tail = newNode;
        newNode->next = head;
        newNode->prev = tail;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        tail->next = head;
        head->prev = tail;
    }
    return;
}

void CLL :: display() {
    if (!head) {
        cout << "List is empty!\n";
        return;
    }
    node *ptr = head;
    if(!ptr) return;
    do {
        cout << ptr->data << " ";
        ptr = ptr->next;
    } while(ptr != head);
    cout << endl;
    return;
}

void CLL :: deleteNode(int val) {
    if(!head) {
        cout << "List is empty!\n";
        return;
    }
    node *ptr = head;
    if(!ptr) return;
    bool found = true;
    do {
        if(ptr->data == val) {
            // delete procedure
            if(ptr == head && ptr == tail) {
                head = NULL;
                tail = NULL;
            }
            else if(ptr == head) {
                head = head->next;
                tail->next = head;
                head->prev = tail;
            }
            else if(ptr == tail) {
                tail = tail->prev;
                tail->next = head;
                head->prev = tail;
            }
            else {
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
            }
            delete ptr;
            found = true;
            break;
        }
        ptr = ptr->next;
    } while(ptr != head);
    if(!found) {
        cout << "Element not found!";
    }
    return;
}

void CLL :: searchNode(int val) {
    if(!head) {
        cout << "List is empty!\n";
        return;
    }
    node *ptr = head;
    if(!ptr) return;
    bool found = false;
    do {
        if(ptr->data == val) {
            found = true;
            break;
        }
        ptr = ptr->next;
    } while(ptr != head);
    if(found) {
        cout << "Element found!\n";
    }
    else {
        cout << "Element not found!\n";
    }
    return;
}
