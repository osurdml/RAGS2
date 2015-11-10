#ifndef RAGS2_HPP
#define RAGS2_HPP

class RAGS2{
  public:
    RAGS2(){
      //make graph
      //search graph
      //totalCost = 0;
      //totalCost = RAGS2(searchGraph, SGPaths[0]->GetVertex(), GSPaths[0]->GetVertex());
      //allCosts.push_back(totalCost);
    };
  private:

}


double RAGS2::Search(Graph * graph, Vertex * source, Vertex * goal){
  // Initialize search
  double cost = 0.0;
  Search * testSearch = new Search(graph, curLoc, goal);
  pathOut pType = RAGS2;
  testSearch.PathSearch(pType);

  // To modify this into D* style search add loop...search after each step 

  delete testSearch;
  return cost;
}
#endif
