#ifndef STACK_H
#define STACK_H

#include<iostream>
using namespace std;

template <typename T>
struct Node{
    T data;
    Node* next;
    Node(const T &d, Node*t):data{d},next{t}{}
};

template <typename T>
class Stack{
    public:
        Stack():top{nullptr},count{0}{
            // cout << "Stack initialised\n";
        }

        ~Stack(){
            if(top){
                Node<T>*temp = top;
                int count{0};
                while(temp){
                    top = temp->next;
                    count++;
                    delete temp;
                    temp = top;
                }
                // cout << "Stack deleted::Elements deleted : " << count << endl;
            }else{
                // cout << "Stack empty\n";
            }
        }

        void push(const T& val){
            Node<T>* temp;
        
            temp = new Node<T>(val,top);
            top = temp;
            count++;
            
        }

        Node<T>* getMiddle(){
            Node<T>* slow = top;
            Node<T>* fast = top;

            while(fast && fast->next){
                slow = slow->next;
                fast = fast->next->next;
            }

            return slow;
        }
        
        T getTop () const{
            if(top)
                return top->data;
            else 
                return 0;
        }

        const T pop(){
            if(top){
                Node<T>* temp = top;
                T data = temp->data;
                top = top -> next;
                delete temp;
                count--;
                return data;
            }else
            {
                cout << "Stack empty!!\n";
            }
            
        }

        bool isEmpty() const{
            return top?false:true;
        }

        size_t length() const{
            return count;
        }

        void print() const{
            Node<T>* temp = top;
            cout << "\n********Stack********\n";
            while(temp){
                cout << "\t" << temp->data << '\n';
                temp = temp->next;
            }
            cout << "********---********\n";
        }

    private:
        Node<T> * top;
        size_t count;
};

#endif