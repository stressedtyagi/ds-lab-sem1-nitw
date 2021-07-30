/* 
L5.1 Implement a circular single linked list of integers
Write a program to Implement a circular single linked list with the following operations
    - bool insertBegin(int v)
    - bool insertEnd(int v)
    - bool insertAtPos(int v, int pos)
    - bool insertAfterValue(int v, int sv)
    - int find(int sv)           - returns the location of the node in the linked list with sv value.
    - bool search(int sv)    - returns true if there is an node in the linked list with sv value.
    - bool deleteByValue(int sv)
    - int deleteBegin()
    - int deleteEnd()
    - int deleteAtPos(int pos)
    - bool isEmpty()
    - int size()
    - void print()
Use a menu in a loop, to call these operations.
(Here, the data type of the objects is int) 
*/
#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(const int val, ListNode *next = nullptr) : val{val}, next{next} {}
};

class CLL
{
public:
    // Utilities
    CLL() : size{0}, head{nullptr} {}
    ~CLL()
    {
        if (size == 1)
        {
            delete head;
        }
        else if (size > 1)
        {
            ListNode *curr = head->next;
            while (curr->next != head)
            {
                curr = curr->next;
            }
            curr->next = nullptr;
            curr = head;
            while (curr)
            {
                ListNode *temp = curr;
                curr = curr->next;
                delete temp;
            }
            delete head;
        }
        cout << "!! Linked List Deleted Successfully" << endl;
    }

    // helper functions
    // bool inesetBegin(int v)
    bool push_front(const int &);

    // bool insertEnd(int v)
    bool push_back(const int &);

    // bool insertAtPos(int v, int pos)
    bool add_element(const size_t, const int &);

    // bool insertAfterValue(int v, int sv)
    bool insertAfterValue(int, const int &);

    // int find(int sv)
    // returns the location of the node in the linked list with sv value.
    int find(const int &) const;

    // bool search(int sv)
    // returns true if there is an node in the linked list with sv value.
    bool search(const int &sv) const;

    // bool deleteByValue(int sv)
    int delete_element(const int &);

    // int deleteBegin()
    int deleteBegin();

    // int deleteEnd()
    int deleteEnd();

    // int deleteAtPos(int pos)
    int deleteAtPos(const int &);

    // bool isEmpty()
    bool isEmpty() { return size == 0 || head == nullptr; }

    // int size()
    size_t length() const { return size; };

    // void print()
    void print() const;

private:
    ListNode *head;
    size_t size;
};

inline bool CLL::push_front(const int &ele)
{
    if (head == nullptr)
    {
        head = new ListNode(ele);
        head->next = head;
    }
    else
    {
        ListNode *newNode = new ListNode(ele, head);
        ListNode *curr = head;
        while (curr->next != head)
        {
            curr = curr->next;
        }
        curr->next = newNode;
        head = newNode;
    }
    size++;
    return true;
}

inline bool CLL::push_back(const int &ele)
{
    if (head == nullptr)
    {
        head = new ListNode(ele);
        head->next = head;
    }
    else
    {
        ListNode *curr = head;
        while (curr->next != head)
        {
            curr = curr->next;
        }
        curr->next = new ListNode(ele, head);
    }
    size++;
    return true;
}

bool CLL::add_element(const size_t index, const int &ele)
{
    if (index <= 0 || index > size)
    {
        throw runtime_error("Error : Index out of bounds");
        return false;
    }
    if (index == 1)
    {
        push_front(ele);
    }
    else if (index == size)
    {
        push_back(ele);
    }
    else
    {
        ListNode *prev = nullptr;
        ListNode *curr = head;
        for (int i = 1; i < index; i++)
        {
            prev = curr;
            curr = curr->next;
        }
        prev->next = new ListNode(ele, curr);
        size++;
    }
    return true;
}

