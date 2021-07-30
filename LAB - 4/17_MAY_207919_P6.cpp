/*  
L4.6 Write a program to implement circular queue using linked list
    EnQueue, Dequeue, Preek, Print, Size, isEmpty
*/
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(const int val, ListNode* next = nullptr) : val{val}, next{next}{}
};

class CircularQueue {
    public:
        // Utilities
        CircularQueue():size{0}, head{nullptr}{}
        ~CircularQueue(){
            if (size == 1) {
                delete head;
            }else if (size > 1){
                ListNode* curr = head->next;
                while(curr->next != head) {
                    curr = curr->next;
                }
                curr->next = nullptr;
                curr = head;
                while(curr) {
                    ListNode* temp = curr;
                    curr = curr->next;
                    delete temp;
                }
                delete head;
            }
            cout << "!! Linked List Deleted Successfully" << endl;
        }

        // helper functions
        void push_back(const int&);
        void push_front(const int&);
        int delete_element();
        int peek() const {return head->val;}
        bool isEmpty() const {return head == nullptr;}
        size_t length() const {return size;};
        void print() const;
    private:
        ListNode *head;
        size_t size;
};
inline void CircularQueue::push_back(const int& ele) {
    if(head == nullptr) {
        head = new ListNode(ele);
        head->next = head;
    }else {
        ListNode* curr = head;
        while(curr->next != head) {
            curr = curr->next;
        }
        curr->next = new ListNode(ele,head);
    }
    size++;
}
inline void CircularQueue::push_front(const int& ele) {
    if(head == nullptr) {
        head = new ListNode(ele);
        head->next = head;
    }else {
        ListNode* newNode = new ListNode(ele,head);
        ListNode* curr = head;
        while(curr->next != head) {
            curr = curr->next;
        }
        curr->next = newNode;
        head = newNode;
    }
    size++;
}
inline int CircularQueue::delete_element() {
    if(head == nullptr) {
        throw runtime_error("Queue in empty");
    }
    ListNode* curr = head->next;
    ListNode* prev = head;
    while(curr != head) {
        prev = curr;
        curr = curr->next;
    }
    ListNode* temp = head;
    int delete_val = temp->val;
    if(prev->next != curr->next)
        prev->next = curr->next;
    size--;
    if(size > 0) head = head->next;
    if(size == 0) head = nullptr;
    delete temp;
    return delete_val;
}
void CircularQueue::print() const{
    if(head == nullptr) {
        throw runtime_error("!! Queue is empty !!");
        return;
    }
    ListNode* curr = head;
    if(size == 1) {
        cout << curr->val;
    }else {
        while(curr->next != head) {            
            cout << curr->val << " -> ";
            curr = curr->next;
        }
        cout << curr->val;
    }
    cout << endl;
}

int main() {
    CircularQueue myQueue;
    while(true) {
        cout << "------------------- MENU -------------------" << endl;
        cout << "1. EnQueue" << endl;
        cout << "2. Dequeue" << endl;
        cout << "3. Print" << endl;
        cout << "4. Size" << endl;
        cout << "5. GetFront" << endl;
        cout << "0. EXIT" << endl;
        cout << "Choice --> ";
        int choice;
        cin >> choice;
        cout << "---------------------------------------------" << endl;
        switch (choice) {
        case 1: {
            int ele;
            cout << "!!! ENQUEUE !!!" << endl;
            cout << "Element value : ";
            cin >> ele;
            myQueue.push_back(ele);
            break;
        }
        case 2: {
            int ele;
            cout << "!!! DEQUEUE !!!" << endl;
            int deleted = myQueue.delete_element();
            cout << "Element " << deleted << " deleted successfully" << endl;
            break;
        }
        case 3: {
            cout << "!!! PRINT Queue !!!" << endl;
            myQueue.print();
            break;
        }   
        case 4: {
            cout << "SIZE : " << myQueue.length() << endl;
            break;
        }
        case 5: {
            cout << "!! Get Front !!" << endl;
            if(!myQueue.isEmpty()) {
                cout << "Front : " << myQueue.peek() << endl;
            }else {
                cout << "!! Error : Queue is Empty !!" << endl; 
            }
            break;
        }
        case 0: {
            return 0;
            break;
        }
        default:
            cout << "!! Incorrect Option" << endl;
            break;
        }
        cout << "---------------------------------------------" << endl;
    }

}