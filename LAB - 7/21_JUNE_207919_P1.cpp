/* 
Design a program to implement an AVL tree with the following operations (using Linked representation), on integer data

•Insert a new node with the given key value
•Delete a node with the given key value
•Search for a given key in the AVL tree, and return true if found, else returns false
•Print the tree in inorder and
•Print the tree in level order
Use a menu in a loop, to call the various options/operations.
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
    size_t height;
    TreeNode(const int val, size_t height = 1, TreeNode *left = nullptr, TreeNode *right = nullptr)
        : val{val}, height{height}, left{left}, right{right}
    {
    }
};

class AVL
{
public:
    // Constructors/Destructors
    AVL() : root{nullptr}, length{0} {}
    ~AVL() {}

    // Main Methods
    // recursive insert
    TreeNode *insert_rec(const int &, TreeNode *);
    // recursive search
    bool search_rec(TreeNode *, const int &) const;
    // iterative bfs
    vector<int> bfs() const;
    // DFS - recursive preorder
    void pre_rec(TreeNode *) const;
    // DFS - recursive inorder
    void in_rec(TreeNode *) const;
    // DFS - recursive postorder
    void post_rec(TreeNode *) const;
    // Delete Node
    TreeNode *delete_node_rec(TreeNode *, const int &);

    // getter & setters
    TreeNode *getRoot() const { return root; }
    void setRoot(TreeNode *newRoot) { root = newRoot; }
    size_t size() const { return length; }

    // Auxillary functions used for AVL tree specially
    size_t height(TreeNode *) const;
    int getBalanceFactor(TreeNode *) const;
    TreeNode *leftRotate(TreeNode *);
    TreeNode *rightRotate(TreeNode *);
    TreeNode *inorder_succ_node(TreeNode *);

private:
    TreeNode *root;
    size_t length;
};

size_t AVL::height(TreeNode *node) const
{
    if (node == nullptr)
        return 0;
    return node->height;
}
int AVL::getBalanceFactor(TreeNode *node) const
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}
TreeNode *AVL::leftRotate(TreeNode *node)
{
    TreeNode *y = node->right;
    TreeNode *temp = y->left;
    y->left = node;
    node->right = temp;
    node->height = max(height(node->left), height(node->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}
TreeNode *AVL::rightRotate(TreeNode *node)
{
    TreeNode *y = node->left;
    TreeNode *temp = y->right;
    y->right = node;
    node->left = temp;
    node->height = max(height(node->left), height(node->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}
TreeNode *AVL::insert_rec(const int &val, TreeNode *root)
{
    if (root == nullptr)
    {
        length++;
        return new TreeNode(val);
    }

    if (val < root->val)
    {
        root->left = insert_rec(val, root->left);
    }
    else if (val > root->val)
    {
        root->right = insert_rec(val, root->right);
    }
    else
    {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balanceFactor = getBalanceFactor(root);

    if (balanceFactor > 1 && root->left->val > val)
    {
        // Left Left Case
        return rightRotate(root);
    }
    else if (balanceFactor > 1 && root->left->val < val)
    {
        // Left Right Case
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    else if (balanceFactor < -1 && root->right->val < val)
    {
        // Right Right Case
        return leftRotate(root);
    }
    else if (balanceFactor < -1 && root->right->val > val)
    {
        // Right Left Case
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
bool AVL::search_rec(TreeNode *root, const int &val) const
{
    if (root == nullptr)
        return false;
    if (root->val == val)
        return true;
    if (root->val > val)
        return search_rec(root->left, val);
    return search_rec(root->right, val);
}
vector<int> AVL::bfs() const
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
void AVL::pre_rec(TreeNode *root) const
{
    if (root == nullptr)
        return;
    cout << root->val << " ";
    pre_rec(root->left);
    pre_rec(root->right);
}
void AVL::in_rec(TreeNode *root) const
{
    if (root == nullptr)
        return;
    in_rec(root->left);
    cout << root->val << " ";
    in_rec(root->right);
}
void AVL::post_rec(TreeNode *root) const
{
    if (root == nullptr)
        return;
    post_rec(root->left);
    post_rec(root->right);
    cout << root->val << " ";
}
TreeNode *AVL::delete_node_rec(TreeNode *root, const int &val)
{
    if (root == nullptr)
        return root;
    if (val < root->val)
    {
        root->left = delete_node_rec(root->left, val);
    }
    else if (val > root->val)
    {
        root->right = delete_node_rec(root->right, val);
    }
    else
    {
        length--;
        if (root->left == nullptr || root->right == nullptr)
        {
            TreeNode *node = root->left ? root->left : root->right;
            if (node == nullptr)
            {
                node = root;
                root = nullptr;
            }
            else
            {
                *root = *node;
            }
            free(node);
        }
        else
        {
            TreeNode *node = inorder_succ_node(root->left);
            root->val = node->val;
            root->left = delete_node_rec(root->left, node->val);
        }
    }

    if (root == nullptr)
        return root;
    root->height = 1 + max(height(root->left), height(root->right));
    int balanceFactor = getBalanceFactor(root);

    if (balanceFactor > 1 && getBalanceFactor(root->left) >= 0)
    {
        // Left Left Case
        return rightRotate(root);
    }
    else if (balanceFactor > 1 && getBalanceFactor(root->left) < 0)
    {
        // Left Right Case
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    else if (balanceFactor < -1 && getBalanceFactor(root->right) <= 0)
    {
        // Right Right Case
        return leftRotate(root);
    }
    else if (balanceFactor > 1 && getBalanceFactor(root->right) > 0)
    {
        // Right Left Case
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
TreeNode *AVL::inorder_succ_node(TreeNode *root)
{
    TreeNode *curr = root;
    while (curr->right)
    {
        curr = curr->right;
    }
    return curr;
}

int main()
{
    AVL tree;
    while (1)
    {
        cout << "--------------------------- BST MENU ---------------------------" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Delete" << endl;
        cout << "3. Search for a Key" << endl;
        cout << "4. Print Tree - DFS (Inorder,Preorder,PostOrder)" << endl;
        cout << "5. Number of node in BST" << endl;
        cout << "0. EXIT" << endl;
        int choice;
        cout << "Choice :- ";
        cin >> choice;
        cout << "--------------------------------------------------------------------" << endl;
        switch (choice)
        {
        case 1:
        {
            cout << "---- Insert In BST ----" << endl;
            int val;
            cout << "Enter value of node : ";
            cin >> val;
            tree.setRoot(tree.insert_rec(val, tree.getRoot()));
            cout << val << " : inserted successfully" << endl;
            break;
        }
        case 2:
        {
            cout << "---- Delete In BST ----" << endl;
            int val;
            cout << "Enter value of node to delete : ";
            cin >> val;
            size_t sz = tree.size();
            tree.setRoot(tree.delete_node_rec(tree.getRoot(), val));
            if (tree.size() < sz)
            {
                cout << val << " : deleted successfully" << endl;
            }
            else
            {
                cout << "!! Error : node not found or Tree is empty !!" << endl;
            }
            break;
        }
        case 3:
        {
            cout << "---- Search In BST ----" << endl;
            int val;
            cout << "Enter value of node to search : ";
            cin >> val;
            if (tree.search_rec(tree.getRoot(), val))
            {
                cout << val << " : found in BST" << endl;
            }
            else
            {
                cout << "!! Error : node not found !!" << endl;
            }
            break;
        }
        case 4:
        {
            cout << "---- Print BST : DFS ----" << endl;
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
            for (auto i : v)
                cout << i << " ";
            cout << endl;
            break;
        }
        case 5:
        {
            cout << "---- Number of nodes In BST ----" << endl;
            cout << "Node Count : " << tree.size() << endl;
            break;
        }
        case 0:
        {
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