#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
using namespace ariel;

ifstream units_file{"units.txt"};

TEST_CASE("Arithmetic Operators - km/m/cm"){
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{5, "km"};
    CHECK(a++ == NumberWithUnits{6, "km"});
    CHECK(a-- == NumberWithUnits{5, "m"});
    CHECK(a*2 == NumberWithUnits{10, "km"});
    // CHECK(2*a == NumberWithUnits{20, "km"});
    // CHECK(-a == NumberWithUnits{-20, "km"});
    // CHECK(-a == NumberWithUnits{-20, "km"});
    // CHECK(+a == NumberWithUnits{20, "km"});
    // CHECK(+a == NumberWithUnits{20, "km"});


    // //Same unit
    // NumberWithUnits b{4, "km"};
    // CHECK((a+b) == NumberWithUnits{24, "km"});
    // CHECK((a-b) == NumberWithUnits{16, "km"});
    // NumberWithUnits c{6, "km"};
    // CHECK((a+=c) == NumberWithUnits{26, "km"});
    // CHECK((a-=c) == NumberWithUnits{20, "km"});
    // CHECK((c-=a) == NumberWithUnits{-14, "km"});

    // //Different unit
    // NumberWithUnits a1{5,"km"};
    // NumberWithUnits a2{300,"m"};
    // NumberWithUnits a3{70000,"cm"};
    // CHECK((a1+a2) == NumberWithUnits{5.3, "km"});
    // CHECK((a1-a2) == NumberWithUnits{4.7, "km"});
    // CHECK((a1+a3) == NumberWithUnits{5.7, "km"});
    // CHECK((a1-a3) == NumberWithUnits{4.3, "km"});

    // CHECK((a2-a1) == NumberWithUnits{-4700, "m"});
    // CHECK((a2+a1) == NumberWithUnits{5300, "m"});
    // CHECK((a2-a3) == NumberWithUnits{-400, "m"});
    // CHECK((a2+a3) == NumberWithUnits{1000, "m"});

    // CHECK((a3-a1) == NumberWithUnits{-430000, "cm"});
    // CHECK((a3+a1) == NumberWithUnits{570000, "cm"});
    // CHECK((a3-a2) == NumberWithUnits{400, "cm"});
    // CHECK((a3+a2) == NumberWithUnits{100000, "cm"});
}

// TEST_CASE("Boolean Operators - km/m/cm"){
//     NumberWithUnits::read_units(units_file);

//     //Same unit
//     NumberWithUnits a1{5,"km"};
//     NumberWithUnits a2{10,"km"};
//     CHECK((a1 == a1) == true);
//     CHECK((a1 == a2) == false);
//     CHECK((a1 != a2) == true);
//     CHECK((a1 < a2) == true);
//     CHECK((a1 > a2) == false);
//     CHECK((a1 <= a1) == true);
//     CHECK((a2 >= a2) == true);

//     //Different unit
//     CHECK((a1 == NumberWithUnits{500,"m"}) == true);
//     CHECK((a1 == NumberWithUnits{500000,"cm"}) == true);

//     NumberWithUnits a3{8000,"m"};
//     CHECK((a3 == NumberWithUnits{8,"km"}) == true);
//     CHECK((a3 == NumberWithUnits{800000,"cm"}) == true);

//     NumberWithUnits a4{8000,"cm"};
//     CHECK((a4 == NumberWithUnits{80,"m"}) == true);
//     CHECK((a3 == NumberWithUnits{0.08,"km"}) == true);

//     CHECK((a3 < a1) == false);
//     CHECK((a1 <= a3) == true);
//     CHECK((a3 != a4) == true);
// }

// TEST_CASE("Exceptions"){
//     NumberWithUnits::read_units(units_file);

//     NumberWithUnits a1{1,"km"};
//     NumberWithUnits a2{1,"m"};
//     NumberWithUnits a3{1,"cm"};
//     NumberWithUnits a4{1,"kg"};
//     NumberWithUnits a5{1,"g"};
//     NumberWithUnits a6{1,"ton"};
//     NumberWithUnits a7{1,"hour"};
//     NumberWithUnits a8{1,"min"};
//     NumberWithUnits a9{1,"sec"};
//     NumberWithUnits a10{1,"USD"};
//     NumberWithUnits a11{1,"ILS"};

//     //km/m/cm with others
//     CHECK_THROWS(a1 + a4);
//     CHECK_THROWS(a2 - a5);
//     CHECK_THROWS(a3 += a6);
//     CHECK_THROWS(a1 -= a7);
//     CHECK_THROWS(a2 >= a8);
//     CHECK_THROWS(a3 <= a9);
//     CHECK_THROWS(a1 == a10);
//     CHECK_THROWS(a2 < a11);

//     //kg/g/ton with others
//     CHECK_THROWS(a4 + a1);
//     CHECK_THROWS(a5 - a2);
//     CHECK_THROWS(a6 += a3);
//     CHECK_THROWS(a4 -= a7);
//     CHECK_THROWS(a5 > a8);
//     CHECK_THROWS(a6 <= a9);
//     CHECK_THROWS(a4 == a10);
//     CHECK_THROWS(a5 != a11);

//     //hour/min/sec with others
//     CHECK_THROWS(a7 + a1);
//     CHECK_THROWS(a8 - a2);
//     CHECK_THROWS(a9 += a3);
//     CHECK_THROWS(a7 -= a4);
//     CHECK_THROWS(a8 <= a5);
//     CHECK_THROWS(a9 >= a6);
//     CHECK_THROWS(a7 == a10);
//     CHECK_THROWS(a8 != a11);

//     //USD/ILS with others
//     CHECK_THROWS(a10 + a1);
//     CHECK_THROWS(a11 - a2);
//     CHECK_THROWS(a10 += a3);
//     CHECK_THROWS(a11 -= a4);
//     CHECK_THROWS(a10 <= a5);
//     CHECK_THROWS(a11 >= a6);
//     CHECK_THROWS(a10 == a7);
//     CHECK_THROWS(a11 != a8);
//     CHECK_THROWS(a10 < a9);
// }

// TEST_CASE("Input and output"){
    
// }

// TEST_CASE("Random conversions"){
//     NumberWithUnits::read_units(units_file);

//     string allUnits[] = {"km","m", "cm", "kg", "g", "ton", "hour","min", "sec", "USD", "ILS"};
    
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> distr(0, 10);

//     for(int n=0; n<50; ++n){
//         NumberWithUnits a1{1,"km"};
//     }
//         std::cout << distr(gen) << ' '; // generate numbers
// }


