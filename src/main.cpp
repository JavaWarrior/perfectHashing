#include <cmath>
#include <random>
#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>
#include <cstring>
#include "hashTable.h"
#include "hashTableN.h"
using namespace std;
char filePath[100];
vector<int> ks;
ifstream inputFile; //input file
bool isRead = false;
//random
unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator(seed);
uniform_int_distribution<int> distribution(INT_MAX+1,INT_MAX);
hashTable * htN2 = new hashTable(distribution,generator);
hashTableN * htN = new hashTableN(distribution,generator);
//random
bool takeFilePath(){
    cout<< "enter file name"<<endl;
    cin>>filePath;
    inputFile.open(filePath);
    return inputFile.is_open();
}
void takeUserInput(){
    cout<<"enter number of elements to insert"<<endl;
    char inpt[100];
    cin>>inpt;
    int n = atoi(inpt);
    ks.clear();
    cout<<"enter "<<n<<"elements spearated"<<endl;
    for(int i = 0 ; i < n ;i++){
        cin>>inpt;
        int temp = atoi(inpt);
        ks.push_back(temp);
    }
}
void scanFile(){
    int line;
    ks.clear();
    while(inputFile>>line)
        ks.push_back(line);
}
void lookUp(){
    if(!isRead)
    {
        cout<<"no input was taken no search can be done"<<endl;
        return;
    }
    cout<<"enter element you're looking for"<<endl;
    char inpt[100];
    cin>>inpt;
    int x = atoi(inpt);
    if(htN2->get(x))
        cout<<"element was fonud in O(N2) method"<<endl;
    else
        cout<<"element was not fonud in O(N2) method"<<endl;
        if(htN->get(x))
        cout<<"element was fonud in O(N) method"<<endl;
    else
        cout<<"element was not fonud in O(N) method"<<endl;
}
void startHashing(){
    htN2->hashVec(&ks);
    htN->hashVec(&ks);
    cout<<"O(N2) method:"<<endl;
    htN2->printHT();
    htN2->printHT("output.log");
    cout<<"O(N) method:"<<endl;
    htN->printHT();
    htN->printHT(true);
    cout<<"outputs was written to output.log"<<endl;
}
void welcomeUser(){
    while(1){
        char choice1[100];
        cout<<"\t\t\twelcome choose your destiny"<<endl;
        cout<<"\t\t------------------------------------------"<<endl;
        cout<<"\t\t\t1:read from file"<<endl;
        cout<<"\t\t\t2:read from CMD"<<endl;
        cout<<"\t\t\t3:lookup an element"<<endl;
        cout<<"\t\t\t4: exit"<<endl;
        cin>>choice1;
        int cho = atoi(choice1);
        switch(cho){
            case 1:{
                if(takeFilePath()){
                    scanFile();
                    isRead = true;
                    startHashing();
                }
                else{
                    cout<<"wrong file path enter correct path"<<endl;
                }
                break;
            }
            case 2:{
                takeUserInput();
                startHashing();
                isRead = true;
                break;
            }case 3:{
                lookUp();
                break;
            }
            case 4:{
                return;
            }default :
                cout<<"wrong choice try again later"<<endl;
        }
    }

}
int main(){
    welcomeUser();
    return 0;
}
