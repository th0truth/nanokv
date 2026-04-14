#pragma once
#include <string>

struct DLLNode {
  std::string key;
  std::string value;
  DLLNode *prev;
  DLLNode *next;
};

class DoublyLinkedList {
  private:
    DLLNode *head;
    DLLNode *tail;

  public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insert(const std::string &key, const std::string &value);
    void remove(const std::string &key);
    void display(const std::string &msg = "");
    void displayReverse(const std::string &msg = "");
    std::string *search(const std::string &key);

    bool isEmpty();
};
