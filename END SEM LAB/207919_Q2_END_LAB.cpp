// I am implementing max Priority Queue here.
#include <iostream>
using namespace std;
#define MAX 5000

class stack
{
public:
    stack() : size{MAX}, top{-1} {}
    stack(int n) : size{n}, top{-1} {}

    // Main operations
    bool push(int);
    int pop();

    // Other
    int peek();
    bool isEmpty();
    bool isFull();
    void print();

private:
    int size;
    int top{-1};
    int topMost{0};
    int a[MAX];
};
bool stack::push(int ele)
{
    if (!isFull())
    {
        a[++top] = ele;
        return true;
    }
    else
    {
        cout << "!! Error : Stack is Full" << endl;
        return false;
    }
}
int stack::pop()
{
    if (!isEmpty())
    {
        int x = a[top];
        top--;
        return x;
    }
    else
    {
        cout << "!! Error : Stack is Empty" << endl;
        return INT16_MIN;
    }
}
int stack::peek()
{
    if (top >= 0 && top <= size)
        return a[top];
    else
    {
        cout << "!! Error : Top Out of bound !!" << endl;
        return INT16_MIN;
    }
}
bool stack::isEmpty()
{
    return (top == -1);
}
bool stack::isFull()
{
    return (size - 1 == top);
}
void stack::print()
{
    if (isEmpty())
    {
        topMost = 0;
        return;
    }
    int curr = peek();
    if (topMost == 0)
        cout << '\t' << peek() << " <- Top" << endl;
    else
        cout << '\t' << peek() << endl;
    topMost--;
    pop();
    print();
    push(curr);
}

class priQueue
{
public:
    bool EnQue(int);
    int DeQue();
    void Print();

private:
    // Helper functions
    bool EnQue_Helper(int);
    stack st;
};
bool priQueue::EnQue_Helper(int val_to_insert)
{
    if (st.isEmpty())
    {
        st.push(val_to_insert);
        return true;
    }
    else if (st.peek() > val_to_insert)
    {
        // Pop stack top when
        // top > val_to_insert
        int currVal = st.peek();
        st.pop();
        bool check = EnQue_Helper(val_to_insert);
        st.push(currVal);
        return check;
    }
    // Push element into stack if current stack top is
    // top <= val_to_insert
    st.push(val_to_insert);
    return true;
}
bool priQueue::EnQue(int val)
{
    return EnQue_Helper(val);
}
int priQueue::DeQue()
{
    if (!st.isEmpty())
    {
        int val = st.peek();
        st.pop();
        return val;
    }
    else
    {
        cout << "!! Priority Queue is Empty !!" << endl;
        return INT32_MAX;
    }
}
void priQueue::Print()
{
    st.print();
}

int main()
{
    priQueue pq;
    while (1)
    {
        cout << "Enter 1. EnQueue 2. DeQue 3. Print 4. Exit : ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "EnQue: ";
            int val;
            cin >> val;
            pq.EnQue(val);
            break;
        }
        case 2:
        {
            int result = pq.DeQue();
            if (result != INT32_MAX)
                cout << "DeQue: " << result << endl;
            else
                cout << "[Error] Priority Queue is Empty" << endl;
            break;
        }
        case 3:
        {
            cout << "int_stack Contents: " << endl;
            pq.Print();
            break;
        }
        case 4:
            return 0;
        default:
            break;
        }
    }
}