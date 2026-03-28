#include <string>
#include <cstring>
#include <cstdint>
#include <cmath>

#include "hash_table.h"
using namespace std;

ht_item HashTable::DELETED_ITEM = {"", ""}; 

// A generic string hashing algortihm (ASCII sum with a prime multiplier)
static int32_t ht_hash(string s, const int a, const int m)
{
  int64_t hash = 0;
  const int len_s = s.size();
  for (int i = 0; i < len_s; i++) {
    hash = (hash * a + s[i]) % m;
  }
  return (int64_t)hash;
}

// First hash function determines the initial bucket
static int32_t ht_get_hash(string s, const int32_t num_buckets, const int32_t attempt)
{
  const int32_t hash_a = ht_hash(s, 151, num_buckets);
  const int32_t hash_b = ht_hash(s, 163, num_buckets);

  // Doulbe hashing: (hash_a + (attempt * (hash_b + 1))) % buckets
  // Adding 1 to hash_b ensures the step size is never 0
  return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

ht_item *HashTable::new_item(string &key, string &value)
{
  // Allocate an item
  ht_item *item = new ht_item;
  item->key = key;
  item->value = value;
  return item;  
}

void HashTable::del_item(ht_item *item)
{
  if (item != nullptr && item != &DELETED_ITEM) {
    delete item;
  }
}

// Insert a new key-value pair
void HashTable::insert(string key, string value)
{
  ht_item *item = new_item(key, value);
  int32_t index = ht_get_hash(item->key, this->size, 0);
  ht_item *current_item = this->items[index];
  int i = 1;

  while (current_item != nullptr && current_item != &DELETED_ITEM) {
    index = ht_get_hash(item->key, this->size, i);
    current_item = this->items[index];
    i++;
  }
  this->items[index] = item;
  this->count++;
}

string *HashTable::search(string key)
{
  int32_t index = ht_get_hash(key, this->size, 0);
  ht_item *current_item = this->items[index];
  int i = 1;
  while (current_item != nullptr) {
    if (current_item != &DELETED_ITEM) {
      if (current_item->key == key) {
        return &current_item->value;
      }
    }
    index = ht_get_hash(key, this->size, i);
    current_item = this->items[index];
    i++;
  }
  return nullptr;
}

void HashTable::remove(string key)
{
  int32_t index = ht_get_hash(key, this->size, 0);
  ht_item *current_item = this->items[index];
  int i = 1;

  while (current_item != nullptr) {
    if (current_item != &DELETED_ITEM) {
      if (!current_item->key.compare(key)) {
        del_item(current_item);
        this->items[index] = &DELETED_ITEM;
        this->count--;
        return;
      }
    }
    index = ht_get_hash(key, this->size, i);
    current_item = this->items[index];
    i++; 
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
