/* 
Design a program to implement a Binary Search Tree (BST) with the following operation using Linked representation, on integer data

- Insert a new node with the given key value
- Delete a node with the given key value
- Find the minimum key in the BST
- Find the maximum key in the BST
- Search for a given key in the BST, and return true if found, else returns false
- Find the inorder predecessor of a node with a given key value
- Find the inorder successor of a node with a given key value
- Print the tree using level order traversal of the BST

The program should have a menu to call the above operations.

[The student should practice to implement trees for other data types including structures & class objects; and to support others operations on the tree/individual-nodes; and other possible ways they can be implemented/used]
*/
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(const int val, TreeNode *left = nullptr, TreeNode *right = nullptr)
        : val{val}, left{left}, right{right}
        {}
};

class BST
{
public:
    // Constructors/Destructors
    BST() : root{nullptr}, length{0} {}
    ~BST() {}

    // Main Methods

    // iterative insert
    bool insert_itr(const int &);

    // iterative search
    bool search_itr(const int &) const;

    // iterative minimum
    int minimum() const;

    // iterative maximum
    int maximum() const;

    // iterative bfs
    vector<int> bfs() const;

    // DFS - recursive preorder
    void pre_rec(TreeNode *) const;

    // DFS - recursive inorder
    void in_rec(TreeNode *) const;

    // DFS - recursive postorder
    void post_rec(TreeNode *) const;

    // Delete Node
    int deleteNode(const int &);

    // finding inorder successor - iterative
    int inorder_succ_itr(const int &);

    // finding inorder predecessor - iterative
    int inorder_pred_itr(const int &);

    // getter for root
    TreeNode *getRoot() const { return root; }

    // getter for size of tree
    size_t size() const { return length; }

private:
    TreeNode *root;
    size_t length;
};

bool BST::insert_itr(const int &val)
{
    if (root == nullptr)
        root = new TreeNode(val);
    else
    {
        TreeNode *curr = root;
        TreeNode *prev = root;
        while (curr)
        {
            prev = curr;
            if (curr->val > val)
            {
                curr = curr->left;
            }
            else
            {
                curr = curr->right;
            }
        }
        if (prev->val > val)
        {
            prev->left = new TreeNode(val);
        }
        else
        {
            prev->right = new TreeNode(val);
        }
    }
    length++;
    return true;
}

bool BST::search_itr(const int &val) const
{
    if (root == nullptr)
        throw runtime_error("Tree is empty");
    TreeNode *curr = root;
    while (curr)
    {
        if (curr->val == val)
        {
            return true;
        }
        else if (curr->val > val)
        {
            curr = curr->left;
        }
        else if (curr->val < val)
        {
            curr = curr->right;
        }
    }
    return false;
}

int BST::minimum() const
{
    if (root == nullptr)
        throw runtime_error("Tree is empty");
    TreeNode *curr = root;
    while (curr->left)
        curr = curr->left;
    return curr->val;
}

int BST::maximum() const
{
    if (root == nullptr)
        throw runtime_error("Tree is empty");
    TreeNode *curr = root;
    while (curr->right)
        curr = curr->right;
    return curr->val;
}

vector<int> BST::bfs() const
{
    vector<int> v;
    if (root == nullptr)
        return v;

    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
        size_t n = q.size();
        while (n--)
        {
            TreeNode *curr = q.front();
            v.push_back(curr->val);
            q.pop();
            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
        }
    }
    return v;
}
void BST::pre_rec(TreeNode *root) const
{
    if (root == nullptr)
        return;
    cout << root->val << " ";
    pre_rec(root->left);
    pre_rec(root->right);
}

void BST::in_rec(TreeNode *root) const
{
    if (root == nullptr)
        return;
    in_rec(root->left);
    cout << root->val << " ";
    in_rec(root->right);
}

void BST::post_rec(TreeNode *root) const
{
    if (root == nullptr)
        return;
    post_rec(root->left);
    post_rec(root->right);
    cout << root->val << " ";
}

int BST::deleteNode(const int &val)
{
    TreeNode *parent = nullptr;
    TreeNode *curr = root;
    bool leftChild{false};
    while (curr && curr->val != val)
    {
        parent = curr;
        if (curr->val > val)
        {
            leftChild = true;
            curr = curr->left;
        }
        else if (curr->val < val)
        {
            leftChild = false;
            curr = curr->right;
        }
    }
    if (!curr)
        return INT32_MAX;

    int returnVal = curr->val;
    if (!curr->left && !curr->right)
    {
        cout << "IN FIRST " << endl;
        if (leftChild && parent)
            parent->left = nullptr;
        else if (!leftChild && parent)
            parent->right = nullptr;
        else
            root = nullptr;
    }
    else if (!curr->left)
    {
        if (leftChild && parent)
            parent->left = curr->right;
        else if (!leftChild && parent)
            parent->right = curr->right;
        else
            root = curr->right;
    }
    else if (!curr->right)
    {
        if (leftChild && parent)
            parent->left = curr->left;
        else if (!leftChild && parent)
            parent->right = curr->left;
        else
            root = curr->left;
    }
    else
    {
        TreeNode *temp = curr->right;
        TreeNode *prev = curr;
        while (temp->left)
        {
            prev = temp;
            temp = temp->left;
        }
        if (prev == curr)
        {
            curr->val = temp->val;
            curr->right = temp->right;
            curr = temp;
        }
        else
        {
            prev->left = temp->right;
            curr->val = temp->val;
            curr = temp;
        }
    }
    length--;
    delete curr;
    return returnVal;
}

