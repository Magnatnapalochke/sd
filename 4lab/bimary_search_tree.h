#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stack>
#include <queue>

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
            clear(node->right_);
            delete node;
        }
    }

public:
    BinarySearchTree(): root_(nullptr){}
    BinarySearchTree(const BinarySearchTree& other) = delete;
    BinarySearchTree& operator=(const BinarySearchTree& other) = delete;
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
            Node* child = nullptr;
            if(removeNode->left_){
                child = removeNode->left_;
            }
            else{
                child = removeNode->right_;
            }
            if(removeNode->p_){
                if(removeNode->p_->left_ == removeNode){
                    removeNode->p_->left_ = child;
                }
                else{
                    removeNode->p_->right_ = child;
                }
            }
            else{
                root_ = child;
            }
            if(child){
                child->p_ = removeNode->p_;
            }
            delete removeNode;
            return true;
        }
        else{
            Node* successor = removeNode->right_;
            while (successor->left_){
                successor = successor->left_;
            }
            removeNode->key_ = std::move(successor->key_);

            Node* child = successor->right_;
            if(successor->p_){
                if(successor->p_->left_ == successor){
                    successor->p_->left_ = child;
                }
                else{
                    successor->p_->right_ = child;
                }
            }
            if(child){
                child->p_ = successor->p_;
            }
            delete successor;
            return true;
        }
        return false;
    }


    void output(std::ostream& out) const{
        outputTree(out, root_);
        out << std::endl;
    }

    int getNumberOfNodes() const{
        return getNumberOfNodes(root_);
    }

    int getHeight()const{
        return getHeight(root_);
    }

    void inorderWalkIterative() const{
        if (root_ == nullptr) {
            return;
        }
        
        std::stack<Node*> stack;
        Node* current = root_;
        
        while (current != nullptr || !stack.empty()) {

            while (current != nullptr) {
                stack.push(current);
                current = current->left_;
            }
            

            current = stack.top();
            stack.pop();
            std::cout << current->key_ << " ";
            current = current->right_;
        }
        
        std::cout << std::endl;
    }
    void inorderWalk()const{
        inorderWalk(root_);
        std::cout<< std::endl;
    }

    void walkByLevels() const{
        if(!root_){
            return;
        }

        std::queue<Node*> queue;
        queue.push(root_);

        while (!queue.empty()){
            Node* current = queue.front();
            queue.pop();
            std::cout << current->key_ << " ";

            if(current->left_){
                queue.push(current->left_);
            }
            if(current->right_){
                queue.push(current->right_);
            }
        }

        std::cout<< std::endl;
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

    void outputTree(std::ostream& out, Node* root)const{
        if(!root){
            return;
        }
        out<<root->key_;
        if(root->left_ || root->right_){
            out<<"(";
            outputTree(out, root->left_);
            out<<",";
            outputTree(out, root->right_);
            out<<")";
        }
    }

    int getNumberOfNodes(const Node* node)const{
        if(!node){
            return 0;
        }
        return 1 + getNumberOfNodes(node->left_) + getNumberOfNodes(node->right_);
    }

    int getHeight(const Node* node) const{
        if(!node){
            return 0;
        }

        int leftHeight = getHeight(node->left_);
        int rightHeight = getHeight(node->right_);

        return 1+std::max(leftHeight, rightHeight);
    }

    void inorderWalk(Node* node)const{
        if(!node){
            return;
        }
        inorderWalk(node->left_);
        std::cout<<node->key_ << " ";
        inorderWalk(node->right_);
    }
};

#endif