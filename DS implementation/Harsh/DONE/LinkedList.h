#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<iostream>
using namespace std;

template<typename T>
struct Node{
    T val;
    Node* next;
    Node(const T& val, Node*temp):val{val},next{temp}{}
};

template<typename T>
class LinkedList{
    public:
    
        LinkedList():head{nullptr},size{0}{
            cout << "LinkedList created" << endl;
        }

        ~LinkedList(){
            if(head){
                while(head){
                    Node<T>*temp = head;
                    head = head->next;
                    delete temp;
                }

                cout << "LinkedList deleted" << endl;
            }
        }

        const T& pushBack(const T& val){
            if(head){
                Node<T>* temp = head;
                while(temp->next)
                    temp = temp -> next;
                temp->next = new Node<T>(val, nullptr);
                size++;
                return temp -> val;
            }
            head = new Node<T>(val,nullptr);
            size++;
            return head->val;
        }

        const T& pushFront(const T& val){
            Node<T>* temp = new Node<T>(val,head);
            head = temp;
            size++;
            return head -> val;
        }

        T deleteElement(const T&val){
            Node<T>*temp = head;
            Node<T>*prev = nullptr;
            while(temp->val != val){
                prev = temp;
                temp = temp->next; 
            }
            if(temp == head){
                head = head->next;
                int val = temp->val;
                delete temp;
                size--;
                return val;
            }
            if(temp){
                prev->next = temp->next;
                int val = temp->val;
                delete temp;
                size--;
                return val;
            }
                throw runtime_error("Element not found");
        }

        const T& addElement(const int& index, const T& val){
            if(!index){
                Node<T>*temp3 = head;
                head = new Node<T>(val, temp3);
                size++;
                return val;
            }
            if(head){
                int count{0};
                Node<T>*temp = head;
                while(count != index-1){
                    temp = temp->next;
                    count++;
                }
                Node<T> *temp2 = temp->next;
                temp->next = new Node<T>(val, temp2);
                size++;
                return val;
            }
            head = new Node<T>(val, nullptr);
            size++;
            return val;
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
           Node<T>* prev = nullptr;
           Node<T>*current = head;
           Node<T>*next  = nullptr;

           while(current){
               next = current->next;
               current->next = prev;
               prev = current;
               current = next;
           }
           head = prev;
        }

    private:
        Node<T>* head;
        size_t size;
    
};

#endif