#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <limits>

using namespace std;


const int MAX_LEVEL = 16;


struct Node {
    int value;
    vector<Node*> forward;

    Node(int val, int level) : value(val), forward(level + 1, NULL) {}
};


class SkipList {
    int level;    
    Node *header;  
public:
    SkipList() {
        level = 0;
        header = new Node(-1, MAX_LEVEL); 
    }

    
    int randomLevel() {
        int lvl = 0;
        while (lvl < MAX_LEVEL && ((rand() % 2) == 1)) {
            lvl++;
        }
        return lvl;
    }

    
    bool search(int value) {
        Node *current = header;
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value) {
                current = current->forward[i];
            }
        }
        current = current->forward[0];
        return current && current->value == value;
    }

    
    void insert(int value) {
        vector<Node*> update(MAX_LEVEL + 1);
        Node *current = header;

        
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        
        int newLevel = randomLevel();
        if (newLevel > level) {
            for (int i = level + 1; i <= newLevel; i++) {
                update[i] = header;
            }
            level = newLevel;
        }

        Node* newNode = new Node(value, newLevel);
        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    
    void erase(int value) {
        vector<Node*> update(MAX_LEVEL + 1);
        Node *current = header;

        
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        
        current = current->forward[0];
        if (current && current->value == value) {
            for (int i = 0; i <= level; i++) {
                if (update[i]->forward[i] != current) break;
                update[i]->forward[i] = current->forward[i];
            }
            delete current;

            
            while (level > 0 && header->forward[level] == NULL) {
                level--;
            }
        }
    }

    // Display the skip list
    void display() {
        for (int i = 0; i <= level; i++) {
            Node *node = header->forward[i];
            cout << "Level " << i << ": ";
            while (node) {
                cout << node->value << " ";
                node = node->forward[i];
            }
            cout << endl;
        }
    }
};

int main() {
    srand((unsigned)time(0));  // Initialize random seed

    SkipList skiplist;
    int choice, value;

    cout << "Skip List Operations:\n";
    cout << "1: Insert\n2: Search\n3: Delete\n4: Display\n0: Exit\n";

    while (true) {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                skiplist.insert(value);
                cout << "Inserted " << value << " into skip list.\n";
                break;
            case 2:
                cout << "Enter value to search: ";
                cin >> value;
                if (skiplist.search(value))
                    cout << "Found " << value << " in the skip list.\n";
                else
                    cout << value << " not found in the skip list.\n";
                break;
            case 3:
                cout << "Enter value to delete: ";
                cin >> value;
                skiplist.erase(value);
                cout << "Deleted " << value << " from the skip list.\n";
                break;
            case 4:
                cout << "Displaying skip list:\n";
                skiplist.display();
                break;
            case 0:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