inline bool CLL::insertAfterValue(int val, const int &afterVal)
{
    if (head == nullptr)
    {
        throw runtime_error("List in empty");
        return false;
    }
    ListNode *curr = head->next;
    while (curr != head && curr->val != afterVal)
    {
        curr = curr->next;
    }
    if (curr == head && curr->val != afterVal)
    {
        return false;
    }
    ListNode *newNode = new ListNode(val, curr->next);
    curr->next = newNode;
    return true;
}

int CLL::find(const int &val) const
{

    if (head == nullptr)
    {
        throw runtime_error("List in empty");
        return INT8_MIN;
    }
    ListNode *curr = head;
    int count{1};
    while (curr->val != val && curr->next != head)
    {
        curr = curr->next;
        count++;
    }
    if (curr->val != val)
    {
        return INT8_MIN;
    }
    return count;
}

bool CLL::search(const int &val) const
{

    if (head == nullptr)
    {
        throw runtime_error("List in empty");
        return false;
    }
    ListNode *curr = head;
    while (curr->val != val && curr->next != head)
        curr = curr->next;
    if (curr->val != val)
        return false;
    return true;
}

inline int CLL::delete_element(const int &ele)
{
    if (head == nullptr)
    {
        throw runtime_error("List in empty");
    }
    ListNode *curr = head->next;
    ListNode *prev = head;
    while (curr != head && curr->val != ele)
    {
        prev = curr;
        curr = curr->next;
    }
    if (curr == head && curr->val != ele)
    {
        throw runtime_error("!! Element Not Found !!");
    }
    ListNode *temp = curr;
    int delete_val = temp->val;
    if (prev->next != curr->next)
        prev->next = curr->next;
    size--;
    if (temp == head && size > 0)
        head = head->next;
    if (size == 0)
        head = nullptr;
    delete temp;
    return delete_val;
}

int CLL::deleteBegin()
{
    if (head == nullptr)
    {
        throw runtime_error("List in empty");
    }
    return delete_element(head->val);
}

int CLL::deleteEnd()
{
    if (head == nullptr)
    {
        throw runtime_error("List in empty");
    }
    ListNode *curr = head->next;
    ListNode *prev = head;
    while (curr->next != head)
    {
        prev = curr;
        curr = curr->next;
    }
    ListNode *deletePtr = curr;
    int delete_val = curr->val;
    if (prev == curr)
    {
        head = nullptr;
    }
    else
    {
        prev->next = curr->next;
    }
    delete deletePtr;
    return delete_val;
}

int CLL::deleteAtPos(const int &pos)
{
    if (isEmpty())
    {
        throw runtime_error("List in empty");
    }
    ListNode *curr = head;
    int i;
    for (i = 1; i < pos && curr->next != head; i++, curr = curr->next)
        ;
    if (i == pos)
    {
        return delete_element(curr->val);
    }
    else
    {
        return INT8_MIN;
    }
}

void CLL::print() const
{
    if (head == nullptr)
    {
        throw runtime_error("!! List is empty !!");
        return;
    }
    ListNode *curr = head;
    if (size == 1)
    {
        cout << curr->val;
    }
    else
    {
        while (curr->next != head)
        {
            cout << curr->val << " -> ";
            curr = curr->next;
        }
        cout << curr->val;
    }
    cout << endl;
}

