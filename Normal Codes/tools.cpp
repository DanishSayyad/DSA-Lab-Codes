#include<iostream>
using namespace std;

// ========== LINKED LIST CLASS ==========
class Node {
public:
    int data;
    Node* next;
    
    Node(int val) {
        data = val;
        next = NULL;
    }
};

class LinkedList {
private:
    Node* head;
    
public:
    LinkedList() {
        head = NULL;
    }
    
    // Add a node at the end
    void addNode(int val) {
        Node* newNode = new Node(val);
        
        if (!head) {
            head = newNode;
            return;
        }
        
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    
    // Remove a node by position (1-indexed)
    bool removeNode(int position) {
        if (!head || position < 1) {
            return false;
        }
        
        if (position == 1) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        
        Node* temp = head;
        Node* prev = NULL;
        int count = 1;
        
        while (temp && count < position) {
            prev = temp;
            temp = temp->next;
            count++;
        }
        
        if (!temp) {
            return false;
        }
        
        prev->next = temp->next;
        delete temp;
        return true;
    }
    
    // Search for a node by value
    int searchNode(int val) {
        Node* temp = head;
        int position = 1;
        
        while (temp) {
            if (temp->data == val) {
                return position;
            }
            temp = temp->next;
            position++;
        }
        
        return -1; // Not found
    }
    
    // Check if list is empty
    bool isEmpty() {
        return head == NULL;
    }
    
    // Display the list
    void display() {
        if (!head) {
            cout << "List is empty!\n";
            return;
        }
        
        Node* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
    
    // Destructor to free memory
    ~LinkedList() {
        Node* temp = head;
        while (temp) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

// ========== STACK CLASS (Dynamic) ==========
class StackNode {
public:
    int data;
    StackNode* next;
    
    StackNode(int val) {
        data = val;
        next = NULL;
    }
};

class Stack {
private:
    StackNode* top;
    
public:
    Stack() {
        top = NULL;
    }
    
    // Push an element onto the stack
    void push(int val) {
        StackNode* newNode = new StackNode(val);
        
        if (!newNode) {
            cout << "Stack overflow (memory allocation failed)!\n";
            return;
        }
        
        newNode->next = top;
        top = newNode;
    }
    
    // Pop an element from the stack and return its value
    int pop() {
        if (isEmpty()) {
            cout << "Stack underflow!\n";
            return -1;
        }
        
        StackNode* temp = top;
        int poppedValue = temp->data;
        top = top->next;
        delete temp;
        
        return poppedValue;
    }
    
    // Peek at the top element without removing it
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return -1;
        }
        
        return top->data;
    }
    
    // Check if stack is empty
    bool isEmpty() {
        return top == NULL;
    }
    
    // Display the stack
    void display() {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return;
        }
        
        StackNode* temp = top;
        cout << "Stack (top to bottom): ";
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    
    // Destructor to free memory
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

// ========== QUEUE CLASS (Dynamic) ==========
class QueueNode {
public:
    int data;
    QueueNode* next;
    
    QueueNode(int val) {
        data = val;
        next = NULL;
    }
};

class Queue {
private:
    QueueNode* front;
    QueueNode* rear;
    
public:
    Queue() {
        front = NULL;
        rear = NULL;
    }
    
    // Enqueue an element to the queue
    void enqueue(int val) {
        QueueNode* newNode = new QueueNode(val);
        
        if (!newNode) {
            cout << "Queue overflow (memory allocation failed)!\n";
            return;
        }
        
        if (!rear) {
            front = rear = newNode;
            return;
        }
        
        rear->next = newNode;
        rear = newNode;
    }
    
    // Dequeue an element from the queue and return its value
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue underflow!\n";
            return -1;
        }
        
        QueueNode* temp = front;
        int dequeuedValue = temp->data;
        front = front->next;
        
        if (!front) {
            rear = NULL;
        }
        
        delete temp;
        return dequeuedValue;
    }
    
    // Peek at the front element without removing it
    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return -1;
        }
        
        return front->data;
    }
    
    // Check if queue is empty
    bool isEmpty() {
        return front == NULL;
    }
    
    // Display the queue
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return;
        }
        
        QueueNode* temp = front;
        cout << "Queue (front to rear): ";
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    
    // Destructor to free memory
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};












