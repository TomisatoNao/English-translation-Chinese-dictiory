#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <string>
#include "basicsearchtree.h"
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

    virtual ~BinarySearchTree() override;

    bool Insert(string englishValue, string chineseValue) override;   //重写插入函数

    QString Find(string englishValue) override;          //重写查找函数

    void Delete(string englishValue) override;          //重写删除函数

private:

    BinarySearchTreeNode *root;

    void Destruct(BinarySearchTreeNode *p);

    bool Insert(BinarySearchTreeNode *p, BinarySearchTreeNode *current);  //插入函数的实际实现

    BinarySearchTreeNode*  getSmallestChildren (BinarySearchTreeNode *p);   //获取右子树中的最小节点

};

#endif // BINARYSEARCHTREE_H
