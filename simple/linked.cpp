#include <iostream>
using namespace std;

// DataItems class definition (as provided)
class __attribute__ ((packed)) DataItems {
public:
    int b;
    double a;
    bool c;

    friend ostream & operator <<(ostream &out, DataItems &item) {
        out << "a: " << item.a << ", b: " << item.b << ", c: ";
        if (item.c) out << "True" << endl;
        else out << "False" << endl;
        return out;
    }
};

// Node structure to represent each element in the list
struct Node {
    DataItems data;  // Data held by the node (an instance of DataItems)
    Node* next;      // Pointer to the next node

    // Constructor to initialize a new node with DataItems
    Node(DataItems val) : data(val), next(nullptr) {}
};

// LinkedList class with basic operations
class LinkedList {
private:
    Node* head;  // Pointer to the first node in the list

public:
    // Constructor initializes an empty list
    LinkedList() : head(nullptr) {}

    // Destructor to delete the entire list
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Function to insert a node at the end of the list
    void insertEnd(DataItems val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Function to delete the first occurrence of a DataItems object
    void deleteValue(DataItems val) {
        if (head == nullptr) return;

        // If the head is the node to delete
        if (head->data.b == val.b && head->data.a == val.a && head->data.c == val.c) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        // Traverse the list to find and delete the node
        Node* current = head;
        while (current->next != nullptr) {
            if (current->next->data.b == val.b && current->next->data.a == val.a && current->next->data.c == val.c) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                return;
            }
            current = current->next;
        }
    }

    // Function to display the entire list
    void display() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data;  // Use the overloaded << operator for DataItems
            current = current->next;
        }
    }

    // Function to check if the list is empty
    bool isEmpty() const {
        return head == nullptr;
    }
};

int main() {
    LinkedList list;

    // Create DataItems instances
    DataItems d1 = {10, 20.5, true};
    DataItems d2 = {20, 30.7, false};
    DataItems d3 = {30, 40.8, true};

    // Insert DataItems into the linked list
    list.insertEnd(d1);
    list.insertEnd(d2);
    list.insertEnd(d3);

    cout << "List after insertion: " << endl;
    list.display();  // Display the list

    // Deleting a DataItems from the list
    list.deleteValue(d2);  // Delete the second DataItems

    cout << "\nList after deleting d2: " << endl;
    list.display();  // Display the list after deletion

    return 0;
}
