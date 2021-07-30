#ifndef DOUBLYCIRCULARLINKEDLIST_H
#define DOUBLYCIRCULARLINKEDLIST_H

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
class DoublyCircularLinkedList{
    public:
    
        DoublyCircularLinkedList():head{nullptr},tail{nullptr},size{0}{
            cout << "DoublyCircularLinkedList created" << endl;
        }

        ~DoublyCircularLinkedList(){
            int count{0};
            if(head){
                while(head != tail){
                    Node<T>*temp = head;
                    head = head->next;
                    count++;
                    delete temp;
                }
                delete tail;
                count++;
                cout << "Doubly-CircularLinkedList deleted::Elements Deleted : "  << count<< endl;
            }
        }

        const T& pushBack(const T& val){
            if(head){
                Node<T>* temp = head;
                while(temp != tail)
                    temp = temp -> next;
                temp->next = new Node<T>(val, head,temp);
                tail = temp->next;
                size++;
                return temp -> val;
            }
            //Cannot pass head, head as prev,next in the node constructor , becasue head will be nullptr at taht time, so first we need to create head and than initialize its next and prev.
            head = new Node<T>(val,nullptr,nullptr);
            head -> next = head;
            head -> prev = head;
            tail = head;
            size++;
            return head->val;
        }

        const T& pushFront(const T& val){
            Node<T>* temp = new Node<T>(val,head,tail);
            if(!head){
                temp -> next = temp;
                tail = temp;
            }
            head = temp;
            tail->next = head;
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
                head->prev = tail;
                tail->next = head;
                int val = temp->val;
                delete temp;
                size--;
                return val;
            }
            if(temp){
                temp->prev->next= temp->next;
                if(temp == tail)tail = temp->prev;
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
                do{
                    cout << temp -> val << endl;
                    temp = temp->next;
                }while(temp != head);

                cout << "**********\n";
            }else{
                cout << "Circult Doubly Linked list is empty" << endl;
            }
        }

    private:
        Node<T>* head;
        Node<T>* tail;
        size_t size;
    
};

#endif