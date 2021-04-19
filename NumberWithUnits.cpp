#include "NumberWithUnits.hpp"
#include<iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;
using namespace ariel;

unordered_map<string, unordered_map<string,double>> unit;

typedef double(*DoFunc)(double);
typedef map<string, DoFunc> mapUnitConvert;
mapUnitConvert callConvertMap; 

namespace ariel{

    double km_m(double num){ return num * unit["km"]["m"]; }
    double km_cm(double num){ return num * unit["km"]["m"] * unit["m"]["cm"]; }
    double m_cm(double num){ return num * unit["m"]["cm"]; }
    double m_km(double num){ return num / unit["km"]["m"]; }
    double cm_km(double num){ return (num / unit["m"]["cm"]) / unit["km"]["m"]; }
    double cm_m(double num){ return num / unit["m"]["cm"]; }
    double kg_g(double num){ return num * unit["g"]["kg"]; }
    double kg_ton(double num){ return num / unit["kg"]["ton"]; }
    double g_kg(double num){ return num / unit["g"]["kg"]; }
    double g_ton(double num){ return (num / unit["g"]["kg"]) / unit["kg"]["ton"]; }
    double ton_kg(double num){ return num * unit["ton"]["kg"]; }
    double ton_g(double num){ return num * unit["g"]["kg"] * unit["kg"]["ton"]; }

    string allUnits[4][3] = {{"km","m", "cm"}, {"kg", "g", "ton"}, {"hour","min", "sec"}, {"USD", "ILS", "ILS"}};
    bool checkValidUnit(string unit){
        for(int i=0 ; i < 4 ; i++){
            for(int j = 0 ; j < 3 ; j++){
                if(unit == allUnits[i][j]) return true;
            }
        }
        return false;
    }

    void NumberWithUnits::read_units(ifstream& units_file){   
        
        string line;
        
        while (getline (units_file, line)) {
            
            istringstream iss1(line.substr(1,line.find('=')-1));
            istringstream iss2(line.substr(line.find('=')+1,line.length()-line.find('=')+1));
            double toNum;
            string fromUnit, toUnit;

            iss1 >> fromUnit;
            iss2 >> toNum >> toUnit;

            if(!checkValidUnit(fromUnit) || !checkValidUnit(toUnit)){
                throw invalid_argument("Invalid input");
            }


            unit[fromUnit][toUnit] = toNum;
        }

        callConvertMap["km_m"] = km_m;
        callConvertMap["km_cm"] = km_cm;
        callConvertMap["m_cm"] = m_cm;
        callConvertMap["m_km"] = m_km;
        callConvertMap["cm_km"] = cm_km;
        callConvertMap["cm_m"] = cm_m;
        callConvertMap["kg_g"] = kg_g;
        callConvertMap["kg_ton"] = kg_ton;
        callConvertMap["g_kg"] = g_kg;
        callConvertMap["g_ton"] = g_ton;
        callConvertMap["ton_kg"] = ton_kg;
        callConvertMap["ton_g"] = ton_g;

        // //Print the hashmap
        // for (auto const &pair: unit) {
        //     cout << pair.first << ": ";
        //     for(auto const &pair2: unit[pair.first]){
        //         std::cout << "{" << pair2.first << ":" << pair2.second << "},";
        //     }
        //     std::cout << '\n';
        // }
    }

    double convert(string from, string to, double num){

        if(from == to) return num;

        int count = 0;
        for(int i=0 ; i < 4 ; i++){
            for(int j=0 ; j < 3 ; j++){
                if((from == allUnits[i][j] || to == allUnits[i][j]) 
                    && (unit.count(from) && unit.count(to))) count++;
            }
            if(count == 2) break;
            count = 0;
        }
        if(count == 2){
            DoFunc f = callConvertMap[from+"_"+to];
            return (*f)(num);
        }else{
            throw invalid_argument("Units do not match - ["+from+"] cannot be converted to ["+to+"]");
        }

        // if(toUnit == "km_m") return num * unit["km"]["m"]; 
        // else if(toUnit == "km_cm") return num * unit["km"]["m"] * unit["m"]["cm"];
        // else if(toUnit == "m_cm") return num * unit["m"]["cm"];
        // else if(toUnit == "m_km") return num / unit["km"]["m"];
        // else if(toUnit == "cm_km") return (num / unit["m"]["cm"]) / unit["km"]["m"];
        // else if(toUnit == "cm_m") return num / unit["m"]["cm"];
        // else if(toUnit == "kg_g") return num * unit["g"]["kg"];
        // else if(toUnit == "kg_ton") return num / unit["kg"]["ton"];
        // else if(toUnit == "g_kg") return num / unit["g"]["kg"];
        // else if(toUnit == "g_ton") return (num / unit["g"]["kg"]) / unit["kg"]["ton"];
        // else if(toUnit == "ton_kg") { return num * unit["ton"]["kg"];}
        // else if(toUnit == "ton_g") return num * unit["g"]["kg"] * unit["kg"]["ton"];

        return -1;
    }

