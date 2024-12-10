#include <bits/stdc++.h>
using namespace std;

// An AVL tree node 
class node 
{ 
    public:
    int key; 
    node *left, *right; 
}; 

node* newNode(int key) 
{ 
    node* Node = new node();
    Node->key = key; 
    Node->left = Node->right = NULL; 
    return (Node); 
} 

node *rightRotate(node *x) 
{ 
    node *y = x->left; 
    x->left = y->right; 
    y->right = x; 
    return y; 
} 

node *leftRotate(node *x) 
{ 
    node *y = x->right; 
    x->right = y->left; 
    y->left = x; 
    return y; 
} 

node *splay(node *root, int key) 
{ 
    if (root == NULL || root->key == key) 
        return root; 

    if (root->key > key) 
    { 
        if (root->left == NULL) return root; 
        if (root->left->key > key) 
        { 
            root->left->left = splay(root->left->left, key); 
            root = rightRotate(root); 
        } 
        else if (root->left->key < key) 
        { 
            root->left->right = splay(root->left->right, key); 
            if (root->left->right != NULL) 
                root->left = leftRotate(root->left); 
        } 
        return (root->left == NULL)? root: rightRotate(root); 
    } 
    else 
    { 
        if (root->right == NULL) return root; 
        if (root->right->key > key) 
        { 
            root->right->left = splay(root->right->left, key); 
            if (root->right->left != NULL) 
                root->right = rightRotate(root->right); 
        } 
        else if (root->right->key < key) 
        { 
            root->right->right = splay(root->right->right, key); 
            root = leftRotate(root); 
        } 
        return (root->right == NULL)? root: leftRotate(root); 
    } 
} 

node *insert(node *root, int k) 
{ 
    if (root == NULL) return newNode(k); 
    root = splay(root, k); 
    if (root->key == k) return root; 

    node *newnode = newNode(k); 
    if (root->key > k) 
    { 
        newnode->right = root; 
        newnode->left = root->left; 
        root->left = NULL; 
    } 
    else
    { 
        newnode->left = root; 
        newnode->right = root->right; 
        root->right = NULL; 
    } 
    return newnode; 
} 

node* deleteNode(node* root, int key) 
{ 
    if (root == NULL) return NULL; 
    root = splay(root, key); 
    if (root->key != key) return root; 

    if (root->left == NULL) 
    { 
        node* temp = root->right; 
        delete root; 
        return temp; 
    } 
    else 
    { 
        node* temp = splay(root->left, key); 
        temp->right = root->right; 
        delete root; 
        return temp; 
    } 
} 

void preOrder(node *root) 
{ 
    if (root != NULL) 
    { 
        cout << root->key << " "; 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
} 

node* search(node* root, int key) 
{
    root = splay(root, key);
    if (root != NULL && root->key == key)
        cout << "Key found: " << key << endl;
    else
        cout << "Key not found." << endl;
    return root;
}

int main() 
{ 
    node* root = NULL; 
    int choice, key; 

    while (true) 
    { 
        cout << "\nSplay Tree Menu:\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Delete\n";
        cout << "4. Display Preorder\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        { 
            case 1: 
                cout << "Enter the key to insert: "; 
                cin >> key; 
                root = insert(root, key); 
                cout << "Key inserted.\n"; 
                break;

            case 2: 
                cout << "Enter the key to search: "; 
                cin >> key; 
                root = search(root, key); 
                break;

            case 3: 
                cout << "Enter the key to delete: "; 
                cin >> key; 
                root = deleteNode(root, key); 
                cout << "Key deleted (if it existed).\n"; 
                break;

            case 4: 
                cout << "Preorder traversal: "; 
                preOrder(root); 
                cout << endl; 
                break;

            case 5: 
                cout << "Exiting program.\n"; 
                return 0;

            default: 
                cout << "Invalid choice. Try again.\n"; 
        } 
    } 
} 
