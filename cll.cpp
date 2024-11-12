#include <iostream>

struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(NULL) {}
};

// Function to insert a new node into the circular linked list
void insert(Node*& head, int val) {
    Node* newNode = new Node(val);
    if (!head) {
        head = newNode;
        newNode->next = head;  // Pointing to itself
    } else {
        Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;  // Closing the circular link
    }
}

// Function to display the circular linked list
void display(Node* head) {
    if (!head) return;
    Node* temp = head;
    do {
        std::cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);
    std::cout << std::endl;
}

// Function to concatenate two circular linked lists
void concatenate(Node*& head1, Node*& head2) {
    if (!head1) {
        head1 = head2;
        return;
    }
    if (!head2) return;

    Node* tail1 = head1;
    while (tail1->next != head1) {
        tail1 = tail1->next;
    }

    Node* tail2 = head2;
    while (tail2->next != head2) {
        tail2 = tail2->next;
    }

    tail1->next = head2;  // Link the end of the first list to the head of the second
    tail2->next = head1;  // Link the end of the second list to the head of the first
}

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;

    // Input for the first circular linked list
    std::cout << "Enter elements for the first circular linked list (enter -1 to stop):" << std::endl;
    int value;
    while (true) {
        std::cin >> value;
        if (value == -1) break;
        insert(list1, value);
    }

    // Input for the second circular linked list
    std::cout << "Enter elements for the second circular linked list (enter -1 to stop):" << std::endl;
    while (true) {
        std::cin >> value;
        if (value == -1) break;
        insert(list2, value);
    }

    // Display the original lists
    std::cout << "First Circular Linked List: ";
    display(list1);
    std::cout << "Second Circular Linked List: ";
    display(list2);

    // Concatenate the two lists
    concatenate(list1, list2);

    // Display the concatenated list
    std::cout << "Concatenated Circular Linked List: ";
    display(list1);

    return 0;
}

