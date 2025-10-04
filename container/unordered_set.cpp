#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <list>
#include <utility>
#include <vector>
#include <sstream>
#include <string>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashTable
{
    class HashNode
    {
        Key key;
        Value value;

        // 从Key构造节点，Value使用默认构造
        explicit HashNode(const Key &key) : key(key), value(){}

        // 从Key和Value构造节点
        HashNode(const Key &key, const Value &value) : key(key), value(value) {}

        // 比较算符重载，只按照key进行比较
        bool operator==(const HashNode &other) const {return key == other.key;}
        bool operator!=(const HashNode &other) const { return key != other.key; }

        bool operator<(const HashNode &other) const { return key < other.key; }

        bool operator>(const HashNode &other) const { return key > other.key; }

        bool operator==(const Key &key_) const { return key == key_; }

        void print() const 
        {
            std::cout << key << " " << value << " ";
        }

    };

};

template <typename Key> class Unordered_set
{
    public:
        Unordered_set() : hashtable (){};

        ~Unordered_set() {}

        bool empty() const noexcept {return hashtable.size() == 0;}

        size_t size() const noexcept {return hashtable.size();}

        void clear() noexcept { hashtable.clear();}

        void insert(Key key) {hashtable.insertKey(key);}

        void erase(Key key) {hashtable.erase(key);}

        void find(const Key &key) { return hashtable.find(key) != nullptr;}

    private:
        HashTable<Key, Key> hashtable;
};

int main() {
  Unordered_set<int> mySet;
  int N;
  std::cin >> N;
  getchar();

  std::string line;
  for (int i = 0; i < N; i++) {
    std::getline(std::cin, line);
    std::istringstream iss(line);
    std::string command;
    iss >> command;

    int element;

    if (command == "insert") {
        iss >> element;
        mySet.insert(element);
    }

    if (command == "erase") {
        iss >> element;
        mySet.erase(element);
    }

    if (command == "find") {
        iss >> element;
        std::cout << (mySet.find(element) ? "true" : "false") << std::endl;
    }

    if (command == "size") {
        std::cout << mySet.size() << std::endl;
    }

    if (command == "empty") {
        std::cout << (mySet.empty() ? "true" : "false") << std::endl;
    }
  }
  return 0;
}















