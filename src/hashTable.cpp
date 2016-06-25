#include <cmath>
#include <random>
#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>
#include <cstring>
#include "hashTable.h"
using namespace std;

int hashTable::countOnes(int num){
    int sum;
    for (sum = 0; num!=0; sum++){
      num &= num - 1;
    }
    return sum;
}
void hashTable::printHT(){
    for(int i = 0 ; i < (1<<b) ;i++){
        if(boolTable[i]){
            cout<<"index : "<<i<<"element :"<<hashTablePtr[i]<<endl;
        }
    }
    cout<<"hashed in : "<<nopasses<<" passes"<<endl;

}
void hashTable::printHT(char* bbb){
    ofstream ofile;
    ofile.open(bbb);
    for(int i = 0 ; i < (1<<b) ;i++){
        if(boolTable[i]){
            ofile<<"index : "<<i<<"element :"<<hashTablePtr[i]<<endl;
        }
    }
    ofile<<"hashed in : "<<nopasses<<" passes"<<endl;
    ofile.close();
}

void hashTable::hashKeys(){
    isColided = false;
    for(int i = 0 ;i < keys->size() ; i++){
        int hx = 0;
        for(int j = 0 ; j <matrix.size() ; j++ ){
            hx |= (countOnes(matrix[j]&(*keys)[i])%2)*(1<<j); //calculate hx as binary number
        }
        if(boolTable[hx]){
            isColided = true;
            return;
        }else{
            boolTable[hx] = true;
            hashTablePtr[hx] = (*keys)[i];
        }
    }
}
void hashTable::generateHF(){
    matrix.clear();
    for(int i = 0 ; i < b ;i++){
        matrix.push_back(distribution(generator));
    }
}
void hashTable::initialize(int n){
    b = ceil(log2(n*n));
    htsize = (1<<b);
    hashTablePtr = (int*) malloc(htsize*sizeof(int));
    boolTable = (bool*)malloc(htsize*sizeof(bool));
    nopasses = 0;
    isColided = false;
}
void hashTable::hashVec(vector <int>* v){
    keys = v;
    initialize(v->size());
    int counter = 0;
    do{
        memset(boolTable ,false, htsize*sizeof(bool));
        generateHF();
        hashKeys();
        counter++;
    }while(isColided);
     nopasses = counter;
}
hashTable::hashTable(uniform_int_distribution<int> distribution1,default_random_engine generator1)
{
    generator = generator1;
    distribution = distribution1;
}
void hashTable::clear(){
    if(hashTablePtr != NULL)
    free(hashTablePtr);
    if(boolTable!=NULL)
    free(boolTable);
    b = 0; htsize = 0;nopasses = 0;isColided = false;
}
bool hashTable::get(int x){
    int hx = 0;
    for(int j = 0 ; j <matrix.size() ; j++ ){
        hx += (countOnes(matrix[j]&x)%2)*(1<<j); //calculate hx as binary number
    }
    if(boolTable[hx])
        return true;
    return false;
}
hashTable::~hashTable()
{
    //dtor
}
