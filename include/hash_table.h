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
  
    ht_item *insert(const char *key, const char *value);
    void remove(ht_item *item);
  
  public:
    // Constructor
    HashTable();

    // Desctructor
    ~HashTable();
};
