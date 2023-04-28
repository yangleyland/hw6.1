#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

#include <string>
#include <cctype>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        std::string tempStr=k;
        unsigned long long w[5]={0,0,0,0,0};
        // Add your code here
        for (int i=4;i>=0;i--){
            if (tempStr.length()==0){
                break;
            }
            else if (tempStr.length()>6){
                std::string newStr = tempStr.substr(tempStr.length() - 6);
                //turn newStr into number   
                w[i]=stringToNumber(newStr);
                tempStr.erase(tempStr.length() - 6);
            }
            else {
                w[i]=stringToNumber(tempStr);
                tempStr.erase(0);
            }
        }
        unsigned long long value=0;
        for (int i=0; i<5; i++){
            value+=w[i]*rValues[i];
        }
        return value;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T stringToNumber(std::string& k) const
    {
        // Add code here or delete this helper function if you do not want it
        unsigned long long value=0;
        for (int i=0; i<(int)k.length(); i++){
            value+=letterToNumber(k[i]);
            value*=36;
        }
        value/=36;
        return value;
    }
    HASH_INDEX_T letterToNumber (char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        unsigned long long value;
        char newLetter = tolower(letter);
        if (newLetter>=97 && newLetter<=122){
            value=newLetter-97;
        } else if (newLetter>=48 && newLetter<=57){
            value=newLetter-22;
        }
        return value;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
