#include<queue>
#include <iostream>
#include <random>
#include "teacher.h"
struct Student;
using namespace std;
int random_numbers(int a, int b);
bool operator<(const Student& lhs, const Student& rhs);
void teacher_simulate
(double arrival_prob, int &teacher_stay, int &students,
 double &teach_time, double &wait_time, double &late_time);

struct Student{
    unsigned int help_time;
    unsigned int arrival_time;
    unsigned int urgency;
};


int main()
{
    // Service time is determined by the data values in the queue
    // Students arrive on average once every 20 seconds until 60 seconds have passed
    // Total simulation time is 600 seconds
    //add references variables to the function and corresponding main function.
    // add variables that correspond to said reference varianbles that will recieve the data in the for loop,
    //number of times teacher stayed after 1 hour, number of students who went to office hours, total time spent with professor,
    //total time waiting for professor
    //in the function, insert the correct values for each variable.
    //compute the averages and answer the questions.
    int teacher_stay = 0;
    int students = 0;
    double teach_time = 0.0;
    double wait_time = 0.0;
    double late_time = 0.0;
    for(int i = 0; i < 100; i++){
        teacher_simulate(1.0/random_numbers(2, 20), teacher_stay, students, teach_time, wait_time, late_time);
    }
    cout<<"The Total amount of Times that the professor stayed overtime is "<< teacher_stay<<endl;
    cout<<"The Total amount students that went to office hours is "<< students<<endl;
    cout<<"The Total amount of time that the professor helped students for was "<< teach_time<<" minutes"<<endl;
    cout<<"The Total amount of time that the students waited for was "<< wait_time<<" minutes"<<endl;
    cout<<"The Total amount of time that the professor stayed past the hour was "<< late_time<<" minutes"<<endl;
    cout<<"The average time a student spends waiting during an office hour visit is "<<
          wait_time/students<< " minutes"<< endl;
    cout<<"The average time a student spends with the professor during an office hour visit is "<<
          teach_time/students<< " minutes"<< endl;
    cout<<"The average time a Professor spends at an office hour beyond the 1 hour he intended to is "<<
          late_time/100<< " minutes"<< endl;
}

void teacher_simulate
(double arrival_prob, int &teacher_stay, int &students,
 double &teach_time, double &wait_time, double &late_time)

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
    for (current_minute = 1; !Student_avail.empty() || current_minute <= 60; ++current_minute)
    {   // Simulate the passage of one second of time.

        // Check whether a new student has arrived.
        if (arrival.query( ) && current_minute <= 60){
            Student Helpee;
            Helpee.arrival_time = current_minute;
            Helpee.help_time = random_numbers(1, 10);
            Helpee.urgency = (random_numbers(1, 5));
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
