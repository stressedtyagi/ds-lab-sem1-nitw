/* 
Infix to postfix using stack
Write a program to evaluate a given postfix expression using stack
The program should support the operators {+ - * / % ^}
1. Also giving runtime error if the entered postfix expression is invalid
2. Program also handles the cases if user enters numbers that are more than single digit. 
    ex, 1123 + 12 - 90 % 3 * 90
   Such expression are also evaluated
3. Paraenthsis check is also done
*/
// Example Infix Input : 1123 + 12 - 90 % 3 * 90
// Also if you want expression with paranthesis write imput like this, with spaces
// I/O :- 123 + 23 ^ ( 1 + 23 ) - 23
// O/P :- 123 23 1 23 + ^ + 23 -
#include <iostream>
#include <math.h>
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
        string val = peek();
        top--;
        return val;
    }else {
        cout << "!! Error : Stack is Empty" << endl;
    }
}
string stack::peek() {
    if(top >= 0 && top <= size) return a[top];
    else {
        cout << "!! Error : Top Out of bound !!" << endl;
        return "";
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

string infixToPostfix(string);
int main() {
    string s;
    cout << "Enter your infix expression (use space as seperator between each variable) : ";
    getline(cin,s);
    string result = infixToPostfix(s);
    cout << "Final Evaluated postfix is (each value is seperated by space) : " << result << endl;
}

bool isOperator(string s) {
    return (s == "^" || s == "*" || s == "/" || s == "-" || s == "+" || s == "%" || s == "(" || s == ")");
}

int precedence(string c) {
    if(c == "^") {
        return 3;
    }else if (c == "*" || c == "/" || c == "%") {
        return 2;
    }else if (c == "+" || c == "-") {
        return 1;
    }
}
string infixToPostfix(string s) {
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
    string res;
    for(int i = 0; i < tokenSize; i++) {
        if(!isOperator(tokens[i])) {
            res += tokens[i] + " ";
        }else if(tokens[i] == "("){
            st.push(tokens[i]);
        }else if(tokens[i] == ")") {
            while(!st.isEmpty() && st.peek() != "(") {
                res += st.peek() + " ";
                st.pop();
            }
            if(st.getSize() != 0)
                st.pop();
        }else {
            while(!st.isEmpty() && st.peek() != "(" && precedence(tokens[i]) <= precedence(st.peek())) {
                res += st.peek() + " ";
                st.pop();
            }
            st.push(tokens[i]);
        }
    }
    while(!st.isEmpty()) {
        res += st.peek() + " ";
        st.pop();
    }
    return res;
}