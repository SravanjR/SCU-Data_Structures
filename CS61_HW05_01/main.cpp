#include<queue>
#include <string>
#include <iostream>
#include <random>
#include <utility>
#include <map>
#include <fstream>
#include <vector>
#include "teacher.h"
struct Student;
using namespace std;
int random_numbers(int a, int b);
bool operator<(const Student& lhs, const Student& rhs);
void teacher_simulate
(double arrival_prob, int &teacher_stay, int &students,
 double &teach_time, double &wait_time, double &late_time,
 vector<string> &Info, map<string, vector<pair<int, string>>> &person_topic, int hournumber);
bool is_in_array(int z, vector<int> m);
struct Student{
    unsigned int help_time;
    unsigned int arrival_time;
    unsigned int urgency;
    string topic;
    string name;
};


int main()
{
    ifstream scores;
    scores.open("/Users/sravanjr/Documents/College Classes/Quarter 3 Sophomore Year/Data Structures/Homework Code/CS61_HW05_01/CS61_HW05_3a.txt");
        if(scores.fail()){
            cout<<"Bzzzzzt!!! Failure!"<<endl;
            return 1;
        }
    vector<string> Information;
    for(string a; getline(scores, a);){
            Information.push_back(a);
     }
    int teacher_stay = 0;
    int students = 0;
    double teach_time = 0.0;
    double wait_time = 0.0;
    double late_time = 0.0;
    map<string,vector<pair<int, string>>> student_topic;
    for(int i = 0; i < 100; i++){
        int x = i;
        teacher_simulate(1.0/random_numbers(2, 20), teacher_stay, students, teach_time, wait_time,
                         late_time, Information, student_topic, x+1);
    }
    scores.close();
    ofstream studies;
    studies.open("/Users/sravanjr/Documents/College Classes/Quarter 3 Sophomore Year/Data Structures/Homework Code/CS61_HW05_01/CS61_HW05_3b.txt");
    if(studies.fail()){
        cout<<"Bzzzzzt!!! Failure!"<<endl;
        return 1;
    }
    for(auto& n: student_topic){
        studies<<n.first<<endl;
        studies<<"Office Hours Attended: "<< n.second.size();
        studies<<endl;;
        for(auto& m : n.second){
            studies<<m.first<< " "<<m.second;
            studies<<endl;
        }
        studies<<endl;
        studies<<endl;
    }
    studies.close();
    return 0;
}

void teacher_simulate
(double arrival_prob, int &teacher_stay, int &students,
 double &teach_time, double &wait_time, double &late_time, vector<string> &Info, map<string,
 vector<pair<int, string>>> &person_topic, int hournumber)

{
    priority_queue<Student> Student_avail; // Waiting customer ís time stamps
    //create the student class with values from the current structure
    //Overload the "<" operator in regards to student to have it ordered by Urgency
    unsigned int next;                 // A value taken from the queue
    bool_source arrival(arrival_prob);
    teacher machine(0);
    averager wait_times;
    averager overtime;
    averager teaching_time;
    unsigned int current_minute;
    vector<int> attended;
    int f = 0;
    for (current_minute = 1; !Student_avail.empty() || current_minute <= 60; ++current_minute)
    {   // Simulate the passage of one second of time.

        // Check whether a new student has arrived.
        if (arrival.query( ) && current_minute <= 60 && f < 20){
            Student Helpee;
            pair<int, string> hourAndTopic;
            int z = Info.size()-1;
            Helpee.topic = Info[random_numbers(0, z)];
            hourAndTopic.first = hournumber;
            hourAndTopic.second = Helpee.topic;
            int n = random_numbers(1, 20);
            while(is_in_array(n, attended)){
                n = random_numbers(1, 20);
            }
            attended.push_back(n);
            f++;
            string x = to_string(n);
            Helpee.name = "Student" + x;
            Helpee.arrival_time = current_minute;
            Helpee.help_time = random_numbers(1, 10);
            Helpee.urgency = (random_numbers(1, 5));
            person_topic[Helpee.name].push_back(hourAndTopic);
            Student_avail.push(Helpee);
        }

        // Check whether we can start helping another student.
        if ((!machine.is_busy( ))  &&  (!Student_avail.empty( )))
        {
            Student Helper = Student_avail.top();
            next = Helper.arrival_time;
            machine.set_seconds_for_student(Helper.help_time);
            Student_avail.pop();
            wait_times.next_number(current_minute - next);
            machine.start_helping( );
        }
        // Tell the teacher to simulate the passage of one minute.

        if(machine.is_busy()){
            teaching_time.next_number(1.0);
        }

        if(machine.is_busy() && current_minute > 60){
            overtime.next_number(1.0);
        }
        machine.one_second( );
    }
    current_minute -= 1;
    if(current_minute > 60){
        teacher_stay += 1;
    }
    current_minute += 1;
    teach_time += teaching_time.getSum();
    wait_time += wait_times.getSum();
    late_time += overtime.getSum();
    students += wait_times.how_many_numbers();
}

int random_numbers(int a, int b){
    // Random seed
    random_device rd;

    // Initialize pseudo-random number generator
    mt19937 gen(rd());

    // Generate pseudo-random numbers
    // uniformly distributed in range (a, b)
    uniform_int_distribution<> dis(a, b);

    int randomX = dis(gen);
    return randomX;
}

bool operator<(const Student& lhs, const Student& rhs)
{
  return lhs.urgency < rhs.urgency;
}

bool is_in_array(int z, vector<int> m){
      bool exists = false;
      for(int i = 0; i< m.size(); i++){
          if(z == m[i])
              return true;
      }
      return exists;
}
