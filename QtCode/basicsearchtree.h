#ifndef BASICSEARCHTREE_H
#define BASICSEARCHTREE_H

#include <string>
#include <QString>
using namespace std;

class BasicSearchTree
{
    public:
        BasicSearchTree();
        virtual ~BasicSearchTree();

        virtual QString Find(string englishValue) = 0;   //虚函数：查

        virtual void Delete(string englishValue) = 0;  //虚函数：删除

        virtual bool Insert(string englishValue, string chineseValue) = 0; //虚函数插入

    private:
};

#endif // BASICSEARCHTREE_H
