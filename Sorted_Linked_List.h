#ifndef SORTED_LINKED_LIST_H
#define SORTED_LINKED_LIST_H

#include <iostream>
using namespace std;

 class Node {
 public:
      int data;
      Node* next;
      Node(int val);
 };

Node::Node(int val) {
    data = val;
    next = nullptr;
}

class SortedLinkedList {
private:
    Node* head;
    void merge(int arr[],int rightHalf[], int leftHalf[]);
public:
    SortedLinkedList();
    // Main function
    void insert(int value);
    void remove(int index);
    void mergesort(int arr[]);
    // Operator overloading
    friend ostream& operator<<(ostream&os, const SortedLinkedList& list);
    int operator[](int index);

    ~SortedLinkedList();
};

SortedLinkedList::SortedLinkedList() : head(nullptr) {}


void SortedLinkedList::insert(int value) {
    if (head == nullptr) {
        head = new Node(value);
        return;
    }

    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    Node* newNode = new Node(value);
    newNode->next = current->next;
    current->next = newNode;
}

void SortedLinkedList::remove(int index) {
    if (head == nullptr && index < 0) {
        cerr << "Invalid operation" << endl;
        return;
    }
    // Delete The head
    if (index == 0) {
        Node* temp = head;
        head = head -> next;
        delete temp;
        return;
    }

    // Delete any position out of head and tail
    Node* current = head;
    for (int i = 1; i <= index && current != nullptr; i++) {
        current = current->next;
    }

    if (current == nullptr || current->next == nullptr) {
        return;
    }

    Node *temp = current->next;
    current->next = temp->next;
    delete temp;
}


ostream& operator<<(ostream&os, const SortedLinkedList& list) {
    Node* temp = list.head;
    os << '[';
    while (temp != nullptr) {
        os << temp->data;
        if (temp->next != nullptr) os << ',';
        temp = temp->next;
    }
    os << ']' << endl;

    return os;
}





void SortedLinkedList::merge(int arr[],int rightHalf[], int leftHalf[]) {
    int leftSize = sizeof(leftHalf) / rightHalf[0];
    int rightSize = sizeof(rightHalf) / leftHalf[0];

    int i = 0, j = 0, k = 0;

    while (i < leftSize && j < rightSize) {
        if (leftHalf[i] < rightHalf[j]) {
            arr[k] = leftHalf[i];
            i++;
        }
        else {
            arr[k] = rightHalf[j];
            j++;
        }
        k++;
    }
    while (i < leftSize) {
        arr[k] = leftHalf[i];
        i++;
        k++;
    }
    while (j < rightSize) {
        arr[k] = rightHalf[i];
        j++;
        k++;
    }

}

void SortedLinkedList::mergesort(int arr[]) {
    int length = sizeof(arr)/arr[0];

    if (length < 2) {
        return;
    }

    int midIdx = length / 2;
    int leftHalf[midIdx];
    int rightHalf[length - midIdx];

    for (int i = 0; i < midIdx; i++) {
        leftHalf[i] = arr[i];
    }
    for (int i = midIdx; i < length; i++) {
        rightHalf[i - midIdx] = arr[i];
    }

    mergesort(leftHalf);
    mergesort(rightHalf);
    merge(arr, rightHalf,leftHalf);
}

SortedLinkedList::~SortedLinkedList() {
    while (head != nullptr) {
        Node* temp = head;
        head = head -> next;
        delete temp;
    }

}



#endif //SORTED_LINKED_LIST_H
