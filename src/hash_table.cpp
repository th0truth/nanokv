#include "hash_table.h"
#include <cstring>

ht_item HashTable::DELETED_ITEM = {nullptr, nullptr}; 

ht_item *HashTable::new_item(const char *key, const char *value)
{
  // Allocate an item
  ht_item *item = new ht_item;
  item->key = strdup(key);
  item->value = strdup(value);
  return item;  
}

void HashTable::del_item(ht_item *item)
{
  if (item != nullptr && item != &DELETED_ITEM) {
    delete[] item->key;
    delete[] item->value;
    delete item;
  }
}

HashTable::HashTable(void)
{
  this->size = 53;
  this->count = 0;

  // Allocate an array of size containing pointers to ht_item.
  this->items = new ht_item*[this->size]();
}

HashTable::~HashTable(void)
{
  for (int i = 0; i < this->size; i++) {
    ht_item *item = this->items[i];
    if (item != nullptr && item != &DELETED_ITEM) {
      del_item(item);
    }
  }

  // Delete the array of pointers
  delete[] this->items;
}