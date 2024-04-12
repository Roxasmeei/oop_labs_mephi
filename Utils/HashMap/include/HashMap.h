#pragma once


#include <iostream>
#include <memory>
#include <utility>

template<typename KeyType, typename ValueType, typename Hash = std::hash<KeyType>>
class HashTable {

private:

    struct Node {
        KeyType key;
        ValueType value;
        bool empty = true;

        Node() = default;


        Node(const KeyType &k, const ValueType &v) : key(k), value(v), empty(false) {}
    };


    size_t table_size = 0;
    size_t cur_size = 0;
    Node *table;
    Hash hasher;

public:

    HashTable(const HashTable &other) : table_size(other.table_size), cur_size(other.cur_size), hasher(other.hasher) {
        table = new Node[table_size];
        try {
            for (size_t i = 0; i < table_size; ++i) {
                table[i] = other.table[i];
            }

        } catch (...) {

            delete[] table;
            throw;
        }
    }


    HashTable &operator=(const HashTable &other) {
        if (this != &other) {


            auto tmp = new Node[other.table_size];

            try {
                for (size_t i = 0; i < other.table_size; ++i) {
                    tmp[i] = other.table[i];
                }
            } catch (...) {
                delete[] tmp;
                throw;
            }


            table_size = other.table_size;
            cur_size = other.cur_size;
            hasher = other.hasher;

            delete[] table;
            table = tmp;

        }
        return *this;
    }

    HashTable(HashTable &&other) noexcept: table_size(other.table_size), cur_size(other.cur_size),  hasher(std::move(other.hasher)) {
        table = other.table;
        other.table = nullptr;
        other.table_size = 0;
        other.cur_size = 0;
    }

    HashTable &operator=(HashTable &&other) noexcept {
        if (this != &other) {
            delete[] table;

            table_size = other.table_size;
            cur_size = other.cur_size;
            hasher = std::move(other.hasher);

            table = other.table;
            other.table = nullptr;
            other.table_size = 0;
            other.cur_size = 0;
        }
        return *this;
    }


    size_t hashFunction(const KeyType &key) const {
        return hasher(key) % table_size;
    }


public:


    explicit HashTable(size_t size) : table_size(size), cur_size(0),
                                      table(new Node[table_size]()) {} //  0 по умолчанию значегие размера

    ~HashTable();

public:

    [[nodiscard]] bool IsEmpty() const;

    bool insert(KeyType key, ValueType value); // конста ссылка?

    bool contains(const KeyType &key) const;


    bool remove(const KeyType &key);

    size_t getTableSize() const { return table_size; } // const

    size_t getCurSize() const { return cur_size; }// const

    Node &getAtIndex(size_t index) {
        return table[index];
    }


public:


    template<bool is_const>
    class Iterator {
    public:
        using ptr = std::conditional_t<is_const, const Node, Node> *;
        using reference = std::conditional_t<is_const, const Node, Node> &;
        using iterator_category = std::forward_iterator_tag;
        using iterator = Iterator<false>;
        using const_iterator = Iterator<true>;
        using difference_type = ptrdiff_t;
        using value_type = ValueType;

    private:

        ptr node;


        explicit Iterator(ptr _node) : node(_node) {}

        friend HashTable<KeyType, ValueType, Hash>;

        friend Iterator<!is_const>;


    public:
        template<bool other_const>
        explicit Iterator(Iterator<other_const> &o) requires (is_const >= other_const) : node(o.node) {}

        template<bool other_const>
        Iterator &operator=(const Iterator<other_const> &o)requires (is_const >= other_const) {
            node = o.node;
            return *this;
        }


        Iterator() noexcept: node(nullptr) {};


        Iterator &operator++() noexcept {
            ++node;
            return *this;
        }

        Iterator operator++(int) noexcept {
            Iterator temp(node);
            ++node;
            return temp;
        }

        Iterator &operator--() noexcept {
            --node;
            return *this;
        }

        Iterator operator--(int) noexcept {
            Iterator res(node);
            --node;
            return res;
        };

        Node operator*() const noexcept {
            return (*node);
        }

        ptr operator->() const noexcept {
            return node;
        }

        bool operator!=(const Iterator<is_const> &other) const noexcept {
            return node != other.node;
        }

        bool operator==(const Iterator<is_const> &other) const noexcept {
            return node == other.node;
        }


    };

    Iterator<false> begin() noexcept {
        return Iterator<false>(&table[0]);
    }

    Iterator<false> end() noexcept {
        return Iterator<false>(&table[table_size]); //  было nullptr
    }

    Iterator<true> begin() const noexcept {
        return Iterator<true>(&table[0]);
    }

    Iterator<true> end() const noexcept {
        return Iterator<true>(&table[table_size]); //  было nullptr
    }

    Iterator<true> find(const KeyType &key) const;



//
//    static_assert(std::forward_iterator<Iterator<false>>);
//    static_assert(std::forward_iterator<Iterator<true>>);


};


template<typename KeyType, typename ValueType, typename Hash>
bool HashTable<KeyType, ValueType, Hash>::IsEmpty() const {
    return cur_size == 0;
}

//template<typename KeyType, typename ValueType, typename Hash>
//void HashTable<KeyType, ValueType, Hash>::output() const {
//
//    for (auto tmp = begin(); tmp != end(); tmp++) {
//        if (!tmp->empty) {
//            std::cout << "Key: " << tmp->key << ", Value: " << tmp->value << std::endl;
//        } else {
//            std::cout << "Empty" << std::endl;
//        }
//    }
//}


template<typename KeyType, typename ValueType, typename Hash>
bool HashTable<KeyType, ValueType, Hash>::insert(KeyType key, ValueType value) {

    if (cur_size == table_size) {
        return false;
    }

    if (contains(key)) return false; // trying to add an element with an already existing key

    size_t index = hashFunction(key);

    if (!table[index].empty) {
        while (!table[index].empty) {
            index = (index + 1) % table_size;
        }
    }


    table[index] = Node(std::move(key), std::move(value));

    cur_size++;

    return true;
}

template<typename KeyType, typename ValueType, typename Hash>
bool HashTable<KeyType, ValueType, Hash>::contains(const KeyType &key) const {

    if (cur_size == 0) return false;
    size_t k = 0;
    for (size_t i = 0; k < cur_size; i++) {
        if (!table[i % table_size].empty) {
            if (table[i % table_size].key == key) return true;
            k++;
        }
    }

    return false;
}

template<typename KeyType, typename ValueType, typename Hash>
HashTable<KeyType, ValueType, Hash>::Iterator<true>
HashTable<KeyType, ValueType, Hash>::find(const KeyType &key) const { // итератор

    if (cur_size == 0) return Iterator<true>(nullptr);
    size_t k = 0;
    for (size_t i = 0; k < cur_size; i++) {
        if (!table[i % table_size].empty) {
            if (table[i % table_size].key == key) return Iterator<true>(&table[i % table_size]);
            k++;
        }
    }

    return Iterator<true>(nullptr);
}


template<typename KeyType, typename ValueType, typename Hash>
bool HashTable<KeyType, ValueType, Hash>::remove(const KeyType &key) {
    if (cur_size == 0) return false;


    size_t index = hashFunction(key);
    size_t originalIndex = index;


    while (true) {
        if (!table[index].empty && table[index].key == key) {
            table[index] = Node();
            cur_size--;
            return true;
        }
        index = (index + 1) % table_size;
        if (index == originalIndex) break;
    }

    return false;
}


template<typename KeyType, typename ValueType, typename Hash>
HashTable<KeyType, ValueType, Hash>::~HashTable() {
    delete[] table;
}