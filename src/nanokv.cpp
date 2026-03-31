#include <iostream>
#include <string>

#include "hash_table.h"
#include "chaining_hash_table.h"
using namespace std;

template <typename T>
void run_repl(T& db) {
  string command, key, value;

  cout << "=== NanoKV ===\n";
  cout << "Commands: SET <key> <value> | GET <key> | DEL <key> | DISPLAY | EXIT\n\n";

  while (true) {
    cout << "db> ";
    if (!(cin >> command)) break;

    if (command == "EXIT" || command == "exit") {
      break;
    } else if (command == "SET" || command == "set") {
      cin >> key;
      getline(cin >> ws, value);
      db.insert(key, value);
      cout << "OK\n";
    } else if (command == "GET" || command == "get") {
      cin >> key;
      string *result = db.search(key);
      if (result) {
        cout << "\"" << *result << "\"\n";
      } else {
        cout << "(null)\n";
      }
    } else if (command == "DEL" || command == "del") {
      cin >> key;
      db.remove(key);
      cout << "OK\n";
    } else if (command == "DISPLAY" || command == "display") {
      db.display("Current Hash Table State: ");
    } else {
      cout << "Error: Unknown command '" << command << "'\n";
      cin.ignore(10000, '\n');  // clear line
    }
  }
}

int main(int argc, char **argv) {
  ProbingStrategy strategy = ProbingStrategy::DOUBLE_HASHING; 
  bool use_chaining = false;

  if (argc > 1) {
    string strat_argv = argv[1];

    if (strat_argv == "LINEAR") {
      strategy = ProbingStrategy::LINEAR;
      cout << "Using strategy: LINEAR PROBING\n";
    } else if (strat_argv == "QUADRATIC") {
      strategy = ProbingStrategy::QUADRATIC;
      cout << "Using strategy: QUADRATIC PROBING\n";
    } else if (strat_argv == "DOUBLE") {
      strategy = ProbingStrategy::DOUBLE_HASHING;
      cout << "Using strategy: DOUBLE HASHING\n" << endl;
    } else if (strat_argv == "CHAINING") {
      use_chaining = true;
      cout << "Using strategy: CHAINING\n" << endl;
    } else {
      cout << "Error: Unknown strategy '" << strat_argv << "'" << endl;
      cout << "Usage: ./build/nanokv [LINEAR | QUADRATIC | DOUBLE | CHAINING]\n" << endl;
      return 1;
    }
  } else {
    cout << "Using default strategy: DOUBLE HASHING\n";
  }

  if (use_chaining) {
    ChainingHashTable db(50);
    run_repl(db);
  } else {
    HashTable db(strategy);
    run_repl(db);
  }

  return 0;
}
