#pragma once

#include <string>
#include <list>
#include <vector>

#include "hash_table.h" // For ht_item

class ChainingHashTable {
private:
  int32_t num_buckets;
  std::vector<std::list<ht_item>> table;

  int32_t get_hash(const std::string &key);

public:
    ChainingHashTable(int32_t size = 50);

    std::string* search(const std::string &key);
    void insert(const std::string &key, const std::string &value);
    void remove(const std::string &key);
    void display(const std::string msg = "Chaining Hash Table contents");
};
