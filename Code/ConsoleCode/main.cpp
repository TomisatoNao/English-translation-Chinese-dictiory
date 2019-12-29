/*1.ѡ�����ݽṹ
    1.1.�����Ƚ�26���ļ��е�����д�뵽��Ӧ�����ݽṹ��
    1.2.�ṩ����
        1.2.1.���ӵ���
        1.2.2.ɾ������
            1.2.2.1.���ҵ���������ʣ����ԣ���˼������ʾ��ɾ��
            1.2.2.2.��û���ҵ�����ʾû��
        1.2.3.���ҵ���
            1.2.3.1.��û���ҵ���Ҫ�����뵥�ʵĴ����뺺����˼�����в���
            1.2.3.2.���ҵ������Ҫ���ҵĵ��ʣ����ԣ�������˼
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

    cout << "��������Ҫѡ����ֵ�ʵ�ַ�ʽ:" << endl;
    cout << "1.��ͨ����������"<<endl;
    cout << "2.�����" << endl;
    cin >> select;

    switch(select) {
        case '1':
            t = new BinarySearchTree;
            break;
        case '2':
            t = new RedBlackTree;
            break;
        default:
            cout << "�������������,�����쳣����" << endl;
            return 0;
    }

    while (1) {
        cout << "��������Ҫ���еĲ���:" << endl;
        cout << "1.���ӵ���" << endl;
        cout << "2.ɾ������" << endl;
        cout << "3.���ҵ���" << endl;
        cout << "4.�˳�" << endl;

        cin >> select;

        if (select == '1') {
            cout << "��������Ҫ���ӵ�Ӣ�ĵ���:" << endl;
            cin >> englishValue;
            cout << "��������Ҫ���ӵ�Ӣ�ĵ��ʵĴ��Լ��人����˼:" << endl;
            cin >> chineseValue;
            t->Insert(englishValue, chineseValue);
        } else if (select == '2') {
            cout << "��������Ҫɾ����Ӣ�ĵ���:" << endl;
            cin >> englishValue;
            t->Delete(englishValue);
        } else if (select == '3') {
            cout << "��������Ҫ���в��ҵ�Ӣ�ĵ���:" << endl;
            cin >> englishValue;
            t->Find(englishValue);
        } else if (select == '4') {
            break;
        }
        system("pause");
        system("cls");
    }

    cout << "лл����ʹ�ã�����" << endl;
    delete t;
    return 0;
}
