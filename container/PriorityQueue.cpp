#include <iostream>
#include <vector>
#include <algorithm> 

template <typename T, typename Container = std::vector<T>>
class MyPriorityQueue
{
    private:
        Container data; // 使用底层容器存储优先队列的元素

    public:
        // 默认构造函数
        MyPriorityQueue() {}

        // 构造函数可以指定容器
        MyPriorityQueue(const Container& c) : data(c)
        {
            std::make_heap(data.begin(), data.end());
        }

        // 将元素添加到优先队列中
        void push(const T& value)
        {
            data.push_back(value);
            std::push_heap(data.begin(), data.end());
        }

        // 弹出优先队列中的最大元素
        void pop()
        {
            if (!empty())
            {
                std::pop_heap(data.begin(), data.end());
                data.pop_back();
            }
            else
            {
                throw std::runtime_error("Priority queue is empty");
            }
        }

        // 访问优先队列中的最大元素
        T& top()
        {
            if (!empty())
            {
                return data.front();
            }
            else
            {
                throw std::runtime_error("Priority queue is empty.");
            }
        }

        // 检查优先队列是否为空
        bool empty() const
        {
            return data.empty();
        }

        // 返回优先队列的大小
        size_t size() const
        {
            return data.size();
        }
}

// 二插堆实现

#include <iostream>
#include <vector>
#include <deque>
#include <stdexcept>
#include <sstream>
#include <string>

template <typename T, typename Container = std::vector<T>>
class MyPriorityQueue
{
    private:
        Container data;

        // 辅助函数：向上调整元素以维护堆性质 
        void heapifyUp()
        {
            int index = data.size() - 1;
            while (index > 0)
            {
                int parentIndex = (index - 1) / 2;
                if (data[index] > data[parentIndex])
                {
                    std::swap(data[index], data[parentIndex]);
                    index = parentIndex;
                }
                else
                {
                    break;
                }
            }
        }
        // 辅助函数：向下调整元素以维护堆性质
        void heapifyDown(int index)
        {
            int size = data.size();
            while (true)
            {
                int leftChild = 2 * index + 1;
                int rightChild = 2 * index + 2;
                int largest = index;

                if (leftChild < size && data[leftChild] > data[largest])
                {
                    largest = leftChild;
                }

                if (rightChild < size && data[rightChild] > data[largest])
                {
                    largest = rightChild;
                }

                if (largest != index)
                {
                    std::swap(data[index], data[largest]);
                    index = largest;
                }
                else
                {
                    break;
                }
            }
        }
    
    public:
        MyPriorityQueue() {}

        MyPriorityQueue(const Container& c) : data(c)
        {
            // 将底层容器转化为堆
            int size = data.size();
            for (int i = (size / 2) - 1; i >= 0; --i)
            {
                // 这样做的目的是为了调整每一层吗?
                heapifyDown();
            }
        }

        void push(const T& value)
        {
            data.push_back(value);
            heapifyUp();
        }

        void pop()
        {
            if (!empty())
            {
                std::swap(data[0], data[data.size() - 1]);
                data.pop_back();
                heapifyDown();
            }
            else
            {
                throw std::runtime_error("Priority queue is empty.");
            }
        }

        T& top()
        {
            if (!empty())
            {
                return data[0];
            }
            else
            {
                throw std::runtime_error("Priority queue is empty.");
            }
        }

        bool empty() const
        {
            return data.empty();
        }
        size_t size() const
        {
            return data.size();
        }

}


















