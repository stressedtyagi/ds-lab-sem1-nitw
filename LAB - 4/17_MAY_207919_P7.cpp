/*  
Write a program to Implement a double linked list with the following operations
1.  bool insertBegin(int v)
2.  bool insertEnd(int v)
3.  bool insertAtPos(int v, int pos)
4.  bool insertAfterValue(int v, int sv)
5.  int find(int sv)           - returns the location of the node in the linked list with sv value.
6.  bool deleteByValue(int sv)
7.  int deleteBegin()
8.  int deleteEnd()
9.  int deleteAtPos(int pos)
10. bool isEmpty()
11. int size()
12. void print()
Use a menu in a loop, to call these operations.
*/
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode* prev;
    ListNode(const int val, ListNode* next = nullptr, ListNode* prev = nullptr)
        :
        val{val},next{next}, prev{prev}
        {}
};

class DLL {
    public:
        DLL()
            :
            size{0}, head{nullptr}
            {}
        ~DLL() {
            ListNode* curr = head;
            while(curr) {
                ListNode* temp = curr;
                curr = curr->next;
                delete temp;
            }
            std::cout << "List Deleted Successfully" << std::endl;
        }

        // 1. bool insertBegin(int v)
        void push_back(const int&);

        // 2. bool insertEnd(int v)
        void push_front(const int&);

        // 3. bool insertAtPos(int v, int pos)
        void add_element(const int&,const size_t&);

        // 4. bool insertAfterValue(int v, int sv)
        bool insertAfterValue(int,int);

        // 5. int find(int sv)
        int find(int) const;

        // 6. int deleteByValue(int sv)
        int deletebyValue(const int&);
        
        // 7. int deleteBegin()
        int deleteBegin();

        // 8. int deleteEnd()
        int deleteEnd();

        // 9. int deleteAtPos(int pos)
        int deleteAtPos(const int);

        // 10. bool isEmpty()
        bool isEmpty() const {return head == nullptr;}

        // 11. int size()
        size_t length() const;

        // 12. void print()
        void print() const;

    private:
        ListNode* head;
        size_t size;
};

void DLL::push_back(const int& val) {
    if(head == nullptr) {
        head = new ListNode(val);
    }else {
        ListNode* curr = head;
        while(curr->next)   curr = curr->next;
        curr->next = new ListNode(val,nullptr,curr);
    }
    size++;
}
void DLL::push_front(const int& val) {
    if(head == nullptr) {
        head = new ListNode(val);
    }else {
        ListNode* newNode = new ListNode(val,head);
        head->prev = newNode;
        head = newNode;
    }
    size++;
}
void DLL::add_element(const int& val,const size_t& index) {
    if(index > 0 && index <= size) {
        size_t i = 1;
        ListNode* curr = head;
        while(i != index) {
            curr = curr->next;
            i++;
        } 
        if(curr == head) {
            ListNode* newNode = new ListNode(val,head);
            head->prev = newNode;
            head = newNode;
        }else {
            ListNode* newNode = new ListNode(val,curr,curr->prev);
            curr->prev->next = newNode;
            if(newNode->next)
                newNode->next->prev = newNode;
        }
        size++;
    }else {
        throw runtime_error("Index Out of Bounds");
    }
}
bool DLL::insertAfterValue(int val, int aftVal) {
    if(head == nullptr)
        return false;
    ListNode* curr = head;
    while(curr && curr->val != aftVal) {
        curr = curr->next;
    }
    if(curr->val == aftVal) {
        curr->next = new ListNode(val,curr->next,curr);
        if(curr->next->next) {
            curr->next->next->prev = curr->next;
        }
        size++;
        return true;
    }else {
        return false;
    }
}
int DLL::find(int val) const {
    if(head == nullptr)
        throw runtime_error("List is empty");
    ListNode* curr = head;
    int i = 1;
    while(curr && curr->val != val) {
        i++;
        curr = curr->next;
    }
    if(curr && curr->val == val) {
        return i;
    }
    // Used INT8_MIN as sentinal to denote that element is not found
    return INT8_MIN;
}
int DLL::deletebyValue(const int& val) {
    ListNode* curr = head;
    while(curr && curr->val != val) {
        curr = curr->next;
    }
    if(curr == nullptr) {
        throw runtime_error("Element not found");
    }
    ListNode* temp = curr;
    int data = temp->val;
    if(curr == head) {
        head = head->next;
        head->prev = nullptr;
    }else {
        curr->prev->next = curr->next;
        if(curr->next)
            curr->next->prev = curr->prev;
    }
    size--;
    delete temp;
    return data;
}
int DLL::deleteBegin() {
    if(head == nullptr)
        throw runtime_error("List is empty");
    ListNode* temp = head;
    int val = head->val;
    head = head->next;
    if(temp->next)
        temp->next->prev = nullptr;
    size--;
    delete temp;
    return val;
}
int DLL::deleteEnd() {
    if(head == nullptr)
        throw runtime_error("List is empty");
    ListNode* curr = head;
    while(curr->next != nullptr) {
        curr = curr->next;
    }
    int val = curr->val;
    if(curr->prev)
        curr->prev->next = nullptr;
    curr->prev = nullptr;
    delete curr;
    size--;
    return val;
}
int DLL::deleteAtPos(const int pos) {
    if(head == nullptr)
        throw runtime_error("List is empty");
    if(pos < 0 || pos > length()) {
        return INT8_MIN;
    }
    ListNode* curr = head;
    ListNode* prev = nullptr;
    for(int i = 1; i != pos && curr; i++, prev = curr, curr = curr->next);
    int val = curr->val;
    if(curr == head) {
        head = head->next;
        delete curr;
    }else {
        prev->next = curr->next;
        delete curr;
    }
    return val;
}
size_t DLL::length() const {
    return this->size;
}
void DLL::print() const {
    for(ListNode* i = head; i != nullptr; i = i->next) {
        if(i->next)
            std::cout << i->val << " -> ";
        else
            std::cout << i->val;
    }
    std::cout << std::endl;
}

