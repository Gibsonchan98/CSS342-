//
// Created by Melanie Palomino on 02/16/2020
//

#include "skiplist.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <cassert>


using namespace std;

int totalPassed = 0;
int totalTests = 0;

//checks if list past contain what is expected 
template <typename T> string isOK(const T& got, const T& expected) {
    ++totalTests;
    if (got == expected) {
        ++totalPassed;
        return "OK: ";
    } else {
        cout << "    Got   " << got << "\n expected " << expected << endl;
        return "ERR: ";
    }
}

//Test different functions of skiplist 
void test04(){
    SkipList sl(6);
    stringstream ss;
    ss << sl;
    cout << isOK(ss.str(), string("Level: 5 -- -2147483648, 2147483647, \n"
                                  "Level: 4 -- -2147483648, 2147483647, \n"
                                  "Level: 3 -- -2147483648, 2147483647, \n"
                                  "Level: 2 -- -2147483648, 2147483647, \n"
                                  "Level: 1 -- -2147483648, 2147483647, \n"
                                  "Level: 0 -- -2147483648, 2147483647, \n"))
            .c_str()
         << "Empty SkipList of Depth=3" << endl;
    sl.add(15);
    sl.add(44);
    sl.add(101);
    sl.add(3);
    sl.remove(44);
    sl.add(96);
    sl.add(81);
    sl.add(57);
    sl.add(66);
    sl.remove(81);
    sl.add(83);
    ss.str("");
    ss << sl;
    cout << isOK(ss.str(), string("Level: 5 -- -2147483648, 57, 2147483647, \n"
                                  "Level: 4 -- -2147483648, 57, 2147483647, \n"
                                  "Level: 3 -- -2147483648, 57, 2147483647, \n"
                                  "Level: 2 -- -2147483648, 3, 57, 96, 2147483647, \n"
                                  "Level: 1 -- -2147483648, 3, 57, 96, 101, 2147483647, \n"
                                  "Level: 0 -- -2147483648, 3, 15, 57, 66, 83, 96, 101, 2147483647, \n"))
            .c_str()
         << "Empty SkipList of Depth=3" << endl;
    cout << isOK(sl.contains(81), false) << "Does not contain 81" << endl;
    cout << isOK(sl.contains(96), true) << "Contains 96" << endl;
    cout << isOK(sl.contains(4), false) << "Does not contain 4" << endl;
    cout << isOK(sl.contains(57), true) << "Contains 57" << endl;

}
//Quick tester function to test each function works properly 
void test03(){
    SkipList s(5);
    for (int i = 0; i < 10; ++i) {
        int number = rand() % 100;
        s.add(number);
        cout<< "  "<<endl;
        cout << "After adding " << number << endl;
        cout << s << endl;
    }
}


//Creates a skiplist and adds various numbers and tests different functions
void test02() {
    SkipList skipList(3);
    stringstream ss;
    ss << skipList;
    cout << isOK(ss.str(), string("Level: 2 -- -2147483648, 2147483647, \n"
                                  "Level: 1 -- -2147483648, 2147483647, \n"
                                  "Level: 0 -- -2147483648, 2147483647, \n"))
            .c_str()
         << "Empty SkipList of Depth=3" << endl;
    srand(100);
    skipList.add(10);
    skipList.add(30);
    skipList.add(5);
    skipList.add(25);
    ss.str("");
    ss << skipList;
    cout << isOK(ss.str(),
                 string(
                         "Level: 2 -- -2147483648, 2147483647, \n"
                         "Level: 1 -- -2147483648, 25, 30, 2147483647, \n"
                         "Level: 0 -- -2147483648, 5, 10, 25, 30, 2147483647, \n"))
         << "SkipList of Depth=3 with 10, 30, 5, 25" << endl;
    cout << isOK(skipList.contains(10), true) << "Contains 10" << endl;
    cout << isOK(skipList.contains(30), true) << "Contains 30" << endl;
    cout << isOK(skipList.contains(71), false) << "Does not contain 71" << endl;
}

//Creates a skiplist and adds various numbers and tests different functions
void test01() {
    SkipList skipList;
    stringstream ss;
    ss << skipList;
    cout << isOK(ss.str(), string("Level: 0 -- -2147483648, 2147483647, \n"))
         << "Empty SkipList" << endl;
    skipList.add(10);
    skipList.add(30);
    skipList.add(5);
    skipList.add(25);
    ss.str("");
    ss << skipList;
    cout << isOK(ss.str(),
                 string(
                         "Level: 0 -- -2147483648, 5, 10, 25, 30, 2147483647, \n"))
         << "Added 10, 30, 5, 25," << endl;
}

//single layer sl test funciton 
void test00() {
    SkipList sl;
    stringstream ss;
    ss << sl;
    cout << isOK(ss.str(), string("Level: 0 -- -2147483648, 2147483647, \n"))
         << "Empty SkipList" << endl;
    sl.add(4);
    sl.add(100);
    sl.add(15);
    sl.add(34);
    sl.remove(34);
    ss.str("");
    ss << sl;
    cout << isOK(ss.str(),
                 string(
                         "Level: 0 -- -2147483648, 4, 15, 100, 2147483647, \n"))
         << "Added 10, 30, 5, 25," << endl;
    cout << isOK(sl.contains(100), true) << "Contains 100" << endl;
    cout << isOK(sl.contains(4), true) << "Contains 4" << endl;
    cout << isOK(sl.contains(34), false) << "Does not contain 34" << endl;
}


int main() {
    cout << "Because of the random nature of SkipList, "
         << "the skip list levels may not match" << endl;
    // Set the random seed for easy debugging
    // NOLINTNEXTLINE
    srand(424242);
    cout << " " << endl;
    cout << "Now starting test 00"<< endl;
    cout << " " << endl;
    test00();
    cout << " " << endl;
    cout << "Now starting test 01"<< endl;
    cout << " " << endl;
    test01();
    cout << " " << endl;
    cout << "Now starting test 02"<< endl;
    cout << " " << endl;
    test02();
    cout << " " << endl;
    cout << "Now starting test 03"<< endl;
    cout << " " << endl;
    test03();
    cout << "Passed: " << totalPassed << "/" << totalTests << endl;
    return 0;
}