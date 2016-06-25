#ifndef HASHTABLEN_H
#define HASHTABLEN_H
#include <bits/stdc++.h>
#include <hashTable.h>
#include<fstream>

using namespace std;

class hashTableN
{
    public:
        hashTableN(uniform_int_distribution<int> distribution,default_random_engine generator);
        void clear();
        void hashVec(std::vector <int> *v);
        void printHT();
        void printHT(bool bbb);
        bool get(int x);
        virtual ~hashTableN();
    protected:
    private:
        //funcs
        int countOnes(int num);
        void hashKeys();
        void initialize(int n);
        void generateHF();
        //vars
        vector<class hashTable*> *ht;
        vector <int> matrix;vector<int>* keys;
        int b; //number of elements
         int htsize;
        //randomness variables
        uniform_int_distribution<int> distribution;
        default_random_engine generator;
        //end or randomness
        //random comment :P;

};

#endif // HASHTABLEN_H