// ========== HASH TABLE WITH LINEAR PROBING ==========
class HashTableLinear {
private:
    int* table;
    bool* occupied;
    int size;
    
    // Hash function (to be implemented based on requirements)
    int hashFunction(int key) {
        // Leave empty for now - can be implemented as needed
        return key % size;
    }
    
public:
    HashTableLinear(int tableSize = 10) {
        size = tableSize;
        table = new int[size];
        occupied = new bool[size];
        
        for (int i = 0; i < size; i++) {
            occupied[i] = false;
        }
    }
    
    // Insert a key using linear probing
    bool insert(int key) {
        int index = hashFunction(key);
        int originalIndex = index;
        
        // Linear probing
        while (occupied[index]) {
            if (table[index] == key) {
                cout << "Key " << key << " already exists!\n";
                return false;
            }
            index = (index + 1) % size;
            
            // Table is full
            if (index == originalIndex) {
                cout << "Hash table is full!\n";
                return false;
            }
        }
        
        table[index] = key;
        occupied[index] = true;
        return true;
    }
    
    // Search for a key
    bool search(int key) {
        int index = hashFunction(key);
        int originalIndex = index;
        
        while (occupied[index]) {
            if (table[index] == key) {
                cout << "Key " << key << " found at index " << index << endl;
                return true;
            }
            index = (index + 1) % size;
            
            if (index == originalIndex) {
                break;
            }
        }
        
        cout << "Key " << key << " not found!\n";
        return false;
    }
    
    // Remove a key
    bool remove(int key) {
        int index = hashFunction(key);
        int originalIndex = index;
        
        while (occupied[index]) {
            if (table[index] == key) {
                occupied[index] = false;
                cout << "Key " << key << " removed successfully!\n";
                return true;
            }
            index = (index + 1) % size;
            
            if (index == originalIndex) {
                break;
            }
        }
        
        cout << "Key " << key << " not found!\n";
        return false;
    }
    
    // Display the hash table
    void display() {
        cout << "Hash Table (Linear Probing):\n";
        for (int i = 0; i < size; i++) {
            if (occupied[i]) {
                cout << "Index " << i << ": " << table[i] << endl;
            } else {
                cout << "Index " << i << ": Empty\n";
            }
        }
    }
    
    // Destructor
    ~HashTableLinear() {
        delete[] table;
        delete[] occupied;
    }
};

// ========== HASH TABLE WITH CHAINING ==========
class HashTableChaining {
private:
    LinkedList* table;
    int size;
    
    // Hash function (to be implemented based on requirements)
    int hashFunction(int key) {
        // Leave empty for now - can be implemented as needed
        return key % size;
    }
    
public:
    HashTableChaining(int tableSize = 10) {
        size = tableSize;
        table = new LinkedList[size];
    }
    
    // Insert a key using chaining
    bool insert(int key) {
        int index = hashFunction(key);
        
        // Check if key already exists in the chain
        if (table[index].searchNode(key) != -1) {
            cout << "Key " << key << " already exists!\n";
            return false;
        }
        
        table[index].addNode(key);
        return true;
    }
    
    // Search for a key
    bool search(int key) {
        int index = hashFunction(key);
        
        int position = table[index].searchNode(key);
        if (position != -1) {
            cout << "Key " << key << " found at index " << index << " (chain position " << position << ")\n";
            return true;
        }
        
        cout << "Key " << key << " not found!\n";
        return false;
    }
    
    // Remove a key
    bool remove(int key) {
        int index = hashFunction(key);
        
        int position = table[index].searchNode(key);
        if (position != -1) {
            table[index].removeNode(position);
            cout << "Key " << key << " removed successfully!\n";
            return true;
        }
        
        cout << "Key " << key << " not found!\n";
        return false;
    }
    
    // Display the hash table
    void display() {
        cout << "Hash Table (Chaining):\n";
        for (int i = 0; i < size; i++) {
            cout << "Index " << i << ": ";
            if (table[i].isEmpty()) {
                cout << "Empty\n";
            } else {
                table[i].display();
            }
        }
    }
    
    // Destructor
    ~HashTableChaining() {
        delete[] table;
    }
};
