#include "NumberWithUnits.hpp"
#include<iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <map>
using namespace std;
using namespace ariel;

map<string, map<string,double>> unit;
const double eps = 0.0001;

namespace ariel{

    const array<string,11> allUnits {"km","m", "cm","kg", "g", "ton","hour","min", "sec","USD", "ILS"};
    //Checks the valid of the unit
    bool checkValidUnit(string const& unit){
        for(uint i=0 ; i < sizeof(allUnits)/sizeof(allUnits[0]) ; i++){
            if(unit == allUnits.at(i)) {return true; }
        }
        return false;
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

            //Check if one of the units is not valid
            if(!checkValidUnit(fromUnit) || !checkValidUnit(toUnit)){
                throw invalid_argument("Invalid input");
            }

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

        // //Print the hashmap
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
    NumberWithUnits operator+ (NumberWithUnits& num1, NumberWithUnits& num2){
        double convertedNum2 = convert(num2.units ,num1.units, num2.n);
        return NumberWithUnits(num1.n + convertedNum2, num1.units);
    }

    NumberWithUnits& operator+= (NumberWithUnits& num1, NumberWithUnits const& num2){
        double convertedNum2 = convert(num2.units, num1.units, num2.n);
        num1.n = num1.n + convertedNum2;
        return num1;
    }

    NumberWithUnits operator+ (NumberWithUnits& num){
        return num;
    }

    NumberWithUnits operator- (NumberWithUnits& num1, NumberWithUnits& num2){
        double convertedNum2 = convert(num2.units, num1.units, num2.n);
        return NumberWithUnits(num1.n - convertedNum2, num1.units);
    }

    NumberWithUnits& operator-= (NumberWithUnits& num1, NumberWithUnits& num2){
        double convertedNum2 = convert(num2.units, num1.units, num2.n);
        num1.n = num1.n - convertedNum2;
        return num1;
    }

    NumberWithUnits operator- (NumberWithUnits& num){
        return NumberWithUnits(-num.n, num.units);
    }

    NumberWithUnits operator*(double num, NumberWithUnits& n){
        return NumberWithUnits(num * n.n, n.units);
    }

    NumberWithUnits operator*(NumberWithUnits& n, double num){
        return NumberWithUnits(num * n.n,n.units);
    }

    //Boolean Operators

    bool operator> (NumberWithUnits& num1, NumberWithUnits& num2){
        double convertedNum2 = convert(num2.units, num1.units, num2.n);
        return (num1.n > convertedNum2);
    }

    bool operator>= (const NumberWithUnits& num1, const NumberWithUnits& num2){
        double convertedNum2 = convert(num2.units, num1.units, num2.n);
        return (num1.n >= convertedNum2);
    }

    bool operator< (NumberWithUnits& num1, NumberWithUnits& num2){
        double convertedNum2 = convert(num2.units, num1.units, num2.n);
        return (num1.n < convertedNum2);
    }

    bool operator<= (const NumberWithUnits& num1,const NumberWithUnits& num2){
        double convertedNum2 = convert(num2.units, num1.units, num2.n);
        return (num1.n <= convertedNum2);
    }

    bool operator== (const NumberWithUnits& num1, const NumberWithUnits& num2){
        double convertedNum2 = convert(num2.units, num1.units, num2.n);
        return (abs(num1.n - convertedNum2) < eps);
    }

    bool operator!= (NumberWithUnits& num1, NumberWithUnits& num2){
        double convertedNum2 = convert(num2.units, num1.units, num2.n);
        return (num1.n != convertedNum2);
    }

    //I/O Operators
        ostream& operator<< (ostream& os,const NumberWithUnits& num){
        os << num.n << '[' << num.units << ']';
        return os;
    }

    istream& operator>> (istream& input, NumberWithUnits& num){
        string bracket;
        input >> num.n >> bracket >> num.units;
        if(checkValidUnit(num.units)) {return input; }

        throw invalid_argument("Invalid input");
    }

}