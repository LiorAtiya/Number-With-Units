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

            int getNumber(){ return this->n; }
            string getUnits(){ return this->units; }
            void setNumber(double num){ this->n = num; }
            void setUnits(string units){ this->units = units; }   

            static void read_units(ifstream& units_file);  
    };

}

string operator+ (ariel::NumberWithUnits& num1, ariel::NumberWithUnits& num2);
// string operator+= (int n, string s);
// string operator+ (int n, string s);
// string operator- (int n, string s);
string operator- (ariel::NumberWithUnits& num);
ariel::NumberWithUnits& operator*(double num, ariel::NumberWithUnits& n);
// string operator-= (int n, string s);
// string operator< (int n, string s);
// string operator<= (int n, string s);
// string operator>= (int n, string s);
// string operator== (int n, string s);
// string operator!= (int n, string s);
// string operator-- (NumberWithUnits n);
// ariel::NumberWithUnits operator*(double num1 , ariel::NumberWithUnits& num2);

ostream& operator<< (ostream& os, ariel::NumberWithUnits& num);