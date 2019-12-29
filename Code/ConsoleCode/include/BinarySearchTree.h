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

    void Insert(string englishValue, string chineseValue);   //��д���뺯��

    void Find(string englishValue);          //��д���Һ���

    void Delete(string englishValue);          //��дɾ������

private:

    BinarySearchTreeNode *root;

    void Destruct(BinarySearchTreeNode *p);

    void Insert(BinarySearchTreeNode *p, BinarySearchTreeNode *current);  //���뺯����ʵ��ʵ��

    BinarySearchTreeNode*  getSmallestChildren (BinarySearchTreeNode *p);   //��ȡ�������е���С�ڵ�

};

#endif // BINARYSEARCHTREE_H
