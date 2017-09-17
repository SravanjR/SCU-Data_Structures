#include <cassert>    // Provides assert
#include <cstdlib>    // Provides rand, RAND_MAX, size_t
#include<iostream>
#include "teacher.h"  // Provides bool_source, averager, washer definitions
using namespace std;

    bool_source::bool_source(double p)
    // Library facilities used: cassert
    {
        assert(p >= 0);
        assert(p <= 1);
        probability = p;
    }

    bool bool_source::query( ) const
    // Library facilities used: cstdlib
    {
        return (rand( ) < probability * RAND_MAX);
    }

    averager::averager( )
    {
        count = 0;
        sum = 0;
    }

    void averager::next_number(double value)
    {
        sum += value;
        ++count;
    }

    double averager::average( ) const
    // Library facilities used: cassert
    {
        assert(how_many_numbers( ) > 0);
        return sum/count;
    }

    teacher::teacher(unsigned int s)
    {
        seconds_for_student = s;
        student_time_left = 0;
    }


    void teacher::one_second( )
    {
        if (is_busy( ))
            --student_time_left;
    }


    void teacher::start_helping( )
    // Library facilities used: cassert
    {
        assert(!is_busy( ));
        student_time_left = seconds_for_student;
    }
