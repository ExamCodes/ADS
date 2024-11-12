#include <iostream>
using namespace std;


struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};


int height(Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}


Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}


Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    
    x->right = y;
    y->left = T2;

    
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    
    return x;
}


Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    
    y->left = x;
    x->right = T2;

    
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    
    return y;
}

int getBalance(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}


Node* insert(Node* node, int key) {
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    
    node->height = 1 + max(height(node->left), height(node->right));

    
    int balance = getBalance(node);

    
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}


Node* deleteNode(Node* root, int key, bool& found) {
    if (root == NULL) {
        found = false;
        return root;
    }

    if (key < root->key)
        root->left = deleteNode(root->left, key, found);
    else if (key > root->key)
        root->right = deleteNode(root->right, key, found);
    else {
        found = true;
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            delete temp;
        }
        else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key, found);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}


int main() {
    Node* root = NULL;
    int choice, key;
    bool found;

    while (true) {
        cout << "\n1. Insert Node\n2. Delete Node\n3. Display Tree (In-Order)\n4. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter key to insert: ";
            cin >> key;
            root = insert(root, key);
            cout << "Tree after insertion: ";
            inOrder(root);
            cout << endl;
            break;
        case 2:
            cout << "Enter key to delete: ";
            cin >> key;
            found = true;
            root = deleteNode(root, key, found);
            if (found)
                cout << "Tree after deletion: ";
            else
                cout << "Element not found." << endl;
            inOrder(root);
            cout << endl;
            break;
        case 3:
            cout << "In-order traversal: ";
            inOrder(root);
            cout << endl;
            break;
        case 4:
            exit(0);
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}

