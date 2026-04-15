#include <iostream>
#include <string>
#include "stack.h"
#include "queue.h"

using namespace std;

template <typename T>
void run_repl(T& db)
{
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
      db.display("Current State: ");
    } else {
      cout << "Error: Unknown command '" << command << "'\n";
      cin.ignore(10000, '\n');  // clear line
    }
  }
}

template <typename T>
void run_stack_repl(Stack<T>& stack)
{
  string command, value;

  cout << "=== NanoKV (Stack Mode) ===\n";
  cout << "Commands: PUSH <value> | POP | TOP | SIZE | DISPLAY | EXIT\n\n";

  while (true) {
    cout << "stack> ";
    if (!(cin >> command)) break;

    if (command == "EXIT" || command == "exit") {
      break;
    } else if (command == "PUSH" || command == "push") {
      cin >> value;
      if (stack.push(value)) {
        cout << "OK\n";
      } else {
        cout << "Error: Stack is full\n";
      }
    } else if (command == "POP" || command == "pop") {
      if (stack.pop()) {
        cout << "OK\n";
      } else {
        cout << "Error: Stack is empty\n";
      }
    } else if (command == "TOP" || command == "top") {
      if (!stack.isEmpty()) {
        cout << "\"" << stack.top() << "\"\n";
      } else {
        cout << "(empty)\n";
      }
    } else if (command == "SIZE" || command == "size") {
      cout << stack.size() << " / " << stack.getCapacity() << "\n";
    } else if (command == "DISPLAY" || command == "display") {
      stack.display("Current Stack State:");
    } else {
      cout << "Error: Unknown command '" << command << "'\n";
      cin.ignore(10000, '\n');  // clear line
    }
  }
};

template <typename T>
void run_queue_repl(Queue<T>& queue)
{
  string command, value;

  cout << "=== NanoKV (Queue Mode) ===\n";
  cout << "Commands: ENQUEUE <value> | DEQUEUE | FRONT | SIZE | DISPLAY | EXIT\n\n";

  while (true) {
    cout << "queue> ";
    if (!(cin >> command)) break;

    if (command == "EXIT" || command == "exit") {
      break;
    } else if (command == "ENQUEUE" || command == "enqueue") {
      cin >> value;
      if (queue.enqueue(value)) {
        cout << "OK\n";
      } else {
        cout << "Error: Queue is full\n";
      }
    } else if (command == "DEQUEUE" || command == "dequeue") {
      if (queue.dequeue()) {
        cout << "OK\n";
      } else {
        cout << "Error: Queue is empty\n";
      }
    } else if (command == "FRONT" || command == "front") {
      if (!queue.isEmpty()) {
        cout << "\"" << queue.front() << "\"\n";
      } else {
        cout << "(empty)\n";
      }
    } else if (command == "SIZE" || command == "size") {
      cout << queue.size() << " / " << queue.getCapacity() << "\n";
    } else if (command == "DISPLAY" || command == "display") {
      queue.display("Current Queue State:");
    } else {
      cout << "Error: Unknown command '" << command << "'\n";
      cin.ignore(10000, '\n');  // clear line
    }
  }
}

