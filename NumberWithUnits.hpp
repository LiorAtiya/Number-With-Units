#include<iostream>
#include <fstream>
using namespace std;
namespace ariel {

    class NumberWithUnits {
        private:
            double n;
            string units;
        public:
            NumberWithUnits(double num,string units){
                this->n = num;
                this->units = units;
            }

            NumberWithUnits(){
                this->n = 0;
                this->units = "";
            } 

            static void read_units(ifstream& units_file);  


            friend NumberWithUnits& operator+ (NumberWithUnits& num1, NumberWithUnits& num2);
            friend NumberWithUnits& operator+= (NumberWithUnits& num1, NumberWithUnits num2);
            friend NumberWithUnits& operator+ (NumberWithUnits& num);
            
            friend NumberWithUnits& operator- (NumberWithUnits& num1, NumberWithUnits& num2);
            friend NumberWithUnits& operator-= (NumberWithUnits& num1, NumberWithUnits& num2);
            friend NumberWithUnits& operator- (NumberWithUnits& num);

            friend bool operator> (NumberWithUnits& num1, NumberWithUnits& num2);
            friend bool operator>= (const NumberWithUnits& num1, const NumberWithUnits& num2);
            friend bool operator< (NumberWithUnits& num1, NumberWithUnits& num2);
            friend bool operator<= (const NumberWithUnits& num1, const NumberWithUnits& num2);
            friend bool operator== (const NumberWithUnits& num1, const NumberWithUnits& num2);
            friend bool operator!= (NumberWithUnits& num1, NumberWithUnits& num2);

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


            friend NumberWithUnits& operator*(double num, NumberWithUnits& n);
            friend NumberWithUnits& operator*(NumberWithUnits& n, double num);

            friend ostream& operator<< (ostream& os, NumberWithUnits& num);
            friend istream& operator>> (istream& input, NumberWithUnits& c); 
    };

}
