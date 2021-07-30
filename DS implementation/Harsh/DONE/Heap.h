#ifndef HEAP_H
#define HEAP_H

#include<iostream>
using namespace std;

template<typename T>
class Heap{
    public:
        Heap(int c):capacity{c},arr{new T[c]},size{-1}{}
        int parent(int i){
            if(i > -1 && i < capacity)return ((i-1)/2);
            return -1;
        }

        int left(int i){
            if(i > -1 && i < capacity)return (2*i+1);
            return -1;
        }

        int right(int i){
            if(i > -1 && i < capacity)return (2*i+2);
            return -1;
        }

        void heapify(int index){
            if(size == -1){
                cout << "[Underflow]Heap is empty!\n";
                return;
            }
            if(index < 0 || index > size){
                cout << "[Invalid index!]\n";
                return;
            }

            int i = index;
            while(i != 0 && arr[i] < arr[parent(i)]){
                swap(arr[i], arr[parent(i)]);
                i = parent(i);
            }
        }

        void heapifyRoot(){
            if(size != -1){
                int i{0};
                int lt{0},rt{0};
                while(lt <= size || rt <= size){
                    lt = left(i); rt = right(i);
                    T smallest = arr[i];
                    int temp;
                    if(lt <= size && arr[lt] < smallest){
                        smallest = arr[lt];
                        temp = lt;
                    }
                    if(rt <= size && arr[rt] < smallest){
                        smallest = arr[rt];
                        temp = rt;
                    }

                    if(smallest == arr[i]){
                        return;
                    }else{
                        swap(arr[i],arr[temp]);
                        i = temp;
                    }
                }
            }
        }

        void decreaseKey(int index, T val){
            if(index < 0 || index > size){
                cout << "[Invalid index!]\n";
                return;
            }

            if(arr[index] < val){
                cout << "[Enter key value lesser than stored value!]\n";
                return;
            }

            arr[index] = val;
            heapify(index);
        }

        void insert(T val){
            if(size == capacity-1){
                cout << "[Overflow]Heap is full!\n";
                return;
            }
            size++;
            arr[size] = val;
            heapify(size);
        }

        void deleteKey(int index){
            if(index < 0 || index > size){
                cout << "[Invalid index!]\n";
                return;
            }
            //Dont know how to assign a generic minimum according to type
            //So this method right now works for integer type only
            arr[index] = INT32_MIN;
            heapify(index);
            extraxtMin();
        }

        T getMin(){
            return arr[0];
        }

        T extraxtMin(){
            swap(arr[0],arr[size]);
            T temp = arr[0];
            size--;
            heapifyRoot();
            return temp;
        }

        void print(){
            if(size == -1){
                cout << "[Underflow]Heap is empty!\n";
                return; 
            }
            for(int i = 0; i <= size; i++)cout << arr[i] << " ";
            cout << endl; 
        }

    private:
        T* arr;
        int capacity;
        int size;
};
INT



#endif