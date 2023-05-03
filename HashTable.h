/*****************************************************************************
*    Brian Chairez                                                           *
*    Goal: Implementation of Hash Table using a vector of lists of pairs     *
*****************************************************************************/

// Default Bucket Size Starts at 5. No tolerance for collisions: Collisions lead to resizing and rehashing the whole table.
// Collision tolerance can be adjusted in the insert() function by adjusting how many pair-nodes you allow in the list for each respective bucket.

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <utility>  //std::pair

template <class K, class V>
class HashTable {
    private:
        std::vector<std::list<std::pair<K, V>>> hash_table_;

        void rehash_();
    public:
        HashTable();
        HashTable(const HashTable<K, V>& other);
        ~HashTable();
        HashTable<K,V>& operator=(const HashTable<K, V>& other);
        int hash(const K& key) const;
        void insert(const std::pair<K, V>& data);
        void erase(const K& key);
        void clear();
        bool contains(const K& key) const;
        bool empty() const;
        int bucket_count() const;
        int size() const;
};

#endif
