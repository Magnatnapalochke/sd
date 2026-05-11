#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"
#include "list.h"
#include <iostream>
#include <string>
#include <stdexcept>

class GraphException : public std::exception {
private:
    std::string message;
public:
    GraphException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Абстрактный базовый класс
class Graph {
protected:
    Vector<List<int> > adjList;
    bool isDirected;
    int vertexCount;
    
    void DFSVisit(int v, Vector<bool>& visited, std::ostream& out) const {
        visited[v] = true;
        out << v << " ";
        
        for (size_t i = 0; i < adjList[v].size(); i++) {
            int neighbor = adjList[v].get(i);
            if (!visited[neighbor]) {
                DFSVisit(neighbor, visited, out);
            }
        }
    }
    
public:
    Graph(bool directed = true) : isDirected(directed), vertexCount(0) {}
    
    virtual ~Graph() {}
    
    // Чисто виртуальные методы
    virtual bool hasEdge(int from, int to) const = 0;
    virtual void addEdge(int from, int to) = 0;
    virtual void removeEdge(int from, int to) = 0;
    
    // Виртуальные методы с реализацией
    virtual void addVertex() {
        adjList.push_back(List<int>());
        vertexCount++;
    }
    
    virtual void removeVertex(int v) {
    if (!hasVertex(v)) {
        throw GraphException("Vertex does not exist");
    }
    
    // 1. Удаляем все рёбра, ведущие к v
    for (int i = 0; i < vertexCount; i++) {
        adjList[i].remove(v);
    }
    
    // 2. Удаляем список смежности вершины v
    adjList.erase(v);
    
    // 3. ОБНОВЛЯЕМ ИНДЕКСЫ! (важно!)
    for (int i = v; i < vertexCount - 1; i++) {
        // Создаём новый список с обновлёнными индексами
        List<int> newList;
        for (size_t j = 0; j < adjList[i].size(); j++) {
            int neighbor = adjList[i].get(j);
            if (neighbor > v) {
                newList.push_back(neighbor - 1);
            } else {
                newList.push_back(neighbor);
            }
        }
        adjList[i] = newList;
    }
    
    vertexCount--;
    }
    
    virtual void DFS(int start, std::ostream& out = std::cout) const {
        if (!hasVertex(start)) {
            throw GraphException("Start vertex does not exist");
        }
        
        Vector<bool> visited(vertexCount, false);
        out << "DFS starting from vertex " << start << ": ";
        DFSVisit(start, visited, out);
        out << std::endl;
    }
    
    // Общие методы
    bool isEmpty() const {
        return vertexCount == 0;
    }
    
    bool hasVertex(int v) const {
        return v >= 0 && v < vertexCount;
    }
    
    int getVertexCount() const {
        return vertexCount;
    }
    
    const List<int>& getAdjList(int v) const {
        if (!hasVertex(v)) {
            throw GraphException("Vertex does not exist");
        }
        return adjList[v];
    }
    
    bool isGraphDirected() const {
        return isDirected;
    }
};

#endif // GRAPH_H