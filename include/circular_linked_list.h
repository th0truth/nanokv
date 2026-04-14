#pragma once
#include <string>

struct CLLNode {
  std::string key;
  std::string value;
  CLLNode *next;
};

class CircularLinkedList {
  private:
    CLLNode *head;

  public:
    CircularLinkedList();
    ~CircularLinkedList();

    void insert(const std::string &key, const std::string &value);
    void remove(const std::string &key);
    std::string* search(const std::string &key);
    void display(const std::string &msg = "");

    bool isEmpty();
};
