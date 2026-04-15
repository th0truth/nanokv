#include <iostream>
#include <string>

#include "hash_table.h"
#include "chaining_hash_table.h"
#include "singly_linked_list.h"
#include "doubly_linked_list.h"
#include "circular_linked_list.h"
#include "stack.h"
#include "repl.h"

using namespace std;

int main(int argc, char **argv)
{
  ProbingStrategy strategy = ProbingStrategy::DOUBLE_HASHING; 
  bool use_chaining = false;
  bool use_list = false;
  bool use_double_list = false;
  bool use_circular_list = false;
  bool use_stack = false;

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
    } else if (strat_argv == "LIST") {
      use_list = true;
      cout << "Using strategy: SINGLY LINKED LIST (O(N) Search)\n" << endl;
    } else if (strat_argv == "DOUBLE_LIST") {
      use_double_list = true;
      cout << "Using strategy: DOUBLY LINKED LIST\n" << endl;
    } else if (strat_argv == "CIRCULAR_LIST") {
      use_circular_list = true;
      cout << "Using strategy: CIRCULAR LINKED LIST\n" << endl;
    } else if (strat_argv == "STACK") {
      use_stack = true;
      cout << "Using strategy: STACK\n" << endl;
    } else {
      cout << "Error: Unknown strategy '" << strat_argv << "'" << endl;
      cout << "Usage: ./build/nanokv [LINEAR | QUADRATIC | DOUBLE | CHAINING | LIST | DOUBLE_LIST | CIRCULAR_LIST | STACK]\n" << endl;
      return 1;
    }
  } else {
    cout << "Using default strategy: DOUBLE HASHING\n";
  }

  if (use_stack) {
    Stack<string> db(100);
    run_stack_repl(db);
  } else if (use_circular_list) {
    CircularLinkedList db;
    run_repl(db);
  } else if (use_double_list) {
    DoublyLinkedList db;
    run_repl(db);
  } else if (use_list) {
    SinglyLinkedList db;
    run_repl(db);
  } else if (use_chaining) {
    ChainingHashTable db(50);
    run_repl(db);
  } else {
    HashTable db(strategy);
    run_repl(db);
  }

  return 0;
}
