#include <bits/stdc++.h>
using namespace std;

// Structure for a tree node
struct TreeNode {
    int key;
    TreeNode *left, *right;
    TreeNode(int k) : key(k), left(NULL), right(NULL) {}
};

// Function to get the sum of array elements freq[i] to freq[j]
int sum(int freq[], int i, int j) {
    int s = 0;
    for (int k = i; k <= j; k++)
        s += freq[k];
    return s;
}

// Function to calculate the optimal cost and construct the tree
int optCost(int freq[], int i, int j, vector<vector<int > >& root) {
    if (j < i) return 0; // No elements in this subarray
    if (j == i) return freq[i]; // One element in this subarray

    int fsum = sum(freq, i, j);
    int minCost = INT_MAX;

    for (int r = i; r <= j; ++r) {
        int cost = optCost(freq, i, r - 1, root) + optCost(freq, r + 1, j, root);
        if (cost < minCost) {
            minCost = cost;
            root[i][j] = r; // Store the root index
        }
    }

    return minCost + fsum;
}

// Function to build the optimal BST from the root indices
TreeNode* buildOBST(int keys[], vector<vector<int > >& root, int i, int j) {
    if (i > j) return NULL; // Base case

    int r = root[i][j]; // Get the root for this subtree
    TreeNode* node = new TreeNode(keys[r]); // Create the tree node

    // Recur for left and right subtrees
    node->left = buildOBST(keys, root, i, r - 1);
    node->right = buildOBST(keys, root, r + 1, j);

    return node; // Return the created node
}

// Function to print the tree in preorder format
void printTree(TreeNode* node) {
    if (node == NULL) return; // Base case
    cout << node->key << " "; // Print the current node
    printTree(node->left); // Recur for left subtree
    printTree(node->right); // Recur for right subtree
}

// The main function that calculates the minimum cost of a Binary Search Tree
int optimalSearchTree(int keys[], int freq[], int n) {
    vector<vector<int > > root(n, vector<int>(n, -1)); // Root table
    int cost = optCost(freq, 0, n - 1, root); // Calculate cost
    TreeNode* rootNode = buildOBST(keys, root, 0, n - 1); // Build the tree

    cout << "Cost of Optimal BST is " << cost << endl;
    cout << "Preorder Traversal of the Optimal BST: ";
    printTree(rootNode); // Print the tree structure

    return cost;
}

// Driver Code
int main() {
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;

    int keys[n], freq[n];
    cout << "Enter the keys: ";
    for (int i = 0; i < n; i++) {
        cin >> keys[i];
    }

    cout << "Enter the frequencies for each key: ";
    for (int i = 0; i < n; i++) {
        cin >> freq[i];
    }

    optimalSearchTree(keys, freq, n); // Calculate and display OBST

    return 0;
}

