#include <iostream>
#include <cstdlib>  // for rand()
#include <ctime>    // for time()

using namespace std;

const int TABLE_SIZE = 20;

class HashTable {
private:
    int table[TABLE_SIZE];

public:
    HashTable() {
        // Initialize all slots as empty (-1 indicates empty)
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = -1;
    }

    // Hash function
    int hashFunc(int key) {
        return key % TABLE_SIZE;
    }

    // Insert with linear probing
    void insert(int key) {
        int index = hashFunc(key);
        int originalIndex = index;
        int i = 0;

        // Find an empty slot
        while (table[index] != -1) {
            index = (originalIndex + ++i) % TABLE_SIZE; // linear probe
            if (i == TABLE_SIZE) {
                cout << "Hash table full. Cannot insert " << key << endl;
                return;
            }
        }
        table[index] = key;
    }

    // Search using same probing logic
    int search(int key) {
        int index = hashFunc(key);
        int originalIndex = index;
        int i = 0;

        while (table[index] != -1) {
            if (table[index] == key)
                return index;  // Found
            index = (originalIndex + ++i) % TABLE_SIZE;
            if (i == TABLE_SIZE)
                break;
        }
        return -1; // Not found
    }

    // Display hash table
    void display() {
        cout << "\nHash Table:\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != -1)
                cout << i << " --> " << table[i] << endl;
            else
                cout << i << " --> [EMPTY]\n";
        }
    }
};

int main() {
    srand(time(0));
    HashTable ht;

    // Insert 10 random numbers
    for (int i = 0; i < 10; i++) {
        int num = rand() % 100;  // Random integer
        cout << "Inserting " << num << endl;
        ht.insert(num);
    }

    ht.display();

    // Search demo
    int key;
    cout << "\nEnter number to search: ";
    cin >> key;
    int index = ht.search(key);

    if (index != -1)
        cout << key << " found at index " << index << endl;
    else
        cout << key << " not found in table." << endl;

    return 0;
}
