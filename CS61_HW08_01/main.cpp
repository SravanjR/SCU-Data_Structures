#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "graph.h"
using namespace std;
//Answers Below Program

bool canChange(std::string const& strA, std::string const& strB, char& letter, std::size_t &index)
{
     bool single_mismatch = false;
     if (strA.size() == strB.size())
     {
         typedef std::string::const_iterator ci;
         typedef std::pair<ci, ci> mismatch_result;

         ci begA(strA.begin()), endA(strA.end());

         mismatch_result result = std::mismatch(begA, endA, strB.begin());

         if (result.first != endA)    //  found a mismatch
         {
             letter = *(result.first);
             index = std::distance(begA, result.first);

             // now look for a second mismatch

             std::advance(result.first, 1);
             std::advance(result.second, 1);

             single_mismatch = (std::mismatch(result.first, endA, result.second).first == endA);
         }
    }
    return single_mismatch;
}
int main()
{
    ifstream words;
    words.open("/Users/sravanjr/Documents/College Classes/Quarter 3 Sophomore Year/Data Structures/Homework Code/CS61_HW08_01/knuth.txt");
    if(words.fail()){
        cout<<"Bzzzzzt!!! Failure!"<<endl;
        return 1;
    }
    //Start with the root word, and check for adjacent words by
    //determining if the words differ by only 1 letter, where the position of the letters is significant.
    vector<string> dictionary;
    graph doublet_answwer;
    for(string a; getline(words, a);){
         dictionary.push_back(a);
         doublet_answwer.add_vertex();
     }
    words.close();
    for(size_t j =0; j < dictionary.size(); j++){
        for(int k =0; k < dictionary.size(); k++){
            size_t index = j;
            char letter = 'a';
            if(canChange(dictionary[j], dictionary[k], letter, index)){
                doublet_answwer.add_edge(j,k);
            }
        }
    }
    string start;
    string end;
    cout<<"Input Starting Word of 5 letters in lowercase letters: ";
    cin>>start;
    cout<<"Input Ending Word of 5 letters in lowercase letters: ";
    cin>>end;
    size_t start_index = dictionary.size()+1;
    for (size_t i=0; i < dictionary.size();i++) if (dictionary[i]==start) {start_index = i; break;}
    size_t end_index = dictionary.size()+1;
    for (size_t i=0; i < dictionary.size(); i++) if (dictionary[i]==end) {end_index = i; break;}
    if ((start_index >= dictionary.size()) || end_index >= dictionary.size()) {
        cout << "Words not in dictionary: " << start << " " << end << endl;
        return 1;
    }
    vector<int> indices = doublet_answwer.shortest_path(end_index, start_index);
    for(auto& value: indices){
        cout<<dictionary[value]<<" ";
    }
    cout<<endl;
    return 0;
}

/*
 * ANSWERS:
 * black clack clank clink chink chine whine white
 *
 * tears sears stars stare stale stile smile
 *
 * small stall stalk stack slack black brack bract brant grant giant
 *
 * stone shone shine chine chins coins corns cores cones coney money
 *
 * There is no sequence from angel to devil
 *
 * amino amine amide abide abode anode anole anile anise arise prise prime prims
 * prams trams trans tuans turns burns burnt buret beret beget begot bigot bight right
 *
 * amigo amino amine amide abide abode anode anole anile anise
 * arise prise prime prims prams trams trans tuans turns burns burnt buret beret beget begot bigot bight sight sighs signs
*/
