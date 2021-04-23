#include "NumberWithUnits.hpp"
#include<iostream>
#include <fstream>
#include <sstream>
// #include <array>
#include <map>
using namespace std;
using namespace ariel;

map<string, map<string,double>> unit;
const double eps = 0.0001;

namespace ariel{
    //Checks the valid of the unit
    bool checkValidUnit(string const& u){
        return (unit.count(u) != 0U);
    }
    //Constructor
    NumberWithUnits::NumberWithUnits(const double num,const string& units){
        if((unit.count(units) != 0U)){
            this->n = num;
            this->units = units;
        }else{
            throw invalid_argument("Invalid input");
        }
    }

    //Reads the units from the text file
    void NumberWithUnits::read_units(ifstream& units_file){   
        
        string line;

        while (getline (units_file, line)) {
            //Read until the char of '='
            istringstream iss1(line.substr(1,line.find('=')-1));
            //Read from char '=' until the end
            istringstream iss2(line.substr(line.find('=')+1,line.length()-line.find('=')+1));

            double toNum = 0;
            string fromUnit;
            string toUnit;

            iss1 >> fromUnit;
            iss2 >> toNum >> toUnit;

            //Puts the all conversion units in the map
            unit[fromUnit][toUnit] = toNum;
            unit[toUnit][fromUnit] = (1/toNum);

            for(const auto& pair: unit[toUnit]) {
                unit[fromUnit][pair.first] = unit[fromUnit][toUnit] * pair.second;
                unit[pair.first][fromUnit] = 1 / (unit[fromUnit][toUnit] * pair.second);
            }
            for(const auto& pair: unit[fromUnit]) {
                unit[toUnit][pair.first] = unit[toUnit][fromUnit] * pair.second;
                unit[pair.first][toUnit] = 1 / (unit[toUnit][fromUnit] * pair.second);
            }
        }      

        //Print the hashmap
        // for (auto const &pair: unit) {
        //     cout << pair.first << ": ";
        //     for(auto const &pair2: unit[pair.first]){
        //         std::cout << "{" << pair2.first << ":" << pair2.second << "},";
        //     }
        //     std::cout << '\n';
        // }
    }

    //Converter from one unit to another unit
    double convert(string const& from, string const& to, double num){

        //Same unit
        if(from == to) {return num; }
        //Checks if it can be converted
        if(unit[from].count(to) != 0U){
            return num * unit[from][to];
        }
        //else
        throw invalid_argument("Units do not match - ["+from+"] cannot be converted to ["+to+"]");
    }

    //Arithmetic Operators
    NumberWithUnits NumberWithUnits::operator+ (NumberWithUnits const& other) const{
        double convertedNum2 = convert(other.units ,this->units, other.n);
        return NumberWithUnits(this->n + convertedNum2, this->units);
    }

    NumberWithUnits& NumberWithUnits::operator+= (NumberWithUnits const& other){
        double convertedNum2 = convert(other.units, this->units, other.n);
        (*this).n = (*this).n + convertedNum2;
        return (*this);
    }

    NumberWithUnits NumberWithUnits::operator+ (){ return (*this); }

    NumberWithUnits NumberWithUnits::operator- (NumberWithUnits const& other) const{
        double convertedNum2 = convert(other.units, this->units, other.n);
        return NumberWithUnits(this->n - convertedNum2, this->units);
    }

    NumberWithUnits& NumberWithUnits::operator-= (NumberWithUnits const& other){
        double convertedNum2 = convert(other.units, this->units, other.n);
        (*this).n = (*this).n - convertedNum2;
        return (*this);
    }

    NumberWithUnits NumberWithUnits::operator- () const{
        return NumberWithUnits(-this->n, this->units);
    }

    NumberWithUnits& NumberWithUnits::operator++ (){
        this->n++;
        return *this;
    }
    

    NumberWithUnits& NumberWithUnits::operator-- (){
        this->n--;
        return *this;
    }

    NumberWithUnits operator*(const double num, NumberWithUnits const& n){
        return NumberWithUnits(num * n.n, n.units);
    }

    NumberWithUnits NumberWithUnits::operator*(double num){
        return NumberWithUnits(num * this->n,this->units);
    }

    //Boolean Operators

    bool NumberWithUnits::operator> (NumberWithUnits const& other) const{
        double convertedNum2 = convert(other.units, this->units, other.n);
        return (this->n > convertedNum2);
    }

    bool NumberWithUnits::operator>= (NumberWithUnits const& other) const{
        double convertedNum2 = convert(other.units, this->units, other.n);
        return (this->n >= convertedNum2);
    }

    bool NumberWithUnits::operator< (NumberWithUnits const& other) const{
        double convertedNum2 = convert(other.units, this->units, other.n);
        return (this->n < convertedNum2);
    }

    bool NumberWithUnits::operator<= (NumberWithUnits const& other) const{
        double convertedNum2 = convert(other.units, this->units, other.n);
        return (this->n <= convertedNum2);
    }

    bool NumberWithUnits::operator== (NumberWithUnits const& other) const{
        double convertedNum2 = convert(other.units, this->units, other.n);
        return (abs(this->n - convertedNum2) < eps);
    }

    bool NumberWithUnits::operator!= (NumberWithUnits const& other) const{
        double convertedNum2 = convert(other.units, this->units, other.n);
        return (this->n != convertedNum2);
    }

    //I/O Operators
        ostream& operator<< (ostream& os,const NumberWithUnits& num){
        if(!checkValidUnit(num.units)) {
            throw invalid_argument("Invalid input");
        }
        os << num.n << '[' << num.units << ']';
        return os;
    }

    istream& operator>> (istream& input, NumberWithUnits& num){
        double number = 0;
        string type;
        string end;
        while(input >> number){
            num.n = number;
            while(input >> type){
                if(type == "[]"){
                    throw invalid_argument("Invalid input");
                }
                //Like this: [unit
                if(type.find('[') < type.length() && type.find(']') > type.length()){
                    type = type.substr(1,type.length()-1);
                    if(type.length() > 0){
                        input >> end;
                    }
                //Like this: unit]
                }else if(type.find('[') > type.length() && type.find(']') < type.length()){
                    type = type.substr(0,type.length()-2);
                //Like this: [unit]
                }else if(type.find('[') < type.length() && type.find(']') < type.length()){
                    type = type.substr(1,type.length()-2);
                }else if(type.find('[') > type.length() && type.find(']') > type.length()){
                    input >> end;
                }
                if(checkValidUnit(type)){
                    num.units = type;
                    return input;
                }

                if(type.length() != 0){
                    throw invalid_argument("Invalid input");
                }
            }
        }
        return input;
    }

}