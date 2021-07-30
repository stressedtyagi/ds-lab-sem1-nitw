/*  
L3.3 Implement a Single Linked List
    Write a program to implement a single linked list with the following operations :
        - bool insertBegin(int v)
        - bool insertEnd(int v)
        - bool insertAtPos(int v, int pos)
        - int deleteBegin()
        - int deleteEnd()
        - int deleteAtPos(int pos)
        - bool isEmpty()
        - int size()
        - void print()
    Use menu in ta loop, to call these operations
*/

#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(const int val, ListNode* next = nullptr) : val{val}, next{next}{}
};

class LL {
    public:
        // Utilities
        LL():length{0}, head{nullptr}{}
        ~LL(){
            while (head) {
                ListNode* temp = head->next;
                delete head;
                head = temp;
            }
        }

        // helper functions
        bool inserBegin(const int&);
        bool insertEnd(const int&);
        bool insertAtPos(const size_t,const int&);
        int deleteBegin();
        int deleteEnd();
        int deleteAtPos(const int&);
        size_t size() const {return length;};
        void print() const;
    private:
        ListNode* head;
        size_t length;
};

bool LL::insertEnd(const int& ele) {
    ListNode* newNode = new ListNode(ele);
    if(head == nullptr) {
        head = newNode;
    }else {
        ListNode* curr = head;
        while(curr->next) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
    length++;
    return true;
}

bool LL::inserBegin(const int& ele) {
    ListNode* newNode = new ListNode(ele,head);
    head = newNode;
    length++;
    return true;
}

int LL::deleteAtPos(const int& pos) {
    if(head == nullptr) {
        throw runtime_error("List in empty");
    }
    if(pos <= 0 || pos > length) {
        throw runtime_error ("Index Out of Bounds");
    }
    ListNode *curr = head, *prev = head;
    for(int i = 1; i < pos; i++) {
        prev = curr;
        curr = curr->next;
    }
    if(curr == head) {
        head = curr->next;
    }else {
        prev->next = curr->next;
    }
    ListNode* temp = curr;
    int val = curr->val;
    delete curr;
    length--;
    return val;
}

int LL::deleteBegin() {
    if(head == nullptr)
        throw runtime_error("List in empty");
    ListNode* temp = head;
    int val = temp->val;
    head = head->next;
    delete temp;
    length--;
    return val;
}

int LL::deleteEnd() {
    if(head == nullptr)
        throw runtime_error("List in empty");
    int val;
    ListNode* temp, *curr{head}, *prev{head};
    while(curr->next != nullptr) {
        prev = curr;
        curr = curr->next;
    }
    if(curr == head) {
        head = curr->next;
    }else {
        prev->next = curr->next;
    }
    temp = curr;
    val = temp->val;
    delete curr;
    length--;
    return val;
}

bool LL::insertAtPos(const size_t index,const int& ele) {
    if(index <= 0 || index > length) {
        throw runtime_error("Error : Index out of bounds");
        return false;
    }
    ListNode* prev = nullptr;
    ListNode* curr = head;
    for(int i = 1; i < index; i++) {
        prev = curr;
        curr = curr->next;
    }
    if(curr == head || (index == 1 && head == nullptr)) {
        ListNode* newNode = new ListNode(ele,head);
        head = newNode;
        length++;    
    }else {
        ListNode* newNode = new ListNode(ele,curr);
        prev->next = newNode;
        length++;
    }
    return true;
}

void LL::print() const{
    if(head == nullptr) {
        throw runtime_error("!! List is empty !!");
        return;
    }
    ListNode* curr = head;
    while(curr) {
        if(curr->next != nullptr)
            cout << curr->val << " -> ";
        else 
            cout << curr->val;
        curr = curr->next;
    }
    cout << endl;
}

int main() {
    LL myList;
    while(true) {
        cout << "------------------- MENU -------------------" << endl;
        cout << "1. Push front" << endl;
        cout << "2. Push back" << endl;
        cout << "3. Push index" << endl;
        cout << "4. Delete - Begin" << endl;
        cout << "5. Delete - End" << endl;
        cout << "6. Delete - At Position" << endl;
        cout << "7. Print" << endl;
        cout << "8. Size of Linkled List currently" << endl;
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
            myList.inserBegin(ele);
            break;
        }
        case 2: {
            int ele;
            cout << "!!! PUSH Back !!!" << endl;
            cout << "Element value : ";
            cin >> ele;
            myList.insertEnd(ele);
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
            myList.insertAtPos(index,ele);
            break;
        }   
        case 4: {
            cout << "!!! DELETE ELEMENT - Begin !!!" << endl;
            int deleted = myList.deleteBegin();
            cout << "Element " << deleted << " deleted successfully" << endl;
            break;
        }
        case 5: {
            cout << "!!! DELETE ELEMENT - End !!!" << endl;
            int deleted = myList.deleteEnd();
            cout << "Element " << deleted << " deleted successfully" << endl;
            break;
        }
        case 6: {
            int pos;
            cout << "!!! DELETE ELEMENT - At Position !!!" << endl;
            cout << "Position value : ";
            cin >> pos;
            int deleted = myList.deleteAtPos(pos);
            cout << "Element " << deleted << " deleted successfully" << endl;
            break;
        }
        case 7: {
            cout << "!!! PRINT LIST !!!" << endl;
            myList.print();
            break;
        }   
        case 8: {
            cout << "SIZE : " << myList.size() << endl;
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