#include "circular_linked_list.h"
#include <iostream>

using namespace std;

CircularLinkedList::CircularLinkedList() : head(nullptr) {}

CircularLinkedList::~CircularLinkedList()
{
  if (head == nullptr) return;

  CLLNode* current = head;
  CLLNode* nextNode;
  do {
    nextNode = current->next;
    delete current;
    current = nextNode;
  } while (current != head);
}

void CircularLinkedList::insert(const string &key, const string &value)
{
  // If key already exists, update its value
  if (head != nullptr) {
    CLLNode* curr = head;
    do {
      if (curr->key == key) {
        curr->value = value;
        return;
      }
      curr = curr->next;
    } while (curr != head);
  }

  // Otherwise, insert new node at the front
  CLLNode* newNode = new CLLNode{key, value, nullptr};
  if (head == nullptr) {
    head = newNode;
    newNode->next = head;
  } else {
    // Find last node to point it to the new head
    CLLNode* last = head;
    while (last->next != head) {
      last = last->next;
    }
    newNode->next = head;
    last->next = newNode;
    head = newNode;
  }
}

string* CircularLinkedList::search(const string &key)
{
  if (head == nullptr) return nullptr;

  CLLNode* curr = head;
  do {
    if (curr->key == key) return &(curr->value);
    curr = curr->next;
  } while (curr != head);

  return nullptr;
}

void CircularLinkedList::remove(const string &key)
{
  if (head == nullptr) return;

  CLLNode *curr = head, *prev = nullptr;

  // Case 1: Head node needs to be removed
  if (head->key == key) {
    // If only one node
    if (head->next == head) {
      delete head;
      head = nullptr;
      return;
    }

    // Find last node to update its next pointer
    CLLNode* last = head;
    while (last->next != head) {
      last = last->next;
    }
    last->next = head->next;
    CLLNode* temp = head;
    head = head->next;
    delete temp;
    return;
  }

  // Case 2: Node somewhere else in the list
  do {
    prev = curr;
    curr = curr->next;
    if (curr->key == key) {
      prev->next = curr->next;
      delete curr;
      return;
    }
  } while (curr != head);
}

void CircularLinkedList::display(const string &msg)
{
  if (!msg.empty()) cout << msg << endl;
  if (head == nullptr) {
    cout << "EMPTY" << endl;
    return;
  }

  CLLNode* curr = head;
  do {
    cout << "[" << curr->key << ": " << curr->value << "] -> ";
    curr = curr->next;
  } while (curr != head);
  cout << "(HEAD)" << endl;
}

bool CircularLinkedList::isEmpty()
{
  return head == nullptr;
}
