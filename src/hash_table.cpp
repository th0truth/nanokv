#include <string>
#include <cstring>
#include <cstdint>
#include <cmath>

#include "hash_table.h"
#include "prime.h"
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
  return (int32_t)hash;
}

int32_t HashTable::get_hash(const string &s, const int32_t num_buckets, const int32_t attempt)
{
  const int32_t hash_a = ht_hash(s, 151, num_buckets);

  switch (this->strategy) {
    case ProbingStrategy::LINEAR: return (hash_a + attempt) % num_buckets;
    case ProbingStrategy::QUADRATIC: return (hash_a + (attempt * attempt)) % num_buckets;
    case ProbingStrategy::DOUBLE_HASHING:
    default:
      const int32_t hash_b = ht_hash(s, 163, num_buckets);
      return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
  }
}

ht_item *HashTable::new_item(const string &key, const string &value)
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
void HashTable::insert(const string &key, const string &value)
{
  const int32_t load = this->count * 100 / this->size;
  if (load > 70) {
    resize_up();
  }

  ht_item *item = new_item(key, value);
  int32_t index = this->get_hash(item->key, this->size, 0);
  ht_item *current_item = this->items[index];
  int i = 1;

  while (current_item != nullptr) {
    if (current_item != &DELETED_ITEM) {
      if (current_item->key == key) {
        // KEY EXISTS: Delete the old one and replace it
        del_item(current_item);
        this->items[index] = item;
        return; 
      }
    }

    // Collision: move to the next index
    index = this->get_hash(item->key, this->size, i);
    current_item = this->items[index];
    i++;
  }
  this->items[index] = item;
  this->count++;
}

string *HashTable::search(const string &key)
{
  int32_t index = this->get_hash(key, this->size, 0);
  ht_item *current_item = this->items[index];
  int i = 1;
  while (current_item != nullptr) {
    if (current_item != &DELETED_ITEM) {
      if (current_item->key == key) {
        return &current_item->value;
      }
    }
    index = this->get_hash(key, this->size, i);
    current_item = this->items[index];
    i++;
  }
  return nullptr;
}

void HashTable::remove(const string &key)
{
  const int32_t load = this->count * 100 / this->size;
  if (load < 10) {
    resize_down();
  }

  int32_t index = this->get_hash(key, this->size, 0);
  ht_item *current_item = this->items[index];
  int i = 1;

  while (current_item != nullptr) {
    if (current_item != &DELETED_ITEM) {
      if (current_item->key == key) {
        del_item(current_item);
        this->items[index] = &DELETED_ITEM;
        this->count--;
        return;
      }
    }
    index = this->get_hash(key, this->size, i);
    current_item = this->items[index];
    i++; 
  }
}

HashTable::HashTable(ProbingStrategy strat)
{
  this->strategy = strat;
  this->base_size = HT_INITIAL_BASE_SIZE;
  this->size = next_prime(this->base_size);
  this->count = 0;

  // Allocate an array of size containing pointers to ht_item.
  this->items = new ht_item*[this->size]();
}

HashTable::HashTable(int32_t base_size, ProbingStrategy strat)
{
  this->strategy = strat;
  this->base_size = base_size;
  this->size = next_prime(this->base_size);
  this->count = 0;

  // Allocate an array of size containing pointers to ht_item.
  this->items = new ht_item*[this->size]();
}

HashTable::~HashTable()
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

void HashTable::resize(const int32_t base_size)
{
  if (base_size < HT_INITIAL_BASE_SIZE) {
    return;
  }
  
  // Create a temporary new has table with the new size
  HashTable new_ht(base_size, this->strategy);

  // Re-hash all existing items into the new table
  for (int i = 0; i < this->size; i++) {
    ht_item *item = this->items[i];
    if (item != nullptr && item != &DELETED_ITEM) {
      new_ht.insert(item->key, item->value);
    }  
  }

  // Update current table's attributes
  this->base_size = new_ht.base_size;
  this->count = new_ht.count;

  // Swap the items arrays
  const int32_t tmp_size = this->size;
  this->size = new_ht.size;
  new_ht.size = tmp_size;

  ht_item **tmp_items = this->items;
  this->items = new_ht.items;
  new_ht.items = tmp_items;
}

void HashTable::resize_up()
{
  const int32_t new_size = this->base_size * 2;
  resize(new_size);
}

void HashTable::resize_down()
{
  const int32_t new_size = this->base_size / 2;
  resize(new_size);
}
