#ifndef BT_CLASS_H
#define BT_CLASS_H

#include <cstdlib>    // Provides size_t
#include "bintree.h"  // Provides binary_tree_node<Item> template class

    template <class Item>
    class binary_tree
    {
    public:
        // CONSTRUCTORS and DESTRUCTOR
        binary_tree( ){
            {
                    root = NULL;
                    current_node = NULL;
                    node_number = 0;
                }
        }
        binary_tree(const binary_tree& source){
            tree_copy(source.root);
        }
        ~binary_tree( ){
            tree_clear(root);
            node_number = 0;
        }

        // MODIFICATION MEMBER FUNCTIONS
        void create_first_node(const Item& entry){
            if(size() == 0){
                root = new binary_tree_node<Item>(entry);
                current_node = root;
                node_number = 1;
            }
        }
        void shift_to_root( ){
            root = current_node;
        }
        void shift_up(binary_tree_node<Item>* root1, binary_tree_node<Item>* current_node1){
            current_node = current_node1;
            if(has_parent(root1, current_node1)){
                if (root == current_node || root == NULL){}
                else if (root1->left() == current_node1 || root1->right() == current_node1){
                    current_node = root1;
                }
                else{
                    if(has_parent(root1->left(), current_node1)){
                        shift_up(root1->left(), current_node1);
                    }
                    else if (has_parent(root1->right(), current_node1)){
                        shift_up(root1->right(), current_node1);
                    }
                }
            }
       }

        void shift_left( ){
            if(has_left_child()){
                current_node = current_node->left();
            }
        }
        void shift_right( ){
            if(has_left_child()){
                current_node = current_node->right();
            }
        }
        void change(const Item& new_entry){
            current_node->data() = new_entry;
        }
        void add_left(const Item& entry){
            if(!has_left_child()){
                current_node->set_left(new binary_tree_node<Item>(entry));
                node_number += 1;
            }
        }
        void add_right(const Item& entry){
            if(!has_right_child()){
                current_node->set_right(new binary_tree_node<Item>(entry));
                node_number += 1;
            }
        }
        // CONSTANT MEMBER FUNCTIONS
        std::size_t size( ) const{
            return node_number;
        }
        Item retrieve( ) const{
            if(size() > 0){
                return current_node->data();
            }
        }
        bool has_parent(binary_tree_node<Item>*root1, binary_tree_node<Item>* current_node1) const{
            current_node1 = current_node;
            if (root1 == current_node1 || root1 == NULL){
                        return false;
                }
            else if (root1->left() == current_node1 || root->right() == current_node1){
                return true;
            }
            else{
                if(has_parent(root1->left(), current_node1)){
                    return true;
                }
                else if (has_parent(root1->right(), current_node1)){
                    return true;
                }
            }
       }

        bool has_left_child() const{
            if(size() > 0){
                if(current_node->left() != NULL){
                    return true;
                }
                else{
                    return false;
                }
            }
        }

        bool has_right_child( ) const{
            if(size() > 0){
                if(current_node->right() != NULL){
                    return true;
                }
                else{
                    return false;
                }
            }
        }


        binary_tree_node<Item>* get_root(){return root;}
        binary_tree_node<Item>* get_currentNode(){return current_node;}
    private:
        binary_tree_node<Item> *root;
        binary_tree_node<Item> *current_node;
        size_t node_number;
        // Private member variables to be specified by the student.
        // My own implementation has a root pointer and a pointer to
        // the "current" node, plus a member variable to keep track of
        // the number of nodes in this tree.
    };

#endif // BT_CLASS_H
