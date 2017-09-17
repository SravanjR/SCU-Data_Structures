#include<iostream>
#include<stack>
#include<string>
using namespace std;
string InfixToPrefix(string expression);
string PrefixToInfix(string expression2);
bool IsParentheses(char C);
bool IsOperator(char C);
bool IsOperand(char C);
int main()
{
    string expr = "((A*B)+(C/D))";
    cout<<expr<<endl;
    string a = InfixToPrefix(expr);
    cout<< a <<endl;
    string expr2 = a;
    //(+(*AB)(/CD))
    cout<<PrefixToInfix(expr2)<<endl;

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

string InfixToPrefix(string expression){
    stack<char> oprtr;
    stack<char> oprtr2;
    string prefix ="";
    string::iterator it;
    //read and push all the operators into the stack from the expression to be inserted in reverse order
    for(int j = 0;j <expression.length(); j++){
        if(IsOperator(expression[j])){
            oprtr.push(expression[j]);
        }
    }
    //reread the expression from the right
    for(int i = expression.length()-1;i >=0; i--){
        //if character is an operand or parentheses it is inserted at the beginning of the new string
        if(IsOperand(expression[i])||IsParentheses(expression[i])){
            it = prefix.insert(prefix.begin(),expression[i]);
        }
        //function assumes that there is no empty space and expression is already in proper infix notation
        //if operands in the built string are place together, insert the top from the operator stack to the front of the string and pop it
        if(IsOperand(prefix[0])&&IsOperand(prefix[1])){
            it = prefix.insert(prefix.begin(),oprtr.top());
            oprtr.pop();
        }
        //if the character is an operator between two parenthesis, push it into the second stack and pop it from the first stack
        if(IsParentheses(expression[i+1])&&IsParentheses(expression[i-1])&&IsOperator(expression[i])){
            oprtr2.push(oprtr.top());
            oprtr.pop();
        }
        //if an operator is between an operand and a parenthesis, then push it into stack 2 and pop it from stack 1
        if(IsOperand(expression[i+1])&&IsParentheses(expression[i-1])&&IsOperator(expression[i])){
            oprtr2.push(oprtr.top());
            oprtr.pop();
        }
        //if stack 2 is not empty and the left parenthesis is read, then insert the top character from stack 2 into the string and pop it from the stacl
        if(!(oprtr2.empty())&&(expression[i] == '(')){
            it = prefix.insert(prefix.begin(),oprtr2.top());
            oprtr2.pop();
        }
    }
    return prefix;
}

string PrefixToInfix(string expression2){
    //(+(*AB)(/CD)) - > ((A*B)+(C/D))
    stack<char> oprtr;
    stack<char> oprtr2;
    string infix ="";
    string::iterator it;
    //read from right to left and push all read operators into stack 1
    for(int j = expression2.length()-1;j >= 0; j--){
        if(IsOperator(expression2[j])){
            oprtr.push(expression2[j]);
        }
    }
    //reread the expression from the left
    for(int i = 0; i < expression2.length(); i++){
        //if the read character is an operator or a parenthesis, insert it into the new string
        if(IsOperand(expression2[i])||IsParentheses(expression2[i])){
            it = infix.insert(infix.begin(),expression2[i]);
        }
        //if the read character is an operator followed by a left parenthesis, then push it into stack 2 and pop the top off the first stack
        if(IsOperator(expression2[i])&&expression2[i+1] == '('){
            oprtr2.push(oprtr.top());
            oprtr.pop();
        }
        //if the read character is a an operand followed by another operand, insert the top operator from stack one and pop it
        if(IsOperand(expression2[i])&&IsOperand(expression2[i+1])){
            it = infix.insert(infix.begin(),oprtr.top());
            oprtr.pop();
        }
        //if the read character is a right parenthesis followed by a left one, insert the top operator from stack 2 and pop it
        if(expression2[i] == ')' && expression2[i+1] == '('){
            it = infix.insert(infix.begin(),oprtr2.top());
            oprtr2.pop();
        }
        //if if the read character is a right parenthesis followed by an operand, insert from the top of stack 2 and pop it
        if(expression2[i] == ')' && IsOperand(expression2[i+1])){
            it = infix.insert(infix.begin(),oprtr2.top());
            oprtr2.pop();
        }
    }
    //the built string will be reversed from the actual infix notation, so reverse it once again and return the return the result
    string infix2= "";
    for(int k = infix.length()-1; k >= 0; k--){
        infix2 += infix[k];
    }
    return infix2;
}
