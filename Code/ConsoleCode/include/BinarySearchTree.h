#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <string>
#include "BasicSearchTree.h"
using namespace std;

struct BinarySearchTreeNode {
    string englishValue;
    string chineseValue;
    BinarySearchTreeNode *leftTree;
    BinarySearchTreeNode *rightTree;
    BinarySearchTreeNode *parent;
    BinarySearchTreeNode(): englishValue(""), chineseValue(""), leftTree(nullptr), rightTree(nullptr), parent(nullptr) {}
};

class BinarySearchTree:  public BasicSearchTree {
public:
    BinarySearchTree();

    virtual ~BinarySearchTree();

    void Insert(string englishValue, string chineseValue);   //重写插入函数

    void Find(string englishValue);          //重写查找函数

    void Delete(string englishValue);          //重写删除函数

private:

    BinarySearchTreeNode *root;

    void Destruct(BinarySearchTreeNode *p);

    void Insert(BinarySearchTreeNode *p, BinarySearchTreeNode *current);  //插入函数的实际实现

    BinarySearchTreeNode*  getSmallestChildren (BinarySearchTreeNode *p);   //获取右子树中的最小节点

};

#endif // BINARYSEARCHTREE_H
