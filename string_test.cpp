// #include <iostream>
// #include <string>
// using namespace std;

// int main() {
//     string s = "hello world, world!";
    
//     // 1. 查找存在的子串：返回第一次出现的下标
//     size_t first_index = s.find("world");
//     // int first_index = s.find("world");
//     if(first_index != string:: npos)
//     {
//         cout << "first index " << first_index << endl;
//     }
//     // 2. 从指定位置开始查找
//     size_t index  = s.find("wor", 7);
//     if(index != string:: npos)
//     {
//         cout << "from index seven to find elem " << index << endl;
//     } 
//     // 3. 查找不存在的子串：返回string::npos
//     size_t no_index = s.find("djsalkd");
//     if (no_index == string:: npos)
//     {
//         cout << "can not find substr " << no_index << endl;
//     }

//     return 0;
// }


// #include <iostream>
// #include <string>
// using namespace std;

// // 函数：将s中的所有old_str替换为new_str
// void replace_all(string &s, const string &old_str, const string &new_str) 
// {
//     size_t pos = 0;
//     while((pos = s.find(old_str, pos)) != string:: npos)
//     {
//         // 1. 删除旧子串：从pos开始，删除old_str的长度个字符
//         s.erase(pos, old_str.size());
//         // 2. 插入新子串：从pos开始插入new_str
//         s.insert(pos, new_str);
//         // 3. 更新下一次查找的起始位置（跳过刚插入的新子串，避免重复替换）
//         pos += new_str.size();
//     }
// }

// int main() {
//     string s = "hello world, world! world is big!";
//     replace_all(s, "world", "C++");
//     cout << "替换后：" << s << endl; 
//     // 输出：hello C++, C++! C++ is big!
//     return 0;
// }

// 需求 1：用户注册信息校验（覆盖比较、插入、子串）
// 需求描述：实现用户注册时的 3 个校验逻辑：
// 用户名长度需≥6（不足则在末尾补*至 6 位）；
// 密码需包含 “大写字母”（通过提取子串判断首字符是否大写）；
// 确认密码需与原密码完全一致（判断相等）

// #include <iostream>
// #include <string>
// #include <cctype> // 包含isupper()
// using namespace std;

// int main() {
//     string username, pwd, confirm_pwd;

//     // 1. 用户名处理：不足6位补*
//     cout << "输入用户名：不足六位补*";
//     cin >> username;
//     if(username.size() < 6)
//     {
//         int need = 6 - username.size();
//         username.insert(username.size(), need, '*'); // 插入：在末尾补need个*
//     }
//     cout << "处理后用户名：" << username << endl;
    

//     // 2. 密码校验：首字符是否为大写
//     cout << "输入密码（首字符大写）：";
//     cin >> pwd;
//     string firstChar = pwd.substr(0, 1);
//     if(!isupper(firstChar[0]))
//     {
//         cout << "密码首字符必须为大写！" << endl;
//         return 1;
//     }

//     // 3. 确认密码：判断相等
//     cout << "确认密码：";
//     cin >> confirm_pwd;
//     if (pwd != confirm_pwd) { // 比较符：直接判断相等
//         cout << "两次密码不一致！" << endl;
//         return 1;
//     }

//     cout << "注册成功！" << endl;
//     return 0;
// }

// 需求 2：日志格式化输出（覆盖数字转串、插入、C 风格转换）
// 需求描述：生成一条格式化日志，包含 “时间戳（数字转串）+ 日志级别（插入前缀）+ 内容”，并通过 C 语言的printf输出（需转 C 风格串）

// #include <iostream>
// #include <string>
// #include <cstdio> // 包含printf
// using namespace std;

// int main() {
//     // 1. 数字转串：时间戳（假设为Unix时间1699999999）
//     long long timestamp = 16999999999;
//     string timeStr = to_string(timestamp);
//     // 2. 插入前缀：日志级别（[INFO]）
//     string logContext = "用户登录成功";
//     logContext.insert(0, "[INFO]");
//     logContext.insert(0, timeStr + " ");
//     // 3. 转C风格串：用printf输出
//     printf("日志: %s\n", logContext.c_str());

//     return 0;
// }

// 需求 3：文本内容处理（覆盖删除、大小写转换、string 转数字）
// 需求描述：处理一段用户输入的文本：
// 删除所有空格；
// 将文本统一转为小写；
// 提取文本中的数字（如 “abc123def45”→ 提取 123 和 45），并计算总和。

#include <iostream>
#include <string>
#include <algorithm> // 包含transform
#include <cctype>    // 包含tolower、isdigit
#include <cstdlib>   // 包含atoi
using namespace std;

int main()
{
    string text = "He llo 123 W orld 45!";
    cout << "inital context:" << text << endl;
    //首先删除所有空格
    for (size_t i = 0; i < text.size();)
    {
        if(text[i] == ' ')
        {
            text.erase(i, 1);
        }
        else
        {
            i++;
        }
    }
    cout << "delete space is :" << text << endl; // 输出：Hello123World45!
    // 2. 转为小写：用transform配合tolower
    transform(
        text.begin(),
        text.end(),
        text.begin(),
        [](char c){
            // 转换为 unsigned char 避免符号扩展（处理中文/负数值）
            return static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }
    );
    cout << "transformer toLower is :" << text << endl;
    // 3. 提取数字并求和：遍历文本，拼接连续数字后转int
    int sum = 0;
    string numStr;
    for(char c : text)
    {
        if(isdigit(c))
        {
            numStr += c;
        }
        else if (!numStr.empty())
        {
            sum += stoi(numStr);
            numStr.clear();
        }
    }

    if(!numStr.empty())
    {
        sum += atoi(numStr.c_str());
    }
    cout << "acquire number sum is : " << sum << endl; // 输出：123+45=168

    return 0;
}


