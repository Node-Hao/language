#include <iostream>
#include <sstream>
#include <string>

enum class Color {RED, BLACK};

template <typename Key, typename Value>
class RedBackTree
{
    class Node
    {
        public:
            Key key;
            Value value;
            Color color;
            Node *left;
            Node *right;
            Node *parent;
        //构造函数
        Node(const Key &k, const Value &v, Color c, Node *p = nullptr)
            : key(k), value(v), color(c), left(nullptr), right(nullptr), parent(p){}
        Node()
            : color(Color:: BLACK), left(nullptr), right(nullptr), parent(nullptr){}
    };
    private:
        Node *root;
        size_t size;
        Node *Nil;

    //查询某节点
    Node *lookUp(Key key)
    {
        Node *cmpNode = root;

        while(cmpNode)
        {
            if(key < cmpNode->key)
            {
                cmpNode = cmpNode->left;
            }
            else if(key > cmpNode->key)
            {
                cmpNode = cmpNode->right;
            }
            else
            {
                return cmpNode;
            }
        }
        return cmpNode;
    }
    //左旋函数
    void rightRotate(Node *node)
    {
        Node *l_son = node->left;//获取当前节点的左子节点
        //当前节点的左子树变成左子节点的右子树
        node->left = l_son->right;
        //如果左子节点的右子树非空，更新其父节点
        if(l_son->right)
        {
            l_son->right->parent = node;
        }
        //左子节点升为当前节点位置，并处理父节点关系
        l_son->parent = node->parent;
        if(!node->parent)
        {
            root = l_son;
            //如果当前节点是其父节点的左子节点，更新父节点的左子结点为左子节点
        }
        else if(node == node->parent->left)
        {
            node->parent->left = l_son;
            //如果当前节点是其父节点的右子节点，更新父节点的右子节点为左子节点
        }
        else
        {
            node->parent->right = l_son;
        }
        // 完成右旋转，将当前节点成为左子节点的右子节点
        l_son->right = node;
        // 更新当前节点的父节点为左子节点
        node->parent = l_son;
    }
        // 左旋函数
    // 是右旋的对称情况，逻辑和右旋是一样的
    void rightRotate(Node *node)
    {
        Node *r_son = node->right;

        node->left = l_son->right;

        if (r_son->left)
        {
            r_son->left->parent = node;
        }
        
        r_son->parent = node->parent;
        if(!node->parent)
        {
            root = r_son;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = r_son;
        }else
        {
            node->parent->right = r_son;
        }

        r_son->left = node;
        node->parent = r_son;
    }
    //插入节点
    void insertNode(const Key &key)
    {
        //创建一个新节点，节点的颜色初始化为红色
        Node *newNode = new Node(key, Color:: RED);
        Node *parent = nullptr;
        Node *cmpNode = root;

        // 遍历树，找到新节点的正确位置
        while (cmpNode)
        {
            parent = cmpNode;// 保留当前节点作为新节点的潜在父节点
            // 如果新节点的键小于当前比较节点的键，则向左子树移动
            if(newNode->key < cmpNode->key)
            {
                cmpNode = cmpNode->left;
                // 如果新节点的键大于当前比较节点的键，则向右子树移动
            }
            else if (newNode->key > cmpNode->key)
            {
                cmpNode = cmpNode->right;
                // 如果键相等，则说明树中已有相同键的节点，删除新节点并返回
            }
            else
            {
                delete newNode;
                return;
            }
        }

        // 树的大小增加
        size++;

        // 将新节点的父节点设置为找到的父节点位置
        newNode->parent = parent;
        // 如果父节点为空说明树是空的，新节点成为根节点

        if(!parent)
        {
            root = newNode;
            // 如果新节点的键小于父节点的键，将新节点插入父节点的左子树
        }
        else if(newNode->key < parent->key)
        {
            parent->right = newNode;
            // 否则，将新节点插入父节点的右子树
        }
        else
        {
            parent->right = newNode;
        }
        // 插入新节点后，调用 insertFixup 函数来修复可能破坏的红黑树的性质
        insertFixup(newNode);
    }












};

















