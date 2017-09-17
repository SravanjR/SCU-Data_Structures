#include<queue>
#include<ctime>
#include<chrono>
#include <iostream>
#include <random>
#include <cstdlib>
#include "teacher.h"
using namespace std;
int random_numbers(int a, int b);
double serviceTime(queue<unsigned int> &service_times, queue<unsigned int> &arrival_times,
                   double &secondsPassed, bool_source arrival, int &students);
void teacher_simulate
(double arrival_prob, int &teacher_stay, int &students,
 double &teach_time, double &wait_time, double &late_time);

int main()
{
    // Service time is determined by the data values in the queue
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
    for(int i = 0; i < 1; i++){
        teacher_simulate(1.0/random_numbers(1000, 4000), teacher_stay, students, teach_time, wait_time, late_time);
    }
    /*cout<<"The Total amount of Times that the professor stayed overtime is "<< teacher_stay<<endl;
    cout<<"The Total amount students that went to office hours is "<< students<<endl;
    cout<<"The Total amount of time that the professor helped students for was "<< teach_time<<" minutes"<<endl;
    cout<<"The Total amount of time that the students waited for was "<< wait_time<<" minutes"<<endl;
    cout<<"The Total amount of time that the professor stayed past the hour was "<< late_time<<" minutes"<<endl;
    */
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
    queue<unsigned int> arrival_times; // Waiting customer ís time stamps
    queue<unsigned int> service_times;
    bool_source arrival(arrival_prob);
    unsigned int current_minute;
    clock_t startTime = clock(); //Start timer
    double secondsPassed;
    while(!arrival_times.empty() || secondsPassed < 6.0)
    {   // Simulate the passage of one second of time.
        cout<<"hi"<<endl;
        secondsPassed = (clock() - startTime) / (double) CLOCKS_PER_SEC;
        // Check whether a new student has arrived.
        if (arrival.query( ) && secondsPassed < 6.0){
            current_minute = secondsPassed;
            arrival_times.push(current_minute);
            service_times.push(random_numbers(1, 2));
            students += 1;
        }
        // Check whether we can start helping another student.
        if(!arrival_times.empty()){
            wait_time += secondsPassed - arrival_times.front();
            teach_time += serviceTime(service_times, arrival_times,
                               secondsPassed, arrival, students);
        }
    }
    if(secondsPassed > 6.0){
        teacher_stay += 1;
        late_time += (secondsPassed - 6.0);
    }

}
double serviceTime(queue<unsigned int> &service_times, queue<unsigned int> &arrival_times,
                   double &secondsPassed, bool_source arrival, int &students)
{
     clock_t startTime = clock(); //Start timer
     double secondsPassed2 = 0.0;
     unsigned int current_minute;
     while(secondsPassed2 < service_times.front())
      {
       secondsPassed2 = (clock() - startTime)/(double) CLOCKS_PER_SEC;
       // Check whether a new student has arrived.
       if (arrival.query( ) && (secondsPassed+secondsPassed2 < 6.0)){
           current_minute = secondsPassed+secondsPassed2;
           arrival_times.push(current_minute);
           service_times.push(random_numbers(1, 10));
           students += 1;
       }
     }
     service_times.pop();
     arrival_times.pop();
     return secondsPassed2;
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
