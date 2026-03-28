#include <iostream>
#include <string>

#include "hash_table.h"
using namespace std;

int main(int argc, char **argv) {
  ProbingStrategy strategy = ProbingStrategy::DOUBLE_HASHING; 

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
    } else {
      cout << "Error: Unknown strategy '" << strat_argv << endl;
      cout << "Usage: ./build/nanokv [LINEAR | QUADRATIC | DOUBLE_HASHING]\n" << endl;
      return 1;
    }
  } else {
    cout << "Using default strategy: DOUBLE HASHING\n";
  }

  HashTable db(strategy);
  string command, key, value;

  cout << "=== NanoKV ===\n";
  cout << "Commands: SET <key> <value> | GET <key> | DEL <key> | EXIT\n\n";

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
      string* result = db.search(key);
      if (result) {
        cout << "\"" << *result << "\"\n";
      } else {
        cout << "(null)\n";
      }
    } else if (command == "DEL" || command == "del") {
      cin >> key;
      db.remove(key);
      cout << "OK\n";
    } else {
      cout << "Error: Unknown command '" << command << "'\n";
      cin.ignore(10000, '\n');  // clear line
    }
  }

  return 0;
}
