#ifndef BT_CLASS_H
#define BT_CLASS_H
#include <cstdlib>    // Provides size_t
#include "bintree.h"  // Provides binary_tree_node<Item> template class

    template <class Item>
    class binary_tree
    {
    public:
        // CONSTRUCTORS and DESTRUCTOR
        binary_tree( );
        binary_tree(const binary_tree& source);
        ~binary_tree( );
        // MODIFICATION MEMBER FUNCTIONS
        void create_first_node(const Item& entry);
        void shift_to_root( );
        void shift_up( );
        void shift_left( );
        void shift_right( );
        void change(const Item& new_entry);
        void add_left(const Item& entry);
        void add_right(const Item& entry);
        // CONSTANT MEMBER FUNCTIONS
        std::size_t size( ) const;
        Item retrieve( ) const;
        bool has_parent( ) const;
        bool has_left_child( ) const;
        bool has_right_child( ) const;
    private:
        // Private member variables to be specified by the student.
        // My own implementation has a root pointer and a pointer to
        // the "current" node, plus a member variable to keep track of
        // the number of nodes in this tree.
    };

#include "bintree.template" // To be written by the student
#endif
