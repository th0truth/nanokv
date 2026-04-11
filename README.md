# NanoKV

A high-performance, in-memory key-value data store implemented entirely from scratch in C++. 

NanoKV provides a robust implementation of two primary hash table architectures: **Open Addressing** (with pluggable probing strategies) and **Chaining** (using linked lists). This project serves as a foundational example of low-level data structure design, manual memory management, and algorithmic optimization in modern C++.

## Architecture & Capabilities

*   **Dual Collision Resolution Architectures:**
    *   **Open Addressing:** Stores all elements directly in the hash table array.
        *   **Double Hashing (Default):** Uses a secondary hash function for the step size to eliminate primary clustering.
        *   **Linear Probing:** Checks sequential slots to resolve collisions.
        *   **Quadratic Probing:** Uses a quadratic function to determine the step size, reducing primary clustering.
    *   **Chaining:** Each bucket in the hash table contains a linked list (`std::list`) of all items that hash to the same index.
*   **Collision Reporting (New!):** Actively monitors and reports the number of collisions/probes required for each insertion, allowing for real-time analysis of hash function efficiency.
*   **Dynamic Auto-Resizing (Open Addressing):** Monitors the load factor and automatically resizes the underlying array (expanding at >70% load, shrinking at <10% load) to maintain optimal $O(1)$ amortized time complexity.
*   **Prime-Sized Buckets:** Automatically calculates and enforces prime number capacities to guarantee that probe sequences can visit every available slot.
*   **Complete CRUD Operations:** Supports fully functional Create, Read, Update, and Delete operations via an interactive shell.
*   **RAII Memory Management:** Ensures safe memory allocation and prevents leaks during table destruction and resizing operations.

## Building and Installation

### Prerequisites
*   A C++11 compatible compiler (e.g., `g++`, `clang++`)
*   `make` build system

### Compilation
Clone the repository and compile the source code using the provided Makefile:

```bash
make clean
make
```

## Usage

NanoKV includes an interactive command-line interface. You can specify the storage and collision resolution strategy as a command-line argument.

| Command | Strategy | Best For |
| :--- | :--- | :--- |
| `./build/nanokv DOUBLE` | **Double Hashing** (Default) | General purpose, avoids clustering. |
| `./build/nanokv LINEAR` | **Linear Probing** | Cache performance, simple to implement. |
| `./build/nanokv QUADRATIC` | **Quadratic Probing** | Reduces primary clustering. |
| `./build/nanokv CHAINING` | **Chaining** | Handles high load factors gracefully. |
| `./build/nanokv LIST` | **Singly Linked List** | O(N) search, simple linked structure. |

### Data Representation

Here is how different strategies represent your data internally when using the `DISPLAY` command:

| Mode | Internal Data Representation Example |
| :--- | :--- |
| **HASH TABLE** | `[0]: (null), [1]: {k: "id", v: "101"}, [2]: (null), ...` |
| **CHAINING** | `[0]: {k: "a", v: "1"} -> {k: "b", v: "2"} -> NULL, [1]: (null), ...` |
| **LIST** | `[id: 101] -> [name: Alice] -> [status: Active] -> NULL` |

### Interactive Shell Commands

```text
=== NanoKV ===
Commands: SET <key> <value> | GET <key> | DEL <key> | DISPLAY | EXIT

db> SET user:1 Alice
OK
db> SET user:2 Bob
[Probe Info] Inserted 'user:2' after resolving 1 collisions.
OK
db> DISPLAY
Current Hash Table State: (Count: 2, Size: 53)
...
db> GET user:1
"Alice"
db> DEL user:1
OK
db> EXIT
```

## Integration Example

NanoKV can be integrated directly into other C++ projects.

```cpp
#include <iostream>
#include <string>
#include "hash_table.h"
#include "chaining_hash_table.h"

int main() {
  // Option 1: Open Addressing (Double Hashing)
  HashTable db_open(ProbingStrategy::DOUBLE_HASHING);
  db_open.insert("type", "open_addressing");

  // Option 2: Chaining
  ChainingHashTable db_chain(50);
  db_chain.insert("type", "chaining");

  return 0;
}
```
