
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>
#include<fstream>
using namespace std;
class hashTable
{
    public:
        hashTable(uniform_int_distribution<int> distribution,default_random_engine generator);
        virtual ~hashTable();
        bool get(int x);
        void clear();
        void hashVec(std::vector <int> *v);
        void printHT();
        void printHT(char* bbb);
    protected:
    private:
        //funcs
        int countOnes(int n);
        void hashKeys();
        void generateHF();
        void initialize(int n);
        //vars
        vector <int> matrix;vector<int>* keys;
        int b; //number of elements
        bool isColided = false;
        int * hashTablePtr,htsize ;bool * boolTable;
        int nopasses;
        //randomness variables
        uniform_int_distribution<int> distribution;
        default_random_engine generator;
};

#endif // HASHTABLE_H
