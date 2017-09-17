#include "student.h"

Student::Student()
{
    arrival_time = 0;
    urgency = 1;
    help_time = 0;
}

Student::Student(const Student &obj){
    arrival_time = obj.get_arrival_time();
    urgency = obj.get_urgency();
    help_time = obj.get_help_time();
}
