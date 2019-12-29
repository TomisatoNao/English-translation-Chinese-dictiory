#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "RedBlackTree.h"
#include "MyStack.h"
using namespace std;

RedBlackTree::RedBlackTree() {
    NIL = new Node;
    NIL->color = BLACK;
    root = nullptr;

    ifstream myFile;
    string fileName = "dictionary\\a.txt";
    string insertEnglishValue;
    string insertChineseValue;

    cout << "正在初始化字典，请稍等..." << endl;

    myFile.open(fileName);
    while(myFile.is_open()) {
        while(!myFile.eof()) {
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

RedBlackTree::~RedBlackTree() {
    MyStack<Node *> ms;
    ofstream myFile;
    string fileName = "dictionary\\a.txt";
    string insertEnglishValue;
    string insertChineseValue;
    myFile.open(fileName);
    Node* p  = root;
    Node* temp;

    while(!ms.Empty() || p != NIL) {         //通过中序遍历的非递归实现将字典写回到字典中
        while(p != NIL) {
            ms.Push(p);
            p = p->leftTree;
        }
        if(!ms.Empty()) {
            p = ms.Top();
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
            ms.Pop();
            temp = p;
            p = p->rightTree;
            delete temp;
        }
    }

    myFile.close();
    delete NIL;
}



void RedBlackTree::Insert(string englishValue, string chineseValue) {
    if(root == nullptr) {
        root = new Node;
        root->color = BLACK;
        root->englishValue = englishValue;
        root->chineseValue = chineseValue;
        root->leftTree = NIL;
        root->rightTree = NIL;
        return;
    }
    Insert(root, englishValue, chineseValue);
}

void RedBlackTree::Insert(Node *p, string englishValue, string chineseValue) {
    if (p->englishValue > englishValue) {
        if(p->leftTree == NIL) {
            Node* current = new Node;
            current->parent = p;
            current->englishValue = englishValue;
            current->chineseValue = chineseValue;
            current->leftTree = NIL;
            current->rightTree = NIL;
            current->parent = p;
            p->leftTree = current;
            InsertCase(current);
            return;
        }
        Insert(p->leftTree, englishValue, chineseValue);
    } else if (p->englishValue < englishValue) {
        if(p->rightTree == NIL) {
            Node* current = new Node;
            current->parent = p;
            current->englishValue = englishValue;
            current->chineseValue = chineseValue;
            current->leftTree = NIL;
            current->rightTree = NIL;
            current->parent = p;
            p->rightTree = current;
            InsertCase(current);
            return;
        }
        Insert(p->rightTree, englishValue, chineseValue);
    } else {
        return;
    }
}

void RedBlackTree::InsertCase(Node *p) {
    if (p == root) {
        p->color = BLACK;
        return;
    }
    if (p->parent == BLACK) {
        return;
    }
    if (p->parent->color == RED && p->uncle()->color == RED) {
        p->parent->color = BLACK;
        p->uncle()->color = BLACK;
        p->grandparent()->color = RED;
        InsertCase(p->grandparent());
        return;
    }
    if (p->parent->color == RED && p->uncle()->color == BLACK) {
        if (p->parent == p->grandparent()->leftTree && p == p->parent->rightTree) {
            RotateLeft(p);
            p = p->leftTree;
        } else if (p->parent == p->grandparent()->rightTree && p == p->parent->leftTree) {
            RotateRight(p);
            p = p->rightTree;
        }

        if (p->parent == p->grandparent()->leftTree && p == p->parent->leftTree) {
            p->parent->color = BLACK;
            p->grandparent()->color = RED;
            RotateRight(p->parent);
        } else if (p->parent == p->grandparent()->rightTree && p == p->parent->rightTree) {
            p->parent->color = BLACK;
            p->grandparent()->color = RED;
            RotateLeft(p->parent);
        }
    }
}


void RedBlackTree::Delete(string englishValue) {
    if (root == nullptr) {
        cout << "没找到您要删除的单词" << endl;
        return;
    }
    Delete(root, englishValue);
}

bool RedBlackTree::Delete(Node* p, string englishValue) {
    if(p->englishValue > englishValue) {
        if (p->leftTree == NIL) {
            cout << "没找到您要删除的单词" << endl;
            return false;
        }
        return Delete(p->leftTree, englishValue);
    } else if (p->englishValue < englishValue) {
        if (p->rightTree == NIL) {
            cout << "没找到您要删除的单词" << endl;
            return false;
        }
        return Delete(p->rightTree, englishValue);
    } else if (p->englishValue == englishValue) {
        if (p->rightTree == NIL) {
            DeleteOneChild(p);
            return true;
        }
        Node* child = GetSmallestChild(p->rightTree);
        swap(p->englishValue, child->englishValue);
        DeleteOneChild(child);
        cout << "删除成功" << endl;
        return true;
    } else {
        cout << "没找到您要删除的单词" << endl;
        return false;
    }
}

Node* RedBlackTree::GetSmallestChild(Node* p) {
    if (p->leftTree == NIL) {
        return p;
    }
    return GetSmallestChild(p->leftTree);
}

void RedBlackTree::DeleteOneChild(Node *p) {
    Node *child = p->leftTree == NIL ? p->rightTree : p->leftTree;
    if (p->parent == nullptr && child == NIL) {
        delete p;
        p = nullptr;
        root = p;
        return;
    }

    if (p->parent == nullptr) {
        delete p;
        child->parent = nullptr;
        root = child;
        root->color = BLACK;
        return;
    }

    if (p->parent->leftTree == p) {
        p->parent->leftTree = child;
    } else {
        p->parent->rightTree = child;
    }
    child->parent = p->parent;

    if (p->color == BLACK) {
        if (child->color == RED) {
            child->color = BLACK;
        } else {
            DeleteCase(child);
        }
    }

    delete p;
}

void RedBlackTree::DeleteCase(Node *p) {
    if (p->parent == nullptr) {
        p->color = BLACK;
        return;
    }

    if (p->sibling()->color == RED) {
        p->parent->color = RED;
        p->sibling()->color = BLACK;
        if (p == p->parent->leftTree) {
            RotateLeft(p->sibling());
        } else {
            RotateRight(p->sibling());
        }
    }

    if (p->parent->color == BLACK && p->sibling()->color == BLACK
            && p->sibling()->leftTree->color == BLACK && p->sibling()->rightTree->color == BLACK) {
        p->sibling()->color = RED;
        DeleteCase(p->parent);
    } else if (p->parent->color == RED && p->sibling()->color == BLACK
               && p->sibling()->leftTree->color == BLACK && p->sibling()->rightTree->color == BLACK) {
        p->sibling()->color = RED;
        p->parent->color = BLACK;
    } else {
        if (p->sibling()->color == BLACK) {
            if (p == p->parent->leftTree && p->sibling()->leftTree->color == RED && p->sibling()->rightTree->color == BLACK) {
                p->sibling()->color = RED;
                p->sibling()->leftTree->color = BLACK;
                RotateRight(p->sibling()->leftTree);
            } else if (p == p->parent->rightTree && p->sibling()->leftTree->color == BLACK && p->sibling()->rightTree->color == RED) {
                p->sibling()->color = RED;
                p->sibling()->rightTree->color = RED;
                RotateLeft(p->sibling()->rightTree);
            }

            p->sibling()->color = p->parent->color;
            p->parent->color = BLACK;
            if (p == p->parent->leftTree) {
                p->sibling()->rightTree->color = BLACK;
                RotateLeft(p->sibling());
            } else {
                p->sibling()->leftTree->color = BLACK;
                RotateRight(p->sibling());
            }
        }
    }
}

void RedBlackTree::Find(string englishValue) {
    Node* current = root;
    while (current != NIL && current != nullptr) {
        if (current->englishValue == englishValue) {
            cout << current->englishValue << " " << current->chineseValue << endl;
            return;
        } else if (current->englishValue > englishValue) {
            current = current->leftTree;
        } else if (current->englishValue < englishValue) {
            current = current->rightTree;
        }
    }
    string chineseValue;
    cout << "请输入您要查找的英文单词的词性及其汉语意思:" << endl;
    cin >> chineseValue;
    Insert(englishValue, chineseValue);
}

void RedBlackTree::RotateRight(Node* p) {
    Node* gp = p->grandparent();
    Node* pa = p->parent;
    Node* rightChild = p->rightTree;

    pa->leftTree = rightChild;
    if (rightChild != NIL) {
        rightChild->parent = pa;
    }
    p->rightTree = pa;
    pa->parent = p;
    p->parent = gp;
    if (pa == root) {
        root = p;
    }
    if (gp != nullptr) {
        if (pa == gp->leftTree) {
            gp->leftTree = p;
        } else {
            gp->rightTree = p;
        }
    }
}

void RedBlackTree::RotateLeft(Node* p) {
    Node* gp = p->grandparent();
    Node* pa = p->parent;
    Node* leftChild = p->leftTree;

    pa->rightTree = leftChild;
    if (leftChild != NIL) {
        leftChild->parent = pa;
    }
    p->leftTree = pa;
    pa->parent = p;
    p->parent = gp;

    if (pa == root) {
        root = p;
    }

    if (gp != nullptr) {
        if (pa == gp->leftTree) {
            gp->leftTree = p;
        } else {
            gp->rightTree = p;
        }
    }
}

void RedBlackTree::Floororder() {
    queue<Node*> q;
    if (root == nullptr) {
        return;
    }
    q.push(root);
    while(!q.empty()) {
        cout << q.front()->englishValue << " " << q.front()->chineseValue << endl;
        if (q.front()->leftTree != nullptr && q.front()->leftTree != NIL) {
            q.push(q.front()->leftTree);
        }
        if (q.front()->rightTree != nullptr && q.front()->rightTree != NIL) {
            q.push(q.front()->rightTree);
        }
        q.pop();
    }
    cout << endl;
}

void RedBlackTree::InOrder() {
    InOrder(root);
}

void RedBlackTree::InOrder(Node *p) {
    if (p == nullptr || p == NIL) {
        return;
    } else {
        InOrder(p->leftTree);
        cout << p->englishValue << " " << p->chineseValue << endl;
        InOrder(p->rightTree);
    }
}

Node* Node::grandparent() {
    if(parent == nullptr) {
        return nullptr;
    } else
        return parent->parent;
}

Node* Node::uncle() {
    if(grandparent() == nullptr) {
        return nullptr;
    }
    return parent == grandparent()->leftTree ? grandparent()->rightTree : grandparent()->leftTree;
}

Node* Node::sibling() {
    if (parent == nullptr) {
        return nullptr;
    }
    return this == parent->leftTree ? parent->rightTree : parent->leftTree;
}
