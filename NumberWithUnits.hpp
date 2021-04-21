#include<iostream>
#include <fstream>
using namespace std;
namespace ariel {

    class NumberWithUnits {
        private:
            double n;
            string units;
        public:
            //Constructor
            NumberWithUnits(double num,string units){
                this->n = num;
                this->units = units;
            }
            //Default constructor
            NumberWithUnits(){
                this->n = 0;
                this->units = "";
            } 

            static void read_units(ifstream& units_file);  
            
            //Arithmetic Operators
            friend NumberWithUnits operator+ (NumberWithUnits& num1, NumberWithUnits& num2);
            friend NumberWithUnits& operator+= (NumberWithUnits& num1, NumberWithUnits const& num2);
            friend NumberWithUnits operator+ (NumberWithUnits& num);
            
            friend NumberWithUnits operator- (NumberWithUnits& num1, NumberWithUnits& num2);
            friend NumberWithUnits& operator-= (NumberWithUnits& num1, NumberWithUnits& num2);
            friend NumberWithUnits operator- (NumberWithUnits& num);

            NumberWithUnits& operator++ (){
                ++n;
                return *this;
            }

            NumberWithUnits operator-- (){
                --n;
                return *this;
            }

            NumberWithUnits operator++ (int){
                n++;
                return *this;
            }
            NumberWithUnits operator-- (int){
                n--;
                return *this;
            }

            friend NumberWithUnits operator*(double num, NumberWithUnits& n);
            friend NumberWithUnits operator*(NumberWithUnits& n, double num);

            //Boolean Operators
            friend bool operator> (NumberWithUnits& num1, NumberWithUnits& num2);
            friend bool operator>= (const NumberWithUnits& num1, const NumberWithUnits& num2);
            friend bool operator< (NumberWithUnits& num1, NumberWithUnits& num2);
            friend bool operator<= (const NumberWithUnits& num1, const NumberWithUnits& num2);
            friend bool operator== (const NumberWithUnits& num1, const NumberWithUnits& num2);
            friend bool operator!= (NumberWithUnits& num1, NumberWithUnits& num2);

            // I/O Operators
            friend ostream& operator<< (ostream& os,const NumberWithUnits& num);
            friend istream& operator>> (istream& input, NumberWithUnits& num); 
    };

}
