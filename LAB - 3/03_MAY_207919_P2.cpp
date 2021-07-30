/*  
L3.1 Write a program to implement a queue using two stacks such that the enqueue operation
    runs in linear time and the dequeue operation runs in constant time. Implement the following operations.
    bool EnQueue(int v)
    int DeQueue()
    bool isEmpty()
    int size()
    void print()
*/

#include <iostream>
using namespace std;
#define MAX 5000

class stack {
    public:
        stack() : size{MAX}, top{-1}{}
        stack(int n) : size{n}, top{-1}{}
        
        // Main operations
        bool push(int ele) {
            if(!isFull()) {
                a[++top] = ele;
                return true;
            }else {
                cout << "!! Error : Stack is Full" << endl;
                return false;
            }
        }
        int pop() {
            if(!isEmpty()) {
                int x = a[top];
                top--;
                return x;
            }else {
                cout << "!! Error : Stack is Empty" << endl;
                return INT16_MIN;
            }
        }

        // Other
        int peek() {
            if(top >= 0 && top <= size) return a[top];
            else {
                cout << "!! Error : Top Out of bound !!" << endl;
                return INT16_MIN;
            }            
        }
        int getSize() {return size;}
        bool isEmpty() {return (top == -1);}
        bool isFull() {return (size-1 == top);}
    private:
        int size;
        int top{-1};
        int a[MAX];
};

class StackQueue{
    public:
        StackQueue(int qSize) : qSize{qSize}{}
        StackQueue() : qSize{MAX} {}
        bool EnQueue(int);
        int DeQueue();
        bool isFull() {return length == qSize;}
        bool isEmpty() {return s1.isEmpty();}
        int size() {return length;}
        void print();
    private:
        stack s1;
        stack s2;
        int length{0}, qSize{0};
};
void StackQueue::print() {
    if(s1.isEmpty()) {
        __throw_runtime_error ("Queue is empty");
    }
    cout << "front-> ";
    while(!s1.isEmpty()) {
        int temp = s1.peek();
        s2.push(s1.peek());
        s1.pop();        
        if(!s1.isEmpty()) 
            cout << temp << "->";
        else
            cout << temp << " <-rear";
    }
    cout << endl;
    while(!s2.isEmpty()) {
        s1.push(s2.peek());
        s2.pop();
    }
}
bool StackQueue::EnQueue(int val) {
    if(!isFull()) {
        while(!s1.isEmpty()) {
            s2.push(s1.peek());
            s1.pop();
        }
        s1.push(val);
        while(!s2.isEmpty()) {
            s1.push(s2.peek());
            s2.pop();
        }
    }else {
        cout << "!! Error : Queue is Full !!" << endl;
        return false;
    }
    length++;
    return true;
}
int StackQueue::DeQueue() {
    if(isEmpty()) {
        __throw_runtime_error ("Qeueue is Empty");
    }
    int ele = s1.peek();
    s1.pop();
    length--;
    return ele;
}

int main() {
    StackQueue myQueue;
    while(true) {
        cout << "------------------- MENU -------------------" << endl;
        cout << "1. EnQueue" << endl;
        cout << "2. DeQueue" << endl;
        cout << "3. Print" << endl;
        cout << "4. Size of Queue" << endl;
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
            bool check = myQueue.EnQueue(ele);
            if(check) {
                cout << "Element " << ele << " inserted successfully" << endl;
            }else {
                cout << "!! Error : cannot insert Element !!" << endl;
            }
            break;
        }
        case 2: {
            int ele;
            cout << "!!! DEQUEUE !!!" << endl;
            int deleted = myQueue.DeQueue();
            if(deleted != INT32_MIN) {
                cout << "Element " << deleted << " deleted successfully" << endl;
            }else {
                cout << "!! Error : cannot delete Element !!" << endl;
            }
            break;
        }
        case 3: {
            cout << "!!! PRINT QUEUE !!!" << endl;
            myQueue.print();
            break;
        }   
        case 4: {
            cout << "SIZE : " << myQueue.size() << endl;
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
    return 0;
}