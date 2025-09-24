#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <string>

template <typename T>
class Deque
{
private:
    T* elements;       // 存储元素的数组
    size_t capacity;   // 容量（可容纳的最大元素数）
    size_t frontIndex; // 前端元素的索引
    size_t backIndex;  // 后端下一个插入位置的索引
    size_t size;       // 当前元素数量

public:
    // 构造函数
    Deque() : elements(nullptr), capacity(0), frontIndex(0), backIndex(0), size(0) {}
    //拷贝构造函数
    Deque(const Deque& other)\
        :size(other.size),capacity(other.capacity),frontIndex(0),backIndex(other.size)
    {
        elements = new T[capacity];
        if(other.frontIndex == 0)
        {
            std::copy(other.elements, other.elements + size, elements);
        }
        else if(other.frontIndex > other.backIndex)
        {
            std::copy(other.elements + other.frontIndex, other.elements + other.capacity, elements);
            std::copy(other.elements, other.elements + other.backIndex, elements + other.capacity - other.frontIndex);
        }
        else
        {
            std::copy(other.elements + other.frontIndex, other.elements + other.backIndex, elements);
        }
    }
    //赋值构造函数
    //把对方赋值给自己
    Deque& operator=(const Deque& other)
    {
        if(this != &other)
        {
            delete[] elements;
            size = other.size;
            capacity = other.capacity;
            frontIndex = 0;
            backIndex = size;
            elements = new T[capacity];
            if(other.frontIndex == 0)
            {
                std::copy(other.elements, other.elements + size, elements);
            }
            else if(other.frontIndex > other.backIndex)
            {
                std::copy(other.elements + other.frontIndex, other.elements + other.capacity, elements);
                std::copy(other.elements, other.elements + other.backIndex, elements + other.capacity - other.frontIndex);
            }
            else
            {
                std::copy(other.elements + other.frontIndex, other.elements + other.backIndex, elements);
            }
        }
        return *this;
    }

    // 析构函数
    ~Deque() {
        delete[] elements;  // 释放数组内存
    }

    // 在前端插入元素
    void push_front(const T& value) {
        if (size == capacity) {
            resize();  // 容量不足时扩容
        }
        // 计算新的前端索引（循环减1）
        frontIndex = (frontIndex - 1 + capacity) % capacity;
        elements[frontIndex] = value;  // 存入元素
        ++size;
    }

    // 在后端插入元素
    void push_back(const T& value) {
        if (size == capacity) {
            resize();  // 容量不足时扩容
        }
        elements[backIndex] = value;  // 存入元素
        backIndex = (backIndex + 1) % capacity;  // 循环加1
        ++size;
    }

    // 从前端移除元素
    void pop_front() {
        if (size == 0) {
            throw std::out_of_range("Deque is empty");
        }
        frontIndex = (frontIndex + 1) % capacity;  // 移动前端索引
        --size;
    }

    // 从后端移除元素
    void pop_back() {
        if (size == 0) {
            throw std::out_of_range("Deque is empty");
        }
        backIndex = (backIndex - 1 + capacity) % capacity;  // 移动后端索引
        --size;
    }

    // 访问指定索引的元素（非const版本）
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        // 计算实际索引（从frontIndex开始偏移index）
        return elements[(frontIndex + index) % capacity];
    }

    // 获取元素数量
    size_t getSize() const {
        return size;
    }

    // 清空队列
    void clear() {
        size = 0;
        frontIndex = 0;
        backIndex = 0;
    }

    // 打印所有元素
    void printElements() const {
        size_t currentSize = size;
        size_t index = frontIndex;
        while (currentSize--) {
            std::cout << elements[index] << " ";
            index = (index + 1) % capacity;
        }
        std::cout << std::endl;
    }

private:
    // 扩容函数
    void resize() {
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;  // 初始容量为1，之后翻倍
        T* newElements = new T[newCapacity];  // 分配新数组

        // 复制旧元素到新数组（从frontIndex开始，按顺序复制size个元素）
        size_t oldSize = size;
        size_t index = frontIndex;
        for (size_t i = 0; i < oldSize; ++i) {
            newElements[i] = elements[index];
            index = (index + 1) % capacity;
        }

        delete[] elements;  // 释放旧数组内存
        elements = newElements;
        capacity = newCapacity;
        frontIndex = 0;  // 新数组前端从0开始
        backIndex = oldSize;  // 新数组后端索引为旧元素数量
    }
};

int main() {
        // 创建一个 Deque 对象
    Deque<int> myDeque;

    int N;
    std::cin >> N;
    // 读走回车
    getchar();
    std::string line;
    // 接收命令
    for (int i = 0; i < N; i++) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        int value;

        if (command == "push_back") {
            iss >> value;
            myDeque.push_back(value);
        }

        if (command == "push_front") {
            iss >> value;
            myDeque.push_front(value);
        }

        if (command == "pop_back") {
            if (myDeque.getSize() == 0) {
                continue;
            }
            myDeque.pop_back();
        }

        if (command == "pop_front") {
            if (myDeque.getSize() == 0) {
                continue;
            }
            myDeque.pop_front();
        }

        if (command == "clear") {
            myDeque.clear();
        }

        if (command == "size") {
            std::cout << myDeque.getSize() << std::endl;
        }

        if (command == "get") {
            iss >> value;
            std::cout << myDeque[value] << std::endl;
        }

        if (command == "print") {
            if (myDeque.getSize() == 0) {
                std::cout << "empty" << std::endl;
            } else {
                myDeque.printElements();
            }
        }
    }
    return 0;
}
