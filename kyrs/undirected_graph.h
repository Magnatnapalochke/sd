#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include "graph.h"
#include "stack.h"

class UndirectedGraph : public Graph {
public:
    UndirectedGraph() : Graph(false) {}
    
    bool hasEdge(int from, int to) const override {
        if (!hasVertex(from) || !hasVertex(to)) {
            return false;
        }
        return adjList[from].contains(to);
    }
    
    void addEdge(int from, int to) override {
        if (!hasVertex(from) || !hasVertex(to)) {
            throw GraphException("One or both vertices do not exist");
        }
        if (!hasEdge(from, to)) {
            adjList[from].push_back(to);
            adjList[to].push_back(from);
        }
    }
    
    void removeEdge(int from, int to) override {
        if (!hasVertex(from) || !hasVertex(to)) {
            throw GraphException("One or both vertices do not exist");
        }
        adjList[from].remove(to);
        adjList[to].remove(from);
    }
    
    Vector<Vector<int> > findConnectedComponents() const {
        Vector<bool> visited(vertexCount, false);
        Vector<Vector<int> > components;
        
        for (int i = 0; i < vertexCount; i++) {
            if (!visited[i]) {
                Vector<int> component;
                Stack<int> st;
                st.push(i);
                visited[i] = true;
                
                while (!st.empty()) {
                    int v = st.top();
                    st.pop();
                    component.push_back(v);
                    
                    for (size_t j = 0; j < adjList[v].size(); j++) {
                        int neighbor = adjList[v].get(j);
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            st.push(neighbor);
                        }
                    }
                }
                components.push_back(component);
            }
        }
        
        return components;
    }
};

#endif // UNDIRECTED_GRAPH_H