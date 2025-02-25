#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// DataItems class definition (as provided)
class __attribute__ ((packed)) DataItems {
public:
    int b;
    double a;
    bool c;
    bool used;  // Flag to check if the data is used or free for reuse

    DataItems() : b(0), a(0.0), c(false), used(true) {}  // Default constructor

    // Friend function to overload the << operator for easy display
    friend ostream & operator <<(ostream &out, DataItems &item) {
        out << "a: " << item.a << ", b: " << item.b << ", c: ";
        if (item.c) out << "True";
        else out << "False";
        out << ", used: " << (item.used ? "True" : "False") << endl;
        return out;
    }
};

// LinkedList class with file persistence
class LinkedList {
private:
    fstream file;  // File to store data
    string filename;

    // Helper function to write DataItems to the file at a given position
    void writeToFile(long pos, DataItems& data) {
        file.seekp(pos * sizeof(DataItems), ios::beg);
        file.write(reinterpret_cast<char*>(&data), sizeof(DataItems));
        file.flush();
    }

    // Helper function to read DataItems from the file at a given position
    void readFromFile(long pos, DataItems& data) {
        file.seekg(pos * sizeof(DataItems), ios::beg);
        file.read(reinterpret_cast<char*>(&data), sizeof(DataItems));
    }

public:
    LinkedList(const string& fname) : filename(fname) {
        file.open(filename, ios::in | ios::out | ios::binary);
        if (!file) {
            // If the file doesn't exist, create it and initialize it with some space
            file.clear();
            file.open(filename, ios::out | ios::binary);
            DataItems emptyItem;
            for (int i = 0; i < 100; ++i) {  // Reserve space for 100 DataItems
                file.write(reinterpret_cast<char*>(&emptyItem), sizeof(DataItems));
            }
            file.close();
            file.open(filename, ios::in | ios::out | ios::binary);
        }
    }

    // Destructor to close the file properly
    ~LinkedList() {
        file.close();
    }

    // Insert a new DataItems to the file, or reuse a deleted slot
    void insert(DataItems& data) {
        long pos = -1;
        DataItems temp;
        file.seekg(0, ios::beg);
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(DataItems))) {
            if (!temp.used) {
                pos = file.tellg() / sizeof(DataItems) - 1;  // Found a free slot
                break;
            }
        }

        if (pos == -1) {
            // If no free slot, append new data to the end
            pos = file.tellg() / sizeof(DataItems);
        }

        data.used = true;  // Mark as used
        writeToFile(pos, data);
    }

    // Delete (mark as unused) a DataItems object in the file
    void deleteData(long pos) {
        DataItems temp;
        readFromFile(pos, temp);
        if (temp.used) {
            temp.used = false;
            writeToFile(pos, temp);  // Mark the data as deleted
        }
    }

    // Display the entire list
    void display() {
        file.seekg(0, ios::beg);
        DataItems temp;
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(DataItems))) {
            cout << temp;
        }
    }

    // Helper function to check if the file is empty
    bool isEmpty() {
        file.seekg(0, ios::beg);
        DataItems temp;
        return !file.read(reinterpret_cast<char*>(&temp), sizeof(DataItems));
    }
};

int main() {
    LinkedList list("data.bin");

    // Create DataItems instances
    DataItems d1 = {10, 20.5, true};
    DataItems d2 = {20, 30.7, false};
    DataItems d3 = {30, 40.8, true};

    // Insert DataItems into the linked list
    cout << "Inserting d1..." << endl;
    list.insert(d1);

    cout << "Inserting d2..." << endl;
    list.insert(d2);

    cout << "Inserting d3..." << endl;
    list.insert(d3);

    cout << "\nList after insertion:" << endl;
    list.display();

    // Delete d2 (mark as unused)
    cout << "\nDeleting d2..." << endl;
    list.deleteData(1);  // Assume position 1 is where d2 is located

    cout << "\nList after deleting d2:" << endl;
    list.display();

    // Insert new data (this should overwrite the space of d2)
    DataItems d4 = {40, 50.9, true};
    cout << "\nInserting d4 (should reuse deleted d2 space)..." << endl;
    list.insert(d4);

    cout << "\nList after inserting d4:" << endl;
    list.display();

    return 0;
}
