#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <vector>
#include<map>
#include<sstream>
using namespace std;

void determineWordSearchSize(ifstream &inputFile, size_t& rows, size_t& columns);
void determineDictionary(size_t rows, size_t columns, char **table, multimap<string, pair<pair<int, int>, pair<int, int>>>& answer,
                         unordered_set<string> dictionary);
//template <size_t rin, size_t column>
string getRight(size_t rows, size_t columns, char **table, int r, int c, int len){
    stringstream ss;
    char s = table[r][c++];
    ss << s;
    string n;
    ss >> n;
    for(int i = 0; i < len-1; i++){
        if(c < columns){
            s = table[r][c++];
            n += s;
        }
    }
    return n;
}

//template <size_t rin, size_t column>
string getLeft(size_t rows, size_t columns, char **table, int r, int c, int len)
{
    char s = table[r][c--];
    stringstream ss;
    ss << s;
    string n;
    ss >> n;
    for(int i = 0; i < len-1; i++){
        if(c >= 0)
            n += table[r][c--];
    }
    return n;
}

//template <size_t rin, size_t column>
string getUp(size_t rows, size_t columns ,char **table, int r, int c, int len){
    char s = table[r--][c];
    stringstream ss;
    ss << s;
    string n;
    ss >> n;
    for(int i = 0; i < len-1; i++){
        if(r >= 0)
            n += table[r--][c];
    }
    return n;
}

//template <size_t rin, size_t column>
string getDown(size_t rows, size_t columns, char **table, int r, int c, int len)
{
    char s = table[r++][c];
    stringstream ss;
    ss << s;
    string n;
    ss >> n;
    for(int i = 0; i < len-1; i++){
        if(r < rows)
            n += table[r++][c];
    }
    return n;
}

//template <size_t rin, size_t column>
string getUpRight(size_t rows, size_t columns, char **table, int r, int c, int len)
{
    char s = table[r--][c++];
    stringstream ss;
    ss << s;
    string n;
    ss >> n;
    for(int i = 0; i < len-1; i++){
        if(r >= 0 && c < columns)
            n += table[r--][c++];
    }
    return n;
}

//template <size_t rin, size_t column>
string getUpLeft(size_t rows, size_t columns ,char **table, int r, int c, int len){
    char s = table[r--][c--];
    stringstream ss;
    ss << s;
    string n;
    ss >> n;
    for(int i = 0; i < len-1; i++){
        if(r >= 0 && c >= 0)
            n += table[r--][c--];
    }
    return n;
}

//template <size_t rin, size_t column>
string getDownRight(size_t rows, size_t columns, char **table, int r, int c, int len){
    char s = table[r++][c++];
    stringstream ss;
    ss << s;
    string n;
    ss >> n;
    for(int i = 0; i < len-1; i++){
        if(r < rows && c < columns)
            n += table[r++][c++];
    }
    return n;
}

// template <size_t rin, size_t column>
string getDownLeft(size_t rows, size_t columns, char **table, int r, int c, int len){
    char s = table[r++][c--];
    stringstream ss;
    ss << s;
    string n;
    ss >> n;
    for(int i = 0; i < len-1; i++){
        if(r < rows && c >= 0)
            n += table[r++][c--];
    }
    return n;
}


