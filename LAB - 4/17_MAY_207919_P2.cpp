/*  
L4.2 Write a program to implement double ended queue (Deque) using arrays
    1. EnQueueFront
    2. EnQueueRear
    3. DeQueueFront
    4. DeQueueRear
    5. getRear
    5. getFront
    6. Print
    7. Size
    8. isEmpty
    9. isFull
*/
#include <iostream>
using namespace std;

class DEQUEUE
{
public:
    // constructors and destructor
    DEQUEUE()
        : arr{new int[INT8_MAX]}, size{INT8_MAX}, front{-1}, rear{-1}, length{0}
    {
    }
    DEQUEUE(size_t n)
        : arr{new int[n]}, size{n}, front{-1}, rear{-1}, length{0}
    {
    }
    ~DEQUEUE()
    {
        delete arr;
        cout << "!! Queue Deleted Successfully" << endl;
    }

    // main functions
    void enqueue_rear(const int &);
    void enqueue_front(const int &);
    int dequeue_front();
    int dequeue_rear();
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
inline void DEQUEUE::enqueue_rear(const int &ele)
{
    if (!isFull())
    {
        if (isEmpty())
        {
            front++;
            rear++;
        }
        else
        {
            rear = (rear + 1) % size;
        }
        arr[rear] = ele;
        length++;
    }
    else
    {
        throw runtime_error("Queue is Full");
    }
}
inline void DEQUEUE::enqueue_front(const int &ele)
{
    if (!isFull())
    {
        if (isEmpty())
        {
            front++;
            rear++;
        }
        else
        {
            front = (front + size - 1) % size;
        }
        arr[front] = ele;
        length++;
    }
    else
    {
        throw runtime_error("Queue is Full");
    }
}

inline int DEQUEUE::dequeue_front()
{
    if (!isEmpty())
    {
        int temp = arr[front];
        if (front == rear)
            front = rear = -1;
        else
            front = (front + 1) % size;
        length--;
        return temp;
    }
    else
    {
        throw runtime_error("Queue is Empty");
    }
}
inline int DEQUEUE::dequeue_rear()
{
    if (!isEmpty())
    {
        int temp = arr[rear];
        if (front == rear)
            front = rear = -1;
        else
            rear = (rear + size - 1) % size;
        length--;
        return temp;
    }
    else
    {
        throw runtime_error("Queue is Empty");
    }
}
inline const int DEQUEUE::getRear() const
{
    return arr[rear];
}
inline const int DEQUEUE::getFront() const
{
    return arr[front];
}
void DEQUEUE::print() const
{
    if (!isEmpty())
    {
        if (front <= rear)
        {
            for (size_t i = front; i <= rear; i++)
            {
                if (i != rear)
                    cout << arr[i] << " - ";
                else
                    cout << arr[i];
            }
        }
        else
        {
            for (size_t i = front; i <= size - 1; i++)
            {
                cout << arr[i] << " - ";
            }
            for (size_t i = 0; i <= rear; i++)
            {
                if (i != rear)
                    cout << arr[i] << " - ";
                else
                    cout << arr[i];
            }
        }
    }
    else
    {
        std::cout << "!! Queue is Empty !!" << endl;
    }
    cout << endl;
}
inline bool DEQUEUE::isEmpty() const
{
    return (front == rear && rear == -1);
}
inline bool DEQUEUE::isFull() const
{
    return ((rear + 1) % size == front);
}
inline size_t DEQUEUE::getLength() const
{
    return (!isEmpty() ? length : 0);
}
int main()
{
    int n;
    cout << "Enter Size of queue you want to create : ";
    cin >> n;
    DEQUEUE myQueue(n);
    while (true)
    {
        cout << "------------------- MENU -------------------" << endl;
        cout << "1. EnQueue - rear" << endl;
        cout << "2. EnQueue - front" << endl;
        cout << "3. Dequeue - front" << endl;
        cout << "4. Dequeue - rear" << endl;
        cout << "5. Print" << endl;
        cout << "6. Size" << endl;
        cout << "7. GetFront" << endl;
        cout << "8. GetRear" << endl;
        cout << "0. EXIT" << endl;
        cout << "Choice --> ";
        int choice;
        cin >> choice;
        cout << "---------------------------------------------" << endl;
        switch (choice)
        {
        case 1:
        {
            int ele;
            cout << "!!! ENQUEUE - Rear !!!" << endl;
            cout << "Element value : ";
            cin >> ele;
            myQueue.enqueue_rear(ele);
            break;
        }
        case 2:
        {
            int ele;
            cout << "!!! ENQUEUE - Front !!!" << endl;
            cout << "Element value : ";
            cin >> ele;
            myQueue.enqueue_front(ele);
            break;
        }
        case 3:
        {
            int ele;
            cout << "!!! DEQUEUE - Front !!!" << endl;
            int deleted = myQueue.dequeue_front();
            cout << "Element " << deleted << " deleted successfully" << endl;
            break;
        }
        case 4:
        {
            int ele;
            cout << "!!! DEQUEUE - Rear !!!" << endl;
            int deleted = myQueue.dequeue_rear();
            cout << "Element " << deleted << " deleted successfully" << endl;
            break;
        }
        case 5:
        {
            cout << "!!! PRINT LIST !!!" << endl;
            myQueue.print();
            break;
        }
        case 6:
        {
            cout << "SIZE : " << myQueue.getLength() << endl;
            break;
        }
        case 7:
        {
            cout << "!! Get Front !!" << endl;
            if (!myQueue.isEmpty())
            {
                cout << "Front : " << myQueue.getFront() << endl;
            }
            else
            {
                cout << "!! Error : Queue is Empty !!" << endl;
            }
            break;
        }
        case 8:
        {
            cout << "!! Get Rear !!" << endl;
            if (!myQueue.isEmpty())
            {
                cout << "Rear : " << myQueue.getRear() << endl;
            }
            else
            {
                cout << "!! Error : Queue is Empty !!" << endl;
            }
            break;
        }
        case 0:
        {
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