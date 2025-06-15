#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>
#include "bellman.h"
#include "tsm.h"
using namespace std;
#define MAX 1000

//Function to print an edge
void printedge(int[]);
//Function to generate a random edges list
int edgeListGen(int[][3],int,int,int);

//main Function
int main()
{
    //Function name for checking: đổi tên enum để tránh xung đột
    enum Func_check {FUNC_BF, FUNC_BF_PATH, FUNC_TRAVELING, FUNC_NONE};
    
    bool randGen=0; // Set to 0 to read from file
    int edgeList[MAX][3] ;
    int numEdges=40;
    int numVertices=10;
    int initlimit=15;
    if(!randGen){
        //Read from file
        ifstream fin("EdgeList.txt");
        for(int i=0;i<numEdges;i++){
            fin>>edgeList[i][0]>>edgeList[i][1]>>edgeList[i][2];
        }
        fin.close();
    }
    else{
        //Generate a random edgelist:
        if(edgeListGen(edgeList,numEdges,numVertices,initlimit)<0) return -1;
    }
    
    //Check the chosen function:
    Func_check func = FUNC_BF; // Đổi tên
    
    switch(func){
        case FUNC_BF: // Đổi tên
        {
            int BFValue[50];
            int BFPrev[50];
            char start_vertices=edgeList[0][0];
            BF(edgeList,numEdges,start_vertices,BFValue,BFPrev);
            break;
        }
        case FUNC_BF_PATH: // Đổi tên
        {
            char start_vertices=edgeList[0][0];
            char end_vertices=edgeList[1][1]; // Fixed the indexing
            BF_Path(edgeList,numEdges,start_vertices,end_vertices);
            break;
        }
        case FUNC_TRAVELING: // Đổi tên
        {
            char start_vertices=edgeList[0][0];
            Traveling(edgeList,numEdges,start_vertices);
            break;
        }
        default: cout<<"no such case";
    }
    return 0;
}

//support function definition 
void printedge(int edge[]){
    cout<<char(edge[0])<<char(edge[1])<<","<<edge[2]<<endl;
}

int edgeListGen(int edgeList[][3],int numEdges,int numVertices,int initlimit=1){
    //random generator init
    srand((unsigned int)time(NULL)); // Use cstdlib and ctime instead of random_device
    
    //exception
    if(numEdges>(numVertices*(numVertices-1))/2){
        cout<<"cannot create simple graph";
        return -1;
    }
    if(numEdges<numVertices-1){
        cout<<"cannot create a connected (weak) graph";
        return -1;
    }
    
    //generate random vertices' names
    int* verList=new int[numVertices];
    vector<int> verName;
    for(int i=33;i<=126;i++){verName.push_back(i);}
    random_shuffle(verName.begin(),verName.end()); // Use random_shuffle instead of shuffle
    for(int i=0;i<numVertices;i++){verList[i]=verName[i];}
    
    //generate random edges, ensure that each vertices will have at least 1 edges;
    bool flag=0;
    vector<pair<int,int> > fullList; // Space between > >
    for(int i=0;i<numVertices;i++){
        for(int j=0;j<numVertices;j++){
            if(i==j) break;
            fullList.push_back(make_pair(verList[i],verList[j])); // Use make_pair
        }
    }
    int* checkList=new int[numVertices];
    while (!flag){
        random_shuffle(fullList.begin(),fullList.end());    
        for(int i=0;i<numEdges;i++){
            edgeList[i][0]=fullList[i].first;
            edgeList[i][1]=fullList[i].second;
        }
        int count=0;
        
        for(int i=0;i<numEdges;i++){
            if(count==numVertices) {
                flag=1; break;
            }
            bool found0=0;
            bool found1=0;
            for(int j=0;j<count;j++){
                if(!found0&&edgeList[i][0]==checkList[j]){
                    found0=1;
                }
                if(!found1&&edgeList[i][1]==checkList[j]){
                    found1=1;
                }
                if(found0&&found1) break;
            }
            if(!found0){
                checkList[count++]=edgeList[i][0];
            }
            if(!found1){
                checkList[count++]=edgeList[i][1];
            }
        }
    }
    delete[] checkList;
    
    ofstream fout("EdgeList.txt");
    //generate the weights
    if(initlimit<=1){//All the weights will be 1
        for(int i=0;i<numEdges;i++){
            edgeList[i][2]=1;            
        }
    }
    else{//randomize edges' weights
        for(int i=0;i<numEdges;i++){
            edgeList[i][2]=rand()%initlimit; // Use rand() instead of uniform_int_distribution
            fout<<edgeList[i][0]<<" "<<edgeList[i][1]<<" "<<edgeList[i][2]<<endl;
        }
    }
    fout.close();
    delete []verList;
    return 1;
}