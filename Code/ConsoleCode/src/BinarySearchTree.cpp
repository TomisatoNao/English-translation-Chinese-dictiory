#include "BinarySearchTree.h"
#include <iostream>
#include "MyStack.h"
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

BinarySearchTree::BinarySearchTree() {
    root = nullptr;

    string fileName = "dictionary\\a.txt";
    string insertEnglishValue;
    string insertChineseValue;
    ifstream myFile;

    myFile.open(fileName);

    cout << "正在初始化字典，请稍等..." << endl;

    while (myFile.is_open()) {
        while (!myFile.eof()) {
            getline(myFile, insertEnglishValue, ' ');
            getline(myFile, insertChineseValue);
            Insert(insertEnglishValue, insertChineseValue);
        }
        myFile.close();
        fileName[11]=fileName[11]+1;
       // cout << fileName;
        myFile.open(fileName);
    }

    myFile.close();

    system("cls");
}


BinarySearchTree::~BinarySearchTree()
{
    MyStack<BinarySearchTreeNode *> ms;
    ofstream myFile;
    string fileName = "dictionary\\a.txt";
    string insertEnglishValue;
    string insertChineseValue;
    myFile.open(fileName);
    BinarySearchTreeNode* p = root;
    BinarySearchTreeNode* temp;

    while(!ms.Empty() || p != nullptr) {           //通过中序遍历非递归实现将字典写回到文件中
        while(p != nullptr) {
            ms.Push(p);
            p = p->leftTree;
        }
        if(!ms.Empty()) {
            p = ms.Top();
            if (myFile.is_open()) {
                 insertEnglishValue = p->englishValue;
                insertChineseValue = p->chineseValue;
                if (insertEnglishValue[0]!=fileName[11]) {
                    myFile.close();
                    fileName[11]=insertEnglishValue[0];
                    myFile.open(fileName);
                    myFile << insertEnglishValue << " " << insertChineseValue << endl;
                } else {
                    myFile << insertEnglishValue << " " << insertChineseValue << endl;
                }
            }
            ms.Pop();
            temp = p;
            p = p->rightTree;
            delete temp;
        }
    }
    if (myFile.is_open()) {
          myFile.close();
    }
}

void BinarySearchTree::Insert(string englishValue, string chineseValue) {
    if (root == nullptr) {
        root = new BinarySearchTreeNode;
        root->englishValue = englishValue;
        root->chineseValue = chineseValue;
    } else {
        BinarySearchTreeNode* current = new BinarySearchTreeNode;
        current->englishValue = englishValue;
        current->chineseValue = chineseValue;
        Insert(root, current);
    }
}


void BinarySearchTree::Insert(BinarySearchTreeNode *p, BinarySearchTreeNode *current) {
    if (p->englishValue > current->englishValue) {
        if(p->leftTree==nullptr) {
            p->leftTree = current;
            current->parent = p;
        } else {
            Insert(p->leftTree, current);
        }
    } else if (p->englishValue < current->englishValue) {
        if(p->rightTree==nullptr) {
            p->rightTree = current;
            current->parent = p;
        } else {
            Insert(p->rightTree, current);
        }
    } else {
        return;
    }
}

void BinarySearchTree::Find(string englishValue) {
    BinarySearchTreeNode* current = root;

    while (current != nullptr) {
        if (current->englishValue == englishValue) {
            cout << current->englishValue << " " << current->chineseValue << endl;
            return;
        } else if (current->englishValue > englishValue) {
            current = current->leftTree;
        } else if (current->englishValue < englishValue) {
            current = current->rightTree;
        }
    }

    cout << "没找到您要查找的英文单词" << endl;
    string chineseValue;
    cout << "请输入您要查找的英文单词的词性及其汉语意思:" << endl;
    cin >> chineseValue;
    Insert(englishValue, chineseValue);
}

void BinarySearchTree::Delete(string englishValue) {

    if (root == nullptr) {
        cout << "字典为空" << endl;
        return;
    }

    BinarySearchTreeNode* current = root;

    while(current != nullptr) {
        if (current->englishValue > englishValue) {
            current = current->leftTree;
        } else if (current->englishValue < englishValue){
            current = current->rightTree;
        } else {
            if (current->rightTree == nullptr) {
                if (current == root) {
                    root = root->leftTree;
                    root->parent = nullptr;
                } else {
                    if (current == current->parent->leftTree) {
                        current->parent->leftTree = current->leftTree;
                    } else {
                        current->parent->rightTree = current->leftTree;
                    }
                }
                delete current;
                return;
            }
            BinarySearchTreeNode* smallest = getSmallestChildren(current->rightTree); //smallest最少也是改节点的右子树
            current->englishValue = smallest->englishValue;
            current->chineseValue = smallest->chineseValue;

            if (smallest == smallest->parent->leftTree) { //smallest的左子树一定是空
                smallest->parent->leftTree = smallest->rightTree;
            } else {
                smallest->parent->rightTree = smallest->rightTree;
            }
        }
    }
}

BinarySearchTreeNode*  BinarySearchTree::getSmallestChildren(BinarySearchTreeNode *p) {
    if (p->leftTree == nullptr) {
        return p;
    }
    while (p->leftTree != nullptr) {
        p = p->leftTree;
    }
    return p;
}
