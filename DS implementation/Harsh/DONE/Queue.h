#ifndef QUEUE_H
#define QUEUE_H

#include<iostream>
using namespace std;

template<typename T>
struct QueueNode{
    T val;
    QueueNode* next;
    QueueNode(const T& val, QueueNode*temp):val{val},next{temp}{}
};

template<typename T>
class Queue{
    public:
    
        Queue():front{nullptr},rear{nullptr},size{0}{}

        ~Queue(){
            int count{0};
            if(front){
                while(front){
                    QueueNode<T>*temp = front;
                    front = front->next;
                    count++;
                    delete temp;
                }

                cout << "Queue deleted::Elements deleted : " << count << endl;
            }
        }

        void enqueue(const T& val){
            if(rear && front){
                rear->next = new QueueNode<T>(val,nullptr);
                rear = rear->next; 
            }else{
                front = new QueueNode<T>(val,nullptr);
                rear = front;
            }
            size++;
        }

        T dequeue(){
            if(front && rear){
               QueueNode<T>* temp = front;
               T data = front->val;
               front = front->next;
               delete temp;
               size--;
               return data; 
            }
            else cout << "Empty queue\n";
        }

        
        
        const T& getFront()const{
            return front->data;
        }
        
        bool isEmpty(){return (front?false:true);}

        const T& getRear()const{
            return rear->data;
        }

        size_t length() const{
            return size;
        }

        void print() const{
            if(front){
                QueueNode<T>* temp = front;
                cout << "**********\n";
                while(temp){
                    cout << temp -> val << endl;
                    temp = temp->next;
                }
                cout << "**********\n";
            }else{
                cout << "Queue is empty" << endl;
            }
        }

    private:
        QueueNode<T>* front;
        QueueNode<T>* rear;
        size_t size;
    
};

#endif