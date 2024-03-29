#include "binarysearchtree.h"
#include "MyStack.h"
#include <fstream>
#include <string>

using namespace std;

BinarySearchTree::BinarySearchTree() {
    root = nullptr;

    string fileName = "dictionary\\a.txt";
    string insertEnglishValue;
    string insertChineseValue;
    ifstream myFile;

    myFile.open(fileName);
    while (myFile.is_open()) {
        while (!myFile.eof()) {
            getline(myFile, insertEnglishValue, ' ');
            if (myFile.eof()) {
                break;
            }
            getline(myFile, insertChineseValue);
            Insert(insertEnglishValue, insertChineseValue);
        }
        myFile.close();
        fileName[11]=fileName[11]+1;
        myFile.open(fileName);
    }

    if (myFile.is_open()) {
        myFile.close();
    }
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

    while(!ms.Empty() || p != nullptr) {
        while(p != nullptr) {
            ms.Push(p);
            p = p->leftTree;
        }
        if(!ms.Empty()) {
            p = ms.Top();
            insertEnglishValue = p->englishValue;
            insertChineseValue = p->chineseValue;
            if (myFile.is_open()) {
                if (insertEnglishValue[0]!=fileName[11]) {
                    myFile.close();
                    fileName[11]=insertEnglishValue[0];
                    myFile.open(fileName);
                    if (myFile.is_open()) {
                        myFile << insertEnglishValue << " " << insertChineseValue << endl;
                    }
                } else {
                    if (myFile.is_open()) {
                        myFile << insertEnglishValue << " " << insertChineseValue << endl;
                    }
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

bool BinarySearchTree::Insert(string englishValue, string chineseValue) {
    if (root == nullptr) {
        root = new BinarySearchTreeNode;
        root->englishValue = englishValue;
        root->chineseValue = chineseValue;
        return true;
    } else {
        BinarySearchTreeNode* current = new BinarySearchTreeNode;
        current->englishValue = englishValue;
        current->chineseValue = chineseValue;
        return Insert(root, current);
    }
}


bool BinarySearchTree::Insert(BinarySearchTreeNode *p, BinarySearchTreeNode *current) {
    if (p->englishValue > current->englishValue) {
        if(p->leftTree==nullptr) {
            p->leftTree = current;
            current->parent = p;
            return true;
        } else {
            return Insert(p->leftTree, current);
        }
    } else if (p->englishValue < current->englishValue) {
        if(p->rightTree==nullptr) {
            p->rightTree = current;
            current->parent = p;
            return true;
        } else {
            return Insert(p->rightTree, current);
        }
    } else {
        return false;
    }
}

QString BinarySearchTree::Find(string englishValue) {
    BinarySearchTreeNode* current = root;

    while (current != nullptr) {
        if (current->englishValue == englishValue) {
            return QString(QString::fromLocal8Bit(current->chineseValue.c_str()));
        } else if (current->englishValue > englishValue) {
            current = current->leftTree;
        } else if (current->englishValue < englishValue) {
            current = current->rightTree;
        }
    }
    return "";
}

bool BinarySearchTree::Delete(string englishValue) {

    if (root == nullptr) {
        return false;
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
                    root = current->leftTree;
                } else {
                    if (current == current->parent->leftTree) {
                        current->parent->leftTree = current->leftTree;
                    } else {
                        current->parent->rightTree = current->leftTree;
                    }
                }

                if (current->leftTree!=nullptr) {
                    current->leftTree->parent = current->parent;
                }
                delete current;
                return true;
            } else {
                BinarySearchTreeNode* smallest = getSmallestChildren(current->rightTree); //smallest最少也是改节点的右子树
                current->englishValue = smallest->englishValue;
                current->chineseValue = smallest->chineseValue;

                if (smallest == smallest->parent->leftTree) { //smallest的左子树一定是空
                    smallest->parent->leftTree = smallest->rightTree;
                } else {
                    smallest->parent->rightTree = smallest->rightTree;
                }
                if(smallest->rightTree!=nullptr) {
                    smallest->rightTree->parent=smallest->parent;  //更新父节点
                }
                delete smallest;
                return true;
            }
        }
    }
    return false;
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
