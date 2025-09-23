#include <iostream>
#include <vector>
#include <memory>  // 智能指针头文件
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>

class Shape
{
    public:
        //虚函数 计算面积，显示信息，析构函数确保执行
        virtual double area() const = 0;
        virtual void displayInfo() const = 0;
        virtual ~Shape() = default;

};

//圆类继承自基类 重新方法
class Round : public Shape
{
    private:
        double radius;
    public:
        //构造函数
        Round(double r): radius(r){}
        //计算面积
        double area() const override
        {
            return M_PI * radius * radius;
        }
        //打印信息
        void displayInfo() const override
        {
            std:: cout << "Round - radius:" << radius
            << "Round area is " << area() << std:: endl;
        }
        
};
//矩形类
class Rectangle : public Shape
{
    private:
        double height, width;
    public:
        Rectangle(double h, double w): height(h), width(w){}
        
        double area() const override
        {
            return height * width;
        }
        
        void displayInfo() const override
        {
            std:: cout << "Rectangle height and width is " << height << "," << width
            << "Rectangle area is " << area() << std:: endl;
        }
};

// 图形管理器 - 用于管理各种图形对象
class ShapeManager
{
    private:
        std:: vector<std:: unique_ptr<Shape>> shapes;
    public:
        //添加图像对象
        void addShape(std:: unique_ptr<Shape> shape)
        {
            shapes.push_back(std:: move(shape));
        }
        //显示所有图形信息
        void displayAllShapes() const
        {
            std:: cout << "\n所有图形信息:\n";
            for(const auto& shape : shapes)
            {
                shape->displayInfo();
            }
        }
        //计算所有图形面积总和
        double calculateTotalArea()
        {
            double total = 0.0;
            for(const auto& shape : shapes)
            {
                total += shape->area();
            }
            return total;
        }
        //清空所有图形
        void clearAllShapes()
        {
            shapes.clear();
            std:: cout << "\n已清除所有图形\n";
        }

};

int main() {
    // 创建图形管理器
    ShapeManager manager;
    
    // 添加图形 - 使用make_unique创建智能指针
    manager.addShape(std:: make_unique<Round>(5.0));
    // 半径为5的圆
    manager.addShape(std:: make_unique<Rectangle>(4, 6));
    // 4x6的矩形
    manager.addShape(std:: make_unique<Round>(3.5));
    // 半径为3.5的圆
    // 展示所有图形
   manager.displayAllShapes();
    
    // 计算并显示总面积
    std::cout << "\n所有图形的总面积: " << manager.calculateTotalArea() << std::endl;
    
    // 演示shared_ptr的使用
    std::cout << "\n演示shared_ptr的使用:\n";
    std::shared_ptr<Shape> sharedCircle = std::make_shared<Round>(10.0);
    std::shared_ptr<Shape> anotherShared = sharedCircle;  // 引用计数增加
    
    std::cout << "共享的圆形信息: ";
    sharedCircle->displayInfo();
    std::cout << "shared_ptr引用计数: " << sharedCircle.use_count() << std::endl;
    
    // 清除所有图形
    manager.clearAllShapes();
    
    return 0;
}


