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













};

















