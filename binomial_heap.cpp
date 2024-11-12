#include <iostream> 

#include <climits> 

using namespace std; 

  

struct BinomialHeapNode { 

    int key; 

    int degree; 

    BinomialHeapNode* parent; 

    BinomialHeapNode* child; 

    BinomialHeapNode* sibling; 

}; 

  

BinomialHeapNode* createNode(int key) { 

    BinomialHeapNode* node = new BinomialHeapNode(); 

    node->key = key; 

    node->degree = 0; 

    node->parent = NULL; 

    node->child = NULL; 

    node->sibling = NULL; 

    return node; 

} 

  

void linkBinomialTrees(BinomialHeapNode* y, BinomialHeapNode* z) { 

    y->parent = z; 

    y->sibling = z->child; 

    z->child = y; 

    z->degree++; 

} 

  

BinomialHeapNode* mergeBinomialHeaps(BinomialHeapNode* h1, BinomialHeapNode* h2) { 

    if (!h1) return h2; 

    if (!h2) return h1; 

  

    BinomialHeapNode* head; 

    BinomialHeapNode* tail; 

  

    if (h1->degree <= h2->degree) { 

        head = h1; 

        h1 = h1->sibling; 

    } else { 

        head = h2; 

        h2 = h2->sibling; 

    } 

    tail = head; 

  

    while (h1 && h2) { 

        if (h1->degree <= h2->degree) { 

            tail->sibling = h1; 

            h1 = h1->sibling; 

        } else { 

            tail->sibling = h2; 

            h2 = h2->sibling; 

        } 

        tail = tail->sibling; 

    } 

  

    if (h1) tail->sibling = h1; 

    if (h2) tail->sibling = h2; 

  

    return head; 

} 

  

BinomialHeapNode* unionBinomialHeaps(BinomialHeapNode* h1, BinomialHeapNode* h2) { 

    BinomialHeapNode* newHead = mergeBinomialHeaps(h1, h2); 

    if (!newHead) return NULL; 

  

    BinomialHeapNode* prev = NULL; 

    BinomialHeapNode* curr = newHead; 

    BinomialHeapNode* next = curr->sibling; 

  

    while (next != NULL) { 

        if ((curr->degree != next->degree) || 

            (next->sibling != NULL && next->sibling->degree == curr->degree)) { 

            prev = curr; 

            curr = next; 

        } else { 

            if (curr->key <= next->key) { 

                curr->sibling = next->sibling; 

                linkBinomialTrees(next, curr); 

            } else { 

                if (prev == NULL) newHead = next; 

                else prev->sibling = next; 

                linkBinomialTrees(curr, next); 

                curr = next; 

            } 

        } 

        next = curr->sibling; 

    } 

    return newHead; 

} 

  

BinomialHeapNode* insert(BinomialHeapNode* heap, int key) { 

    BinomialHeapNode* node = createNode(key); 

    return unionBinomialHeaps(heap, node); 

} 

  

BinomialHeapNode* reverseList(BinomialHeapNode* node) { 

    BinomialHeapNode* prev = NULL; 

    BinomialHeapNode* current = node; 

    BinomialHeapNode* next; 

  

    while (current != NULL) { 

        next = current->sibling; 

        current->sibling = prev; 

        prev = current; 

        current = next; 

    } 

    return prev; 

} 

  

BinomialHeapNode* extractMin(BinomialHeapNode* heap) { 

    if (!heap) return NULL; 

  

    BinomialHeapNode* prevMin = NULL; 

    BinomialHeapNode* minNode = heap; 

    BinomialHeapNode* current = heap; 

    BinomialHeapNode* prev = NULL; 

  

    // Find the minimum node 

    while (current->sibling != NULL) { 

        if (current->sibling->key < minNode->key) { 

            prevMin = current; 

            minNode = current->sibling; 

        } 

        current = current->sibling; 

    } 

  

    // Remove the minimum node from the heap 

    if (prevMin != NULL) { 

        prevMin->sibling = minNode->sibling; 

    } else { 

        heap = minNode->sibling; 

    } 

  

    // Reverse the child list of the minimum node and merge with the heap 

    if (minNode->child) { 

        minNode->child = reverseList(minNode->child); 

        heap = unionBinomialHeaps(heap, minNode->child); 

    } 

  

    delete minNode; 

    return heap; 

} 

  

