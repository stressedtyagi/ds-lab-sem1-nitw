#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node *next;
    Node(const T &d, Node *t) : data{d}, next{t} {}
};

template <typename T>
class Stack
{
public:
    Stack() : top{nullptr}, count{0} {}

    void push(const T &val)
    {
        Node<T> *temp;

        temp = new Node<T>(val, top);
        top = temp;
        count++;
    }

    T getTop() const
    {
        if (top)
            return top->data;
        else
            return 0;
    }

    void pop()
    {
        if (top)
        {
            Node<T> *temp = top;
            top = top->next;
            delete temp;
            count--;
        }
        else
        {
            cout << "Stack empty!!\n";
        }
    }

    bool empty() const
    {
        return top ? false : true;
    }

    size_t size() const
    {
        return count;
    }

private:
    Node<T> *top;
    size_t count;
};

int precedence(char c)
{
    if (c == '^')
    {
        return 3;
    }
    else if (c == '*' || c == '/')
    {
        return 2;
    }
    else if (c == '+' || c == '-')
    {
        return 1;
    }
}
string infixToPrefix(string s)
{
    Stack<char> st;
    string res;

    for (int i = 0; i < s.length(); ++i)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            res += s[i];
        }
        else
        {
            while (!st.empty() && precedence(s[i]) <= precedence(st.getTop()))
            {
                res += st.getTop();
                st.pop();
            }
            st.push(s[i]);
        }
    }
    while (!st.empty())
    {
        res += st.getTop();
        st.pop();
    }
    return res;
}

int calculate(char s, int e1, int e2)
{
    int eval;
    if (s == '+')
    {
        eval = e1 + e2;
    }
    else if (s == '-')
    {
        eval = e1 - e2;
    }
    else if (s == '*')
    {
        eval = e1 * e2;
    }
    else if (s == '/')
    {
        eval = e1 / e2;
    }
    return eval;
}
int postEval(string s)
{
    Stack<int> st;
    int n = s.length();
    for (int i = n - 1; i > -1; i--)
    {
        char ch = s[i];
        if (ch == '+' || ch == '-' || ch == '/' || ch == '*')
        {
            int e1 = st.getTop();
            st.pop();
            int e2 = st.getTop();
            st.pop();
            st.push(calculate(ch, e1, e2));
        }
        else
            st.push(ch - '0');
    }
    int result = st.getTop();
    st.pop();
    return st.empty() ? result : INT32_MIN;
}

void reverse(string &str)
{
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}

int main()
{
    string str;
    cout << "Enter infix expression : ";
    cin >> str;
    reverse(str);
    string prefix = infixToPrefix(str);
    reverse(prefix);

    cout << "The Prefix expression is : " << prefix << endl;

    int result = postEval(prefix);
    cout << "The value of the evaluated prefix expression is: " << result << endl;
}