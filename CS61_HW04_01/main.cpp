#include <iostream>
#include "bintree.h"
#include "btree.h"
#include<string>
#include <queue>
using namespace std;

template<typename T>
binary_tree<T> prefix_to_tree(string expr);

bool IsParentheses(char C);
bool IsOperator(char C);
bool IsOperand(char C);
//both sides are covered by parenthesis like (+(*AB)(/CD))

int main()
{
    //(+(*AB)(/CD))
    string prefix = "(+(*AB)(/CD))";
    binary_tree<char> bt = prefix_to_tree(prefix);

    //inorder(bt.get_root());
    return 0;

}

bool IsParentheses(char C)
{
    if(C == ')' || C == '(') return true;
    return false;
}
bool IsOperand(char C)
{
    if(C >= '0' && C <= '9') return true;
    if(C >= 'a' && C <= 'z') return true;
    if(C >= 'A' && C <= 'Z') return true;
    return false;
}

bool IsOperator(char C){
    if(C == '+' || C == '-' || C == '*' || C == '/' || C== '$')
        return true;
    return false;
}


binary_tree<char> prefix_to_tree(string expr){
    binary_tree<char> tree;
    queue<char> Operators;
    queue<char> Operands;
    for(int i = 0; i < expr.length();i++){
        if(IsOperator(expr[i])||IsParentheses(expr[i])){
            Operators.push(expr[i]);
        }
        else if(IsOperand(expr[i])){
            Operands.push(expr[i]);
        }
    }
    while(!Operators.empty() && !Operands.empty()){
        if(IsOperator(Operators.front())&&(tree.size()==0)){
            tree.create_first_node(Operators.front());
            Operators.pop();
        }
        else if(IsOperator(Operators.front())){
            if(!tree.has_left_child()){
                tree.add_left(Operators.front());
            }
            if(tree.has_left_child()){
                tree.add_right(Operators.front());
            }
            Operators.pop();
        }
        else if(Operators.front() == ')'){
            Operators.pop();
            if(!tree.has_left_child()){
                tree.add_left(Operands.front());
                Operands.pop();
            }
            if(!tree.has_right_child()){
                tree.add_right(Operands.front());
                Operands.pop();
            }
            tree.shift_up(tree.get_root(), tree.get_currentNode());
        }
        else if(Operators.front() == '('){
            Operators.pop();
        }
    }
    return tree;
}



