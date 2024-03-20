// Map.h
#ifndef MAP_H
#define MAP_H

#include <string>
#include <cassert>
#include <iostream>

using KeyType = std::string;
using ValueType = double;

class Map {
public:
    Map();
    ~Map();
    Map(const Map& other);
    Map& operator=(const Map& other);

    bool empty() const;
    int size() const;
    bool insert(const std::string& key, double value);
    bool update(const std::string& key, double value);
    bool insertOrUpdate(const std::string& key, double value);
    bool erase(const std::string& key);
    bool contains(const std::string& key) const;
    bool get(const std::string& key, double& value) const;
    bool get(int i, std::string& key, double& value) const;
    void swap(Map& other);
    void dump() const;
    void clear();
    void combine(const Map& m1, const Map& m2, Map& result);
    void subtract(const Map& m1, const Map& m2, Map& result);
    void deepCopy(const Map& other);
private:
    struct Node {
            std::string key;
            double value;
            Node* prev;
            Node* next;
            Node(const std::string& k, double v) : key(k), value(v), prev(nullptr), next(nullptr) {}
        };
    Node* head;
    Node* tail;
    int m_size;};
#endif // MAP_H
