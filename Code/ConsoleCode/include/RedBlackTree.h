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

    Node* grandparent(); //��ȡ�游�ڵ�

    Node* uncle();   //��ȡ����ڵ�

    Node* sibling();  //��ȡ�ֵܽڵ�
};

class RedBlackTree : public BasicSearchTree{

private:

    void RotateLeft(Node* p);   //����ת

    void RotateRight(Node* p);  //����ת

    void Insert(Node *p, string englishValue, string chineseValue); //�������

    void InsertCase(Node *p);    //�Բ���������з�����ά�������������

    Node* GetSmallestChild(Node* p);   //��ȡ��С�󱲽ڵ�

    bool Delete(Node* p, string englishValue);  //ɾ���ڵ�

    void DeleteOneChild(Node *p);    //ɾ���ڵ�


    void DeleteCase(Node *p);     //��ɾ���ڵ���з�����ά�������������

    void DeStruct(Node *p);     //������������

    void InOrder(Node *p);      //�������

public:
    RedBlackTree();             //���캯��

    ~RedBlackTree();          //��������

    void Insert(string englishValue, string chineseValue);   //�������

    void Delete(string englishValue);    //ɾ������

    void Floororder();                    //�������

    void Find(string englishValue);       //���Ҳ���

    void InOrder();                 //����������ֵ�����

private:

    Node* root;                    //���ڵ�

    Node* NIL;                     //���Ҷ�ڵ�
};


#endif // REDBLACKTREE_H
