#include <algorithm>
#include <string>
#include <complex>
#include <cassert>
#include <memory>
#include <set>
#include <stack>
#include <map>
#include <list>
#include <deque>
#include <numeric>
#include <cctype>
#include <cstddef>
#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <chrono>
#include <bitset>
#include "hashTableN.h"
#include "hashTable.h"
using namespace std;
int hashTableN::countOnes(int num){
    int sum;
    for (sum = 0; num!=0; sum++){
      num &= num - 1;
    }
    return sum;
}
void hashTableN::printHT(){
    int counter = 0;
    for(int i = 0 ; i < (1<<b) ;i++){
        if(((*ht)[i])!=NULL){
            cout<<"\tBucket"<<i<<": "<<endl;
            ((*ht)[i])->printHT();
            counter++;
        }
    }
    cout<<"Bucket sizes: "<<counter<<endl;
}
void hashTableN::printHT(bool bbb){
       int counter = 0;
       ofstream ofile;
       ofile.open("outputN.log");
    for(int i = 0 ; i < (1<<b) ;i++){
        if(((*ht)[i])!=NULL){
            ofile<<"\tBucket"<<i<<": "<<endl;
            ((*ht)[i])->printHT("outputN.log");
            counter++;
        }
    }
    ofile<<"Bucket sizes: "<<counter<<endl;
    ofile.close();
}
bool hashTableN::get(int x){
    int hx = 0;
    for(int j = 0 ; j <matrix.size() ; j++ ){
        hx += (countOnes(matrix[j]&x)%2)*(1<<j); //calculate hx as binary number
    }
    if((*ht)[hx] != NULL){
         return (*ht)[hx]->get(x);
    }
        return false;

}
void hashTableN::hashKeys(){
    vector< vector<int> >* tempHT = new vector<vector<int> >();
//    (*tempHT) = (vector<int  >*)malloc(htsize*sizeof(vector<int>));
    tempHT->resize(htsize);
    for(int i = 0 ;i < keys->size() ; i++){
        int hx = 0;
        for(int j = 0 ; j <matrix.size() ; j++ ){
            hx += (countOnes(matrix[j]&(*keys)[i])%2)*(1<<j); //calculate hx as binary number
        }
        ((*tempHT)[hx]).push_back((*keys)[i]);
    }
    ht = new vector<hashTable *>();
    ht->resize(htsize);//allocate vector
    for(int i = 0 ; i < htsize ;i++){
        if((*tempHT)[i].size()){
            ((*ht)[i]) = new hashTable(distribution,generator);
            ((*ht)[i])->hashVec(&((*tempHT)[i]));
        }
    }
}
void hashTableN::generateHF(){
    matrix.clear();
    for(int i = 0 ; i < b ;i++){
        matrix.push_back(distribution(generator));
    }
}
void hashTableN::initialize(int n){
    b = ceil(log2(n));
    htsize = (1<<b);
}
void hashTableN::hashVec(vector <int>* v){
    keys = v;
    initialize(v->size());
    generateHF();
    hashKeys();
}
hashTableN::hashTableN(uniform_int_distribution<int> distribution1,default_random_engine generator1)
{
    distribution = distribution1;
    generator = generator1;
}
void hashTableN::clear(){
    b = 0; htsize = 0;
}
hashTableN::~hashTableN()
{
    //dtor
}
