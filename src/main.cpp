// Min includes in main.cpp
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <math.h>

// Includes to be distributed into other .h files
#include <string>
#include <algorithm>
#include <queue>
#include <functional>
#include <cmath>
#include <float.h>
#include <limits.h>
#include <typeinfo>

using namespace std;

typedef unsigned long int ULONG;
int trialNum;

#include "config.h"
#include "vertex.h"
#include "edge.h"
#include "node.h"
#include "graph.h"
#include "queue.h"
#include "search.h"
#include "path.h"
#include "execute_path.h"


vector< vector< double > > makeVertices(double x, double y, int numVerts){

  // Initialize variables for random vertice generation
  vector< vector< double > > vertices(numVerts, vector<double>(2));
  srand(time(NULL));
  double vertx, verty;
  int xx = x;
  int yy = y;
  double testx, testy;

  // Generate random vertice locations
  for(int i = 0; i < numVerts; i++){
    if(i == 0){
      vertices[i][0] = 0;
      vertices[i][1] = 0;
    }
    else if(i == numVerts-1){
      vertices[i][0] = x;
      vertices[i][1] = y;
    }
    else{
      vertx = rand() % xx;
      verty = rand() % yy;
      vertices[i][0] = vertx;
      vertices[i][0] = verty;
    }
  }

  // Write vertices to txt file
  stringstream vFileName;
  vFileName << "../results/vertices" << trialNum << ".txt";
  ofstream vertsFile;
  vertsFile.open(vFileName.str().c_str());
  for(ULONG i = 0; i < vertices.size(); i++){
    vertsFile << vertices[i][0] << "," << vertices[i][1] << "\n";
  }
  vertsFile.close();

  return vertices;
}

// Main Loop for testing graph search
int main(){

  //Begin Trials
  cout << "Trial number: ";
  cin >> trialNum;
  cout << "Test program " << trialNum << "..\n";
  srand(time(NULL));
  bool loop = true;

  // Loop -if the graph is bad (if statement checks paths found) then redo the test
  while(loop){

    // Initialize Graph variables
    vector< vector< double > > vertVec2;
    double mapX, mapY, radius;
    int numVerts = 100;
    mapX = 100;
    mapY = 100;

    // Generate vertices in a map sized mapX by mapY
    cout << "Generating Random Vertices in " << mapX << " by " << mapY << endl;
    vertVec2 = makeVertices(mapX, mapY, numVerts);

    // Calculate a radius based on PRM* algorithm
    radius = sqrt((6.0/pi)*mapX*mapY*(log((double)numVerts)/(double)numVerts));
    cout << "Connecting with radius " << radius << endl;

    // Generate a graph with vertices and radius
    Graph * testGraph = new Graph(vertVec2, radius);

    // Get starting and ending Vertices
    Vertex * sourceSec = testGraph->GetVertices()[0];
    Vertex * goalSec = testGraph->GetVertices()[testGraph->GetNumVertices()-1];

    // Create a search object to perform path search
    cout << "Creating search object..." ;
    Search * testSearch = new Search(testGraph, sourceSec, goalSec);
    cout << "complete.\n";

    //Begin Search from start to goal
    cout << "Performing path search from (" << sourceSec->GetX() << "," << sourceSec->GetY() << ") to (";
    cout << goalSec->GetX() << "," << goalSec->GetY() << ")...\n";
    pathOut pType = ALL;
    vector<Node *> bestPaths = testSearch->PathSearch(pType);
    cout << "Path search complete, " << bestPaths.size() << " paths found.\n";

    // Write paths to file
    if(bestPaths.size() !=0){
      stringstream pFileName;
      pFileName << "../results/bestPaths" << trialNum << ".txt";
      ofstream pathsFile;
      pathsFile.open(pFileName.str().c_str());
      for(ULONG i = 0; i < (ULONG)bestPaths.size(); i++){
        pathsFile << "Path " << i << endl;
        Node * curNode = bestPaths[i];
        while(curNode->GetParent()){
          pathsFile << "(" << curNode->GetVertex()->GetX() << "," << curNode->GetVertex()->GetY() << ")\n";
          curNode = curNode->GetParent();
          pathsFile << "(" << curNode->GetVertex()->GetX() << "," << curNode->GetVertex()->GetY() << ")\n\n";
        }
        pathsFile.close();
      }
    }

    // Delete the graph and search if the number of paths are too small or large
    if(bestPaths.size() < 30 || bestPaths.size() > 100){
      delete testGraph;
      testGraph = 0;
      delete testSearch;
      testSearch = 0;
      continue;
    }
    else{
      loop = false;
    }

    // Execute paths
    // Because paths are over distributions run enough stat runs to show improvement not a fluke
    vector< double > costs;
    int totalStatRuns = 100;
    vector< vector< double > > allCosts(totalStatRuns, vector<double>(5));
    for(int numStatRuns = 0; numStatRuns < totalStatRuns; numStatRuns++){
      // Setting the random generated edge costs based on edge distributions
      AssignTrueEdgeCosts(testGraph, numStatRuns+1);
      costs = executePath(bestPaths, testGraph);
      allCosts[numStatRuns] = costs;
    }

    // Write path costs to txt file
    stringstream cFileName ;
    cFileName << "../results/pathCosts" << trialNum << ".txt" ;
    ofstream costsFile ;
    costsFile.open(cFileName.str().c_str()) ;
    for (ULONG i = 0; i < allCosts.size(); i++){
      for (int j = 0; j < allCosts[i].size(); j++){
        costsFile << allCosts[i][j] << "," ;
      }
      costsFile << "\n" ;
    }
    costsFile.close() ;

    // Delete pointers and set to null
    delete testGraph;
    testGraph = 0;
    delete testSearch;
    testSearch = 0;

  }
  return 0;
}
