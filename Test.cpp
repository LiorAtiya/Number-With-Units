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
    CHECK(a-- == NumberWithUnits{5, "km"});
    CHECK(a*2 == NumberWithUnits{10, "km"});
    CHECK(2*a == NumberWithUnits{10, "km"});
    CHECK(-a == NumberWithUnits{-5, "km"});
    CHECK(-a == NumberWithUnits{-5, "km"});
    CHECK(+a == NumberWithUnits{5, "km"});


    //Same unit
    NumberWithUnits b{4, "km"};
    CHECK((a+b) == NumberWithUnits{9, "km"});
    CHECK((a-b) == NumberWithUnits{1, "km"});
    NumberWithUnits c{6, "km"};
    CHECK((a+=c) == NumberWithUnits{11, "km"});
    CHECK((b-=c) == NumberWithUnits{-2, "km"});
    CHECK((c-=b) == NumberWithUnits{8, "km"});

    //Different unit
    NumberWithUnits a1{5,"km"};
    NumberWithUnits a2{300,"m"};
    NumberWithUnits a3{70000,"cm"};
    CHECK((a1+a2) == NumberWithUnits{5.3, "km"});
    CHECK((a1-a2) == NumberWithUnits{4.7, "km"});
    CHECK((a1+a3) == NumberWithUnits{5.7, "km"});
    CHECK((a1-a3) == NumberWithUnits{4.3, "km"});

    CHECK((a2-a1) == NumberWithUnits{-4700, "m"});
    CHECK((a2+a1) == NumberWithUnits{5300, "m"});
    CHECK((a2-a3) == NumberWithUnits{-400, "m"});
    CHECK((a2+a3) == NumberWithUnits{1000, "m"});

    CHECK((a3-a1) == NumberWithUnits{-430000, "cm"});
    CHECK((a3+a1) == NumberWithUnits{570000, "cm"});
    CHECK((a3-a2) == NumberWithUnits{40000, "cm"});
    CHECK((a3+a2) == NumberWithUnits{100000, "cm"});
}

TEST_CASE("Boolean Operators - km/m/cm"){
    NumberWithUnits::read_units(units_file);

    //Same unit
    NumberWithUnits a1{5,"km"};
    NumberWithUnits a2{10,"km"};
    CHECK((a1 == a1) == true);
    CHECK((a1 == a2) == false);
    CHECK((a1 != a2) == true);
    CHECK((a1 < a2) == true);
    CHECK((a1 > a2) == false);
    CHECK((a1 <= a1) == true);
    CHECK((a2 >= a2) == true);

    //Different unit
    CHECK((a1 == NumberWithUnits{500,"m"}) == false);
    CHECK((a1 == NumberWithUnits{500000,"cm"}) == true);

    NumberWithUnits a3{8000,"m"};
    CHECK((a3 == NumberWithUnits{8,"km"}) == true);
    CHECK((a3 == NumberWithUnits{800000,"cm"}) == true);

    NumberWithUnits a4{8000,"cm"};
    CHECK((a4 == NumberWithUnits{80,"m"}) == true);
    CHECK((a4 == NumberWithUnits{0.08,"km"}) == true);

    CHECK((a3 < a1) == false);
    CHECK((a1 <= a3) == true);
    CHECK((a3 != a4) == true);
}

TEST_CASE("Arithmetic Operators - kg/g/ton"){
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{5, "kg"};
    CHECK(a++ == NumberWithUnits{6, "kg"});
    CHECK(a-- == NumberWithUnits{5, "kg"});
    CHECK(a*2 == NumberWithUnits{10, "kg"});
    CHECK(2*a == NumberWithUnits{10, "kg"});
    CHECK(-a == NumberWithUnits{-5, "kg"});
    CHECK(-a == NumberWithUnits{-5, "kg"});
    CHECK(+a == NumberWithUnits{5, "kg"});


    //Same unit
    NumberWithUnits b{4, "kg"};
    CHECK((a+b) == NumberWithUnits{9, "kg"});
    CHECK((a-b) == NumberWithUnits{1, "kg"});
    NumberWithUnits c{6, "kg"};
    CHECK((a+=c) == NumberWithUnits{11, "kg"});
    CHECK((b-=c) == NumberWithUnits{-2, "kg"});
    CHECK((c-=b) == NumberWithUnits{8, "kg"});

    //Different unit
    NumberWithUnits a1{5,"kg"};
    NumberWithUnits a2{300,"g"};
    NumberWithUnits a3{7,"ton"};
    CHECK((a1+a2) == NumberWithUnits{5.3, "kg"});
    CHECK((a1-a2) == NumberWithUnits{4.7, "kg"});
    CHECK((a1+a3) == NumberWithUnits{7005, "kg"});
    CHECK((a1-a3) == NumberWithUnits{-6995, "kg"});

    CHECK((a2-a1) == NumberWithUnits{-4700, "g"});
    CHECK((a2+a1) == NumberWithUnits{5300, "g"});
    NumberWithUnits a4{0.05,"ton"};
    CHECK((a2-a4) == NumberWithUnits{-49700, "g"});
    CHECK((a2+a4) == NumberWithUnits{50300, "g"});

    CHECK((a3-a1) == NumberWithUnits{6.995, "ton"});
    CHECK((a3+a1) == NumberWithUnits{7.005, "ton"});
    CHECK((a3-a2) == NumberWithUnits{6.9997, "ton"});
    CHECK((a3+a2) == NumberWithUnits{7.0003, "ton"});
}

