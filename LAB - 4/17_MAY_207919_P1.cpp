/*  
L4.1 Write a program to implement circular queue using arrays/
    1. EnQueue
    2. DeQueue
    3. Peek
    4. Print
    5. Size
    6. isEmpty
    7. isFull
*/
#include <iostream>
using namespace std;

class CircluarQueue {
    public:
        // constructors and destructor
        CircluarQueue()
            :
            arr{new int[INT8_MAX]},size{INT8_MAX}, front{-1}, rear{-1}, length{0}
            {}
        CircluarQueue(size_t n)
            :
            arr{new int[n]},size{n}, front{-1}, rear{-1}, length{0}
            {}        
        ~CircluarQueue(){
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
        size_t getLength() const;
        void print() const;
    private:
        int front, rear;
        int *arr;
        size_t size, length;
};
inline void CircluarQueue::enqueue(const int& ele) {
    if(!isFull()) {
        if(isEmpty()) {
            front++;
            rear++;
        }else {
            rear = (rear+1)%size;
        }
        arr[rear] = ele;
        length++;
    }else {
        throw runtime_error("Queue is Full");        
    }
}
inline int CircluarQueue::dequeue() {
    if(!isEmpty()) {
        int temp = arr[front];
        if(front == rear)
            front = rear = -1;
        else 
            front = (front+1)%size;
        length--;
        return temp;
    }else {
        throw runtime_error("Queue is Empty");
    }
}
inline const int CircluarQueue::getRear() const {
    return arr[rear];
}
inline const int CircluarQueue::getFront() const {
    return arr[front];
}
void CircluarQueue::print() const{
    if(!isEmpty()) {
        if(front <= rear) {
            for(size_t i = front; i <= rear; i++) {
                if(i != rear)
                    cout << arr[i] << " - ";
                else 
                    cout << arr[i];
            }
        }else {
            for(size_t i = front; i <= size-1; i++) {
                    cout << arr[i] << " - ";
            }
            for(size_t i = 0; i <= rear; i++) {
                if(i != rear)
                    cout << arr[i] << " - ";
                else 
                    cout << arr[i];
            }
        }        
    }else {
        std::cout << "!! Queue is Empty !!" << endl;
    }
    cout << endl;
}
inline bool CircluarQueue::isEmpty() const {
    return (front == rear && rear == -1);
}
inline bool CircluarQueue::isFull() const {
    return ((rear+1)%size == front);
}
inline size_t CircluarQueue::getLength() const {
    return (!isEmpty() ? length : 0);
}
int main() {
    int n;
    cout << "Enter Size of queue you want to create : ";
    cin >> n;
    CircluarQueue myQueue(n);
    while(true) {
        cout << "------------------- MENU -------------------" << endl;
        cout << "1. EnQueue" << endl;
        cout << "2. Dequeue" << endl;
        cout << "3. Print" << endl;
        cout << "4. Size" << endl;
        cout << "5. GetFront" << endl;
        cout << "6. GetRear" << endl; 
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
            myQueue.enqueue(ele);
            break;
        }
        case 2: {
            int ele;
            cout << "!!! DEQUEUE !!!" << endl;
            int deleted = myQueue.dequeue();
            cout << "Element " << deleted << " deleted successfully" << endl;
            break;
        }
        case 3: {
            cout << "!!! PRINT LIST !!!" << endl;
            myQueue.print();
            break;
        }   
        case 4: {
            cout << "SIZE : " << myQueue.getLength() << endl;
            break;
        }
        case 5: {
            cout << "!! Get Front !!" << endl;
            if(!myQueue.isEmpty()) {
                cout << "Front : " << myQueue.getFront() << endl;
            }else {
                cout << "!! Error : Queue is Empty !!" << endl; 
            }
            break;
        }
        case 6: {
            cout << "!! Get Rear !!" << endl;
            if(!myQueue.isEmpty()) {
                cout << "Rear : " << myQueue.getRear() << endl;
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