int main()
{
    CLL myList;
    while (true)
    {
        cout << "------------------- MENU -------------------" << endl;
        cout << "1. Push front" << endl;
        cout << "2. Push back" << endl;
        cout << "3. Push index" << endl;
        cout << "4. Push After Value" << endl;
        cout << "5. Delete - By Value" << endl;
        cout << "6. Delete - Begin" << endl;
        cout << "7. Delete - End" << endl;
        cout << "8. Delete - At Position" << endl;
        cout << "9. Find Element Location" << endl;
        cout << "10. Find If Element Exist" << endl;
        cout << "11. Print" << endl;
        cout << "12. Size of CLL currently" << endl;
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
            cout << "!!! PUSH FRONT !!!" << endl;
            cout << "Element value : ";
            cin >> ele;
            if (myList.push_front(ele))
            {
                cout << "Element inserted Successfully" << endl;
            }
            else
            {
                cout << "Error: can't insert element";
            }
            break;
        }
        case 2:
        {
            int ele;
            cout << "!!! PUSH Back !!!" << endl;
            cout << "Element value : ";
            cin >> ele;
            if (myList.push_back(ele))
            {
                cout << "Element inserted Successfully" << endl;
            }
            else
            {
                cout << "Error: can't insert element";
            }

            break;
        }
        case 3:
        {
            int ele;
            size_t index;
            cout << "!!! PUSH Index !!!" << endl;
            cout << "Index value : ";
            cin >> index;
            cout << "Element value : ";
            cin >> ele;
            if (myList.add_element(index, ele))
            {
                cout << "Element inserted Successfully" << endl;
            }
            else
            {
                cout << "Error: Index not found";
            }
            break;
        }
        case 4:
        {
            int val;
            int afterVal;
            cout << "!!! PUSH ELEMENT AFTER A VALUE !!!" << endl;
            cout << "Enter value to push : ";
            cin >> val;
            cout << "Enter value after which to push : ";
            cin >> afterVal;
            if (myList.insertAfterValue(val, afterVal))
            {
                cout << "Element inserted Successfully" << endl;
            }
            else
            {
                cout << "Error: Ref element not found";
            }
            break;
        }
        case 5:
        {
            int ele;
            cout << "!!! DELETE ELEMENT - By Value !!!" << endl;
            cout << "Element value : ";
            cin >> ele;
            int deleted = myList.delete_element(ele);
            if (deleted == ele)
            {
                cout << "Element " << deleted << " deleted successfully" << endl;
            }
            else
            {
                cout << "!! Error : something went wrong deleting the element" << endl;
            }
            break;
        }
        case 6:
        {
            cout << "!!! DELETE ELEMENT - Begin !!!" << endl;
            int deleted = myList.deleteBegin();
            if (deleted != INT8_MIN)
            {
                cout << "Element " << deleted << " deleted successfully" << endl;
            }
            else
            {
                cout << "!! Error : something went wrong deleting the element" << endl;
            }
            break;
        }
        case 7:
        {
            cout << "!!! DELETE ELEMENT - End !!!" << endl;
            int deleted = myList.deleteEnd();
            if (deleted != INT8_MIN)
            {
                cout << "Element " << deleted << " deleted successfully" << endl;
            }
            else
            {
                cout << "!! Error : something went wrong deleting the element" << endl;
            }
            break;
        }
        case 8:
        {
            int pos;
            cout << "!!! DELETE ELEMENT - At Position !!!" << endl;
            cout << "Position : ";
            cin >> pos;
            int deleted = myList.deleteAtPos(pos);
            if (deleted != INT8_MIN)
            {
                cout << "Element " << deleted << " deleted successfully" << endl;
            }
            else
            {
                cout << "!! Error : something went wrong deleting the element" << endl;
            }
            break;
        }
        case 9:
        {
            int ele;
            cout << "!!! FIND ELEMENT LOCATION !!!" << endl;
            cout << "Element value : ";
            cin >> ele;
            int location = myList.find(ele);
            if (location != INT8_MIN)
            {
                cout << ele << " location is CLL : " << location << endl;
            }
            else
            {
                cout << "!! Element not found !!" << endl;
            }
            break;
        }
        case 10:
        {
            int ele;
            cout << "!!! FIND ELEMENT Existence !!!" << endl;
            cout << "Element value : ";
            cin >> ele;
            bool location = myList.search(ele);
            if (location != INT8_MIN)
            {
                cout << ele << " exist in CLL " << endl;
            }
            else
            {
                cout << ele << " does not exist in CLL " << endl;
            }
            break;
        }
        case 11:
        {
            cout << "!!! PRINT LIST !!!" << endl;
            myList.print();
            break;
        }

        case 12:
        {
            cout << "SIZE : " << myList.length() << endl;
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