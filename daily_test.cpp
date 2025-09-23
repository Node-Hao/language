#include <iostream>
#include <vector>
#include <memory>  // 智能指针头文件
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>

// 抽象基类 - 图形
class Shape {
public:
    // 纯虚函数 - 计算面积
    virtual double area() const = 0;
    
    // 虚函数 - 显示图形信息
    virtual void displayInfo() const = 0;
    
    // 虚析构函数，确保派生类析构函数被正确调用
    virtual ~Shape() = default;
};

// 圆形类 - 继承自图形
class Circle : public Shape {
private:
    double radius;  // 半径
public:
    // 构造函数
    Circle(double r) : radius(r) {}
    
    // 重写计算面积的方法
    double area() const override {
        return M_PI * radius * radius;
    }
    
    // 重写显示信息的方法
    void displayInfo() const override {
        std::cout << "圆形 - 半径: " << radius 
                  << ", 面积: " << area() << std::endl;
    }
};