void decreaseKey(BinomialHeapNode* node, int newKey) { 

    if (newKey > node->key) { 

        cout << "New key is greater than current key" << endl; 

        return; 

    } 

  

    node->key = newKey; 

    BinomialHeapNode* current = node; 

    BinomialHeapNode* parent = node->parent; 

  

    while (parent != NULL && current->key < parent->key) { 

        swap(current->key, parent->key); 

        current = parent; 

        parent = parent->parent; 

    } 

} 

  

void displayHeap(BinomialHeapNode* heap) { 

    if (!heap) { 

        cout << "Heap is empty" << endl; 

        return; 

    } 

  

    while (heap != NULL) { 

        cout << "Binomial Tree, B" << heap->degree << endl; 

        cout << "Root: " << heap->key << endl; 

        displayHeap(heap->child); 

        heap = heap->sibling; 

    } 

} 

  

BinomialHeapNode* findNode(BinomialHeapNode* heap, int key) { 

    if (heap == NULL) return NULL; 

  

    if (heap->key == key) return heap; 

  

    BinomialHeapNode* child = findNode(heap->child, key); 

    if (child) return child; 

  

    return findNode(heap->sibling, key); 

} 

  

int main() { 

    BinomialHeapNode* heap = NULL; 

    int choice, key, newKey; 

  

    while (true) { 

        cout << "\nBinomial Heap Operations Menu:" << endl; 

        cout << "1. Insert an element" << endl; 

        cout << "2. Extract minimum element" << endl; 

        cout << "3. Delete an element" << endl; 

        cout << "4. Decrease a key" << endl; 

        cout << "5. Display heap" << endl; 

        cout << "6. Exit" << endl; 

        cout << "Enter your choice: "; 

        cin >> choice; 

  

    switch (choice) 

{ 

    case 1: { 

        cout << "Enter the element to insert: "; 

        cin >> key; 

        heap = insert(heap, key); 

        cout << key << " inserted." << endl; 

        break; 

    } 

  

    case 2: { 

        if (heap == NULL) { 

            cout << "Heap is empty." << endl; 

        } else { 

            heap = extractMin(heap); 

            cout << "Minimum element extracted." << endl; 

        } 

        break; 

    } 

  

    case 3: { 

        cout << "Enter the element to delete: "; 

        cin >> key; 

        BinomialHeapNode* node = findNode(heap, key); // Declare node inside this scope 

        if (node) { 

            decreaseKey(node, INT_MIN); 

            heap = extractMin(heap); 

            cout << "Element " << key << " deleted." << endl; 

        } else { 

            cout << "Element " << key << " not found." << endl; 

        } 

        break; 

    } 

  

    case 4: { 

        cout << "Enter the element to decrease: "; 

        cin >> key; 

        cout << "Enter the new key: "; 

        cin >> newKey; 

        BinomialHeapNode* node = findNode(heap, key); // Declare node inside this scope 

        if (node) { 

            decreaseKey(node, newKey); 

            cout << "Key decreased from " << key << " to " << newKey << "." << endl; 

        } else { 

            cout << "Element " << key << " not found." << endl; 

        } 

        break; 

    } 

  

    case 5: { 

        cout << "Displaying the binomial heap:" << endl; 

        displayHeap(heap); 

        break; 

    } 

  

    case 6: { 

        cout << "Exiting program." << endl; 

        return 0; 

    } 

  

    default: 

        cout << "Invalid choice. Please try again." << endl; 

  } 

  

    } 

  

    return 0; 

} 
