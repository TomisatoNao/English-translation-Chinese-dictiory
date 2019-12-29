#ifndef MYSTACK_H_INCLUDED
#define MYSTACK_H_INCLUDED

template <typename T>
struct MyStackNode {
    T data;
    MyStackNode* next;
    MyStackNode():next(nullptr){}
};

template <typename T>
class MyStack{
private:
    MyStackNode<T> *top;
public:
    MyStack (){
        top = nullptr;
    }
    virtual ~MyStack() {
        MyStackNode<T> *current;
        while (top) {
            current = top;
            top=top->next;
            delete current;
        }
    }
    void Push(T t) {
        MyStackNode<T> *current = new MyStackNode<T>;
        current->data = t;
        current->next = top;
        top = current;
    }
    void Pop() {
        MyStackNode<T> *current = top;
        top = top->next;
        delete current;
    }
    T Top(){
        return top->data;
    }
    bool Empty() {
        return top==nullptr;
    }
};


#endif // MYSTACK_H_INCLUDED
