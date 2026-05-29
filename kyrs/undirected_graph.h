#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include "graph.h"

class UndirectedGraph : public Graph {
private:
    void DFSVisit(int v, Vector<bool>& visited, std::ostream& out) const {
        visited[v] = true;
        out << vertices_[v] << " ";
        
        const Vector<int>& neighbors = adjList_[v];
        for (size_t i = 0; i < neighbors.size(); ++i) {
            int neighbor = neighbors[i];
            if (!visited[neighbor]) {
                DFSVisit(neighbor, visited, out);
            }
        }
    }
    
public:
    UndirectedGraph() : Graph(false) {}
    
    bool hasEdge(int from, int to) const override {
        int fromIdx = findVertexIndex(from);
        int toIdx = findVertexIndex(to);
        if (fromIdx == -1 || toIdx == -1) return false;
        
        const Vector<int>& neighbors = adjList_[fromIdx];
        for (size_t i = 0; i < neighbors.size(); ++i) {
            if (neighbors[i] == toIdx) return true;
        }
        return false;
    }
    
    void addEdge(int from, int to) override {
        int fromIdx = findVertexIndex(from);
        int toIdx = findVertexIndex(to);
        
        if (fromIdx == -1) {
            addVertex(from);
            fromIdx = findVertexIndex(from);
        }
        if (toIdx == -1) {
            addVertex(to);
            toIdx = findVertexIndex(to);
        }
        
        // Проверяем, не существует ли уже ребро
        Vector<int>& neighborsFrom = adjList_[fromIdx];
        Vector<int>& neighborsTo = adjList_[toIdx];
        
        for (size_t i = 0; i < neighborsFrom.size(); ++i) {
            if (neighborsFrom[i] == toIdx) return;
        }
        
        // Добавляем в обе стороны
        neighborsFrom.push_back(toIdx);
        neighborsTo.push_back(fromIdx);
    }
    
    void removeEdge(int from, int to) override {
        int fromIdx = findVertexIndex(from);
        int toIdx = findVertexIndex(to);
        
        if (fromIdx == -1 || toIdx == -1) {
            throw GraphException("Vertex not found");
        }
        
        Vector<int>& neighborsFrom = adjList_[fromIdx];
        Vector<int>& neighborsTo = adjList_[toIdx];
        
        for (size_t i = 0; i < neighborsFrom.size(); ++i) {
            if (neighborsFrom[i] == toIdx) {
                neighborsFrom.erase(i);
                break;
            }
        }
        
        for (size_t i = 0; i < neighborsTo.size(); ++i) {
            if (neighborsTo[i] == fromIdx) {
                neighborsTo.erase(i);
                break;
            }
        }
    }
    
    // Обход в глубину для неориентированного графа
    void DFSUndirected(int start, std::ostream& out = std::cout) const {
        if (vertexCount_ == 0) {
            throw GraphException("Graph is empty");
        }
        if (!hasVertex(start)) {
            throw GraphException("Start vertex does not exist");
        }
        
        int startIdx = findVertexIndex(start);
        Vector<bool> visited(vertexCount_, false);
        
        out << "DFS (undirected) from vertex " << start << ": ";
        DFSVisit(startIdx, visited, out);
        out << std::endl;
    }
};

#endif // UNDIRECTED_GRAPH_H