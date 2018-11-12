/** Copyright www.github.com/jrezzende */
#ifndef STRUCTURES_AVI_TREE_H
#define STRUCTURES_AVI_TREE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions
#include "array_list.h"

namespace structures {
/**CLASS AVLTREE*/
template<typename T>
class AVLTree {
public:
    AVLTree()= default;
    virtual ~AVLTree();  // DESTRUCTOR
    void insert(const T& data);  // INSERTS A NODE INTO THE TREE
    void remove(const T& data);  // REMOVES A NODE FROM THE TREE
    bool contains(const T& data) const;  // TRUE IF THE TREE CONTAINS SUCH NODE
    bool empty() const;  // TRUE IF THE TREE IS EMPTY
    std::size_t size() const;  // RETURNS THE ACTUAL SIZE OF THE TREE
    /**ROOT > LEFT > RIGHT*/
    ArrayList<T> pre_order() const {
    ArrayList<T> v{size_};
        if (!empty())
            root->pre_order(v);
        return v;
    }
    /**LEFT > ROOT > RIGHT*/
    ArrayList<T> in_order() const {
        ArrayList<T> v{size_};
        if (!empty())
            root->in_order(v);
        return v;
    }
    /**LEFT > RIGHT > ROOT*/
    ArrayList<T> post_order() const {
        ArrayList<T> v{size_};
        if (!empty())
            root->post_order(v);
        return v;
    }	 	  	 	     	    	     	 	      	     	     	 	

private:
    struct Node {
        explicit Node(const T& data) : data{data}, left{nullptr}, right{nullptr}
        {}
        T data;
        std::size_t height;
        Node* left;
        Node* right;
/**INSERTS NODE INTO THE TREE*/
        void insert(const T& data_) {
            Node* new_node;
            if (data_ < this->data) {
                if (this->left == nullptr) {
                    new_node = new Node(data_);
                    new_node->left = nullptr;
                    new_node->right = nullptr;
                    this->left = new_node;
                } else {
                    left->insert(data_);
                }
            } else {
                if (this->right == nullptr) {
                    new_node = new Node(data_);
                    new_node->left = nullptr;
                    new_node->right = nullptr;
                    this->right = new_node;
                } else {
                    right->insert(data_);
                }
            }
        }
/**REMOVES A NODE FROM THE TREE*/
        bool remove(const T& data_) {
            bool temp = false;
            if (data_ == this->data) {	 	  	 	     	    	     	 	      	     	     	 	
                Node* new_node;
                if ((this->left != nullptr) && (this->right != nullptr)) {
                    new_node = this->right;
                    while (new_node->left != nullptr)
                        new_node = new_node->left;
                    this->data = new_node->data;
                    temp = right -> remove(this->data);
                } else {
                    if (this->right != nullptr) {
                        this->data = right->data;
                        temp = right -> remove(this->data);
                    } else {
                        if (this->left != nullptr) {
                        this->data = left->data;
                        temp = left->remove(this->data);
                        } else {
                            delete this;
                            temp = true;
                        }
                    }
                }
            } else {
            if ((this->left != nullptr) && (data_ < this->data))
                temp = left->remove(data_);
            if ((this->right != nullptr) && (data_ > this->data))
                temp = right->remove(data_);
            }
            return temp;
        }
/**TRUE IF THE TREE CONTAINS SUCH DATA*/
        bool contains(const T& data_) const {
            bool temp = false;
            if (data_ == this->data) {
                temp = true;
            } else {
                if ((this->left != nullptr) && (data_ < this->data)) {	 	  	 	     	    	     	 	      	     	     	 	
                    temp = left->contains(data_);
                } else if ((this->right != nullptr) && (data_ > this->data)) {
                    temp = right->contains(data_);
                }
            }
            return temp;
        }
/*UPDATE TREE HEIGHT*/
        void updateHeight() {
            if (this->left == nullptr || this->right == nullptr)
                return -1;
            this->heigth++;
        }
/**SIMPLE ROTATION TO THE LEFT*/
        Node* simpleLeft(Node* k2) {
            Node* k1;
            k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            k2->updateHeight();
            k1->updateHeight();
            return k1;
        }
/**SIMPLE ROTATION TO THE RIGHT*/
        Node* simpleRight(Node* k2) {
            Node* k1;
            k1 = k2->right;
            k2->right = k1->left;
            k1->left = k2;
            k2->updateHeight();
            k1->updateHeight();
            return k1;
        }
/**DOUBLE ROTATION TO THE LEFT*/
        Node* doubleLeft(Node* k3) {
            k3->left = simpleRight(k3->left);
            return simpleLeft(k3);
        }	 	  	 	     	    	     	 	      	     	     	 	
/**DOUBLE ROTATION TO THE RIGHT*/
        Node* doubleRight(Node* k3) {
            k3->right = simpleLeft(k3->right);
            return simpleRight(k3);
        }
/**ROOT > LEFT > RIGHT*/
        void pre_order(ArrayList<T>& v) const {
            v.push_back(this->data);
            if (this->left != nullptr)
                left->pre_order(v);
            if (this->right != nullptr)
                right->pre_order(v);
        }
/*LEFT > ROOT > RIGHT**/
        void in_order(ArrayList<T>& v) const {
             if (this->left != nullptr)
                left->in_order(v);
            v.push_back(this->data);
            if (this->right != nullptr)
                right->in_order(v);
        }
/**LEFT > RIGHT > ROOT*/
        void post_order(ArrayList<T>& v) const {
             if (this->left != nullptr)
                left->post_order(v);
            if (this->right != nullptr)
                right->post_order(v);
            v.push_back(this->data);
        }
    };

    Node* root{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures
#endif
/**TREE DESTRUCTOR*/
template<typename T>
structures::AVLTree<T>::~AVLTree() {	 	  	 	     	    	     	 	      	     	     	 	
    size_= 0;
    delete root;
}
/**INSERTS A NODE INTO THE TREE*/
template<typename T>
void structures::AVLTree<T>::insert(const T& data) {
    if (empty())
        root= new Node(data);
    else
        root->insert(data);
    size_++;
}
/**REMOVES A NODE FROM THE THREE*/
template<typename T>
void structures::AVLTree<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("TREE IS EMPTY!");
    if (contains(data)) {
        size_--;
        root->remove(data);
    }
}
/**TRUE IF THE TREE CONTAINS GIVEN DATA*/
template<typename T>
bool structures::AVLTree<T>::contains(const T& data) const {
    return root->contains(data);
}
/**TRUE IF THE TREE IS EMPTY*/
template<typename T>
bool structures::AVLTree<T>::empty() const {
    return size_ == 0;
}
/**RETURNS THE ACTUAL SIZE OF THE TREE*/
template<typename T>
std::size_t structures::AVLTree<T>::size() const {
    return size_;
}	 	  	 	     	    	     	 	      	     	     	 	
