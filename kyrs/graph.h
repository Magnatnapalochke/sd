#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"
#include "stack.h"
#include <iostream>
#include <string>
#include <stdexcept>

class GraphException : public std::exception {
private:
    std::string message_;
public:
    GraphException(const std::string& msg) : message_(msg) {}
    const char* what() const noexcept override {
        return message_.c_str();
    }
};

class Graph {
protected:
    Vector<int> vertices_;           // имена вершин
    Vector<Vector<int>> adjList_;    // список смежности (только индексы)
    int vertexCount_;
    bool isDirected_;
    
    // Поиск индекса по имени вершины
    int findVertexIndex(int vertex) const {
        for (size_t i = 0; i < vertices_.size(); ++i) {
            if (vertices_[i] == vertex) return static_cast<int>(i);
        }
        return -1;
    }
    
public:
    Graph(bool directed = true) : vertexCount_(0), isDirected_(directed) {}
    
    virtual ~Graph() {}
    
    bool isEmpty() const {
        return vertexCount_ == 0;
    }
    
    bool hasVertex(int vertex) const {
        return findVertexIndex(vertex) != -1;
    }
    
    int getVertexCount() const {
        return vertexCount_;
    }
    
    const Vector<int>& getVertices() const {
        return vertices_;
    }
    
    int getVertexName(int index) const {
        if (index < 0 || index >= vertexCount_) {
            throw GraphException("Index out of range");
        }
        return vertices_[index];
    }
    
    // Добавление вершины
    void addVertex(int vertex) {
        if (hasVertex(vertex)) return;
        
        vertices_.push_back(vertex);
        adjList_.push_back(Vector<int>());
        vertexCount_++;
    }
    
    // Удаление вершины
    void removeVertex(int vertex) {
        int idx = findVertexIndex(vertex);
        if (idx == -1) {
            throw GraphException("Vertex not found");
        }
        
        // Удаляем все рёбра, ведущие к idx
        for (size_t i = 0; i < adjList_.size(); ++i) {
            Vector<int>& neighbors = adjList_[i];
            for (size_t j = 0; j < neighbors.size();) {
                if (neighbors[j] == idx) {
                    neighbors.erase(j);
                } else {
                    if (neighbors[j] > idx) {
                        neighbors[j]--;
                    }
                    ++j;
                }
            }
        }
        
        // Удаляем вершину
        adjList_.erase(idx);
        vertices_.erase(idx);
        vertexCount_--;
    }
    
    // Виртуальные методы
    virtual bool hasEdge(int from, int to) const = 0;
    virtual void addEdge(int from, int to) = 0;
    virtual void removeEdge(int from, int to) = 0;
    
    // Получение списка соседей вершины
    const Vector<int>& getNeighbors(int vertex) const {
        int idx = findVertexIndex(vertex);
        if (idx == -1) throw GraphException("Vertex not found");
        return adjList_[idx];
    }
    
    // Вывод графа
    virtual void print() const {
        std::cout << "Vertices: ";
        for (size_t i = 0; i < vertices_.size(); ++i) {
            std::cout << vertices_[i] << " ";
        }
        std::cout << std::endl;
        
        for (size_t i = 0; i < vertices_.size(); ++i) {
            std::cout << vertices_[i] << " -> ";
            const Vector<int>& neighbors = adjList_[i];
            for (size_t j = 0; j < neighbors.size(); ++j) {
                std::cout << vertices_[neighbors[j]] << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif // GRAPH_H