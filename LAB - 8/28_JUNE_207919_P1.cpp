// L8.1 Implement hashing using Separate Chaining
#include <iostream>
#include <list>
using namespace std;
#define HASHGROUPS 10

class HashTable {
public:
    bool isEmpty() const;
    int hash(int key) const;
    void insert(int key, string val);
    void remove(int key);
    string search(int key) const;
    void print() const;

private:
    // I am using list rather than vecotr since deleting operation in list is of contant time
    // whereas in vector it is linear time
    list<pair<int, string>> table[HASHGROUPS];
};

bool HashTable::isEmpty() const {
    for(int i = 0; i < HASHGROUPS; i++) {
        if(table[i].size() > 0)    return false;
    }
    return true;
}
int HashTable::hash(int key) const {
    return key % HASHGROUPS;
}
void HashTable::insert(int key, string val) {
    int hashValue = hash(key);
    auto& hashCell = table[hashValue];
    bool keyExist{false};
    for(auto& it : hashCell) {
        // checking if given key already exist in hash table of not
        if(it.first == key) {
            keyExist = true;
            cout << "[Warning] Key already exist. Updating value with new one" << endl;
            it.second = val;
            break;
        }
    }
    // if key does not exist make new <key,val> pair and insert it into list
    if(!keyExist)
        hashCell.push_back({key,val});
}
void HashTable::remove(int key) {
    int hashValue = hash(key);
    auto& hashCell = table[hashValue];
    bool keyExist{false};
    for(auto it = begin(hashCell); it != end(hashCell); it++) {
        // checking if given key exist in hash table of not
        if(it->first == key) {
            keyExist = true;
            it = hashCell.erase(it);
            cout << "[Prompt] Item Removed" << endl;
            break;
        }
    }
    // if key does not exist
    if(!keyExist) {
         cout << "[Warning] Key not found. Item not removed" << endl;
    }
}
void HashTable::print() const {
    for(int i{}; i < HASHGROUPS; i++) {
        // checking if given hash group has any pair or not
        if(table[i].size() == 0)    continue;

        for(auto& it : table[i]) {
            cout << "Key : " << it.first << " Value : " << it.second << endl;
        }
    }
    cout << endl;
}
string HashTable::search(int key) const {
    int hashValue = hash(key);
    auto& hashCell = table[hashValue];
    bool keyExist{false};
    string KeyValue;
    for(auto& it : hashCell) {
        // checking if given key already exist in hash table of not
        if(it.first == key) {
            keyExist = true;
            KeyValue = it.second;
            break;
        }
    }
    // if key does not exist make new <key,val> pair and insert it into list
    if(!keyExist) {
        cout << "[Warning] Key not found in hash" << endl;
        return "";
    }
    return KeyValue;
}

int main() {
    HashTable ht;
    while(1) {
        cout << "----------------------------------- MENU -----------------------------------" << endl;
        cout << "1. Insert into hash" << endl;
        cout << "2. Remove key from hash" << endl;
        cout << "3. Search into hash" << endl;
        cout << "4. Print all Key" << endl;
        cout << "0. Exit" << endl;
        int choice{};
        cout << "Choice --> ";
        cin >> choice;
        cout << "-----------------------------------------------------------------------------" << endl;
        switch(choice) {
            case 1: {
                cout << "!!!! INSERT !!!!!" << endl;
                int key;
                string value;
                cout << "Enter Key : ";
                cin >> key;
                cout << "Enter Value: ";
                cin >> value;
                ht.insert(key,value);
                break;
            }
            case 2: {
                cout << "!!!! REMOVE !!!!!" << endl;
                int key;
                cout << "Enter Key : ";
                cin >> key;
                ht.remove(key);
                break;
            }
            case 3: {
                cout << "!!!! SEARCH !!!!!" << endl;
                int key;
                cout << "Enter Key : ";
                cin >> key;
                string res = ht.search(key);
                if(res != "")   cout << "[Prompt] Value corresponding to Key " << key << " : " << res << endl;
                break;
            }
            case 4: {
                cout << "!!!! PRINT !!!!!" << endl;
                ht.print();
                break;
            }
            case 0: {
                return 0;
            }
            default: {
                cout << "[Warning] Wrong option selected" << endl;
            }
        }
        cout << "-----------------------------------------------------------------------------" << endl;
    }
}