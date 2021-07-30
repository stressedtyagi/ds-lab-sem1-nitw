/*  
L4.5 Write a program to implement a stack using linked list.
    push, pop, peek, print, size, isEmpty()
*/

#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(const int val, ListNode* next = nullptr) 
        : 
        val{val}, next{next}
        {}
};
class STACK {
    public:
        // Utilities
        STACK()
            :
            size{0}, top{nullptr}
            {}
        ~STACK(){
            while (top) {
                ListNode* temp = top->next;
                delete top;
                top = temp;
            }
            cout << "!! Stack Deleted Successfully" << endl;
        }

        // main functions
        void push(const int&);
        int pop();
        bool isEmpty() const;
        const int getTop() const;

        // auxillary functions
        size_t length() const;
        void print() const;
    private:
        ListNode *top;
        size_t size;
};
inline const int STACK::getTop() const {
    return top->val;
}
inline bool STACK::isEmpty() const {
    return (top == nullptr);
}
inline void STACK::push(const int& ele) {
    ListNode* newNode = new ListNode(ele,top);
    top = newNode;
    size++;
}
inline int STACK::pop() {
    if(!isEmpty()) {
        ListNode* temp = top;
        int ele = getTop();
        top = top->next;
        delete temp;
        size--;
        return ele;
    }else {
        throw runtime_error("Stack is Empty");
    }
}
inline size_t STACK::length() const {
    return size;
}
void STACK::print() const{
    if(!isEmpty()) {
        ListNode* temp = top;
        while(temp) {
            if(temp->next != nullptr)
                cout << temp->val << "->";
            else 
                cout << temp->val;
            temp = temp->next;
        }
        cout << endl;
    }else {
        std::cout << "!! Stack is Empty !!" << endl;
    }
}

int main() {
    STACK myStack;
    while(true) {
        cout << "------------------- MENU -------------------" << endl;
        cout << "1. Push" << endl;
        cout << "2. Pop" << endl;
        cout << "3. Print" << endl;
        cout << "4. Size" << endl;
        cout << "0. EXIT" << endl;
        cout << "Choice --> ";
        int choice;
        cin >> choice;
        cout << "---------------------------------------------" << endl;
        switch (choice) {
        case 1: {
            int ele;
            cout << "!!! PUSH FRONT !!!" << endl;
            cout << "Element value : ";
            cin >> ele;
            myStack.push(ele);
            break;
        }
        case 2: {
            int ele;
            cout << "!!! POP ELEMENT !!!" << endl;
            int deleted = myStack.pop();
            cout << "Element " << deleted << " deleted successfully" << endl;
            break;
        }
        case 3: {
            cout << "!!! PRINT STACK !!!" << endl;
            myStack.print();
            break;
        }   
        case 4: {
            cout << "SIZE : " << myStack.length() << endl;
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