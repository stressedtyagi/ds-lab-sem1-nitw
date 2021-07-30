/*Many methods contains both recursive and iterative approach */
/*1[choice]->Recusrsive*/
/*0[choice]->Iterative*/
//Used my own queue implementation for height of the tree using iterative method

#ifndef BINTREE_H
#define BINTREE_H

#include<iostream>
#include "Queue.h"
using namespace std;

template <typename T>
struct Node{
    T data;
    Node<T>* left;
    Node<T>* right;

    Node(const T &d, Node<T>* l, Node<T>* r):data{d},left{l},right{r}{}
};

template <typename T>
class BinaryTree{
    public:
        BinaryTree():root{nullptr},length{0}{
            cout << "\nBinary tree initialized\n";
        }
        
        void insert(const T& data, short choice){
            //Recursive insertion
            if(choice){
                root = insertRecurs(data,root);
                length++;
            }
            //Iterative insertion
            else{
                Node<T>* temp = root;
                Node<T>*prev = root;
                Node<T>* temp2 = new Node<T>(data,nullptr,nullptr);
                if(!root){
                    root = temp2;
                    return;
                }
                while(temp){
                    if(data > temp->data){
                        prev = temp;
                        temp = temp->right;
                    }
                    else{
                        prev = temp;
                        temp = temp->left;
                    }
                }
                if(data > prev->data)
                    prev->right = temp2;
                else
                    prev->left = temp2;

                length++;
            }
            
        }

        bool search(const T& data,short choice){
            if(choice)
                return searchRecurs(data,root);
            Node<T>* temp = root;
            Node<T>* prev = root;
            while(temp){
                if(data > temp->data){
                    prev = temp;
                    temp = temp->right;
                }else{
                    prev = temp;
                    temp = temp->left;
                }
            }
            if(prev && prev->data == data)
                return true;
            return false;
             
        }

        Node<T>* insertRecurs(const T& data, Node<T>* r){
            if(r){
                if(data <= r->data){
                    r->left = insertRecurs(data, r->left);
                }else{
                    r-> right= insertRecurs(data, r->right);
                }

                return r;
            }else{
                return new Node<T>(data,nullptr,nullptr);
            }
        }  

        bool searchRecurs(const T& data, Node<T>* r){
            if(!r)
                return false;
            if(data == r->data)
                return true;
            if(data < r->data)
                return searchRecurs(data, r->left);
    
            return searchRecurs(data, r->right);
        }

        T min(short choice) const{
            if(!root)
                throw runtime_error("Tree empty!");

            //Recursive minimum
            if(choice){
                return minRecurs(root);
            }

            //Iterative minimum
            Node<T>* temp = root;
    
            while(temp->left){
                temp = temp->left;
            }

            return temp->data;
        }


        T max(short choice) const{
            if(!root)
                throw runtime_error("Tree empty!");

            //Recursive maximum
            if(choice){
                return maxRecurs(root);
            }

            //Iterative maximum
            Node<T>* temp = root;
    
            while(temp->right){
                temp = temp->right;
            }

            return temp->data;
        }

        int getHeight(short choice)const {
            if(choice){
                return getHeightRecurs(root);
            }

            Queue<Node<T>*> q;
            q.enqueue(root);
            int height{-1};

            while(!q.isEmpty()){
                height++;

                int nodeCount = q.length();

                while(nodeCount--){
                    Node<T>* temp = q.dequeue();
                    if(temp->left)q.enqueue(temp->left);
                    if(temp->right)q.enqueue(temp->right);
                }
            }

            return height;

        }
        
        void bftPrint(){
            if(root){
                Queue<Node<T>*> q;
                q.enqueue(root);

                while(!q.isEmpty()){
                    size_t nodeCount{q.length()};

                    while(nodeCount--){
                        Node<T>* temp = q.dequeue();
                        cout << temp->data << " ";
                        if(temp->left){
                            q.enqueue(temp->left);
                        }
                        if(temp->right){
                            q.enqueue(temp->right);
                        }
                    }

                    cout << endl;
                }

            }else{
                cout << ":-Tree empty\n";
            }
        }

        void dfPrePrint(){
            cout << "\n------------------Pre-order----------------------\n";
            prePrint(root);     
            cout << "----------------------------------------------\n";
        }

