#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Define the DataItems class
class DataItems {
public:
    int intData;
    double doubleData;
    bool boolData;

    // Constructor to initialize DataItems
    DataItems(int i = 0, double d = 0.0, bool b = false) {
        intData = i;
        doubleData = d;
        boolData = b;
    }

    // Function to display the DataItems
    void display() const {
        cout << "[" << intData << ", " << doubleData << ", " << boolData << "]";
    }

    // Function to write DataItems to the file at a specific position
    void write(ostream &out, long pos, bool setUsed = true) {
        out.seekp(pos * sizeof(DataItems));  // Seek to the correct position (in bytes)
        if (setUsed) {
            // Here you can perform any operations when the item is being saved
        }
        out.write(reinterpret_cast<char *>(this), sizeof(DataItems));  // Write the DataItems to the file
        out.flush();  // Ensure data is written immediately
    }

    // Function to read DataItems from the file at a specific position
    void read(istream &in, long pos) {
        in.seekg(pos * sizeof(DataItems));  // Seek to the correct position (in bytes)
        in.read(reinterpret_cast<char *>(this), sizeof(DataItems));  // Read the DataItems from the file
    }
};

// Database class for managing the binary file
class Database {
public:
    fstream file;

    // Static method to create the database (initialize the file if it doesn't exist)
    static void createDB(string fname) {
        ofstream outFile(fname, ios::binary);  // Create and open the file in binary mode
        outFile.close();  // Close the file
    }

    // Method to get the size of the database file (number of records)
    long getSize() {
        file.seekg(0, ios::end);  // Seek to the end of the file
        return file.tellg() / sizeof(DataItems);  // Calculate the size (in terms of number of DataItems)
    }

    // Constructor: Open the database file (or create it if it doesn't exist)
    Database(string fname) {
        ifstream test(fname);
        if (!test.good()) {
            Database::createDB(fname);  // If file doesn't exist, create it
        } else {
            test.close();
        }
        file.open(fname, ios::in | ios::out | ios::binary);  // Open the file for reading and writing in binary mode
    }

    // Method to write a DataItems object to a specific position in the file
    void write(long pos, const DataItems &d) {
        d.write(file, pos, true);  // Write the DataItems to the file at the specified position
    }

    // Method to read a DataItems object from a specific position in the file
    DataItems read(long pos) {
        DataItems d;
        d.read(file, pos);  // Read the DataItems from the file at the specified position
        return d;  // Return the read DataItems
    }

    // Method to delete data at a specific position (mark it as deleted)
    void dataDelete(long pos) {
        // Here, we simply overwrite the data with default values to "delete" it.
        DataItems emptyData;
        write(pos, emptyData);  // Write an empty DataItems object to the specified position
    }

    // Method to create a new data entry (finds the next available position)
    long dataNew() {
        long size = getSize();
        return size;  // Return the current size as the next available position
    }

    // Destructor: Ensure data is flushed and the file is properly closed
    ~Database() {
        file.flush();  // Ensure all data is written to the file
        file.close();  // Close the file
    }
};

// Define the structure for a node in the linked list
struct Node {
    DataItems data;  // Store DataItems object in each node
    Node* next;

    // Constructor to initialize the node with DataItems
    Node(const DataItems& value) : data(value), next(nullptr) {}
};

// Define the LinkedList class
class LinkedList {
private:
    Node* head;
    Database& db;  // Reference to the Database class to interact with the file

public:
    // Constructor to initialize the linked list and load data from the database
    LinkedList(Database& database) : head(nullptr), db(database) {}

    // Function to insert a node at the end of the list and save to the database
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
        long pos = db.dataNew();  // Get the next available position in the database
        db.write(pos, value);  // Write the new DataItems to the database
    }

    // Function to delete a node with a specific DataItems and update the database
    void deleteValue(const DataItems& value) {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        if (head->data.intData == value.intData && head->data.doubleData == value.doubleData && head->data.boolData == value.boolData) {
            Node* temp = head;
            head = head->next;
            db.dataDelete(0);  // Delete the first node in the database
            delete temp;
            return;
        }

        Node* temp = head;
        long index = 0;
        while (temp->next != nullptr &&
               (temp->next->data.intData != value.intData ||
                temp->next->data.doubleData != value.doubleData ||
                temp->next->data.boolData != value.boolData)) {
            temp = temp->next;
            index++;
        }

        if (temp->next == nullptr) {
            cout << "Value not found!" << endl;
        } else {
            Node* delNode = temp->next;
            temp->next = temp->next->next;
            db.dataDelete(index + 1);  // Delete the node from the database
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
    Database db("Data.bin");

    // Create the linked list, passing the database as reference
    LinkedList list(db);

    // Inserting nodes into the linked list and saving them to the database
    list.insert(DataItems(10, 20.5, true));
    list.insert(DataItems(20, 30.5, false));
    list.insert(DataItems(30, 40.5, true));

    // Display the linked list
    cout << "Linked List: ";
    list.display();

    // Deleting a node with specific DataItems from the linked list and database
    cout << "Deleting DataItems [20, 30.5, false]..." << endl;
    list.deleteValue(DataItems(20, 30.5, false));

    // Display the linked list again
    cout << "Linked List after deletion: ";
    list.display();

    // Final display of the list
    cout << "Final Linked List: ";
    list.display();

    return 0;
}