    NumberWithUnits output;

    NumberWithUnits& operator+ (ariel::NumberWithUnits& num1, ariel::NumberWithUnits& num2){
        double convertedNum2 = convert(num2.units ,num1.units, num2.n);
            output.n = num1.n + convertedNum2;
            output.units = num1.units;
        return output;
    }

    NumberWithUnits& operator+= (NumberWithUnits& num1, NumberWithUnits num2){
        double convertedNum2 = convert(num2.units, num1.units, num2.n);
        if(convertedNum2 != -1){
            num1.n = num1.n + convertedNum2;
        }else{
            throw invalid_argument("Units do not match - ["+num2.units+"] cannot be converted to ["+num1.units+"]");
        }
        return num1;
    }

    NumberWithUnits& operator+ (NumberWithUnits& num){
        output.n = num.n;
        output.units = num.units;
        return output;
    }

    NumberWithUnits& operator- (NumberWithUnits& num1, NumberWithUnits& num2){
        double convertedNum2 = convert(num2.units, num1.units, num2.n);
        if(convertedNum2 != -1){
            output.n = num1.n - convertedNum2;
            output.units = num1.units;
        }else{
            throw invalid_argument("Units do not match - ["+num2.units+"] cannot be converted to ["+num1.units+"]");
        }
        return output;
    }

    NumberWithUnits& operator-= (NumberWithUnits& num1, NumberWithUnits& num2){
        double convertedNum2 = convert(num2.units, num1.units, num2.n);
        if(convertedNum2 != -1){
            num1.n = num1.n - convertedNum2;
        }else{
            throw invalid_argument("Units do not match - ["+num2.units+"] cannot be converted to ["+num1.units+"]");
        }
        return num1;
    }

    NumberWithUnits& operator- (NumberWithUnits& num){
        output.n = -num.n;
        output.units = num.units;
        return output;
    }

    bool operator> (NumberWithUnits& num1, NumberWithUnits& num2){
        double convertedNum2 = convert(num2.units, num1.units, num2.n);
        if(convertedNum2 != -1){
            if(num1.n > convertedNum2) return true;
        }else{
            throw invalid_argument("Units do not match - ["+num2.units+"] cannot be converted to ["+num1.units+"]");
        }
        return false;
    }

    bool operator>= (NumberWithUnits& num1, NumberWithUnits& num2){
        double convertedNum2 = convert(num2.units, num1.units, num2.n);
        if(convertedNum2 != -1){
            if(num1.n >= convertedNum2) return true;
        }else{
            throw invalid_argument("Units do not match - ["+num2.units+"] cannot be converted to ["+num1.units+"]");
        }
        return false;
    }

    bool operator< (NumberWithUnits& num1, NumberWithUnits& num2){
        double convertedNum2 = convert(num2.units, num1.units, num2.n);
        if(convertedNum2 != -1){
            if(num1.n < convertedNum2) return true;
        }else{
            throw invalid_argument("Units do not match - ["+num2.units+"] cannot be converted to ["+num1.units+"]");
        }
        return false;
    }

    bool operator<= (NumberWithUnits& num1, NumberWithUnits& num2){
        double convertedNum2 = convert(num2.units, num1.units, num2.n);
        if(convertedNum2 != -1){
            if(num1.n <= convertedNum2) return true;
        }else{
            throw invalid_argument("Units do not match - ["+num2.units+"] cannot be converted to ["+num1.units+"]");
        }
        return false;
    }

    bool operator== (NumberWithUnits& num1, NumberWithUnits num2){
        double convertedNum2 = convert(num2.units, num1.units, num2.n);
        if(convertedNum2 != -1){
            if(num1.n == convertedNum2) return true;
        }else{
            throw invalid_argument("Units do not match - ["+num2.units+"] cannot be converted to ["+num1.units+"]");
        }
        return false;
    }

    bool operator!= (NumberWithUnits& num1, NumberWithUnits& num2){
        double convertedNum2 = convert(num2.units, num1.units, num2.n);
        if(convertedNum2 != -1){
            if(num1.n != convertedNum2) return true;
        }else{
            throw invalid_argument("Units do not match - ["+num2.units+"] cannot be converted to ["+num1.units+"]");
        }
        return false;
    }


