#include <iostream>
#include <iomanip>

#include "chaining_hash_table.h"
#include "prime.h"
using namespace std;

ChainingHashTable::ChainingHashTable(int32_t size)
{
  this->num_buckets = next_prime(size);
  this->table.resize(this->num_buckets);
}

int32_t ChainingHashTable::get_hash(const string &key)
{
  int64_t hash = 0;
  for (char c : key) {
    hash = (hash * 31 + c) % this->num_buckets;
  }
  return (int32_t)hash;
}

void ChainingHashTable::insert(const string &key, const string &value)
{
  int32_t index = get_hash(key);
  int collisions = 0;

  for (auto &item : table[index]) {
    if (item.key == key) {
      item.value = value;
      return;
    }
    collisions++; 
  }

  table[index].push_back({key, value});

  if (collisions > 0) {
    cout << "[Chain Info] Inserted '" << key << "' into chain of length " << collisions << ".\n";
  }
}

string *ChainingHashTable::search(const string &key)
{
  int32_t index = get_hash(key);
    
  for (auto &item : table[index]) {
    if (item.key == key) {
      return &item.value;
    }
  }
  return nullptr;
}

void ChainingHashTable::remove(const string &key)
{
  int32_t index = get_hash(key);
    
  auto &list = table[index];
  for (auto it = list.begin(); it != list.end(); ++it) {
    if (it->key == key) {
      list.erase(it);
      return;
    }
  }
}

void ChainingHashTable::display(const string msg)
{
  cout << "\n" << msg << " (Buckets: " << this->num_buckets << ")\n";
  cout << "  +-------+--------------------------------------------------\n";
  
  for (int i = 0; i < num_buckets; i++) {
    if (table[i].empty()) continue; // Only show non-empty buckets for brevity, or show all
        
    cout << "  | " << right << setw(5) << i << " | ";
    for (const auto &item : table[i]) {
      cout << "{" << item.key << ": " << item.value << "} -> ";
    }
    cout << "null\n";
  }
  cout << "  +-------+--------------------------------------------------\n\n";
}
