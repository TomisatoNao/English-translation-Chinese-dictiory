/*1.选择数据结构
    1.1.进来先讲26个文件中的数据写入到相应的数据结构中
    1.2.提供功能
        1.2.1.增加单词
        1.2.2.删除单词
            1.2.2.1.若找到，输出单词，词性，意思，并提示已删除
            1.2.2.2.若没有找到，提示没有
        1.2.3.查找单词
            1.2.3.1.若没有找到，要求输入单词的词性与汉语意思，进行插入
            1.2.3.2.若找到，输出要查找的单词，词性，汉语意思
*/

#include "RedBlackTree.h"
#include "BinarySearchTree.h"
#include "BasicSearchTree.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    char select;
    string englishValue;
    string chineseValue;
    BasicSearchTree *t;

    cout << "请输入您要选择的字典实现方式:" << endl;
    cout << "1.普通二叉搜索树"<<endl;
    cout << "2.红黑树" << endl;
    cin >> select;

    switch(select) {
        case '1':
            t = new BinarySearchTree;
            break;
        case '2':
            t = new RedBlackTree;
            break;
        default:
            cout << "由于您输入错误,程序异常结束" << endl;
            return 0;
    }

    while (1) {
        cout << "请输入您要进行的操作:" << endl;
        cout << "1.增加单词" << endl;
        cout << "2.删除单词" << endl;
        cout << "3.查找单词" << endl;
        cout << "4.退出" << endl;

        cin >> select;

        if (select == '1') {
            cout << "请输入您要增加的英文单词:" << endl;
            cin >> englishValue;
            cout << "请输入您要增加的英文单词的词性及其汉语意思:" << endl;
            cin >> chineseValue;
            t->Insert(englishValue, chineseValue);
        } else if (select == '2') {
            cout << "请输入您要删除的英文单词:" << endl;
            cin >> englishValue;
            t->Delete(englishValue);
        } else if (select == '3') {
            cout << "请输入您要进行查找的英文单词:" << endl;
            cin >> englishValue;
            t->Find(englishValue);
        } else if (select == '4') {
            break;
        }
        system("pause");
        system("cls");
    }

    cout << "谢谢您的使用！！！" << endl;
    delete t;
    return 0;
}
