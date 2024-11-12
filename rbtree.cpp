#include <iostream>
using namespace std;
enum Color { RED, BLACK };

struct RBTreeNode {
    int data;
    Color color;
    RBTreeNode *left, *right, *parent;
};

struct RBTree {
    RBTreeNode *root;
    RBTreeNode *NIL;
};

RBTreeNode* createNode(int data, Color color, RBTreeNode *NIL) {
    RBTreeNode *newNode = new RBTreeNode;
    newNode->data = data;
    newNode->color = color;
    newNode->left = NIL;
    newNode->right = NIL;
    newNode->parent = NIL;
    return newNode;
}


void leftRotate(RBTree *tree, RBTreeNode *x) {
    RBTreeNode *y = x->right;
    x->right = y->left;
    if (y->left != tree->NIL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == tree->NIL)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}


void rightRotate(RBTree *tree, RBTreeNode *y) {
    RBTreeNode *x = y->left;
    y->left = x->right;
    if (x->right != tree->NIL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == tree->NIL)
        tree->root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;
    x->right = y;
    y->parent = x;
}


void insertFixUp(RBTree *tree, RBTreeNode *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBTreeNode *y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        } else {
            RBTreeNode *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}
void rbInsert(RBTree *tree, int data) {
    RBTreeNode *z = createNode(data, RED, tree->NIL);
    RBTreeNode *y = tree->NIL;
    RBTreeNode *x = tree->root;

    while (x != tree->NIL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == tree->NIL)
        tree->root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    z->left = tree->NIL;
    z->right = tree->NIL;
    z->color = RED;

    insertFixUp(tree, z);
}
RBTree* createRBTree() {
    RBTree *tree = new RBTree;
    tree->NIL = new RBTreeNode;
    tree->NIL->color = BLACK;
    tree->root = tree->NIL;
    return tree;
}
void inorder(RBTreeNode *node, RBTreeNode *NIL) {
    if (node != NIL) {
        inorder(node->left, NIL);
        cout << node->data << " ";
        if(node->color==1)
        cout<<"Black"<<" ";
        else
        cout<<"Red"<<" ";
        inorder(node->right, NIL);
    }
}
void preOrder(RBTreeNode *node, RBTreeNode *NIL) {
    if (node != NIL) {
    	cout << node->data << " ";
        if(node->color==1)
        cout<<"Black"<<" ";
        else
        cout<<"Red"<<" ";
        inorder(node->left, NIL);
        inorder(node->right, NIL);
    }
}
int main() {
    RBTree *tree = createRBTree();
    int n, data;

    while(true)
    {
    	cout<<"Enter the node to insert\n";
    	int val;
    	cin>>val;
    	rbInsert(tree, val);
    	cout<<"Enter 1 to continue\n";
    	int n;
    	cin>>n;
    	
    	if(n!=1)
    	break;
    	
	}

    cout << "Inorder traversal of the constructed Red-Black Tree:\n";
    inorder(tree->root, tree->NIL);
    cout << endl;
    cout << "Preorder traversal of the constructed Red-Black Tree:\n";
    inorder(tree->root, tree->NIL);
    cout << endl;

    return 0;
}

