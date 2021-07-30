/*
Implement a simple queue
Write a program to implement a simple queue with the following operation
1. bool enQueue(int v)
2. int deQueue()
3. bool isEmpty()
4. bool isFull()
5. int size()
6. int peek()
7. void print()  
*/
#include <iostream>
using namespace std;

#define MAX 500

class queue {
    public:
        // constructors
        queue() :
            a{new int[MAX]},front{-1},rear{-1},size{MAX}
            {}
        queue(int n) :
            a{new int[n]},front{-1},rear{-1},size{n}
            {}
        
        // functions
        bool enqueue(int);
        int dequeue();
        bool isEmpty();
        bool isFull();
        int getSize();
        int peek();
        void print();

    private:
        int front,rear,size;
        int *a;
};

// function definations

bool queue::enqueue(int val) {
    if(!isFull()) {
        if(isEmpty()) {
            front++;
        }
        a[++rear] = val; 
        return true;
    }
    return false;
}

int queue::dequeue() {
    if(!isEmpty()) {
        int val = a[front];
        if(front == rear) 
            front = rear = -1;
        else
            front++;
        return val;
    }else {
        throw runtime_error("Queue is Empty");
        return INT32_MIN;
    }
}

bool queue::isEmpty() {
    return (front == rear && rear == -1);
}

bool queue::isFull() {
    return (rear == size-1);
}

int queue::getSize() {
    return !isEmpty() ? rear-front+1 : 0;
}

// will return element present at rear end
int queue::peek() {
    if(!isEmpty()) {
        return a[rear];
    }else {
        throw runtime_error("Queue is empty");
    }
}

void queue::print() {
    if(!isEmpty()) {
        for(int i = front; i <= rear; i++) {
            if(i != rear)
                cout << a[i] << " - ";
            else 
                cout << a[i];
        }
    }
    cout << endl;
}

int main() {
    queue myQueue;
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
            cout << "!!! ENQUEUE !!!" << endl;
            cout << "Element value : ";
            cin >> ele;
            bool check = myQueue.enqueue(ele);
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
            int deleted = myQueue.dequeue();
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
            cout << "SIZE : " << myQueue.getSize() << endl;
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