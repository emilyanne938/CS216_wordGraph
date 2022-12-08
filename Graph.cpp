/*
 * File: Graph.cpp
 * Course: CS216
 * Project: Project 3 
 * Purpose: Declaration of Graph class
 *          This class represents an undirected Graph (no weight on each edge)
 *          using adjacent map representation
 *          It contains one private data memeber: adjMap
 *          which represents the mapping from a Vertex, say u (key) to a set of vertices (value) which directly connect to u 
 * 
 * **Class was fully defined by me based on the .h file provided for me. 
 */
#ifndef GRAPH_CPP
#define GRAPH_CPP

#include <iostream>
#include <queue>
#include <map>
#include <set>
#include "Graph.h"
 
using namespace std;

template <typename T>
// default constructor
Graph<T>::Graph()
{
}

// to check if an edge exists between v and w
template <typename T>
bool Graph<T>::hasEdge(T v, T w) const
{
    if (adjMap.find(v) == adjMap.end())
        return false;
  
    if (adjMap.at(v).find(w) != adjMap.at(v).end())
        return true;
    else 
        return false;
}

// to add an edge beween v and w to the graph
template <typename T>
void Graph<T>::addEdge(T v, T w)
{
    adjMap[v].insert(w);
    //you needed to insert again
    adjMap[w].insert(v);
}

// Apply BFS traversal to find the shortest path from the given source s to destination t
// return the distnace from s to t
// if s or t does not exist, return INVALID_VERTEX (=-2) 
// if there is no path from s to t, return NOPATH (=-1)
// store the shortest path distance from the given source s  to vertex w in distance map<w, distance>
// store which next vertex to go through on the shortest path to the given source s in go_through map<w, v>. 
// Here a pair <w, v> in go_through map represents on the shortest path from w to the given source s, it needs to take the path: w-->v...-->s  
template <typename T>
int Graph<T>::BFS(T s, T t, map<T, int>& distance, map<T, T>& go_through) const
{
    

//1. check if the source of destination
    if ((adjMap.find(s) == adjMap.end()) || (adjMap.find(t) == adjMap.end())) {
        return INVALID_VERTEX; 
    }   

//2. mark all of the vertices with current distance to s: -1 or NOPATH using for loop 
    for(auto it = adjMap.begin(); it != adjMap.end(); it++) {
        distance[it->first] = NOPATH;
    }

//3. create a queue for BFS
    queue<T> bfsQueue;
    distance[s] = 0;
    go_through[s] = s;
    bfsQueue.push(s);
    T current = s;
    
    while (!bfsQueue.empty() && current != t) {
        current = bfsQueue.front();
        bfsQueue.pop();

        auto setindex = adjMap.find(current);
	auto set = setindex->second;

        for (auto i = set.begin(); i != set.end(); i++) {
            if (distance[*i] == -1) {
                distance[*i] = distance[current]+1;
                go_through[*i] = current;
                bfsQueue.push(*i);
            }
        }
    }    

    return distance[t];
}
#endif  /* SORTINGLIST_CPP */
