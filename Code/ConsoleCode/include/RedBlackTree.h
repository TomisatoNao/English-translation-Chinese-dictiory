#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#define RED 1
#define BLACK 0
#include <string>
#include "BasicSearchTree.h"

using namespace std;

struct Node {
    string englishValue;
    string chineseValue;
    bool color;
    Node* parent, *leftTree, *rightTree;

    Node():englishValue(""), chineseValue(""), color(RED), parent(nullptr), leftTree(nullptr), rightTree(nullptr) {}

    Node* grandparent(); //获取祖父节点

    Node* uncle();   //获取叔叔节点

    Node* sibling();  //获取兄弟节点
};

class RedBlackTree : public BasicSearchTree{

private:

    void RotateLeft(Node* p);   //左旋转

    void RotateRight(Node* p);  //右旋转

    void Insert(Node *p, string englishValue, string chineseValue); //插入操作

    void InsertCase(Node *p);    //对插入情况进行分析，维护红黑树的性质

    Node* GetSmallestChild(Node* p);   //获取最小后辈节点

    bool Delete(Node* p, string englishValue);  //删除节点

    void DeleteOneChild(Node *p);    //删除节点

    void DeleteCase(Node *p);     //对删除节点进行分析，维护红黑树的性质

public:
    RedBlackTree();             //构造函数

    ~RedBlackTree();          //析构函数

    void Insert(string englishValue, string chineseValue);   //插入操作

    void Delete(string englishValue);    //删除操作

    void Find(string englishValue);       //查找操作

private:

    Node* root;                    //根节点

    Node* NIL;                     //标记叶节点
};


#endif // REDBLACKTREE_H