int main()
{

    size_t columns = 0;
    size_t rows = 0;
    ifstream words;
    words.open("/Users/sravanjr/Documents/College Classes/Quarter 3 Sophomore Year/Data Structures/Homework Code/CS61_HW07_02/words.txt");
    if(words.fail()){
        cout<<"Bzzzzzt!!! Failure!"<<endl;
        return 1;
    }
    unordered_set<string> dictionary;
    for(string a; getline(words, a);){
        if(a.length() >= 6)
            dictionary.insert(a);
     }
    words.close();
    ifstream puzzle;
    puzzle.open("/Users/sravanjr/Documents/College Classes/Quarter 3 Sophomore Year/Data Structures/Homework Code/CS61_HW07_02/puzzle.txt");
    determineWordSearchSize(puzzle, rows, columns);
    puzzle.close();
    ifstream puzzle2;
    puzzle2.open("/Users/sravanjr/Documents/College Classes/Quarter 3 Sophomore Year/Data Structures/Homework Code/CS61_HW07_02/puzzle.txt");
    //cout<<rows<<"x"<<columns<<endl;
    char *table[rows];
    for (size_t i=0; i < rows; i++)
        table[i] = new char [(sizeof(char) * columns)];
    char ch;
    for (size_t i=0; i<rows; i++)
    {
        for (size_t j=0; j<columns; ) {
            puzzle2>>ch;
            if ( ch != ' ')
                table[i][j++] = ch;
        }
    }
    puzzle2.close();
    multimap<string, pair<pair<int, int>, pair<int, int>>> answer;
    determineDictionary(rows, columns, table, answer, dictionary);
    for(auto& n: answer){
        cout<<n.first<<" from ("<<n.second.first.first<<", "<<n.second.first.second<<") "<<"to ("<<n.second.second.first<<", "
           <<n.second.second.second<<")"<<endl;
    }

    return 0;
}

void determineWordSearchSize(ifstream &inputFile, size_t& rows, size_t& columns){
    vector<string> determinator;
    for(string b; getline(inputFile, b); rows++){
        if (b.length() <= 0) continue;
        b.erase( remove( b.begin(), b.end(), ' ' ), b.end() );
        determinator.push_back(b);
     }
    columns = determinator[0].length();
}

void determineDictionary(size_t rows, size_t columns, char **table, multimap<string,
                         pair<pair<int, int>, pair<int, int>>>& answer, unordered_set<string> dictionary){
    for(int len = 6; len <31; len++){
        for(int r = 0; r< rows; r++){
            for(int c = 0; c < columns; c++){
                string R = getRight(rows, columns,table,r,c,len);
                string L = getLeft(rows, columns , table, r, c , len);
                string U = getUp(rows, columns, table, r, c, len);
                string D = getDown(rows, columns, table, r, c, len);
                string UR = getUpRight(rows, columns, table, r, c, len);
                string UL = getUpLeft(rows, columns, table, r, c, len);
                string DR = getDownRight(rows, columns, table, r, c, len);
                string DL = getDownLeft(rows, columns, table, r, c, len);
                if(dictionary.find(R) != dictionary.end()) {
                    answer.insert(make_pair(R, make_pair(make_pair(r,c), make_pair(r, c+R.length()-1))));
                }
                if(dictionary.find((L)) != dictionary.end()){
                    answer.insert(make_pair(L, make_pair(make_pair(r,c), make_pair(r, c-L.length()+1))));
                }
                if(dictionary.find((U)) != dictionary.end()){
                    answer.insert(make_pair(U, make_pair(make_pair(r,c), make_pair(r-U.length()+1, c))));
                }
                if(dictionary.find((D)) != dictionary.end()){
                    answer.insert(make_pair(D, make_pair(make_pair(r,c), make_pair(r+D.length()-1, c))));
                }
                if(dictionary.find((UR)) != dictionary.end()){
                    answer.insert(make_pair(UR, make_pair(make_pair(r,c), make_pair(r-UR.length()+1, c+UR.length()-1))));
                }
                if(dictionary.find((UL)) != dictionary.end()){
                    answer.insert(make_pair(UL, make_pair(make_pair(r,c), make_pair(r-UL.length()+1, c-UL.length()+1))));

                }
                if(dictionary.find((DR)) != dictionary.end()){
                    answer.insert(make_pair(DR, make_pair(make_pair(r,c), make_pair( r+DR.length()-1, c+DR.length()-1))));
                }
                if(dictionary.find((DL)) != dictionary.end()){
                    answer.insert(make_pair(DL, make_pair(make_pair(r,c), make_pair( r+DL.length()-1, c-DL.length()+1))));

                }
            }
        }
    }
}
