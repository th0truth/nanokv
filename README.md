# NanoKV

A high-performance, in-memory key-value data store implemented entirely from scratch in C++. 

NanoKV provides a robust implementation of a dynamically resizing hash table, utilizing open addressing and double hashing for efficient collision resolution. Built without reliance on standard library container abstractions, this project serves as a foundational example of low-level data structure design, manual memory management, and algorithmic optimization in modern C++.

## Architecture & Capabilities

*   **Custom Hash Implementation:** Features a custom string hashing algorithm implementing Horner's method for efficient and uniform key distribution.
*   **Double Hashing:** Resolves collisions using Open Addressing with a secondary hash function, virtually eliminating primary clustering and ensuring efficient probe sequences.
*   **Dynamic Auto-Resizing:** Actively monitors the load factor and automatically resizes the underlying array (expanding at >70% load, shrinking at <10% load) to maintain optimal $O(1)$ amortized time complexity.
*   **Prime-Sized Buckets:** Automatically calculates and enforces prime number capacities for the bucket array, a mathematical requirement to guarantee that the double-hashing probe sequence can visit every available slot.
*   **Complete CRUD Operations:** Supports fully functional Create, Read, Update, and Delete operations via an interactive shell.
*   **RAII Memory Management:** Leverages C++ class encapsulation and standard library strings to ensure safe memory allocation and prevent leaks during table destruction and resizing operations.

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

NanoKV includes an interactive command-line interface, operating similarly to a lightweight Redis shell. 

To start the interface, execute the compiled binary:
```bash
./build/nanokv
```

### Interactive Shell Commands

```text
=== NanoKV Interactive Shell ===
Commands: SET <key> <value> | GET <key> | DEL <key> | EXIT

db> SET user:1 Alice
OK
db> SET user:2 Bob
OK
db> GET user:1
"Alice"
db> DEL user:1
OK
db> GET user:1
(nil)
db> EXIT
```

## Integration Example

NanoKV can also be integrated directly into other C++ projects by including the core data structure.

```cpp
#include <iostream>
#include <string>
#include "hash_table.h"

int main() {
  // Initialize the data store
  HashTable db;

  // Create records
  db.insert("service_status", "initializing");
  db.insert("max_connections", "100");

  // Update existing records
  db.insert("service_status", "running");

  // Retrieve records
  std::string* status = db.search("service_status");
  if (status) {
    std::cout << "Status: " << *status << std::endl; 
  }

  // Delete records
  db.remove("max_connections");

  return 0;
}
```
