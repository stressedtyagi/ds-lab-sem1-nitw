// L8.2 Implement hashing using Open addressing method (with Quadratic probing).

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

#define HASHGROUPS 11

enum EntryType
{
    Inserted,
    Empty,
    Deleted
};

struct HashData
{
    int key;
    string value;
    EntryType status;
};

class HashTable
{
public:
    // Initially setting all entries in hash table Status : Empty
    HashTable()
    {
        for (int i = 0; i < HASHGROUPS; i++)
        {
            table.push_back({-1, "", Empty});
        }
    }
    bool isEmpty() const;
    int hash(int key) const;
    void insert(int key, string val);
    void remove(int key);
    string search(int key) const;
    void print() const;

private:
    // I am using vector since random access in vector is of
    // constant time, since random access is done a lot in
    // quadratic probing this will help us a lot
    vector<HashData> table;
};

int HashTable::hash(int key) const
{
    return key % HASHGROUPS;
}
void HashTable::insert(int key, string val)
{
    int hashValue = hash(key);
    int collisions = 0;
    bool keyExist{false};
    for (int i = 0; i < table.size(); i++)
    {
        // checking if given key already exist in hash table of not
        int itr = (hashValue + i * i) % table.size();
        HashData *hd = &table[itr];
        if (hd->key == key && hd->status == Inserted)
        {
            keyExist = true;
            cout << "[Warning] Key already exist. Updating value with new one" << endl;
            hd->value = val;
            break;
        }
        else if (hd->status == Empty || hd->status == Deleted)
        {
            keyExist = true;
            hd->key = key;
            hd->value = val;
            hd->status = Inserted;
            cout << "[Prompt] Pair inserted succesfully" << endl;
            break;
        }
    }
    // if hash table is full
    if (!keyExist)
        cout << "[Warning] Hash Table is full" << endl;
}
void HashTable::remove(int key)
{
    int hashValue = hash(key);
    int collisions = 0;
    bool keyExist{false};
    for (int i = 0; i < table.size(); i++)
    {
        // checking if given key already exist in hash table of not
        int itr = (hashValue + i * i) % table.size();
        HashData *hd = &table[itr];
        if (hd->key == key && hd->status == Inserted)
        {
            keyExist = true;
            hd->status = Deleted;
            cout << "[Prompt] Item Removed" << endl;
            break;
        }
    }
    // if key does not exist
    if (!keyExist)
    {
        cout << "[Warning] Key not found. Item not removed" << endl;
    }
}
void HashTable::print() const
{
    for (int i{}; i < table.size(); i++)
    {
        int key = table[i].key;
        string value = table[i].value;
        if (table[i].status == Deleted)
            cout << "Key : "
                 << "[Deleted]"
                 << " Value : "
                 << " NULL " << endl;
        else if (table[i].status == Empty)
            cout << "Key : "
                 << "[Empty]"
                 << " Value : "
                 << " NULL " << endl;
        else
            cout << "Key : " << key << " Value : " << value << endl;
    }
    cout << endl;
}
string HashTable::search(int key) const
{

    int hashValue = hash(key);
    int collisions = 0;
    bool keyExist{false};
    string KeyValue;
    for (int i = 0; i < table.size(); i++)
    {
        // checking if given key already exist in hash table of not
        int itr = (hashValue + i * i) % table.size();
        HashData hd = table[itr];
        if (hd.key == key && hd.status == Inserted)
        {
            keyExist = true;
            KeyValue = hd.value;
            break;
        }
    }
    if (!keyExist)
    {
        cout << "[Warning] Key not found in hash" << endl;
        return "";
    }
    return KeyValue;
}

int main()
{
    HashTable ht;
    while (1)
    {
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
        switch (choice)
        {
        case 1:
        {
            cout << "!!!! INSERT !!!!!" << endl;
            int key;
            string value;
            cout << "Enter Key : ";
            cin >> key;
            cout << "Enter Value: ";
            cin >> value;
            ht.insert(key, value);
            break;
        }
        case 2:
        {
            cout << "!!!! REMOVE !!!!!" << endl;
            int key;
            cout << "Enter Key : ";
            cin >> key;
            ht.remove(key);
            break;
        }
        case 3:
        {
            cout << "!!!! SEARCH !!!!!" << endl;
            int key;
            cout << "Enter Key : ";
            cin >> key;
            string res = ht.search(key);
            if (res != "")
                cout << "[Prompt] Value corresponding to Key " << key << " : " << res << endl;
            break;
        }
        case 4:
        {
            cout << "!!!! PRINT !!!!!" << endl;
            ht.print();
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            cout << "[Warning] Wrong option selected" << endl;
        }
        }
        cout << "-----------------------------------------------------------------------------" << endl;
    }
}