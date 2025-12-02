//
//  main.cpp
//  stackandQ
//
//  Created by xavier saltos on 9/30/25.
//

#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Iterate to a given position (0-based index)
    Node* iterate(int position) {
        if (position < 0) return nullptr;
        Node* current = head;
        int index = 0;
        while (current != nullptr && index < position) {
            current = current->next;
            index++;
        }
        return current; // nullptr if not found
    }

    // Insert at position
    void insertAt(int position, int value) {
        Node* newNode = new Node(value);
        if (position <= 0 || head == nullptr) { // Insert at beginning
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* prev = iterate(position - 1);
        if (prev == nullptr) { // Position too big, append at end
            append(value);
            delete newNode; // avoid leak
            return;
        }

        newNode->next = prev->next;
        prev->next = newNode;
    }

    // Prepend (beginning)
    void prepend(int value) {
        insertAt(0, value);
    }

    // Append (end)
    void append(int value) {
        if (head == nullptr) {
            head = new Node(value);
            return;
        }

        Node* last = iterate(size() - 1);
        last->next = new Node(value);
    }

    // Find node by value
    Node* find(int value) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == value)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    // Contains (true/false)
    bool contains(int value) {
        return find(value) != nullptr;
    }

    // Remove by value
    bool remove(int value) {
        if (head == nullptr) return false;

        // Special case: head
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        Node* current = head;
        while (current->next != nullptr) {
            if (current->next->data == value) {
                Node* target = current->next;
                current->next = target->next;
                delete target;
                return true;
            }
            current = current->next;
        }

        return false; // Not found
    }

    // Remove node at position (0-based)
    bool removeAtPos(int position) {
        if (head == nullptr || position < 0)
            return false;

        if (position == 0) { // remove head
            Node* temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        Node* prev = iterate(position - 1);
        if (prev == nullptr || prev->next == nullptr)
            return false; // position out of range

        Node* target = prev->next;
        prev->next = target->next;
        delete target;
        return true;
    }

    // Remove first node
    bool removeFirst() {
        return removeAtPos(0);
    }

    // Remove last node
    bool removeLast() {
        if (head == nullptr)
            return false;
        if (head->next == nullptr) { // only one element
            delete head;
            head = nullptr;
            return true;
        }

        Node* prev = iterate(size() - 2);
        if (prev == nullptr || prev->next == nullptr)
            return false;

        delete prev->next;
        prev->next = nullptr;
        return true;
    }

    // Get size
    int size() {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // Display
    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    LinkedList list;
    list.append(10);
    list.append(20);
    list.append(30);
    list.prepend(5);
    list.insertAt(2, 15);

    cout << "Linked List: ";
    list.display();

    cout << "Contains 20? " << (list.contains(20) ? "Yes" : "No") << endl;

    list.remove(20);
    cout << "After removing 20: ";
    list.display();

    list.removeFirst();
    cout << "After removeFirst(): ";
    list.display();

    list.removeLast();
    cout << "After removeLast(): ";
    list.display();

    list.removeAtPos(1);
    cout << "After removeAtPos(1): ";
    list.display();

    cout << "Final size: " << list.size() << endl;

    return 0;
}
