#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include<iostream>
using namespace std;

template<typename T>
struct Node{
    T val;
    Node* next;
    Node(const T& val, Node*temp):val{val},next{temp}{}
};

template<typename T>
class CircularLinkedList{
    public:
    
        CircularLinkedList():head{nullptr},size{0}{
            cout << "CircularLinkedList created" << endl;
        }

        ~CircularLinkedList(){
            if(head){
                Node<T>*temp = head->next;
                while(temp->next != head){
                    Node<T>*t = temp;
                    temp = temp->next;
                    delete t;
                }
                delete head;

                cout << "CircularLinkedList deleted" << endl;
            }
        }

        const T& pushBack(const T& val){
            if(head){
                Node<T>* temp = head;
                while(temp->next != head)
                    temp = temp -> next;
                temp->next = new Node<T>(val, head);
                size++;
                return temp -> val;
            }
            head = new Node<T>(val,head);
            head->next = head;
            size++;
            return head->val;
        }

        const T& pushFront(const T& val){
            Node<T>* temp;
            Node<T>* t = head;
            if(!head){
                temp = new Node<T>(val,temp);
                temp->next = temp;
            }
            else{
                temp = new Node<T>(val,head);
                while(t->next != head)t = t->next;
            }
            head = temp;
            t->next = head;
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
                Node<T>*t = head; 
                if(head->next != head){
                    while(t->next != head)t = t->next;
                    head = head->next;
                    t->next = head;
                }
                int val = temp->val;
                delete temp;
                size--;
                return val;
            }
            if(temp){
                if(!temp->next)
                    prev->next = head;
                else
                    prev->next = temp->next;
                int val = temp->val;
                delete temp;
                size--;
                return val;
            }
                throw runtime_error("Element not found");
        }

        const T& addElement(const int& index, const T& val){
            if(!index)return pushFront(val);
            if(head){
                int count{0};
                Node<T>*temp = head;
                while(count != index-1){
                    temp = temp->next;
                    count++;
                }
                Node<T> *temp2 ;
                if(!temp->next)
                    temp2 = head;
                else
                    temp2 = temp->next;

                temp->next = new Node<T>(val, temp2);
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
                do{
                    cout << temp -> val << endl;
                    temp = temp->next;
                }while(temp != head);
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