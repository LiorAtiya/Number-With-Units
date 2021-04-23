#include<iostream>
#include <fstream>
#include <map>
using namespace std;
namespace ariel {

    class NumberWithUnits {
        private:
            double n;
            string units;
        public:
            //Constructor
            NumberWithUnits(const double num,const string& units);
            // //Default constructor
            // NumberWithUnits(){
            //     this->n = 0;
            //     this->units = "";
            // } 

            static void read_units(ifstream& units_file);  
            
            //Arithmetic Operators
            NumberWithUnits operator+ (NumberWithUnits const& other) const;
            NumberWithUnits& operator+= (NumberWithUnits const& other);
            NumberWithUnits operator+ ();
                    
            NumberWithUnits operator- (NumberWithUnits const& other) const;
            NumberWithUnits& operator-= (NumberWithUnits const& other);
            NumberWithUnits operator- () const;
            //prefix
            NumberWithUnits& operator++ ();
            NumberWithUnits& operator-- ();

            //postfix
            NumberWithUnits operator++ (int dummy_flag_for_postfix){
                NumberWithUnits copy = *this;
                this->n++;
                return copy;
            }
            NumberWithUnits operator-- (int dummy_flag_for_postfix){
                NumberWithUnits copy = *this;
                this->n--;
                return copy;
            }

            NumberWithUnits operator*(double num);
            friend NumberWithUnits operator*(const double num, NumberWithUnits const& n);

            //Boolean Operators
            bool operator> (NumberWithUnits const& other) const;
            bool operator>= (NumberWithUnits const& other) const;
            bool operator< (NumberWithUnits const& other) const;
            bool operator<= (NumberWithUnits const& other) const;
            bool operator== (NumberWithUnits const& other) const;
            bool operator!= (NumberWithUnits const& other) const;

            // I/O Operators
            friend ostream& operator<< (ostream& os,const NumberWithUnits& num);
            friend istream& operator>> (istream& input, NumberWithUnits& num); 
    };

}
