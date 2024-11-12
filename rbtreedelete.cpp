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

// Transplant function used in deletion
void rbTransplant(RBTree *tree, RBTreeNode *u, RBTreeNode *v) {
    if (u->parent == tree->NIL) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

RBTreeNode* minimum(RBTreeNode *node, RBTreeNode *NIL) {
    while (node->left != NIL) {
        node = node->left;
    }
    return node;
}

void deleteFixUp(RBTree *tree, RBTreeNode *x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            RBTreeNode *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            RBTreeNode *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

void rbDelete(RBTree *tree, RBTreeNode *z) {
    RBTreeNode *y = z;
    RBTreeNode *x;
    Color yOriginalColor = y->color;

    if (z->left == tree->NIL) {
        x = z->right;
        rbTransplant(tree, z, z->right);
    } else if (z->right == tree->NIL) {
        x = z->left;
        rbTransplant(tree, z, z->left);
    } else {
        y = minimum(z->right, tree->NIL);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == BLACK) {
        deleteFixUp(tree, x);
    }
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
        if (node->color == BLACK)
            cout << "Black ";
        else
            cout << "Red ";
        inorder(node->right, NIL);
    }
}

int main() {
    RBTree *tree = createRBTree();
    int n, data;

    while (true) {
        cout << "Enter the node to insert\n";
        int val;
        cin >> val;
        rbInsert(tree, val);
        cout << "Enter 1 if you want to continue inserting\n";
        int choice;
        cin >> choice;
        if (choice != 1)
            break;
    }

    cout << "Inorder traversal of the constructed Red-Black Tree:\n";
    inorder(tree->root, tree->NIL);
    cout << endl;


    while (true) {
        cout << "Enter the node to delete\n";
        int val;
        cin >> val;

        RBTreeNode *nodeToDelete = tree->root;
        while (nodeToDelete != tree->NIL && nodeToDelete->data != val) {
            if (val < nodeToDelete->data)
                nodeToDelete = nodeToDelete->left;
            else
                nodeToDelete = nodeToDelete->right;
        }

        if (nodeToDelete != tree->NIL) {
            rbDelete(tree, nodeToDelete);
            cout << "Node " << val << " deleted\n";
        } else {
            cout << "Node not found\n";
        }

        cout << "Enter 1 if you want to continue deleting\n";
        int choice;
        cin >> choice;
        if (choice != 1)
            break;
    }

    cout << "Inorder traversal after deletions:\n";
    inorder(tree->root, tree->NIL);
    cout << endl;

    return 0;
}

