// dp3.h
// Chaweinta Hale
// 2019-09-28
//
// For CS 311 Fall 2019
// Source for Project 3 Functions

#include "dp3.h"       // For Project 3 prototypes & templates

#include <functional>
using std::function;


void didItThrow(const function<void()> & ff,
                bool & threw)
{
    try {
      ff();
    }
    catch (...){
       threw = true;
       throw;
    }
    threw = false;
}


int gcd(int a,
        int b)
{
    while(true){
    if (a == 0){
        return b;
    } else if (b == 0){
        return a;
    }
    int c = a;
    a = (b % a);
    b = c;
    }
}

