#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

enum Sex
{
    MALE,
    FEMALE
};

enum Major
{
    PHYSICS,
    COMPUTER,
    MATH,
    CHEMISTRY
};

class Student
{
    private:
        int id;
        string name;
        Sex sex;
        string birth_place;
        Major major;

    public:
        Student(int id, string name, Sex sex, string birth_place, Major major)
        :id(id), name(name), sex(sex), birth_place(birth_place), major(major){} 

        int get_id() const{return id;}
        string get_name() const{return name;}
        Sex get_sex() const{return sex;}
        string get_birth_place() const{return birth_place;}
        Major get_major() const{return major;}

        void display() const{
            cout << "Student ID:" << id
                 << ", name:" << name
                 << ", sex:" << (sex == MALE ? "male": "female")
                 << ", birth_place:" << birth_place
                 << ", major: ";
            //转换专业枚举为字符串
            switch(major)
            {
                case COMPUTER: cout << "computer";break;
                case MATH: cout << "math";break;
                case PHYSICS: cout << "physics";break;
                case CHEMISTRY: cout << "chemistry";break;
            }
        }
};

//按学号排序的比较函数
bool compare_id(const Student& s1, const Student& s2)
{
    return s1.get_id() < s2.get_id();//从小到大排序
}

//按姓名排序的比较函数
bool compare_name(const Student& s1, const Student& s2)
{
    return s1.get_name() < s2.get_name();
}

//显示学生信息的函数
void display_Student(const Student& s)
{
    s.display();
    cout << endl;
}
// 统计特定专业的函数（供count_if使用）
bool match_major_computer(const Student &st) {
    return st.get_major() == COMPUTER;
}
bool match_major_physics(const Student &st) {
    return st.get_major() == PHYSICS;
}

// 4. 函数对象（仿函数）：更灵活的条件判断
// 按专业统计的函数对象
class MatchMajor
{
    private:
        Major target_major;
    public:
        MatchMajor(Major m) : target_major(m){}
        // 重载()运算符，使对象可像函数一样调用
        bool operator()(const Student& st) const
        {
            return st.get_major() == target_major;
        }
};
// 按“专业+性别”统计的函数对象
class MatchMajorAndSex
{
    private:
        Major target_major;
        Sex target_sex;
    public:
        MatchMajorAndSex(Major m, Sex s) : target_major(m), target_sex(s){}

        bool operator() (const Student& s) const
        {
            return s.get_major() == target_major && s.get_sex() == target_sex;
        }

};
int main()
{
    vector<Student> students;
    // 手动添加几个示例学生（实际场景可改为用户输入）
    students.emplace_back(103, "zhangsan", MALE, "Nanjing", COMPUTER);
    students.emplace_back(101, "lisi", FEMALE, "Beijing", PHYSICS);
    students.emplace_back(102, "wangwu", MALE, "Nanjing", COMPUTER);
    students.emplace_back(105, "zhaoliu", FEMALE, "shanghai", MATH);
    students.emplace_back(104, "sunqi", FEMALE, "Nanjing", COMPUTER);
    // 步骤2：按学号排序（使用普通函数作为排序规则）
    sort(students.begin(), students.end(), compare_id);
    cout << "==According to sort by studnets ID of students list=="<< endl;
    for_each(students.begin(), students.end(), display_Student);

    // 步骤3：统计各专业人数（对比三种方式）
    cout << "\n Statistic of professional numbers"<<endl;

    // 方式1：用普通函数（每个专业一个函数）
    cout << "the Major of Computer numbers(normal function)" << endl
         << count_if(students.begin(), students.end(), match_major_computer) << endl;

    // 方式2：用函数对象（一个类适配所有专业）
    cout << "the Major of Physicial(function object)" << endl
         << count_if(students.begin(), students.end(), MatchMajor(PHYSICS)) << endl;

    cout << "the Major of Math(function object)" << endl
         << count_if(students.begin(), students.end(), MatchMajor(MATH)) << endl;

    // 方式3：用Lambda表达式（无需定义额外函数/类，直接写逻辑）
    cout << "the Major of Chemistry" << endl
         << count_if(students.begin(), students.end(), 
        [](const Student &s){return s.get_major() == CHEMISTRY;}) << endl;

    // 步骤4：复杂条件统计（专业+性别+出生地）
    cout << "complex condition statistic " << endl;

    // 统计“计算机专业女生”人数（函数对象）
    cout << "female numbers of computer major" << endl
         << count_if(students.begin(), students.end(), MatchMajorAndSex(COMPUTER, FEMALE)) << endl;

    // 统计“南京籍计算机专业学生”人数（Lambda）
    cout << "the studens who have Nanjing birth_place numbers of computer major "<< endl
         << count_if(students.begin(), students.end(),
        [](const Student &s){return s.get_major() == COMPUTER && s.get_birth_place() == "Nanjing";} ) << endl;

    // 步骤5：按姓名排序（Lambda作为排序规则）
    sort(students.begin(), students.end(), 
         [](const Student &s1, const Student &s2){return s1.get_name() < s2.get_name();});

    for_each(students.begin(), students.end(), 
         [](const Student &s){s.display();
         cout << endl;});
         
    return 0;
}