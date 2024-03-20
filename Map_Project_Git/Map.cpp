// Map.cpp
#include "Map.h"

Map::Map() : head(nullptr), tail(nullptr), m_size(0) {}

Map::~Map() {
    clear();
}

Map::Map(const Map& other) : head(nullptr), tail(nullptr), m_size(0) {deepCopy(other);}
Map& Map::operator=(const Map& other) {
    if (this != &other) {clear(); deepCopy(other);}
    return *this;}

bool Map::empty() const {return m_size == 0;}

int Map::size() const {return m_size;}

bool Map::insert(const std::string& key, double value) {
  
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->key == key) { std::cout << "Key: " << key << "' already exists in the map." << std::endl; return false;}
        curr = curr->next;
    }

  
    Node* newNode = new Node(key, value);
    if (empty()) {
        head = newNode;}
    else {
        tail->next = newNode;
        newNode->prev = tail;}
    tail = newNode;
    m_size++;
std::cout << "Inserted key '" << key << "' with value " << value << " into the map." << std::endl;
    return true;}
bool Map::update(const std::string& key, double value)
{
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->key == key) {
            curr->value = value;
            return true;
        }
        curr = curr->next;
    }    return false;}


bool Map::insertOrUpdate(const std::string& key, double value) {

    Node* curr = head;
    while (curr != nullptr) {
        if (curr->key == key) {
         
            curr->value = value; return true;}
        curr = curr->next;
    }

    Node* newNode = new Node(key, value);
    if (empty()) {
        head = newNode;}
    else { tail->next = newNode;
        newNode->prev = tail; }
    tail = newNode;
    m_size++; return true;}

bool Map::erase(const std::string& key) {

    Node* curr = head;
    while (curr != nullptr) {
        if (curr->key == key) {
           
            if (curr->prev != nullptr) {
                curr->prev->next = curr->next;
            } else {
                head = curr->next;
            }
            if (curr->next != nullptr) { curr->next->prev = curr->prev;}
            else {tail = curr->prev;}
            delete curr;
            m_size--;
            return true;}
        curr = curr->next;}
    return false;}

bool Map::contains(const std::string& key) const {
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->key == key) {return true;}
        curr = curr->next; }
    return false;}

bool Map::get(const std::string& key, double& value) const {
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->key == key) {
            value = curr->value;
            return true;}
        curr = curr->next;
    }
    return false;}

bool Map::get(int i, std::string& key, double& value) const {
    if (i < 0 || i >= m_size) {return false;}
    Node* curr = head;
    for (int j = 0; j < i; j++) {curr = curr->next;}

    key = curr->key;
    value = curr->value;
    return true;
}



void Map::swap(Map& other) {
    Node* temp_head = head;
    head = other.head;
    other.head = temp_head;
    
    Node* temp_tail = tail;
    tail = other.tail;
    other.tail = temp_tail;
    
    
    std::swap(m_size, other.m_size);
    
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->prev == other.head) {curr->prev = head;}
        else {curr->prev = other.head;}
        curr = curr->next;
    }
    
    curr = other.head;
    while (curr != nullptr) {
        if (curr->prev == head) {
            curr->prev = other.head;
        } else {
            curr->prev = head;
        }
        curr = curr->next;
    }}

bool combine(const Map& m1, const Map& m2, Map& result) {
    for (int i = 0; i < m1.size(); ++i) {
        std::string key;
        double value;
        if (m1.get(i, key, value)) { result.insertOrUpdate(key, value);}
    }
    for (int i = 0; i < m2.size(); ++i) {
        std::string key;
        double value;
        if (m2.get(i, key, value)) { result.insertOrUpdate(key, value);} }
    return true;}

void subtract(const Map& m1, const Map& m2, Map& result) {
    for (int i = 0; i < m1.size(); ++i) {
        std::string key;
        double value;
        if (m1.get(i, key, value)) {
            if (!m2.contains(key)) {
                result.insert(key, value);}
  }
 }
}

void Map::dump() const {
    Node* curr = head;
    std::cout << "Dumping Map:" << std::endl;
    while (curr != nullptr) {
std::cout << "Key: " << curr->key << ", Value: " << curr->value << std::endl; curr = curr->next;}
std::cout << "End of Map dump." << std::endl;}

void Map::deepCopy(const Map& other) {
    clear();
    Node* curr = other.head;
    while (curr != nullptr) {insert(curr->key, curr->value); curr = curr->next;}
}
void Map::clear() {
    while (head != nullptr) {Node* temp = head; head = head->next; delete temp;} tail = nullptr; m_size = 0;}


void testMap() {
    Map map;
    assert(map.empty());
    assert(map.size() == 0);
    assert(map.insert("A", 88));
    assert(map.insert("B", 44));
    assert(map.insert("C", 88));
    assert(!map.insert("A", 20));
    assert(map.size() == 3);
    assert(!map.empty());
    double v;
    assert(map.update("A", 20));
    bool result = map.get("A", v);
    assert(result && v == 20);
    assert(!map.update("D", 36));
    assert(map.insertOrUpdate("D", 36));
    assert(map.get("D", v) && v == 36);
    assert(map.insertOrUpdate("B", 21));
    assert(map.get("B", v) && v == 21);
    assert(map.erase("C"));
    assert(!map.contains("C"));
    assert(map.contains("A"));
    assert(!map.contains("C"));
    double value;
    assert(map.get("B", value) && value == 21);
    assert(!map.get("E", value));
    std::string key;
    assert(map.get(0, key, value));
    assert((key == "A" && value == 20) || (key == "B" && value == 21) || (key == "D" && value == 36));
    assert(!map.get(3, key, value));
    Map map2;
    map2.insert("X", 100);
    map2.insert("Y", 200);
    map.swap(map2);
    assert(map.update("Y", 20));
    map.clear();
    assert(map.empty());}

void testSubtract() {
    Map m1, m2, result;
    m1.insert("Fred", 342);
    m1.insert("Ethel", 543);
    m1.insert("Lucy", 678);

    m2.insert("Lucy", 145);
    m2.insert("Ricky", 432);

    subtract(m1, m2, result);

    assert(result.contains("Fred") && result.contains("Ethel"));
    assert(!result.contains("Lucy") && !result.contains("Ricky"));

    assert(result.size() == 2);
}
void testCombine() {
    Map m1, m2, result;
    m1.insert("Fred", 342);
    m1.insert("Ethel", 543);
    m2.insert("Lucy", 678);
    m2.insert("Ricky", 432);

    assert(combine(m1, m2, result));

    assert(result.contains("Fred") && result.contains("Ethel") &&
           result.contains("Lucy") && result.contains("Ricky"));

    assert(result.size() == 4);
}

int main() {
    testMap();
    testCombine();
    testSubtract();

    std::cout << "All tests passed." << std::endl;
    return 0;
}
