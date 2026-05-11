#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include "graph.h"
#include "stack.h"

class DirectedGraph : public Graph {
private:
    void fillOrder(int v, Vector<bool>& visited, Stack<int>& finishOrder) const {
        visited[v] = true;
        
        for (size_t i = 0; i < adjList[v].size(); i++) {
            int neighbor = adjList[v].get(i);
            if (!visited[neighbor]) {
                fillOrder(neighbor, visited, finishOrder);
            }
        }
        finishOrder.push(v);
    }
    
    void DFSCollect(int v, Vector<bool>& visited, Vector<int>& component, const DirectedGraph& graph) const {
        visited[v] = true;
        component.push_back(v);
        
        for (size_t i = 0; i < graph.getAdjList(v).size(); i++) {
            int neighbor = graph.getAdjList(v).get(i);
            if (!visited[neighbor]) {
                DFSCollect(neighbor, visited, component, graph);
            }
        }
    }
    
public:
    DirectedGraph() : Graph(true) {}
    
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
        }
    }
    
    void removeEdge(int from, int to) override {
        if (!hasVertex(from) || !hasVertex(to)) {
            throw GraphException("One or both vertices do not exist");
        }
        adjList[from].remove(to);
    }
    
    DirectedGraph getReverseGraph() const {
        DirectedGraph reversed;
        for (int i = 0; i < vertexCount; i++) {
            reversed.addVertex();
        }
        for (int i = 0; i < vertexCount; i++) {
            for (size_t j = 0; j < adjList[i].size(); j++) {
                int neighbor = adjList[i].get(j);
                reversed.addEdge(neighbor, i);
            }
        }
        return reversed;
    }
    
    Vector<Vector<int> > findSCC() const {
        int V = vertexCount;
        Vector<bool> visited(V, false);
        Stack<int> finishOrder;
        
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                fillOrder(i, visited, finishOrder);
            }
        }
        
        DirectedGraph reversed = getReverseGraph();
        
        Vector<bool> visitedReversed(V, false);
        Vector<Vector<int> > sccs;
        
        while (!finishOrder.empty()) {
            int vertex = finishOrder.top();
            finishOrder.pop();
            
            if (!visitedReversed[vertex]) {
                Vector<int> component;
                reversed.DFSCollect(vertex, visitedReversed, component, reversed);
                sccs.push_back(component);
            }
        }
        
        return sccs;
    }
};

#endif // DIRECTED_GRAPH_H