TEST_CASE("Boolean Operators - kg/g/ton"){
    NumberWithUnits::read_units(units_file);

    //Same unit
    NumberWithUnits a1{5,"kg"};
    NumberWithUnits a2{10,"kg"};
    CHECK((a1 == a1) == true);
    CHECK((a1 == a2) == false);
    CHECK((a1 != a2) == true);
    CHECK((a1 < a2) == true);
    CHECK((a1 > a2) == false);
    CHECK((a1 <= a1) == true);
    CHECK((a2 >= a2) == true);

    //Different unit
    CHECK((a1 == NumberWithUnits{500,"g"}) == false);
    CHECK((a1 == NumberWithUnits{0.005,"ton"}) == true);

    NumberWithUnits a3{8000,"g"};
    CHECK((a3 == NumberWithUnits{8,"kg"}) == true);
    CHECK((a3 == NumberWithUnits{800000,"kg"}) == false);

    NumberWithUnits a4{8,"ton"};
    CHECK((a4 == NumberWithUnits{8000000,"g"}) == true);
    CHECK((a4 == NumberWithUnits{8000,"kg"}) == true);

    CHECK((a3 < a1) == false);
    CHECK((a1 <= a3) == true);
    CHECK((a3 != a4) == true);
}

TEST_CASE("Exceptions"){
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a1{1,"km"};
    NumberWithUnits a2{1,"m"};
    NumberWithUnits a3{1,"cm"};
    NumberWithUnits a4{1,"kg"};
    NumberWithUnits a5{1,"g"};
    NumberWithUnits a6{1,"ton"};
    NumberWithUnits a7{1,"hour"};
    NumberWithUnits a8{1,"min"};
    NumberWithUnits a9{1,"sec"};
    NumberWithUnits a10{1,"USD"};
    NumberWithUnits a11{1,"ILS"};

    //km/m/cm with others
    CHECK_THROWS(a1 + a4);
    CHECK_THROWS(a2 - a5);
    CHECK_THROWS(a3 += a6);
    CHECK_THROWS(a1 -= a7);
    CHECK_THROWS((a2 >= a8));
    CHECK_THROWS(a3 <= a9);
    CHECK_THROWS(a1 == a2);
    CHECK_THROWS(a2 < a11);

    //kg/g/ton with others
    CHECK_THROWS(a4 + a1);
    CHECK_THROWS(a5 - a2);
    CHECK_THROWS(a6 += a3);
    CHECK_THROWS(a4 -= a7);
    CHECK_THROWS(a5 > a8);
    CHECK_THROWS(a6 <= a9);
    CHECK_THROWS(a4 == a10);
    CHECK_THROWS(a5 != a11);

    //hour/min/sec with others
    CHECK_THROWS(a7 + a1);
    CHECK_THROWS(a8 - a2);
    CHECK_THROWS(a9 += a3);
    CHECK_THROWS(a7 -= a4);
    CHECK_THROWS(a8 <= a5);
    CHECK_THROWS(a9 >= a6);
    CHECK_THROWS(a7 == a10);
    CHECK_THROWS(a8 != a11);

    //USD/ILS with others
    CHECK_THROWS(a10 + a1);
    CHECK_THROWS(a11 - a2);
    CHECK_THROWS(a10 += a3);
    CHECK_THROWS(a11 -= a4);
}

TEST_CASE("Input Operator"){
    //Good input
    NumberWithUnits a;
    istringstream in1{"100 [ min ]"};
    istringstream in2{"-15 [ cm ]"};
    istringstream in3{"30 [ ton ]"};
    istringstream in4{"7 [ USD ]"};
    istringstream in5{"4005 [ ILS ]"};
    in1 >> a;
    CHECK(a == NumberWithUnits{100,"min"});
    in2 >> a;
    CHECK(a == NumberWithUnits{-15,"cm"});
    in3 >> a;
    CHECK(a == NumberWithUnits{30,"ton"});
    in4 >> a;
    CHECK(a == NumberWithUnits{7,"USD"});
    in5 >> a;
    CHECK(a == NumberWithUnits{4005,"ILS"});

    //Bad input
    istringstream in6{"100 [ Kg ]"};
    istringstream in7{"100 ~ USB ]"};
    istringstream in8{"$$ [ hour ]"};
    istringstream in9{"10000"};
    istringstream in10{"km"};
    CHECK_THROWS(in6 >> a);
    CHECK_THROWS(in7 >> a);
    CHECK_THROWS(in8 >> a);
    CHECK_THROWS(in9 >> a);
    CHECK_THROWS(in10 >> a);
}

TEST_CASE("Output Operator"){
    string allUnits[] = {"km","m", "cm","kg", "g", "ton","hour","min", "sec","USD", "ILS"};
    int units = 11;
    ostringstream output;

    for(int i = 0 ; i < units ; i++){
        NumberWithUnits num1{10,allUnits[i]};
        output.str("");
        output << num1;
        CHECK(output.str() == "10["+allUnits[i]+"]");
    }
}

  


