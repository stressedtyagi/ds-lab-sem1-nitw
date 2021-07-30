#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include<iostream>
using namespace std;

template<typename T>
class CircularQueue{
    private:
        T* arr;
        int front;
        int rear;
        size_t length;
        size_t capacity;

    public:
        CircularQueue(const size_t &size):length{0},front{-1},rear{-1},capacity{size}{
            arr = new int[size];
            cout << "Circular queue created\n";
        }

        ~CircularQueue(){
            delete[] arr;
            cout << "Circular queue deleted\n";
        }

        void enqueue(const T& val){
            int temp = (rear+1)%capacity;
            if(temp != front || !length){
                rear = temp;
                arr[rear] = val;
                length++;
                if(!rear && front == -1)front = 0;
            }else{
                cout << "Queue full!\n";
            }

            cout << "*****front: " << front << " " << "rear: " << rear << endl;
        }

        T dequeue(){
            if(length){
                length--;
                T data = arr[front];

                front = (front+1)%capacity;
    
                cout << "*****front: " << front << " " << "rear: " << rear << endl;

                return data;
            }else{
                cout << "Empty queue\n";
            }
        }

        size_t getLength()const{return length;}

        void print(){
            if(length){
                cout << "\n**********\n";
                int temp = front;
                while(temp != rear){
                    cout << arr[temp] << endl;
                    temp = (temp+1)%capacity;
                }
                cout << arr[rear] << endl;
                cout << "**********\n";
            }else{
                cout << "Circular queue empty\n";
            }
        }

};

#endif
