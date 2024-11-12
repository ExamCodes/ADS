#include <iostream>
#include <climits>

struct Node {
    int data;
    Node* left;
    Node* right;
    int npl;  // Null Path Length

    Node(int val) : data(val), left(NULL), right(NULL), npl(0) {}
};

// Function to merge two leftist heaps
Node* merge(Node* h1, Node* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    // Ensure h1 has the smaller root
    if (h1->data > h2->data) {
        std::swap(h1, h2);
    }

    // Merge the right child of h1 with h2
    h1->right = merge(h1->right, h2);

    // Ensure the leftist property
    if (!h1->left || (h1->left->npl < h1->right->npl)) {
        std::swap(h1->left, h1->right);
    }

    // Update the npl (null path length)
    h1->npl = (h1->right ? h1->right->npl + 1 : 0);
    return h1;
}

// Function to insert a new value into the leftist heap
Node* insert(Node* root, int val) {
    Node* newNode = new Node(val);
    return merge(root, newNode);
}

// Function to extract the minimum value from the leftist heap
int extractMin(Node*& root) {
    if (!root) return INT_MAX;  // If heap is empty

    int minValue = root->data;
    Node* oldRoot = root;
    root = merge(root->left, root->right);
    delete oldRoot;  // Free the old root
    return minValue;
}

// Function to delete a specific value from the leftist heap
Node* deleteValue(Node* root, int val) {
    if (!root) return NULL;

    if (root->data == val) {
        // If found, extract the minimum (the root) to remove it
        Node* oldRoot = root;
        root = merge(root->left, root->right);
        delete oldRoot;
        return root;
    }

    // Recursively search in the left and right children
    root->left = deleteValue(root->left, val);
    root->right = deleteValue(root->right, val);
    return root;
}

// Function for in-order traversal to display the heap
void inOrder(Node* node) {
    if (!node) return;
    inOrder(node->left);
    std::cout << node->data << " ";
    inOrder(node->right);
}

// Function to display the heap
void display(Node* root) {
    inOrder(root);
    std::cout << std::endl;
}

int main() {
    Node* heap = NULL;
    int choice, value;

    while (true) {
        std::cout << "\nLeftist Heap Operations:\n";
        std::cout << "1. Insert\n";
        std::cout << "2. Extract Min\n";
        std::cout << "3. Display Heap\n";
        std::cout << "4. Delete Value\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter value to insert: ";
                std::cin >> value;
                heap = insert(heap, value);
                std::cout << value << " inserted into the heap.\n";
                break;

            case 2:
                value = extractMin(heap);
                if (value == INT_MAX) {
                    std::cout << "Heap is empty!\n";
                } else {
                    std::cout << "Extracted min: " << value << std::endl;
                }
                break;

            case 3:
                std::cout << "Heap elements (in-order): ";
                display(heap);
                break;

            case 4:
                std::cout << "Enter value to delete: ";
                std::cin >> value;
                heap = deleteValue(heap, value);
                std::cout << (heap ? "Value deleted from the heap.\n" : "Value not found in the heap.\n");
                break;

            case 5:
                std::cout << "Exiting...\n";
                return 0;

            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    }
}

