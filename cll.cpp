#include <iostream>

struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(NULL) {}
};

// Function to insert a new node into the circular lin#include <iostream>
using namespace std;


struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int data) {
        this->data = data;
        this->prev = this->next = NULL;
    }
};


struct CircularDoublyLinkedList {
    Node* head;

    CircularDoublyLinkedList() {
        head = NULL;
    }

    
    void append(int data) {
        Node* newNode = new Node(data);
        if (head == NULL) {
            head = newNode;
            newNode->next = newNode->prev = newNode;
        } else {
            Node* last = head->prev;
            last->next = newNode;
            newNode->prev = last;
            newNode->next = head;
            head->prev = newNode;
        }
    }

    
    void display() {
        if (head == NULL) {
            cout << "The list is empty." << endl;
            return;
        }
        Node* temp = head;
        do {
            cout << temp->data << " <-> ";
            temp = temp->next;
        } while (temp != head);
        
    }

    
    void concatenate(CircularDoublyLinkedList& other) {
        if (head == NULL || other.head == NULL) {
            cout << "One or both lists are empty." << endl;
            return;
        }

        
        Node* tail1 = head->prev;
        Node* tail2 = other.head->prev;

        tail1->next = other.head;
        other.head->prev = tail1;

        head->prev = tail2;
        tail2->next = head;

        
        other.head = NULL;
    }
};

int main() {
    CircularDoublyLinkedList list1, list2;

    
    int n1;
    cout << "Enter the number of nodes for the first list: ";
    cin >> n1;
    for (int i = 0; i < n1; ++i) {
        int data;
        cout << "Enter data for node "<<i<<": ";
        cin >> data;
        list1.append(data);
    }

    
    int n2;
    cout << "Enter the number of nodes for the second list: ";
    cin >> n2;
    for (int i = 0; i < n2; ++i) {
        int data;
        cout << "Enter data for node: ";
        cin >> data;
        list2.append(data);
    }

    
    cout << "\nFirst Circular Doubly Linked List:" << endl;
    list1.display();

    cout << "\nSecond Circular Doubly Linked List:" << endl;
    list2.display();

    
    list1.concatenate(list2);

    
    cout << "\nConcatenated Circular Doubly Linked List:" << endl;
    list1.display();

    return 0;
}
ked list
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

