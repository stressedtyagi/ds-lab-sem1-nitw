#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include<iostream>
using namespace std;

template<typename T>
struct Node{
    T val;
    Node* next;
    Node* prev;
    Node(const T& val, Node*temp, Node*temp2):val{val},next{temp},prev{temp2}{}
};

template<typename T>
class DoublyLinkedList{
    public:
    
        DoublyLinkedList():head{nullptr},size{0}{
            cout << "DoublyLinkedList created" << endl;
        }

        ~DoublyLinkedList(){
            if(head){
                while(head){
                    Node<T>*temp = head;
                    head = head->next;
                    delete temp;
                }

                cout << "Doubly-LinkedList deleted" << endl;
            }
        }

        const T& pushBack(const T& val){
            if(head){
                Node<T>* temp = head;
                while(temp->next)
                    temp = temp -> next;
                temp->next = new Node<T>(val, nullptr,temp);
                size++;
                return temp -> val;
            }
            head = new Node<T>(val,nullptr,nullptr);
            size++;
            return head->val;
        }

        const T& pushFront(const T& val){
            Node<T>* temp = new Node<T>(val,head,nullptr);
            head = temp;
            size++;
            return head -> val;
        }

        T deleteElement(const T&val){
            Node<T>*temp = head;
            while(temp->val != val){
                temp = temp->next; 
            }
            if(temp == head){
                head = head->next;
                head->prev = nullptr;
                int val = temp->val;
                delete temp;
                size--;
                return val;
            }
            if(temp){
                temp->prev->next= temp->next;
                int val = temp->val;
                delete temp;
                size--;
                return val;
            }
                throw runtime_error("Element not found");
        }

        const T& addElement(const int& index, const T& val){
            if(!index)return pushFront(val);
            if(index == size)return pushBack(val);
            if(head){
                int count{0};
                Node<T>*temp = head;
                while(count != index){
                    temp = temp->next;
                    count++;
                }
                temp->prev->next = new Node<T>(val, temp,temp->prev);
                size++;
                return val;
            }
        }

        T& operator[](size_t index) const{
            if(index < size){
                Node<T> *temp = head;
                size_t count{0};
                while(count != index){
                    count++;
                    temp = temp->next;
                }
                return temp->val;
            }else
                throw runtime_error("Index out of bound exception");
        }

        size_t length() const{
            return size;
        }

        void print() const{
            if(head){
                Node<T>* temp = head;
                cout << "**********\n";
                while(temp){
                    cout << temp -> val << endl;
                    temp = temp->next;
                }
                cout << "**********\n";
            }else{
                cout << "Linked list is empty" << endl;
            }
        }

        void reverse(){
            Node<T>* secondLast = head;
            int count{0};
            
        }

    private:
        Node<T>* head;
        size_t size;
    
};

#endif