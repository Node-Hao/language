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
    public:
        Key key;
        Value value;
        // 从 key 构造节点
        explicit HashNode(const Key &key) : key(key), value() {};
        // 从 key 和 value 构造节点
        HashNode(const Key &key, const Value &value) : key(key), value(value) {}
        // 比较重载运算符
        bool operator==(const HashNode &other) const { return key == other.key; }
        bool operator!=(const HashNode &other) const { return key != other.key; }
        bool operator<(const HashNode &other) const { return key < other.key; }  // 修复缺少的闭合括号
        bool operator>(const HashNode &other) const { return key > other.key; }  // 修复比较逻辑错误
        bool operator==(const Key &key_) const { return key == key_; }
        
        void print() const
        {
            std::cout << key << " " << value << " ";
        }
    };
private:
    using Bucket = std::list<HashNode>;  // 定义桶的类型为存储键的链表
    std::vector<Bucket> buckets;  // 定义所有桶的动态数组
    Hash hashFunction;  // 哈希函数对象
    size_t tableSize;  // 哈希表的大小
    size_t numElements;  // 哈希表中元素的数量

    float maxLoadFactor = 0.75;  // 默认的最大负载因子

    // 计算键的哈希值，并将其映射到桶的索引
    size_t hash(const Key &key) const { return hashFunction(key) % tableSize; }
    
    // 当元素数量超过最大负载因子定义的容量时，增加桶的数量并重新分配所有键
    void rehash(size_t newSize)
    {
        if (newSize == 0) return;  // 避免无效的新大小
        std::vector<Bucket> newBuckets(newSize);  // 创建新的桶数组

        for (Bucket& bucket : buckets)  // 遍历旧桶数组
        {
            for (HashNode& hashNode : bucket)  // 遍历桶中的节点
            {
                size_t newIndex = hashFunction(hashNode.key) % newSize;
                newBuckets[newIndex].push_back(hashNode);
            }
        }
        buckets = std::move(newBuckets);  // 使用移动语义更新桶数组
        tableSize = newSize;  // 更新哈希表大小
    }

public:
    // 构造函数初始化哈希表
    HashTable(size_t size = 10, const Hash& hashFunc = Hash())
        : buckets(size), hashFunction(hashFunc), tableSize(size), numElements(0) {}

    // 插入键值对到哈希表中
    void insert(const Key& key, const Value& value)
    {
        // 检查是否需要重哈希
        if ((numElements + 1) > maxLoadFactor * tableSize)
        {
            // 处理 clear 后再次插入元素时 tableSize = 0 的情况
            if (tableSize == 0) tableSize = 1;
            rehash(tableSize * 2);  // 重哈希, 桶数量翻倍
        }
        size_t index = hash(key);  // 计算桶的索引
        std::list<HashNode>& bucket = buckets[index];  // 获取对应的桶
        // 如果键不在桶中，则添加到桶中
        if (std::find(bucket.begin(), bucket.end(), key) == bucket.end())
        {
            bucket.push_back(HashNode(key, value));
            ++numElements;  // 增加元素数量（修复注释错误）
        }
    }
    
    void insertKey(const Key& key) { insert(key, Value{}); }

    // 从哈希表中删除键
    void erase(const Key& key)  // 修复返回值错误
    {
        if (tableSize == 0) return;  // 空表直接返回
        size_t index = hash(key);  // 计算键的索引
        auto& bucket = buckets[index];  // 获取对应的桶
        // 查找键是否在桶中
        auto it = std::find(bucket.begin(), bucket.end(), key);
        if (it != bucket.end())
        {
            bucket.erase(it);  // 执行删除操作
            --numElements;     // 更新元素数量
        }
    }

    // 查找键是否存在于哈希表中
    Value* find(const Key &key)
    {
        if (tableSize == 0) return nullptr;  // 空表直接返回
        size_t index = hash(key);
        auto& bucket = buckets[index];
        // 查找键是否在桶中
        auto it = std::find(bucket.begin(), bucket.end(), key);
        if (it != bucket.end())
        {
            return &it->value;
        }
        return nullptr;
    }
    
    // 获取哈希表中元素的数量
    size_t size() const { return numElements; }

    // 打印哈希表中的所有元素
    void print() const
    {
        for (size_t i = 0; i < buckets.size(); ++i)
        {
            if (!buckets[i].empty())  // 只打印非空桶
            {
                for (const HashNode& node : buckets[i])
                {
                    node.print();
                }
            }
        }
        std::cout << std::endl;
    }
    
    void clear()
    {
        buckets.clear();  // 修复成员名拼写错误
        numElements = 0;
        tableSize = 0;
    }
};