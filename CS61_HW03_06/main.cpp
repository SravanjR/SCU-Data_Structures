#include <iostream>
#include<queue>
#include"bintree.h"
#include"bt_class.h"
using namespace std;

bool IsParentheses(char C);
bool IsOperator(char C);
bool IsOperand(char C);

binary_tree<char> prefix_to_tree(string expr);

int main(){
    string input;
    //(+(*AB)(/CD))
    // cin >> input;
    // string prefix = "(+(*AB)(/CD))";
    string prefix = "(+(*(+AB)X)(/CD))";
    //input must be surrounded on both sides by parentheses
    binary_tree<char> bt = prefix_to_tree(prefix);
    inorder(bt.get_root());
    cout<<endl;
    return 0;

   return 0;
}


binary_tree<char> prefix_to_tree(string expr){
    binary_tree<char> tree;
    queue<char> Operators;
    queue<char> Operands;
    for(size_t i = 0; i < expr.length();i++){
        if(IsOperator(expr[i])||IsParentheses(expr[i])){
            Operators.push(expr[i]);
            cout<<Operators.back();
        }
        else if(IsOperand(expr[i])){
            Operands.push(expr[i]);
            cout<<Operands.back();
        }
    }
    cout<<endl;
    while(!Operands.empty()&&!Operators.empty()){
        if(IsOperator(Operators.front())){
             if(tree.size()==0){
                 tree.create_first_node(Operators.front());
             }
             else if(!tree.has_left_child()){
                 tree.add_left(Operators.front());
                 tree.shift_left();
             }
             else if(!tree.has_right_child()){
                 tree.add_right(Operators.front());
                 tree.shift_right();
             }
             Operators.pop();
        }

        if(Operators.front()==')' && !Operands.empty()){
            Operators.pop();
            if(!tree.has_left_child()){
                tree.add_left(Operands.front());
                Operands.pop();
            }
            if(!tree.has_right_child()){
                tree.add_right(Operands.front());
                Operands.pop();
            }
        }
        while(tree.has_left_child()&&tree.has_right_child() && tree.get_currentNode() != tree.get_root()){
            //cout<<"a";
            tree.shift_up(tree.get_root(), tree.get_currentNode());
        }

        if(Operators.front()== '(')
            Operators.pop();
    }
    //(+(*AB)(/CD))*/
    return tree;
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
