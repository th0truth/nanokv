#pragma once
#include <string>

#define HT_INITIAL_BASE_SIZE 50

enum class ProbingStrategy {
  LINEAR,
  QUADRATIC,
  DOUBLE_HASHING
};

typedef struct {
  std::string key;
  std::string value;
} ht_item;

class HashTable {
  private:
    int32_t base_size;

    // Store the chosen strategy
    ProbingStrategy strategy;
    
    void resize(const int32_t base_size);
    void resize_up();
    void resize_down();

    int32_t size;
    int32_t count;
    ht_item **items;
 
    static ht_item DELETED_ITEM;

    ht_item *new_item(const std::string &key, const std::string &value);
    void del_item(ht_item *item);

    int32_t get_hash(const std::string &key, const int32_t num_buckets, const int32_t attempt);
    
  public:
    // Constructor
    HashTable(ProbingStrategy strat = ProbingStrategy::DOUBLE_HASHING);
    HashTable(int32_t base_size, ProbingStrategy strat = ProbingStrategy::DOUBLE_HASHING);
    
    // Desctructor
    ~HashTable();

    std::string *search(const std::string &key);
    void insert(const std::string &key, const std::string &value);
    void remove(const std::string &key);

    void display(const std::string msg = "Hash Table contents");

};
