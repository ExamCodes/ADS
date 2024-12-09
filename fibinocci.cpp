#include <bits/stdc++.h>
using namespace std;
class Node {
public:
    int key;
    int degree;
    bool mark;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;

    Node(int val) : key(val), degree(0), mark(false), parent(NULL), child(NULL) {
        left = right = this;
    }
};

class FibonacciHeap {
private:
    Node* min;
    int numNodes;

    void link(Node* y, Node* x) {
        
        y->left->right = y->right;
        y->right->left = y->left;

        y->parent = x;

        if (x->child == NULL) {
            x->child = y;
            y->right = y->left = y;
        } else {
            y->left = x->child;
            y->right = x->child->right;
            x->child->right->left = y;
            x->child->right = y;
        }

        x->degree++;
        y->mark = false;
    }

    void consolidate() {
        int maxDegree = log2(numNodes) + 1;
        std::vector<Node*> A(maxDegree + 1, NULL);

        
        Node* start = min;
        Node* w = min;
        do {
            Node* x = w;
            int d = x->degree;
            while (A[d] != NULL) {
                Node* y = A[d];
                if (x->key > y->key) std::swap(x, y);
                link(y, x);
                A[d] = NULL;
                d++;
            }
            A[d] = x;
            w = w->right;
        } while (w != start);

        min = NULL;
        for (size_t i = 0; i < A.size(); ++i) {
		    Node* root = A[i];
		    if (root != NULL) {
		        if (min == NULL || root->key < min->key) min = root;
		    }
		}
    }

public:
    FibonacciHeap() : min(NULL), numNodes(0) {}

    Node* insert(int key) {
        Node* newNode = new Node(key);
        if (min == NULL) {
            min = newNode;
        } else {
            newNode->left = min;
            newNode->right = min->right;
            min->right->left = newNode;
            min->right = newNode;
            if (key < min->key) {
                min = newNode;
            }
        }
        numNodes++;
        return newNode;
    }

    int getMin() {
        if (min == NULL) throw std::runtime_error("Heap is empty");
        return min->key;
    }

    int extractMin() {
        if (min == NULL) throw std::runtime_error("Heap is empty");

        Node* z = min;
        if (z != NULL) {
            if (z->child != NULL) {
                Node* child = z->child;
                do {
                    child->parent = NULL;
                    child = child->right;
                } while (child != z->child);
            }

            z->left->right = z->right;
            z->right->left = z->left;
            if (z == z->right) {
                min = NULL;
            } else {
                min = z->right;
                consolidate();
            }
            numNodes--;
        }
        int minValue = z->key;
        delete z;
        return minValue;
    }

    void decreaseKey(Node* x, int newKey) {
        if (newKey > x->key) throw std::invalid_argument("New key is greater than current key");

        x->key = newKey;
        Node* y = x->parent;

        if (y != NULL && x->key < y->key) {
            cut(x, y);
            cascadingCut(y);
        }
        if (x->key < min->key) {
            min = x;
        }
    }

    void cut(Node* x, Node* y) {
        if (y->child == x) {
            if (x->right != x) {
                y->child = x->right;
            } else {
                y->child = NULL;
            }
        }
        y->degree--;

        x->left->right = x->right;
        x->right->left = x->left;

        x->parent = NULL;
        x->mark = false;

        x->right = min;
        x->left = min->left;
        min->left->right = x;
        min->left = x;
    }

    void cascadingCut(Node* y) {
        Node* z = y->parent;
        if (z != NULL) {
            if (!y->mark) {
                y->mark = true;
            } else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }

    void deleteNode(Node* x) {
        decreaseKey(x, INT_MIN);
        extractMin();
    }
    void display(Node* node, int depth = 0) {
    if (node == NULL) return;

    Node* start = node;
    do {
        
        std::cout << std::string(depth * 4, ' ') << "Node: " << node->key << ", Degree: " << node->degree << ", Mark: " << (node->mark ? "True" : "False") << std::endl;

        
        if (node->child != NULL) {
            std::cout << std::string((depth + 1) * 4, ' ') << "Children: " << std::endl;
            display(node->child, depth + 1);
        }

        node = node->right;
    } while (node != start); 
}

void displayHeap() {
    if (min == NULL) {
        std::cout << "The Fibonacci heap is empty.\n";
        return;
    }
    std::cout << "Fibonacci Heap Structure:\n";
    display(min);
}

};

int main() {
    FibonacciHeap heap;
    int choice, key, newKey;
    Node* nodes[1000] = { NULL }; 
    int nodeCount = 0;

    while (true) {
        std::cout << "\nFibonacci Heap Menu:\n";
        std::cout << "1. Insert Key\n";
        std::cout << "2. Find Minimum\n";
        std::cout << "3. Extract Minimum\n";
        std::cout << "4. Decrease Key\n";
        std::cout << "5. Delete Node\n";
        std::cout << "6. Display Heap\n"; 
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the key to insert: ";
                std::cin >> key;
                nodes[nodeCount++] = heap.insert(key);
                std::cout << "Inserted key " << key << " into the heap.\n";
                break;

            case 2:
                try {
                    std::cout << "Minimum key is: " << heap.getMin() << std::endl;
                } catch (const std::runtime_error& e) {
                    std::cout << e.what() << std::endl;
                }
                break;

            case 3:
                try {
                    std::cout << "Extracted minimum key: " << heap.extractMin() << std::endl;
                } catch (const std::runtime_error& e) {
                    std::cout << e.what() << std::endl;
                }
                break;

            case 4:
                std::cout << "Enter the index of the node to decrease (0 to " << nodeCount - 1 << "): ";
                std::cin >> key;
                if (key < 0 || key >= nodeCount || nodes[key] == NULL) {
                    std::cout << "Invalid node index.\n";
                    break;
                }
                std::cout << "Enter the new key value (smaller than current): ";
                std::cin >> newKey;
                try {
                    heap.decreaseKey(nodes[key], newKey);
                    std::cout << "Decreased key to " << newKey << ".\n";
                } catch (const std::invalid_argument& e) {
                    std::cout << e.what() << std::endl;
                }
                break;

            case 5:
                std::cout << "Enter the index of the node to delete (0 to " << nodeCount - 1 << "): ";
                std::cin >> key;
                if (key < 0 || key >= nodeCount || nodes[key] == NULL) {
                    std::cout << "Invalid node index.\n";
                    break;
                }
                heap.deleteNode(nodes[key]);
                nodes[key] = NULL; 
                std::cout << "Deleted node.\n";
                break;

            case 6:
                heap.displayHeap(); 
                break;

            case 7:
                std::cout << "Exiting program.\n";
                return 0;

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
    return 0;
}

