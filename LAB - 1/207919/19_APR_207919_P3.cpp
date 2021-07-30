#include <iostream>
using namespace std;
#define MAX 5000

class stack {
    public:
        stack() : size{MAX}, top{-1}{}
        stack(int n) : size{n}, top{-1}{}
        
        // Main operations
        bool push(string);
        string pop();

        // Other
        string peek();
        int getSize();
        bool isEmpty();
        bool isFull();
    private:
        int size;
        int top{-1};
        string a[MAX];
};

bool stack::push(string ele) {
    if(!isFull()) {
        a[++top] = ele;
        return true;
    }else {
        cout << "!! Error : Stack is Full" << endl;
        return false;
    }
}

string stack::pop() {
    if(!isEmpty()) {
        string x = a[top];
        top--;
        return x;
    }else {
        cout << "!! Error : Stack is Empty" << endl;
        return "NULL";
    }
}

string stack::peek() {
    if(top >= 0 && top <= size) return a[top];
    else {
        cout << "!! Error : Top Out of bound !!" << endl;
        return "NULL";
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
        cout << endl << "-------- STUDENT STACK IMPLEMENTATION --------" << endl;
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
                cin.ignore();
                string ele;
                cout << "Enter name of student to push into stack : ";
                getline(cin,ele);
                bool pushCheck = st.push(ele);
                if(pushCheck) {
                    cout << ele << " - Element pushed successfully" << endl;
                }else {
                    cout << "!! Error : There is some error occured while pushing the element !!" << endl;
                }
                break;
            }

            case 2 : {
                string popEle = st.pop();
                if (popEle.compare("NULL") != 0) {
                    cout << popEle << " successfully poped from the stack" << endl;
                }else {
                    cout << "!! Error : Some error occured while poping the element !!" << endl;
                }
                break;
            }

            case 3 : {
                string  topEle = st.peek();
                if(topEle.compare("NULL") != 0) 
                    cout << "Student on top is : " << st.peek() << endl;
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
                    cout << "!! Stack is Empty, No Student Found !!" << endl;
                }else {
                    cout << "!! Stack is not Empty !!" << endl;
                }
                break;
            }

            case 6 : { 
                if(st.isFull()) {
                    cout << "!! Stack is FULL, Cannot Insert More Student !!" << endl;
                }else {
                    cout << "!! Stack is NOT FULL !!" << endl;
                }
                break;
            }

            case 7 : {
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