#ifndef BASICSEARCHTREE_H
#define BASICSEARCHTREE_H

#include <string>
using namespace std;

class BasicSearchTree
{
    public:
        BasicSearchTree();
        virtual ~BasicSearchTree();

        virtual void Find(string englishValue) = 0;   //�麯������

        virtual void Delete(string englishValue) = 0;  //�麯����ɾ��

        virtual void Insert(string englishValue, string chineseValue) = 0; //�麯������

    private:
};

#endif // BASICSEARCHTREE_H
