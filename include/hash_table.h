#pragma once
#include <string>
using namespace std;

typedef struct {
  string key;
  string value;
} ht_item;

class HashTable {
  private:
    int32_t size;
    int32_t count;
    ht_item **items;
 
    static ht_item DELETED_ITEM;

    ht_item *new_item(string &key, string &value);
    void del_item(ht_item *item);
    
    public:
    // Constructor
    HashTable();
    
    // Desctructor
    ~HashTable();

    string *search(string key);
    void insert(string key, string value);
    void remove(string key);

};
