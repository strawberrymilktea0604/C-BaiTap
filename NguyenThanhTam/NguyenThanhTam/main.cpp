#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <random>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#define MAX 1000
#include "bellman.h"
#include "tsm.h"

//Function to print an edge
void printedge(int[]);
//Function to generate a random edges list
int edgeListGen(int[][3],int,int,int);

//main Function
int main()
{
    enum Func_check {FUNC_BF, FUNC_BF_PATH, FUNC_TRAVELING, FUNC_NONE};

    bool randGen=0;
    int edgeList[MAX][3] ;
    int numEdges=40;
    int numVertices=10;
    int initlimit=15;

    if(!randGen){
        ifstream fin("EdgeList.txt");
        if (!fin.is_open()) {
            cout << "Error: Cannot open EdgeList.txt" << endl;
            return -1;
        }
        for(int i=0;i<numEdges;i++){
            fin>>edgeList[i][0]>>edgeList[i][1]>>edgeList[i][2];
        }
        fin.close();
    }
    else{
        if(edgeListGen(edgeList,numEdges,numVertices,initlimit)<0) return -1;
    }

    cout << "Graph loaded with " << numEdges << " edges:" << endl;
    for(int i=0;i<5 && i<numEdges;i++){
        cout << "Edge " << i << ": " << char(edgeList[i][0]) << " -> "
             << char(edgeList[i][1]) << " (weight: " << edgeList[i][2] << ")" << endl;
    }
    cout << "..." << endl;

    Func_check func = FUNC_BF;

    switch(func){
        case FUNC_BF:
        {
            int BFValue[256];
            int BFPrev[256];
            char start_vertices = edgeList[0][0];
            cout << "\n=== Running Bellman-Ford Algorithm ===" << endl;
            cout << "Starting from vertex: " << char(start_vertices) << " (ASCII: " << (int)start_vertices << ")" << endl;
            BF(edgeList,numEdges,start_vertices,BFValue,BFPrev);
            break;
        }
        case FUNC_BF_PATH:
        {
            char start_vertices = edgeList[0][0];
            char end_vertices = edgeList[1][1];
            cout << "\n=== Running Bellman-Ford Path Algorithm ===" << endl;
            cout << "From: " << char(start_vertices) << " To: " << char(end_vertices) << endl;
            BF_Path(edgeList,numEdges,start_vertices,end_vertices);
            break;
        }
        case FUNC_TRAVELING:
        {
            char start_vertices = edgeList[0][0];
            cout << "\n=== Running Traveling Salesman Algorithm ===" << endl;
            cout << "Starting from vertex: " << char(start_vertices) << endl;
            Traveling(edgeList,numEdges,start_vertices);
            break;
        }
        default:
            cout<<"No such case" << endl;
    }
    return 0;
}

void printedge(int edge[]){
    cout<<char(edge[0])<<" -> "<<char(edge[1])<<", weight: "<<edge[2]<<endl;
}

int edgeListGen(int edgeList[][3],int numEdges,int numVertices,int initlimit){
    srand((unsigned int)time(NULL));

    if(numEdges>(numVertices*(numVertices-1))/2){
        cout<<"cannot create simple graph";
        return -1;
    }
    if(numEdges<numVertices-1){
        cout<<"cannot create a connected (weak) graph";
        return -1;
    }

    int* verList=new int[numVertices];
    vector<int> verName;
    for(int i=33;i<=126;i++){verName.push_back(i);}
    random_shuffle(verName.begin(),verName.end());
    for(int i=0;i<numVertices;i++){verList[i]=verName[i];}

    bool flag=0;
    vector<pair<int,int> > fullList;
    for(int i=0;i<numVertices;i++){
        for(int j=i+1;j<numVertices;j++){
            fullList.push_back(make_pair(verList[i],verList[j]));
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
    if(initlimit<=1){
        for(int i=0;i<numEdges;i++){
            edgeList[i][2]=1;
            fout<<edgeList[i][0]<<" "<<edgeList[i][1]<<" "<<edgeList[i][2]<<endl;
        }
    }
    else{
        for(int i=0;i<numEdges;i++){
            edgeList[i][2]=rand()%initlimit + 1;
            fout<<edgeList[i][0]<<" "<<edgeList[i][1]<<" "<<edgeList[i][2]<<endl;
        }
    }
    fout.close();
    delete []verList;
    return 1;
}
