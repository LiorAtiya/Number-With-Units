#include "NumberWithUnits.hpp"
#include<iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
using namespace std;

namespace ariel{

    string allUnits[] = {"km","m", "cm", "kg", "g", "ton", "hour","min", "sec", "USD", "ILS"};
    bool checkValidUnit(string unit){
        for(int i=0 ; i < sizeof(allUnits)/sizeof(allUnits[0]) ; i++){
            if(unit == allUnits[i]) return true;
        }
        return false;
    }
    unordered_map<string, unordered_map<string,double>> unit;

    void NumberWithUnits::read_units(ifstream& units_file){
        string line;
        while (getline (units_file, line)) {
            istringstream iss(line);
            double fromNum, toNum;
            string fromUnit, toUnit, eq;

            iss >> fromNum >> fromUnit >> eq >> toNum >> toUnit;
            // cout << fromNum << " " << fromUnit << " " << eq << " " << toNum << " " << toUnit <<'\n';
            // cout << fromUnit << '\n';
            if(!checkValidUnit(fromUnit) || !checkValidUnit(toUnit)){
                throw invalid_argument("Invalid input");
            }

            unit[fromUnit][toUnit] = toNum;

//         //     int i=1;
//         //     string from = "";
//         //     while(i != '='){
//         //         if(line[i] != ' ') from += line[i];
//         //     }
//         //     int num = 0;
//         //     while(i < line.size()){

//         //     }
//         //     cout << line;
        }

        //Print the hashmap
        for (auto const &pair: unit) {
            for(auto const &pair2: unit[pair.first]){
                std::cout << "{" << pair2.first << ":" << pair2.second << "},";
            }
            std::cout << '\n';
        }
    }

}


ariel::NumberWithUnits output;

string operator+ (ariel::NumberWithUnits& num1, ariel::NumberWithUnits& num2){
    return "";
}

ariel::NumberWithUnits& operator*(double num, ariel::NumberWithUnits& n){
    output.setNumber(n.getNumber()*num);
    output.setUnits(n.getUnits()+"");
    return output;
}

string operator- (ariel::NumberWithUnits& num){
    return "-" + to_string(num.getNumber()) + '[' + num.getUnits() + ']';
}

ostream& operator<< (ostream& os, ariel::NumberWithUnits& num){
    os << num.getNumber() << '[' << num.getUnits() << ']';
    return os;
}