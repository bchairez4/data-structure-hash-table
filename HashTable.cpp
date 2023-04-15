#include "HashTable.h"

#define DEFAULT_BUCKET_COUNT 5

/*****************************************************************************
    Constructors/Destructor
*****************************************************************************/

template <class K, class V>
HashTable<K, V>::HashTable() : hash_table_(DEFAULT_BUCKET_COUNT) {}

template <class K, class V>
HashTable<K, V>::HashTable(const HashTable<K, V>& other) : hash_table_(other.bucket_count()) {
    hash_table_ = other.hash_table_;
}

template <class K, class V>
HashTable<K, V>::~HashTable() {
    clear();
}

/*****************************************************************************
    Operator Overload
*****************************************************************************/
template <class K, class V>
HashTable<K, V>& HashTable<K, V>::operator=(const HashTable<K, V>& other) {
    hash_table_ = other.hash_table_;
}

/*****************************************************************************
    Data Modification
*****************************************************************************/
template <class K, class V>
int HashTable<K, V>::hash(const K& key) const {
    return (int(key) % bucket_count());
}

template <class K, class V>
void HashTable<K, V>::insert(const std::pair<K, V>& pair) {
    if (contains(pair.first)) {
        return;
    }

    if (!hash_table_[hash(pair.first)].empty()) {       //adjust collision tolerance here
        rehash_();
    }
    
    hash_table_[hash(pair.first)].push_back(pair);
}

template <class K, class V>
void HashTable<K, V>::erase(const K& key) {
    if (!contains(key)) {
        return;
    }

    typename std::list<std::pair<K, V>>::const_iterator it = hash_table_[hash(key)].begin();
    while ((*it).first != key) {
        ++it;
    }

    hash_table_[hash(key)].erase(it);
}

template <class K, class V>
void HashTable<K, V>::clear() {
    for (int i = 0; i < hash_table_.size(); ++i) {
        if (!hash_table_[i].empty()) {
            hash_table_[i].clear();
        }
    }

    hash_table_.clear();
}

/*****************************************************************************
    Data Observation
*****************************************************************************/
template <class K, class V>
bool HashTable<K, V>::contains(const K& key) const {
    if (empty()) {
        return false;
    }

    if (hash_table_[hash(key)].empty()) {
        return false;
    }

    typename std::list<std::pair<K, V>>::const_iterator it = hash_table_[hash(key)].begin();
    while (it != hash_table_[hash(key)].end()) {
        if ((*it).first == key) {
            return true;
        }

        ++it;
    }

    return false;
}

template <class K, class V>
bool HashTable<K, V>::empty() const {
    return size() == 0;
}

template <class K, class V>
int HashTable<K, V>::bucket_count() const {
    return hash_table_.size();
}

template <class K, class V>
int HashTable<K, V>::size() const {
    int size = 0;

    for (int i = 0; i < bucket_count(); ++i) {
        if (!hash_table_[i].empty()) {
            ++size;
        }
    }

    return size;
}

template <class K, class V>
void HashTable<K, V>::print() const {
    for (int i = 0; i < bucket_count(); ++i) {
        if (!hash_table_[i].empty()) {
            std::cout << "Bucket[" << i << "]: ";
            typename std::list<std::pair<K,V>>::const_iterator it = hash_table_[i].begin();
            while (it != hash_table_[i].end()) {
                std::cout << "Key: " << (*it).first << " "
                          << "Value: " << (*it).second;
                ++it;
            }
            std::cout << '\n';
        }
    }
}

/*****************************************************************************
    Private Functions
*****************************************************************************/
template <class K, class V>
void HashTable<K, V>::rehash_() {
    int new_size = bucket_count() * 2;
    std::vector<std::list<std::pair<K, V>>> temp_hash_table(new_size);

    for (int i = 0; i < bucket_count(); ++i) {
        if (!hash_table_[i].empty()) {
            typename std::list<std::pair<K, V>>::const_iterator it = hash_table_[i].begin();
            while (it != hash_table_[i].end()) {
                temp_hash_table[hash((*it).first)].push_back((*it));
                ++it;
            }
        }
    }

    hash_table_.swap(temp_hash_table);
}