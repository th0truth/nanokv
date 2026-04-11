#include "singly_linked_list.h"
#include <iostream>

using namespace std;

SinglyLinkedList::SinglyLinkedList() : head(nullptr) {}

SinglyLinkedList::~SinglyLinkedList()
{
  Node* current = head;
  while (current != nullptr) {
    Node* next = current->next;
    delete current;
    current = next;
  }
}

void SinglyLinkedList::insert(const string &key, const string &value)
{
  // If key already exists, update its value
  Node* curr = head;
  while (curr != nullptr) {
    if (curr->key == key) {
      curr->value = value;
      return;
    }
    curr = curr->next;
  }
  
  // Otherwise, prepend new node to list
  Node* n = new Node{key, value, head};
  head = n;
}

string *SinglyLinkedList::search(const string &key)
{
  Node* curr = head;
  while (curr != nullptr) {
    if (curr->key == key) {
      return &(curr->value);
    }
    curr = curr->next;
  }
  return nullptr;
}

void SinglyLinkedList::remove(const string &key) {
  if (head == nullptr) return;

  if (head->key == key) {
    Node* temp = head;
    head = head->next;
    delete temp;
    return;
  }

  Node* curr = head;
  while (curr->next != nullptr && curr->next->key != key) {
    curr = curr->next;
  }

  if (curr->next != nullptr) {
    Node* temp = curr->next;
    curr->next = curr->next->next;
    delete temp;
  }
}

void SinglyLinkedList::display(const string &msg) {
  if (!msg.empty()) {
    cout << msg << endl;
  }
  
  Node* curr = head;
  while (curr != nullptr) {
    cout << "[" << curr->key << ": " << curr->value << "] -> ";
    curr = curr->next;
  }
  cout << "NULL" << endl;
}

bool SinglyLinkedList::isEmpty() {
  return head == nullptr;
}
