#ifndef STUDENT_H
#define STUDENT_H


class Student
{
public:
    Student();
    Student( const Student &obj);
    unsigned int get_help_time() const{return help_time;}
    unsigned int get_arrival_time() const {return arrival_time;}
    unsigned int get_urgency() const{return urgency;}
    void set_help_time(unsigned int i){help_time = i;}
    void set_arrival_time(unsigned int i){arrival_time = i;}
    void set_urgency(int i){urgency = i;}
    bool operator()(const Student& t1, const Student& t2)
        {
            if (t2.urgency < t1.urgency) return true;
            if (t2.urgency == t1.urgency && t2.arrival_time < t1.arrival_time) return true;
            if (t2.urgency == t1.urgency && t2.arrival_time == t1.arrival_time && t2.help_time < t1.help_time) return true;
            return false;
        }
    unsigned int help_time;
    unsigned int urgency;
    unsigned int arrival_time;
};

class CompareStudent {
public:
    CompareStudent();
    bool operator()(const Student& t1, const Student& t2)
        {
            if (t2.urgency < t1.urgency) return true;
            if (t2.urgency == t1.urgency && t2.arrival_time < t1.arrival_time) return true;
            if (t2.urgency == t1.urgency && t2.arrival_time == t1.arrival_time && t2.help_time < t1.help_time) return true;
            return false;
        }
};

#endif // STUDENT_H

