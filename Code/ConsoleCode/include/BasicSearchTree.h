#ifndef BASICSEARCHTREE_H
#define BASICSEARCHTREE_H

#include <string>
using namespace std;

class BasicSearchTree
{
    public:
        BasicSearchTree();
        virtual ~BasicSearchTree();

        virtual void Find(string englishValue) = 0;   //Ðéº¯Êý£º²é

        virtual void Delete(string englishValue) = 0;  //Ðéº¯Êý£ºÉ¾³ý

        virtual void Insert(string englishValue, string chineseValue) = 0; //Ðéº¯Êý²åÈë

    private:
};

#endif // BASICSEARCHTREE_H