int BST::inorder_succ_itr(const int &val)
{
    if (root == nullptr)
        throw runtime_error("Tree is empty");
    stack<TreeNode *> st;
    TreeNode *curr = root;
    bool find{false};
    while (!st.empty() || curr)
    {
        while (curr)
        {
            st.push(curr);
            curr = curr->left;
        }
        TreeNode *t = st.top();
        st.pop();
        if (find == true)
            return t->val;
        if (t->val == val)
            find = true;
        curr = t->right;
    }
    return INT32_MAX;
}

int BST::inorder_pred_itr(const int &val)
{
    if (root == nullptr)
        throw runtime_error("Tree is empty");
    stack<TreeNode *> st;
    TreeNode *curr = root;
    TreeNode *prev = nullptr;
    while (!st.empty() || curr)
    {
        while (curr)
        {
            st.push(curr);
            curr = curr->left;
        }
        TreeNode *t = st.top();
        st.pop();
        if (t->val == val) {
            if(prev)
                return prev->val;
            else
                return INT32_MAX;
        }else {
            prev = t;
        }
        curr = t->right;
    }
    return INT32_MAX;
}

int main() {
    BST tree;
    while(1) {
        cout << "--------------------------- BST MENU ---------------------------" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Delete" << endl;
        cout << "3. Find Maximum" << endl;
        cout << "4. Find Minimum" << endl;
        cout << "5. Search for a Key" << endl;
        cout << "6. Inorder Predecessor" << endl;
        cout << "7. Inorder Succsessor" << endl;
        cout << "8. Print Tree" << endl;
        cout << "9. Number of node in BST" << endl;
        cout << "0. EXIT" << endl;
        int choice;
        cout << "Choice :- ";
        cin >> choice;
        cout << "--------------------------------------------------------------------" << endl;
        switch (choice) {
        case 1: {
            cout << "---- Insert In BST ----" << endl;
            int val;
            cout << "Enter value of node : ";
            cin >> val;
            if(tree.insert_itr(val)) {
                cout << val << " : inserted successfully" << endl;
            }else {
                cout << "!! Error while inserting new node !!" << endl;
            }
            break;
        }
        case 2: {
            cout << "---- Delete In BST ----" << endl;
            int val;
            cout << "Enter value of node to delete : ";
            cin >> val;
            int deletedValue = tree.deleteNode(val);
            if(deletedValue != INT32_MAX) {
                cout << deletedValue << " : deleted successfully" << endl;
            }else {
                cout << "!! Error : node not found !!" << endl;
            }
            break;
        }
        case 3: {
            cout << "---- Maximum In BST ----" << endl;
            cout << "Maximum node in BST is : " << tree.maximum() << endl;
            break;
        }
        case 4: {
            cout << "---- Minimum In BST ----" << endl;
            cout << "Minimum node in BST is : " << tree.minimum() << endl;
            break;
        }
        case 5: {
            cout << "---- Search In BST ----" << endl;
            int val;
            cout << "Enter value of node to search : ";
            cin >> val;
            if(tree.search_itr(val)) {
                cout << val << " : found in BST" << endl;
            }else {
                cout << "!! Error : node not found !!" << endl;
            }
            break;
        }
        case 6: {
            cout << "---- Inorder Predecessor In BST ----" << endl;
            int val;
            cout << "Enter value of node: ";
            cin >> val;
            int pred = tree.inorder_pred_itr(val);
            if(pred != INT32_MAX)
                cout << "Inorder predecessor of " << val << " is : " << pred << endl;
            else
                cout << "Inorder predecessor of " << val << " does not exist" << endl;

            break;
        }
        case 7: {
            cout << "---- Inorder Successor In BST ----" << endl;
            int val;
            cout << "Enter value of node: ";
            cin >> val;
            int succ = tree.inorder_succ_itr(val);
            if(succ != INT32_MAX)
                cout << "Inorder successor of " << val << " is : " << succ << endl;
            else
                cout << "Inorder successor of " << val << " does not exist" << endl;
            break;
        }
        case 8: {
            cout << "---- Print BST ----" << endl;
            cout << "Inorder : ";
            tree.in_rec(tree.getRoot());
            cout << endl;

            cout << "PreOrder : ";
            tree.pre_rec(tree.getRoot());
            cout << endl;

            cout << "Postorder : ";
            tree.post_rec(tree.getRoot());
            cout << endl;

            cout << "Level order : ";
            vector<int> v = tree.bfs();
            for(auto i : v) cout << i << " ";
            cout << endl;
            break;
        }
        case 9: {
            cout << "---- Number of nodes In BST ----" << endl;
            cout << "Node Count : " << tree.size() << endl;
            break;
        }
        case 0: {
            return 0;
            break;
        }
        default:
            cout << "!! Incorrect Option !!" << endl;
            break;
        }
        cout << "--------------------------------------------------------------------" << endl;
    }
}