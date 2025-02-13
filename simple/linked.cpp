#include <iostream>
using namespace std;

// Define a class for DataItems
class DataItems {
public:
    int intData;
    double doubleData;
    bool boolData;

    // Constructor to initialize DataItems
    DataItems(int i, double d, bool b) {
        intData = i;
        doubleData = d;
        boolData = b;
    }

    // Function to display the DataItems
    void display() const {
        cout << "[" << intData << ", " << doubleData << ", " << boolData << "]";
    }
};

// Define the structure for a node
struct Node {
    DataItems data;  // Store DataItems object in each node
    Node* next;

    // Constructor to initialize the node with DataItems
    Node(const DataItems& value) : data(value), next(nullptr) {}
};

// Define the class for Linked List
class LinkedList {
private:
    Node* head;

public:
    // Constructor to initialize the linked list
    LinkedList() {
        head = nullptr;
    }

    // Function to insert a node at the end of the list
    void insert(const DataItems& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Function to delete a node with a specific DataItems
    void deleteValue(const DataItems& value) {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        if (head->data.intData == value.intData && head->data.doubleData == value.doubleData && head->data.boolData == value.boolData) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr &&
               (temp->next->data.intData != value.intData ||
                temp->next->data.doubleData != value.doubleData ||
                temp->next->data.boolData != value.boolData)) {
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            cout << "Value not found!" << endl;
        } else {
            Node* delNode = temp->next;
            temp->next = temp->next->next;
            delete delNode;
        }
    }

    // Function to display the linked list
    void display() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        Node* temp = head;
        while (temp != nullptr) {
            temp->data.display();
            cout << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Destructor to delete all nodes and free memory
    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList list;

    // Inserting nodes into the list
    list.insert(DataItems(10, 20.5, true));
    list.insert(DataItems(20, 30.5, false));
    list.insert(DataItems(30, 40.5, true));
    list.insert(DataItems(40, 50.5, false));

    // Display the list
    cout << "Linked List: ";
    list.display();

    // Deleting a node with specific DataItems
    cout << "Deleting DataItems [20, 30.5, false]..." << endl;
    list.deleteValue(DataItems(20, 30.5, false));

    // Display the list again
    cout << "Linked List after deletion: ";
    list.display();

    // Deleting a node that does not exist
    cout << "Trying to delete DataItems [50, 60.5, true]..." << endl;
    list.deleteValue(DataItems(50, 60.5, true));

    // Final display of the list
    cout << "Final Linked List: ";
    list.display();

    return 0;
}
