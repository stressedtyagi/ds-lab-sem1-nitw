#include <iostream>
using namespace std;

struct Node
{
    int val;
    Node *next;
    Node(int val, Node *temp) : val{val}, next{temp} {}
};

class LinkedList
{
public:
    // made head global - just to avoid using getters and setters for new head after reverse
    Node *head;

    LinkedList() : head{nullptr}, size{0} {}

    void pushBack(int val)
    {
        if (head)
        {
            Node *temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = new Node(val, nullptr);
            size++;
            return;
        }
        head = new Node(val, nullptr);
        size++;
    }

    size_t length() const
    {
        return size;
    }

    void print()
    {
        if (head)
        {
            Node *temp = head;
            cout << "\n---------------------------------\n";
            cout << "Head -> ";
            while (temp)
            {
                if (temp->next)
                    cout << temp->val << "->";
                else
                    cout << temp->val;
                temp = temp->next;
            }
            cout << "\n---------------------------------\n";
        }
        else
        {
            cout << "!! Linked list is empty !!" << endl;
        }
    }

    Node *reverse(int k, Node *head)
    {
        if (!head)
            return nullptr;

        // checking if the current list from given head has k nodes or not
        Node *node = head;
        for (int i = 0; i < k; i++)
        {
            if (!node)
                return head;
            node = node->next;
        }

        Node *prev = head;
        Node *current = head->next;
        Node *next = nullptr;

        int i{0};
        // Reversing current k elements of linked list
        while (i < k - 1 && current)
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
            i++;
        }

        // reccursively calling to reverse for remaining elements of linked list
        head->next = reverse(k, current);
        return prev;
    }

private:
    size_t size;
};

int main()
{
    int n, k;
    cout << "Enter size of linked list: ";
    cin >> n;

    LinkedList ll;
    while (n--)
    {
        int t;
        cout << "Enter element: ";
        cin >> t;

        ll.pushBack(t);
    }
    cout << "\nEnter value of k: ";
    cin >> k;

    ll.head = ll.reverse(k, ll.head);
    ll.print();
}