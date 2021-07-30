/*  
L4.3 Write a program to implement a stack using two queues such that
the push operation runs in linear time and the pop operation runs in 
constant time.
*/

#include <iostream>
using namespace std;
#define MAX INT16_MAX
class QUEUE {
    public:
        // constructors and destructor
        QUEUE()
            :
            arr{new int[INT16_MAX]},size{INT16_MAX}, front{-1}, rear{-1}
            {}
        QUEUE(size_t n)
            :
            arr{new int[n]},size{n}, front{-1}, rear{-1}
            {}        
        ~QUEUE(){
            delete arr;
            cout << "!! Queue Deleted Successfully" << endl;
        }

        // main functions
        void enqueue(const int&);
        int dequeue();
        bool isEmpty() const;
        bool isFull() const;
        const int getRear() const;
        const int getFront() const;

        // auxillary functions
        size_t length() const;
        void print() const;
    private:
        int front, rear;
        int *arr;
        size_t size;
};
inline const int QUEUE::getRear() const {
    return arr[rear];
}
inline const int QUEUE::getFront() const {
    return arr[front];
}
inline bool QUEUE::isEmpty() const {
    return (front == rear && rear == -1);
}
inline bool QUEUE::isFull() const {
    return (rear == size-1);
}
inline void QUEUE::enqueue(const int& ele) {
    if(!isFull()) {
        if(isEmpty()) {
            front++;
        }
        arr[++rear] = ele;
    }else {
        throw runtime_error("Queue is Full");        
    }
}
inline int QUEUE::dequeue() {
    if(!isEmpty()) {
        int temp = arr[front];
        if(front == rear)
            front = rear = -1;
        else 
            front++;
        return temp;
    }else {
        throw runtime_error("Queue is Empty");
    }
}
inline size_t QUEUE::length() const {
    return (!isEmpty() ? rear-front+1 : 0);
}
void QUEUE::print() const{
    if(!isEmpty()) {        
        for(size_t i = front; i <= rear; i++) {
            if(i != rear)
                cout << arr[i] << " - ";
            else 
                cout << arr[i];
        }
    }else {
        std::cout << "!! Queue is Empty !!" << endl;
    }
    cout << endl;
}

class stack {
    public:
        stack() 
            : 
            size{MAX}, top{-1}
            {}
        stack(int n) 
            : 
            size{n}, top{-1}
            {}
        
        // Main operations
        bool push(int x) {
            if(!isFull()) {
                while(!q1.isEmpty()) {
                    q2.enqueue(q1.getFront());
                    q1.dequeue();
                }
                q1.enqueue(x);
                top++; 
                while(!q2.isEmpty()) {
                    q1.enqueue(q2.getFront());
                    q2.dequeue();
                }
                return true;
            }else {
                return false;
            }
        }
        int pop() {
            if(q1.isEmpty()) {
                return INT16_MIN;
            }
            int val = q1.getFront();
            q1.dequeue();
            top--;
            return val;            
        }

        // Other
        int peek() {
            if(!q1.isEmpty()) 
                return q1.getFront();
            else
                throw runtime_error("Stack is empty");
        }
        size_t getSize() const {
            return top+1;
        }
        bool isEmpty() const {
            return (top == -1 && q1.isEmpty());
        }
        bool isFull() {
            return top == size-1;
        }
    private:
        int size;
        int top{-1};
        QUEUE q1, q2;
};

int main() {
    int n;
    cout << "Enter Size of stack : ";
    cin >> n;
    if(n <= 0) {
        cout << "!! Invalid Size !!" << endl;
        return 0;
    }
    stack st(n);
    cout << "-----------------------------------------------------" << endl;
    cout << "!! Stack with size " << n << " created Successfully !!" << endl;
    cout << "-----------------------------------------------------" << endl;        

    while(1) {
        cout << endl << "-------- STACK IMPLEMENTATION --------" << endl;
        cout << "1. PUSH" << endl;
        cout << "2. POP" << endl;
        cout << "3. PEEK" << endl;
        cout << "4. GET-SIZE" << endl;
        cout << "5. IS-EMPTY" << endl;
        cout << "6. IS-FULL" << endl;
        cout << "0. EXIT" << endl;
        cout << "Choice --> ";
        int choice;
        cin >> choice;

        cout << endl;
        cout << "-----------------------------------------------------" << endl;
        switch(choice) {
            case 1 : {
                int ele;
                cout << "Enter element to push into stack : ";
                cin >> ele;
                bool pushCheck = st.push(ele);
                if(pushCheck) {
                    cout << ele << " - Element pushed successfully" << endl;
                }else {
                    cout << "!! Error : There is some error occured while pushing the element !!" << endl;
                }
                break;
            }

            case 2 : {
                int popEle = st.pop();
                if (popEle != INT16_MIN) {
                    cout << popEle << " successfully poped from the stack" << endl;
                }else {
                    cout << "!! Error : Some error occured while poping the element !!" << endl;
                }
                break;
            }

            case 3 : {
                int  topEle = st.peek();
                if(topEle != INT16_MIN) 
                    cout << "Element on top is : " << st.peek() << endl;
                else 
                    cout << "!! Error : Some error occured !!" << endl;
                break;
            }

            case 4 : {
                cout << "Current Size of stack is : " << st.getSize() << endl;
                break;
            }

            case 5 : { 
                if(st.isEmpty()) {
                    cout << "!! Stack is Empty !!" << endl;
                }else {
                    cout << "!! Stack is not Empty !!" << endl;
                }
                break;
            }

            case 6 : { 
                if(st.isFull()) {
                    cout << "!! Stack is FULL !!" << endl;
                }else {
                    cout << "!! Stack is NOT FULL !!" << endl;
                }
                break;
            }

            case 0 : {
                return 0;
            }

            default : {
                cout << "!! Please Enter correct option !!" << endl;
                break;
            }
        }
    }
    return 0;
}