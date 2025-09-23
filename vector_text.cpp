#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>

template <typename T>
class Vector
{
    private:
        T *elements;//指向动态数组的指针
        size_t capacity;
        size_t size;

    public:
        //构造函数
        Vector() : elements(nullptr),capacity(0),size(0){}
        //析构函数
        ~Vector()
        {
            delete[] elements;
        }
    //拷贝构造函数
        Vector(const Vector &other): capacity(other.capacity),size(other.size)
        {
            elements = new T[capacity];
            std:: copy(other.elements, other.elements + size, elements);
        }
    //拷贝赋值操作符
        Vector& operator=(const Vector& other)
        {
            if(this != &other)
            {
                delete[] elements;
                capacity = other.capacity;
                size = other.size;
                elements = new T[capacity];
                std:: copy(other.elements, other.elements + size, elements);
            }
            return *this;
        }

        void push_back(const T &value)
        {
            if(size == capacity)
            {
                reserve(capacity == 0 ? 1 : 2 *capacity);
            }
            elements[size++] = value;
        }
        
        size_t getSize() const
        {
            return size;
        }

        size_t getCapacity() const
        {
            return capacity;
        }
        //下标操作符
        T& operator[](size_t index)
        {
            if(index >= size)
            {
                throw std:: out_of_range("Index out of range");
            }
            return elements[index];
        }

        const T& operator[](size_t index) const
        {
            if(index >= size)
            {
                throw std:: out_of_range("Index out of range");
            }
            return elements[index];
        }
        void insert(size_t index, const T& value)
        {
            if(index > size)
            {
                throw std:: out_of_range("Index out of range");
            }
            if(size == capacity)
            {
                reserve(capacity == 0 ? 1 : 2 * capacity);
            }
            for(size_t i = size; i > index; --i)
            {
                elements[i] = elements[i - 1];
            }
            elements[index] = value;
            ++size;
        }
        void pop_back()
        {
            if(size > 0)
            {
                //新元素直接进行覆盖即可
                --size;
            }
        }
        void clear()
        {
            //依旧是新元素直接覆盖即可
            size = 0;
        }
        //迭代器相关的函数 begin 和 end, 实际上就是指针
        T* begin()
        {
            return elements;
        }
        T* end()
        {
            return elements + size;
        }
        //const 版本用于只读
        const T* begin() const
        {
            return elements;
        }
        const T* end() const
        {
            return elements + size;
        }
        
        void printElements() const
        {
            for(size_t i = 0; i < size; ++i)
            {
                std:: cout << elements[i] << " ";
            }
            std:: cout << std:: endl;
        }
        void reserve(size_t new_capacity)
        {
            if(new_capacity > capacity)
            {
                //分配内存并复制新元素
                T* new_element = new T[new_capacity];
                for (size_t i = 0; i < capacity; i++)
                {
                    new_element[i] = elements[i];
                }
                delete[] elements;
                elements = new_element;
                capacity = new_capacity;
            }
        }
};
int main()
{
    // 创建一个 Vector 对象
    Vector<int> myVector;

    int N;
    std::cin >> N;
    // 读走回车
    getchar();

    std::string line;
    for (int i = 0; i < N; i++)
    {
        // 读取整行
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "push")
        {
            int value;
            iss >> value;
            myVector.push_back(value);
        }
        else if (command == "print")
        {
            if (myVector.getSize() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            myVector.printElements();
        }
        else if (command == "size")
        {
            std::cout << myVector.getSize() << std::endl;
        }
        else if (command == "get")
        {
            int index;
            iss >> index;
            std::cout << myVector[index] << std::endl;
        }
        else if (command == "insert")
        {
            int index, value;
            iss >> index >> value;
            myVector.insert(index, value);
        }
        else if (command == "pop")
        {
            myVector.pop_back();
        }
        else if (command == "iterator")
        {
            if (myVector.getSize() == 0)
            {
                std::cout << "empty" << std::endl;
                continue;
            }
            for (auto it = myVector.begin(); it != myVector.end(); ++it)
            {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        }
        else if (command == "foreach")
        {
            if (myVector.getSize() == 0)
            {
                std::cout << "empty" << std::endl;
                continue;
            }
            for (const auto &element : myVector)
            {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
        else if (command == "clear")
        {
            myVector.clear();
        }
    }
    return 0;
}






















