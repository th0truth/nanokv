#pragma once
#include <string>

struct Node
{
  std::string key;
  std::string value;
  Node *next;
};

class SinglyLinkedList
{
  private:
    Node *head;

  public:
    SinglyLinkedList();
    ~SinglyLinkedList();
    
    void insert(const std::string &key, const std::string &value);
    void remove(const std::string &key);
    std::string *search(const std::string &key);
    void display(const std::string &msg = "");
    bool isEmpty();
};
