#include <iostream>
using namespace std;
#define MAX 5000

class stack {
    public:
        stack() : size{MAX}, top{-1}{}
        stack(int n) : size{n}, top{-1}{}
        
        // Main operations
        bool push(int);
        int pop();

        // Other
        int peek();
        int getSize();
        bool isEmpty();
        bool isFull();

        int gtop() {return top;}
    private:
        int size;
        int top{-1};
        int a[MAX];
};

bool stack::push(int ele) {
    if(!isFull()) {
        a[++top] = ele;
        return true;
    }else {
        cout << "!! Error : Stack is Full" << endl;
        return false;
    }
}

int stack::pop() {
    if(!isEmpty()) {
        int x = a[top];
        top--;
        return x;
    }else {
        cout << "!! Error : Stack is Empty" << endl;
        return INT16_MIN;
    }
}

int stack::peek() {
    if(top >= 0 && top <= size) return a[top];
    else {
        cout << "!! Error : Top Out of bound !!" << endl;
        return INT16_MIN;
    }
}

int stack::getSize() {
    return size;
}

bool stack::isEmpty() {
    return (top == -1);
}

bool stack::isFull() {
    return (size-1 == top);
}

// P4 function implementation
void comapreStack(stack st1,stack st2) {
    if(st1.isEmpty() || st2.isEmpty()) {
        cout << "Error : Operation Not Sucessful ABORT !!" << endl;
        return;
    }   
    cout << endl << "ST-1           ST-2" << endl;
    while(!st1.isEmpty() && !st2.isEmpty()) {
        int i = st1.peek();
        int j = st2.peek();
        if(i == j)
            cout << i << "      EQUAL    " << j << endl;
        else
            cout << i << "    NOT EQUAL  " << j << endl;
        st1.pop();
        st2.pop();
    }
}

void menu(stack&);

int main() {
    cout << "-----------------------------------------------------" << endl;
    cout << "!!               Enter Contents Of ST-1             !!" << endl;
    cout << "-----------------------------------------------------" << endl; 

    int n1;
    cout << "Enter Size of stack - 1 : ";
    cin >> n1;
    if(n1 <= 0) {
        cout << "!! Invalid Size !!" << endl;
        return 0;
    }
    stack st1(n1);
    cout << "-----------------------------------------------------" << endl;
    cout << "!! Stack with size " << n1 << " created Successfully !!" << endl;
    cout << "-----------------------------------------------------" << endl;        
    menu(st1);

    cout << "-----------------------------------------------------" << endl;
    cout << "!!               Enter Contents Of ST-2             !!" << endl;
    cout << "-----------------------------------------------------" << endl; 
    stack st2(n1);
    cout << "-----------------------------------------------------" << endl;
    cout << "!! Stack with size " << n1 << " created Successfully !!" << endl;
    cout << "-----------------------------------------------------" << endl;        
    menu(st2);
    cout << "-----------------------------------------------------" << endl;
    cout << "!!        COMPARING CONTENT OF ST-1 TO ST-2         !!" << endl;
    cout << "-----------------------------------------------------" << endl; 
    comapreStack(st1,st2);
    return 0;
}

void menu(stack &st) {
    while(1) {
        cout << endl << "-------- STACK IMPLEMENTATION --------" << endl;
        cout << "1. PUSH" << endl;
        cout << "2. POP" << endl;
        cout << "3. PEEK" << endl;
        cout << "4. GET-SIZE" << endl;
        cout << "5. IS-EMPTY" << endl;
        cout << "6. IS-FULL" << endl;
        cout << "7. EXIT" << endl;
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

            case 7 : {
                return;
            }

            default : {
                cout << "!! Please Enter correct option !!" << endl;
                break;
            }
        }
    }
}