int main() {
    DLL myList;
    while(true) {
        cout << "------------------- MENU -------------------" << endl;
        cout << "1. Push front" << endl;
        cout << "2. Push back" << endl;
        cout << "3. Push index" << endl;
        cout << "4. Push After Value" << endl;
        cout << "5. Delete - By Value" << endl;
        cout << "6. Delete - Begin" << endl;
        cout << "7. Delete - End" << endl;
        cout << "8. Delete - At Position" << endl;
        cout << "9. Find Element" << endl;
        cout << "10. Print" << endl;
        cout << "11. Size of DLL currently" << endl;
        cout << "0. EXIT" << endl;
        cout << "Choice --> ";
        int choice;
        cin >> choice;
        cout << "---------------------------------------------" << endl;
        switch (choice) {
        case 1: {
            int ele;
            cout << "!!! PUSH FRONT !!!" << endl;
            cout << "Element value : ";
            cin >> ele;
            myList.push_front(ele);
            break;
        }
        case 2: {
            int ele;
            cout << "!!! PUSH Back !!!" << endl;
            cout << "Element value : ";
            cin >> ele;
            myList.push_back(ele);
            break;
        }
        case 3: {
            int ele;
            size_t index;
            cout << "!!! PUSH Index !!!" << endl;
            cout << "Index value : ";
            cin >> index;
            cout << "Element value : ";
            cin >> ele;
            myList.add_element(ele,index);
            break;
        }   
        case 4: {
            int val, afterVal;
            cout << "!!! PUSH After a Value !!!" << endl;
            cout << "Enter value of new Node : ";
            cin >> val;
            cout << "Enter value of node after which you want to insert : ";
            cin >> afterVal;
            if(myList.insertAfterValue(val,afterVal)) {
                cout << "-- Element inserted Successfully -- " << endl;
            }else {
                cout << "!! Error occured which inserting new node !!" << endl;
            }
            break;
        }
        case 5: {
            int ele;
            cout << "!!! DELETE - BY VALUE !!!" << endl;
            cout << "Element value : ";
            cin >> ele;
            int deleted = myList.deletebyValue(ele);
            if(deleted == ele) {
                cout << "Element " << deleted << " deleted successfully" << endl;
            }else {
                cout << "!! Error : something went wrong deleting the element" << endl;
            }
            break;
        }
        case 6: {
            cout << "!!! DELETE - Begin !!!" << endl;
            int deleted = myList.deleteBegin();
            cout << "Element " << deleted << " deleted successfully" << endl;
            break;
        }
        case 7: {
            cout << "!!! DELETE - END !!!" << endl;
            int deleted = myList.deleteEnd();
            cout << "Element " << deleted << " deleted successfully" << endl;
            break;
        }
        case 8: {
            int pos;
            cout << "!!! DELETE - At Position !!!" << endl;
            cout << "Element position : ";
            cin >> pos;
            int deleted = myList.deleteAtPos(pos);
            if(deleted != INT8_MIN) {
                cout << "Element " << deleted << " deleted successfully" << endl;
            }else {
                cout << "!! Error : something went wrong deleting the element" << endl;
            }
            break;
        }        
        case 9: {
            int val;
            cout << "!!! FIND Element !!!" << endl;
            cout << "Enter Element Value : ";
            cin >> val;
            int pos = myList.find(val);
            if(pos != INT8_MIN) {
                cout << "Element found at position : " << pos << endl;
            }else {
                cout << "Element not found" << endl;
            }
            break;
        } 
        case 10: {
            cout << "!!! PRINT LIST !!!" << endl;
            myList.print();
            break;
        }   
        case 11: {
            cout << "SIZE : " << myList.length() << endl;
            break;
        }
        case 0: {
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