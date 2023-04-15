# data-structure-hash-table

Created by Brian Chairez

This C++ project implements the hash table data stucture using std::vector, std::list, and std::pair.
The vector, where every index can hold a list of pairs, acts as the number of buckets available for hashing into.
The list, which holds (the chain of) pairs, acts as the fail-safe in case a collision during hashing. Tolerance is adjustable.
The pair acts as the container for the key/value data pair.

Since the hash table follows the key/value structure, no duplicate key values are allowed to be inserted.
This is a rather simple implementation meaning only numerical data types are currerntly supported as keys.
Will update to be able to support characters and strings soon.
