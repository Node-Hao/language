#pragma once

#include<iostream>
#include<stdexcept>
#include<algorithm>
#include<sstream>
#include<string>

template<typename T>
class List
{
private:
    // 定义节点结构
    struct Node
    {
        T data;
        Node* next;
        Node* prev;

        // 构造函数
        Node(const T& value, Node* nextNode = nullptr, Node* prevNode = nullptr)
            : data(value), next(nextNode), prev(prevNode) {}
    };

    Node* head;   // 头结点指针
    Node* tail;   // 尾结点指针
    size_t size;  // 链表中节点的数量

public:
    // 构造函数
    List() : head(nullptr), tail(nullptr), size(0) {}

    // 析构函数
    ~List() { clear(); }

    // 在链表末尾添加元素
    void push_back(const T& value)
    {
        Node* newNode = new Node(value, nullptr, tail);

        if (tail)
        {
            tail->next = newNode;
        }
        else
        {
            head = newNode;  // 空链表时，新节点同时是头结点
        }
        tail = newNode;
        ++size;
    }

    // 在链表开头添加元素
    void push_front(const T& value)
    {
        Node* newNode = new Node(value, head, nullptr);

        if (head)
        {
            head->prev = newNode;
        }
        else
        {
            tail = newNode;  // 空链表时，新节点同时是尾结点（原代码错误：tail = head）
        }
        head = newNode;
        ++size;
    }

    // 获取链表中节点的数量
    size_t getSize() const { return size; }

    // 访问链表中的元素（非const版本）
    T& operator[](size_t index)
    {
        Node* current = head;
        for (size_t i = 0; i < index; ++i)  // 原代码用int，可能越界，改为size_t
        {
            if (!current)
            {
                throw std::out_of_range("Index out of range");
            }
            current = current->next;
        }
        return current->data;
    }

    // 访问链表中的元素（const版本）
    const T& operator[](size_t index) const
    {
        Node* current = head;
        for (size_t i = 0; i < index; ++i)  // 原代码用int，改为size_t
        {
            if (!current)
            {
                throw std::out_of_range("Index out of range");
            }
            current = current->next;
        }
        return current->data;
    }

    // 删除链表末尾的元素
    void pop_back()
    {
        if (size == 0) return;  // 空链表直接返回

        Node* oldTail = tail;
        tail = tail->prev;

        if (tail)
        {
            tail->next = nullptr;
        }
        else
        {
            head = nullptr;  // 链表为空时，头指针也置空
        }

        delete oldTail;
        --size;
    }

    // 删除链表开头节点
    void pop_front()
    {
        if (size == 0) return;  // 空链表直接返回

        Node* oldHead = head;
        head = head->next;

        if (head)
        {
            head->prev = nullptr;
        }
        else
        {
            tail = nullptr;  // 链表为空时，尾指针也置空
        }

        delete oldHead;
        --size;
    }

    // 获取指定值的节点（私有辅助函数）
    Node* getNode(const T& val) const
    {
        Node* node = head;
        while (node != nullptr && node->data != val)
        {
            node = node->next;
        }
        return node;
    }

    // 查找指定值并返回地址
    T* find(const T& val)
    {
        Node* node = getNode(val);
        return (node != nullptr) ? &node->data : nullptr;
    }

    // 删除指定值的节点
    void remove(const T& val)
    {
        Node* node = getNode(val);
        if (node == nullptr) return;  // 未找到节点

        if (node == head && node == tail)  // 唯一节点
        {
            head = nullptr;
            tail = nullptr;
        }
        else if (node == head)  // 头节点
        {
            head = node->next;
            head->prev = nullptr;  // 原代码错误：head-prev
        }
        else if (node == tail)  // 尾节点
        {
            tail = node->prev;
            tail->next = nullptr;
        }
        else  // 中间节点
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        delete node;
        --size;
    }

    // 检查链表是否为空
    bool empty() const { return size == 0; }  // 加const，支持const对象调用

    // 清空链表
    void clear()
    {
        while (head)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    // 打印元素（公有接口，供main调用）
    void printElements() const
    {
        for (Node* current = head; current; current = current->next)
        {
            std::cout << current->data << " ";
        }
        std::cout << std::endl;
    }

    // 友元声明：重载<<运算符
    template<typename L>
    friend std::ostream& operator<<(std::ostream& os, const List<L>& pt);
};

// 实现友元函数：重载<<运算符
template<typename L>
std::ostream& operator<<(std::ostream& os, const List<L>& pt)  // 原代码多了os
{
    for (typename List<L>::Node* current = pt.head; current; current = current->next)
    {
        os << " " << current->data;
    }
    os << std::endl;
    return os;
}


// main函数放在全局作用域
int main() {
    List<int> myList;

    int N;
    std::cin >> N;
    getchar();  // 读走回车

    std::string line;
    for (int i = 0; i < N; i++) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        int value;

        if (command == "push_back") {
            iss >> value;
            myList.push_back(value);
        }
        else if (command == "push_front") {  // 用else if避免多条件同时执行
            iss >> value;
            myList.push_front(value);
        }
        else if (command == "pop_back") {
            myList.pop_back();
        }
        else if (command == "pop_front") {
            myList.pop_front();
        }
        else if (command == "remove") {
            iss >> value;
            myList.remove(value);
        }
        else if (command == "clear") {
            myList.clear();
        }
        else if (command == "size") {
            std::cout << myList.getSize() << std::endl;
        }
        else if (command == "get") {
            iss >> value;
            try {  // 捕获[]可能抛出的异常
                std::cout << myList[value] << std::endl;
            } catch (const std::out_of_range& e) {
                std::cout << "Index out of range" << std::endl;
            }
        }
        else if (command == "print") {
            if (myList.empty()) {  // 用empty()更清晰
                std::cout << "empty" << std::endl;
            } else {
                myList.printElements();
            }
        }
    }
    return 0;
}
