#pragma once

typedef struct {
  char *key;
  char *value;
} ht_item;

class HashTable {
  private:
    int size;
    int count;
    ht_item **items;
 
    static ht_item DELETED_ITEM;

    ht_item *new_item(const char *key, const char *value);
    void del_item(ht_item *item);
    
    public:
    // Constructor
    HashTable();
    
    // Desctructor
    ~HashTable();

    void *insert(const char *key, const char *value);
    void remove(ht_item *item);
};
