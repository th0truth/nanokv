#include <iostream>
#include <string>

#include "hash_table.h"
using namespace std;

int main() {
  HashTable db;
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