    NumberWithUnits& operator*(double num, NumberWithUnits& n){
        output.n = num * n.n;
        output.units = n.units;
        return output;
    }

    NumberWithUnits& operator*(NumberWithUnits& n, double num){
        output.n = num * n.n;
        output.units = n.units;
        return output;
    }

    istream& operator>> (istream& input, NumberWithUnits& num){
        double n;
        string open, unit, close;
        input >> n >> open >> unit >> close;
        num.n = n;
        num.units = unit;
        return input;
    }

    ostream& operator<< (ostream& os, NumberWithUnits& num){
        os << num.n << '[' << num.units << ']';
        return os;
    }

}


// ariel::NumberWithUnits& operator+ (ariel::NumberWithUnits& num1, ariel::NumberWithUnits& num2){
//     double convertedNum2 = convertedNum2 = convert(num2.getUnits() + '_' + num1.getUnits(), num2.getNumber());
//     if(convertedNum2 != -1){
//         output.setNumber(num1.getNumber() + convertedNum2);
//         output.setUnits(num1.getUnits());
//     }else{
//         throw invalid_argument("Units do not match - ["+num2.getUnits()+"] cannot be converted to ["+num1.getUnits()+"]");
//     }
//     return output;
// }

// ariel::NumberWithUnits& operator- (ariel::NumberWithUnits& num1, ariel::NumberWithUnits& num2){
//     double convertedNum2 = convert(num2.getUnits() + '_' + num1.getUnits(), num2.getNumber());
//     output.setNumber(num1.getNumber() - convertedNum2);
//     output.setUnits(num1.getUnits());
//     return output;
// }

// bool operator< (ariel::NumberWithUnits& num1, ariel::NumberWithUnits& num2){
//     double convertedNum2 = convert(num2.getUnits() + '_' + num1.getUnits(), num2.getNumber());
//     if(num1.getNumber() < convertedNum2) return true;
//     return false;
// }

// bool operator> (ariel::NumberWithUnits& num1, ariel::NumberWithUnits& num2){
//     double convertedNum2 = convert(num2.getUnits() + '_' + num1.getUnits(), num2.getNumber());
//     if(num1.getNumber() > convertedNum2) return true;
//     return false;
// }

// bool operator>= (ariel::NumberWithUnits& num1, ariel::NumberWithUnits& num2){
//     double convertedNum2 = convert(num2.getUnits() + '_' + num1.getUnits(), num2.getNumber());
//     if(num1.getNumber() >= convertedNum2) return true;
//     return false;
// }

// bool operator<= (ariel::NumberWithUnits& num1, ariel::NumberWithUnits& num2){
//     double convertedNum2 = convert(num2.getUnits() + '_' + num1.getUnits(), num2.getNumber());
//     if(num1.getNumber() <= convertedNum2) return true;
//     return false;
// }

// bool operator== (ariel::NumberWithUnits& num1, ariel::NumberWithUnits num2){
//     double convertedNum2 = convert(num2.getUnits() + '_' + num1.getUnits(), num2.getNumber());
//     if(num1.getNumber() == convertedNum2){ return true; }
//     return false;
// }

// ariel::NumberWithUnits& operator*(double num, ariel::NumberWithUnits& n){
//     output.setNumber(n.getNumber()*num);
//     output.setUnits(n.getUnits()+"");
//     return output;
// }

// ariel::NumberWithUnits& operator+= (ariel::NumberWithUnits& num1, ariel::NumberWithUnits num2){
//     double convertedNum2 = convert(num2.getUnits() + '_' + num1.getUnits(), num2.getNumber());
//     num1.setNumber(num1.getNumber()+convertedNum2);
//     return num1;
// }

// ariel::NumberWithUnits& operator- (ariel::NumberWithUnits& num){
//     if(num.getNumber() > 0){
//         output.setNumber(num.getNumber()*(-1));
//     }else{
//         output.setNumber(num.getNumber());
//     }
//     output.setUnits(num.getUnits());
//     return output;
// }

// // ariel::NumberWithUnits operator++ (ariel::NumberWithUnits& num1){

// // }

// // ariel::NumberWithUnits operator-- (ariel::NumberWithUnits& num1){

// // }

// istream& operator>> (istream& input, ariel::NumberWithUnits& num){
//     double n;
//     string open, unit, close;
//     input >> n >> open >> unit >> close;
//     num.setNumber(n);
//     num.setUnits(unit);
//     return input;
// }

// ostream& operator<< (ostream& os, ariel::NumberWithUnits& num){
//     os << num.getNumber() << '[' << num.getUnits() << ']';
//     return os;
// }