        void dfPostPrint(){
            cout << "\n--------------------Post-order---------------------\n";
            postPrint(root);     
            cout << "----------------------------------------------\n";
        }

        void dfInPrint(){
            cout << "\n----------------------In-order---------------------\n";
            inPrint(root);     
            cout << "----------------------------------------------\n";
        }

        void deleteNode(const T& data){
            Node<T>* temp = root;
            Node<T>* parent = nullptr;

            if(root){
                //searching for required node
                while(temp && temp->data != data){
                    parent = temp;
                    if(data > temp->data)
                        temp = temp-> right;
                    else
                        temp = temp->left;
                }

                if(temp){
                    //Case 1
                    //No child
                    if(!temp->left && !temp->right){
                        if(!parent)root = nullptr;
                        else if(parent->left == temp){
                            parent->left = nullptr;
                        }else{
                            parent->right = nullptr;
                        }
                        delete temp;
                    }else{
                        //Case2 Exactly one child
                        if(temp->left && !temp->right){
                            if(!parent){
                                root = temp->left;
                            }
                            else if(parent->left == temp){
                                parent->left = temp->left;
                            }else{
                                parent->right = temp->left;
                            }
                            delete temp;

                        }else if(temp->right && !temp->left){
                            if(!parent){
                                root = temp->right;
                            }
                            else if(parent->left == temp){
                                parent->left = temp->right;
                            }else{
                                parent->right = temp->right;
                            }
                            delete temp;
                        }
                        //2 children
                        else{
                            Node<T>* temp2 = temp->right;
                            Node<T>* temp2Parent = temp;

                            //Searching left most element in right sub tree of node to be deleted
                            while(temp2->left){
                                temp2Parent = temp2;
                                temp2 = temp2->left;
                            }
    
                            if(temp2Parent != temp)
                                temp2Parent->left = temp2->right;

                            temp2->left = temp->left;

                            if(temp2 != temp->right)
                                temp2->right = temp->right;
                        

                            if(!parent){
                                root = temp2;
                            }
                            else if(parent->left == temp){
                                parent->left = temp2;
                            }else{
                                parent->right = temp2;
                            }

                            delete temp;
                        }
                    }            

                    
                }else{
                    cout << "No node with given data\n";
                }
            }else{
                cout << "Empty tree!\n";
            }
        }

        T inorderSucc(T data){
            Node<T>* temp = root;
            while(temp && temp->data != data){
                if(data > temp->data){
                    temp = temp->right;
                }else{
                    temp = temp->left;
                }
            }
            
            if(temp){
                Node<T>* rightSub = temp->right;
                if(rightSub){
                    Node<T>* temp2 = rightSub;
                    while(temp2->left)temp2 = temp2->left;

                    return temp2->data;
                }else{
                    Node<T>* ancestor = root;
                    Node<T>* successor = nullptr;

                    while(ancestor != temp){
                        if(data > ancestor->data){
                            ancestor = ancestor->right;
                        }else{
                            successor = ancestor;
                            ancestor = ancestor->left;
                        }
                    }

                    return successor->data;

                }
            }else{
                cout << "Node not found\n";
            }
            
        }
    
    private:
        T minRecurs(Node<T>* root) const{
            if(!root->left)
                return root->data;
            return minRecurs(root->left);
        }

        T maxRecurs(Node<T>* root) const{
            if(!root->right)
                return root->data;
            return maxRecurs(root->right);
        }

        int getHeightRecurs(Node<T>* root) const{
            if(!root)
                return -1;
            int leftHeight = getHeightRecurs(root->left);
            int rightHeight = getHeightRecurs(root->right);
            
            return (std::max(leftHeight, rightHeight) + 1);
        }
        
        void prePrint(Node<T>* r){
            if(!r)return;
            cout << r->data << " ";
            prePrint(r->left);
            prePrint(r->right);
        }

        void postPrint(Node<T>* r){
            if(!r)return;
            postPrint(r->left);
            postPrint(r->right);
            cout << r->data << " ";
        }

        void inPrint(Node<T>* r){
            if(!r)return;
            inPrint(r->left);
            cout << r->data << " ";
            inPrint(r->right);
        }

    private:
        Node<T>* root;
        size_t length;
};

#endif