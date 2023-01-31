// graph.h <Starter Code>
// Mohammed Hisham Moizuddin
//
// Basic graph class using adjacency matrix representation.  Currently
// limited to a graph with at most 100 vertices.
//
// University of Illinois at Chicago
// CS 251: Spring 2021
// Project #7 - Openstreet Maps
//

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

template<typename VertexT, typename WeightT>
class graph {
 private:
    // Map to represent list of edges
    map<VertexT, map<VertexT, WeightT>> edgeList;
  //
  // _LookupVertex
  //
  // Finds the vertex in the Vertices vector and returns it's
  // index position if found, otherwise returns -1.
  //
  int _LookupVertex(VertexT v) const {
    int isFound = -1;
    if (edgeList.count(v) > 0) {
        isFound = 1;
    } else {
        isFound = -1;
    }
    return isFound;
  }

 public:
  //
  // constructor:
  //
  graph() {}

  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
  int NumVertices() const {
    return edgeList.size();
  }

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const {
    int count = 0;
    //
    // loop through the adjacency matrix and count how many
    // edges currently exist:
    //
    for (auto &e : edgeList) {
        count += e.second.size();
    }
    return count;
  }

  //
  // addVertex
  //
  // Adds the vertex v to the graph if there's room, and if so
  // returns true.  If the graph is full, or the vertex already
  // exists in the graph, then false is returned.
  //
  bool addVertex(VertexT v) {
    //
    // is the vertex already in the graph?  If so, we do not
    // insert again otherwise Vertices may fill with duplicates:
    //
    if (_LookupVertex(v) == 1) {
      return false;
    }
    edgeList[v]; // if vertex doesn't exist, we insert it.
    return true;
  }

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist or for some reason the
  // graph is full, false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
  bool addEdge(VertexT from, VertexT to, WeightT weight) {
    if (_LookupVertex(from) == -1 || _LookupVertex(to) == -1) {
        return false;   // not found
    }
    edgeList[from][to] = weight;    // overwriting the weight
    return true;
  }

  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
  bool getWeight(VertexT from, VertexT to, WeightT& weight) const {
    //
    // we need to search the Vertices and find the position
    // of each vertex; this will denote the row and col to
    // access in the adjacency matrix:
    //
    if (_LookupVertex(from) == -1 || _LookupVertex(to) == -1) {
        return false;   // not found
    }
    // for storing 'values' of map type associated with key vertex.
    map<VertexT, WeightT> edges = edgeList.at(from);

    bool isEdge = false; // true if edge exists and false if not
    for (auto &e : edges) {
        if (e.first == to) {
            weight = e.second;  //updates weight if it exists
            isEdge = true;
        }
    }
    return isEdge;
  }

  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  //
  set<VertexT> neighbors(VertexT v) const {
    set<VertexT> S;

    if (_LookupVertex(v) == -1) {
        return S;   // if vertex is not found
    }
    // for storing 'values' of map type associated with key vertex.
    map<VertexT, WeightT> edges = edgeList.at(v);
    for (auto &e : edges) {
        S.insert(e.first);
    }

    return S;
  }

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
  vector<VertexT> getVertices() const {
    vector<VertexT> v;

    for (auto &x : edgeList) {
        v.push_back(x.first);
    }

    return v;
  }

  //
  // dump
  //
  // Dumps the internal state of the graph for debugging purposes.
  //
  // Example:
  //    graph<string,int>  G(26);
  //    ...
  //    G.dump(cout);  // dump to console
  //
  void dump(ostream& output) const {
    int vNum = 0;
    output << "***************************************************" << endl;
    output << "********************* GRAPH ***********************" << endl;

    output << "**Num vertices: " << this->NumVertices() << endl;
    output << "**Num edges: " << this->NumEdges() << endl;

    output << endl;
    output << "**Vertices:" << endl;
    for (auto &v : edgeList) {
        output << " " << vNum << ". " << v.first << endl;
        vNum++;
    }

    output << endl;
    output << "**Edges:" << endl;
    for (auto &v : edgeList) {
        for (auto &e : v.second) {
            output << "(" << v.first << "," << e.first << ","
            << e.second << ") ";
        }
        output << endl;
    }
    output << "**************************************************" << endl;
  }
};
