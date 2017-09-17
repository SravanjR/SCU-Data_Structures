#ifndef TEACHER_H
#define TEACHER_H

#include <cstdlib> // Provides std::size_t

    class bool_source
    {
    public:
        // CONSTRUCTOR
        bool_source(double p = 0.5);
        // CONSTANT function
        bool query( ) const;
    private:
        double probability; // Probability of query( ) returning true
    };

    class averager
    {
    public:
        // CONSTRUCTOR
        averager( );
        // MODIFICATION function
        void next_number(double value);
        // CONSTANT functions
        std::size_t how_many_numbers( ) const { return count; }
        double average( ) const;
        double getSum() const {return sum;}
    private:
        std::size_t count; // How many numbers have been given to the averager
        double sum;   // Sum of all the numbers given to the averager
    };

    class teacher
    {
    public:
        // CONSTRUCTOR
        teacher(unsigned int s);
        // MODIFICATION functions
        void one_second( );
        void start_helping( );
        void set_seconds_for_student(unsigned int s){seconds_for_student = s;}
        // CONSTANT function
        bool is_busy( ) const { return (student_time_left > 0); }
    private:
        unsigned int seconds_for_student; // Seconds for a single student
        unsigned int student_time_left;   // Seconds until washer no longer busy
    };

#endif // TEACHER_H
