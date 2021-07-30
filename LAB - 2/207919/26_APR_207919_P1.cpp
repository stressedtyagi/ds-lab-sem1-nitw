/* 
Postfix evaluation using stack
Write a program to evaluate a given postfix expression using stack
The program should support the operators {+ - * / % ^}
1. Also giving runtime error if the entered postfix expression is invalid
2. Program also handles the cases if user enters numbers that are more than single digit. 
    ex, 123 23 + 11 2133 - *
   Such expression are also evaluated
*/
// Example Postfix Input : 123 90 + 900 10 % -
#include <iostream>
#include <math.h>
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
inline int stack::getSize() {
    return size;
}
inline bool stack::isEmpty() {
    return (top == -1);
}
inline bool stack::isFull() {
    return (size-1 == top);
}

int postEval(string);
int main() {
    string s;
    cout << "Enter your postfix expression (use space as seperator between each variable) : ";
    getline(cin,s);
    int result = postEval(s);
    if(result != INT32_MIN) {
        cout << "Final Evaluated value is : " << result << endl;
    }else {
        throw runtime_error("!! Invalid Expression !!");
    }
}
int calculate(string s, int e1, int e2) {
    int eval;
    if(s == "+"){
        eval = e1 + e2;
    }else if (s == "-") {
        eval = e1 - e2;
    }else if (s == "*") {
        eval = e1 * e2;
    }else if (s == "/") {
        eval = e1 / e2;
    }else if (s == "^") {
        eval = pow(e1,e2);
    }else if (s == "%") {
        eval = e1 % e2;
    }
    return eval;
}
int postEval(string s) {
    // creating tokens for each number and opertor in string
    // used this to handle number of more the one digit
    // using space as seperator to calculate the tokens
    string* tokens = new string[s.length()];
    int tokenSize{0};
    for(int i = 0; i < s.length(); i++) {
        string str = "";
        while(i < s.length() && s[i] != ' ') {
            str += s[i];
            i++;
        }
        tokens[tokenSize++] = str;
    }

    stack st(s.length());
    for(int i = 0; i < tokenSize; i++) {
        if(tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "/" || tokens[i] == "*" || tokens[i] == "%" || tokens[i] == "^") {
            int e2 = st.peek();
            st.pop();
            int e1 = st.peek();
            st.pop();
            st.push(calculate(tokens[i],e1,e2));
        }else
            st.push(stoi(tokens[i]));
    }
    int result = st.peek();
    st.pop();
    return st.isEmpty() ? result : INT32_MIN;
}