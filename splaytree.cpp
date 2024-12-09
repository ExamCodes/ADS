#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

class SplayTree {
private:
    Node* root;

    Node* newNode(int key) {
        Node* node = new Node();
        node->key = key;
        node->left = node->right = NULL;
        return node;
    }

    Node* rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    Node* splay(Node* root, int key) {
        if (!root || root->key == key)
            return root;

        if (key < root->key) {
            if (!root->left) return root;

            if (key < root->left->key) {
                root->left->left = splay(root->left->left, key);
                root = rightRotate(root);
            } else if (key > root->left->key) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right)
                    root->left = leftRotate(root->left);
            }
            return root->left ? rightRotate(root) : root;
        } else {
            if (!root->right) return root;

            if (key > root->right->key) {
                root->right->right = splay(root->right->right, key);
                root = leftRotate(root);
            } else if (key < root->right->key) {
                root->right->left = splay(root->right->left, key);
                if (root->right->left)
                    root->right = rightRotate(root->right);
            }
            return root->right ? leftRotate(root) : root;
        }
    }

    Node* deleteNode(Node* root, int key) {
        if (!root) return NULL;

        root = splay(root, key);

        if (root->key != key)
            return root;

        if (!root->left) {
            Node* temp = root;
            root = root->right;
            delete temp;
        } else {
            Node* temp = root;
            root = splay(root->left, key);
            root->right = temp->right;
            delete temp;
        }
        return root;
    }

    void preorderTraversal(Node* root) {
        if (root) {
            cout << root->key << " ";
            preorderTraversal(root->left);
            preorderTraversal(root->right);
        }
    }

public:
    SplayTree() : root(NULL) {}

    void insert(int key) {
        if (!root) {
            root = newNode(key);
            cout << "Key " << key << " inserted as the root.\n";
            return;
        }
        root = splay(root, key);
        if (root->key == key) {
            cout << "Key " << key << " already exists. No insertion.\n";
            return;
        }

        Node* newNodePtr = newNode(key);

        if (key < root->key) {
            newNodePtr->right = root;
            newNodePtr->left = root->left;
            root->left = NULL;
        } else {
            newNodePtr->left = root;
            newNodePtr->right = root->right;
            root->right = NULL;
        }
        root = newNodePtr;
        cout << "Key " << key << " inserted successfully.\n";
    }

    void search(int key) {
        root = splay(root, key);
        if (root && root->key == key)
            cout << "Key " << key << " found in the tree.\n";
        else
            cout << "Key " << key << " not found in the tree.\n";
    }

    void remove(int key) {
        root = deleteNode(root, key);
        cout << "Key " << key << " removed (if it existed).\n";
    }

    void display() {
        if (!root) {
            cout << "The tree is empty.\n";
            return;
        }
        cout << "Preorder traversal: ";
        preorderTraversal(root);
        cout << endl;
    }
};

int main() {
    SplayTree tree;
    int choice, key;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Delete\n";
        cout << "4. Display (Preorder Traversal)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the key to insert: ";
            cin >> key;
            tree.insert(key);
            break;
        case 2:
            cout << "Enter the key to search: ";
            cin >> key;
            tree.search(key);
            break;
        case 3:
            cout << "Enter the key to delete: ";
            cin >> key;
            tree.remove(key);
            break;
        case 4:
            tree.display();
            break;
        case 5:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

