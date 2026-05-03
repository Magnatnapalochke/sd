#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

template<typename T>
class BinarySearchTree{
private:
    struct Node{
        T key_;
        Node* left_;
        Node* right_;
        Node* p_;
        Node(const T& value): key_(value), left_(nullptr), 
        right_(nullptr), p_(nullptr){}
    };
    Node* root_;

    void clear(Node* node){
        if(node){
            clear(node->left_);
            clear(node->right-);
            delete node;
        }
    }

public:
    BinarySearchTree(): root_(nullptr){}
    BinarySearchTree(const BinarySearchTree& other) = delete;
    BinarySearchTree& operator=(const BinarySearchtree& other) = delete;
    BinarySearchTree(BinarySearchTree&& other)noexcept : root_(other.root_){
        other.root_ = nullptr;
    }
    BinarySearchTree& operator=(BinarySearchTree&& other)noexcept{
        if(this != &other){
            clear(root_)

            root_ = other.root_;
            other.root_ = nullptr;
        }
        return *this;
    }
    ~BinarySearchTree(){
        clear(root_);
    }


    bool searchIterative(const T& key) const{
        return searchIterativeNode(key) != nullptr;
    }

    bool insert(const T& key){
        if(searchIterative(key)){
            return false;
        }
        Node* newNode = new Node(key);
        Node* current = root_;
        Node* parent = nullptr;
        while (current != nullptr){
            parent = current;
            if(key < current->key_){
                current = current->left_;
            }
            else{
                current = current->right_;
            }
        }
        newNode->p_ = parent;
        if (!parent){
            root_ = newNode;
        }
        else if(key < parent->key_) parent->left_ = newNode;
        else parent->right_ = newNode;

        return true;
    }

    bool remove(const T& key){
        Node* removeNode = searchIterativeNode(key);
        if(!removeNode){
            return false;
        }
        if(removeNode->left_ == nullptr || removeNode->right_==nullptr){
            if(removeNode-> == nullptr && removeNode->right_ == nullptr){
                if(key == root_->key_){
                    root_ = nullptr;
                    return true;
                }
            }
            else{
                removeNode_->p_
            }
        }
    }


private:
    Node* searchIterativeNode(const T& key)const{
        Node* current = root_;
        while (current != nullptr && key != current->key_){
            if(key < current->key_){
                current = current->left_;
            }
            else{
                current = current->right_;
            }
        }
        return current;
    }
};

#endif