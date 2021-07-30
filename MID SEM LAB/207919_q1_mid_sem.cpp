#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
    Node(int d, Node *t) : data{d}, next{t} {}
};

class Integer_Stack
{
public:
    Integer_Stack() : top{nullptr}, count{0} {}

    void push(int val)
    {
        Node *temp;
        temp = new Node(val, top);
        top = temp;
        count++;
    }

    int getTop() const
    {
        if (top)
            return top->data;
        else
            return 0;
    }

    int pop()
    {
        if (top)
        {
            Node *temp = top;
            int data = temp->data;
            top = top->next;
            delete temp;
            count--;
            return data;
        }
        else
        {
            cout << "Stack empty!!\n";
            return INT32_MAX;
        }
    }

    bool isEmpty() const
    {
        return top ? false : true;
    }

    size_t length() const
    {
        return count;
    }

    void print() const
    {
        Node *temp = top;
        cout << "front-> ";
        while (temp)
        {
            cout << temp->data << ' ';
            temp = temp->next;
        }
        cout << " <-rear";
        cout << endl;
    }

private:
    Node *top;
    size_t count;
};

class Dequeue
{
public:
    bool EnQueueFront(int v)
    {
        is.push(v);
        return true;
    }

    int DeQueueFront()
    {
        if (is.isEmpty())
            return INT32_MAX;
        return is.pop();
    }

    bool EnQueueRear(int v)
    {
        if (is.isEmpty())
        {
            is.push(v);
            return true;
        }

        int temp = is.pop();
        EnQueueRear(v);
        is.push(temp);
        return true;
    }

    int DeQueueRear()
    {
        if (is.isEmpty())
            return INT32_MAX;
        if (is.length() == 1)
        {
            return is.pop();
        }
        int t1 = is.pop();
        int t2 = DeQueueRear();
        is.push(t1);
        return t2;
    }
    void print()
    {
        if (is.isEmpty())
        {
            cout << "!! DEQUEUE is Empty !!" << endl;
            return;
        }
        is.print();
    }

private:
    Integer_Stack is;
};

int main()
{
    Dequeue dq;
    while (true)
    {
        cout << "\n--------------------------------------------------------\n";
        cout << "\n------------------------- Menu -------------------------\n";
        cout << "1.Enqueue Front\n";
        cout << "2.Enqueue Rear\n";
        cout << "3.Dequeue Front\n";
        cout << "4.Dequeue Rear\n";
        cout << "5.Print Deque\n";
        cout << "0.Exit\n\n";
        cout << "Choice -> ";
        int choice;
        cin >> choice;
        cout << "\n--------------------------------------------------------\n";
        switch (choice)
        {
        case 1:
        {
            int temp;
            cout << "Enter number to enqueue to front: ";
            cin >> temp;

            dq.EnQueueFront(temp);
            break;
        }
        case 2:
        {
            int temp;
            cout << "Enter number to enqueue to rear end: ";
            cin >> temp;

            dq.EnQueueRear(temp);
            break;
        }
        case 3:
        {
            int t = dq.DeQueueFront();
            if (t == INT32_MAX)
            {
                cout << "DeQue is empty[Underflow]\n";
            }
            else
            {
                cout << "Dequeued element: " << t << endl;
            }
            break;
        }
        case 4:
        {
            int t = dq.DeQueueRear();
            if (t == INT32_MAX)
            {
                cout << "DeQue is empty[Underflow]\n";
            }
            else
            {
                cout << "Dequeued element: " << t << endl;
            }
            break;
        }
        case 5:
        {
            dq.print();
            break;
        }
        case 0:
            return 0;
        default:
            break;
        }
    }
}
