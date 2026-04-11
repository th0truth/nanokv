#include "doubly_linked_list.h"
#include <iostream>

using namespace std;

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

DoublyLinkedList::~DoublyLinkedList() {
  DLLNode* current = head;
  while (current != nullptr) {
    DLLNode* next = current->next;
    delete current;
    current = next;
  }
}

void DoublyLinkedList::insert(const string& key, const string& value)
{
  // If key already exists, update its value
  DLLNode* curr = head;
  while (curr != nullptr) {
    if (curr->key == key) {
      curr->value = value;
      return;
    }
    curr = curr->next;
  }

  // Otherwise, prepend new node to list (Your bi-directional linking)
  DLLNode* newNode = new DLLNode{key, value, nullptr, head};
  if (head != nullptr) {
    head->prev = newNode;
  }
  head = newNode;
  if (tail == nullptr) {
    tail = newNode;
  }
}

string* DoublyLinkedList::search(const string &key){

  DLLNode* curr = head;
  while (curr != nullptr) {
    if (curr->key == key) {
      return &(curr->value);
    }
    curr = curr->next;
  }
  return nullptr;
}

void DoublyLinkedList::remove(const string &key)
{
  DLLNode* curr = head;
  while (curr != nullptr && curr->key != key) {
    curr = curr->next;
  }

  if (curr == nullptr) return;

  if (curr->prev) {
    curr->prev->next = curr->next;
  } else {
    head = curr->next;
  }

  if (curr->next) {
    curr->next->prev = curr->prev;
  } else {
    tail = curr->prev;
  }

  delete curr;
}

void DoublyLinkedList::display(const string &msg)
{
  if (!msg.empty()) {
    cout << msg << endl;
  }
  DLLNode* curr = head;
  while (curr != nullptr) {
    cout << "[" << curr->key << ": " << curr->value << "]";
    if (curr->next) {
      cout << " <-> ";
    }
    curr = curr->next;
  }
  cout << " <-> NULL" << endl;
}

void DoublyLinkedList::displayReverse(const string &msg)
{
  if (!msg.empty()) {
    cout << msg << endl;
  }
  DLLNode* curr = tail;
  while (curr != nullptr) {
    cout << "[" << curr->key << ": " << curr->value << "]";
    if (curr->prev) {
      cout << " <-> ";
    }
    curr = curr->prev;
  }
  cout << " <-> NULL" << endl;
}

bool DoublyLinkedList::isEmpty()
{
  return head == nullptr;
}
