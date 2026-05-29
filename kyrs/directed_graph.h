#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include "graph.h"

class DirectedGraph : public Graph {
private:
    // Рекурсивный обход для первого прохода (заполнение стека)
    void fillOrder(int v, Vector<bool>& visited, Stack<int>& finishOrder) const {
        visited[v] = true;
        
        const Vector<int>& neighbors = adjList_[v];
        for (size_t i = 0; i < neighbors.size(); ++i) {
            int neighbor = neighbors[i];
            if (!visited[neighbor]) {
                fillOrder(neighbor, visited, finishOrder);
            }
        }
        finishOrder.push(v);
    }
    
    // Рекурсивный обход для сбора компоненты
    void DFSCollect(int v, Vector<bool>& visited, Vector<int>& component, const DirectedGraph& graph) const {
        visited[v] = true;
        component.push_back(v);
        
        const Vector<int>& neighbors = graph.adjList_[v];
        for (size_t i = 0; i < neighbors.size(); ++i) {
            int neighbor = neighbors[i];
            if (!visited[neighbor]) {
                DFSCollect(neighbor, visited, component, graph);
            }
        }
    }
    
    // Внутренний DFS для обхода (выводит имена)
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
    DirectedGraph() : Graph(true) {}
    
    // Проверка существования ребра
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
    
    // Добавление ребра
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
        
        // Проверяем, не существует ли уже такое ребро
        Vector<int>& neighbors = adjList_[fromIdx];
        for (size_t i = 0; i < neighbors.size(); ++i) {
            if (neighbors[i] == toIdx) return;
        }
        
        neighbors.push_back(toIdx);
    }
    
    // Удаление ребра
    void removeEdge(int from, int to) override {
        int fromIdx = findVertexIndex(from);
        int toIdx = findVertexIndex(to);
        
        if (fromIdx == -1 || toIdx == -1) {
            throw GraphException("Vertex not found");
        }
        
        Vector<int>& neighbors = adjList_[fromIdx];
        for (size_t i = 0; i < neighbors.size(); ++i) {
            if (neighbors[i] == toIdx) {
                neighbors.erase(i);
                return;
            }
        }
    }
    
    // Построение обратного графа
    DirectedGraph getReverseGraph() const {
        DirectedGraph reversed;
        
        // Копируем вершины
        for (size_t i = 0; i < vertices_.size(); ++i) {
            reversed.addVertex(vertices_[i]);
        }
        
        // Добавляем обратные рёбра
        for (size_t i = 0; i < adjList_.size(); ++i) {
            const Vector<int>& neighbors = adjList_[i];
            for (size_t j = 0; j < neighbors.size(); ++j) {
                int fromName = vertices_[neighbors[j]];
                int toName = vertices_[i];
                reversed.addEdge(fromName, toName);
            }
        }
        
        return reversed;
    }
    
    // Поиск сильно связанных компонент (алгоритм Косарайю)
    Vector<Vector<int>> findSCC() const {
        int V = vertexCount_;
        Vector<bool> visited(V, false);
        Stack<int> finishOrder;
        
        // Первый проход: заполняем стек порядком завершения
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                fillOrder(i, visited, finishOrder);
            }
        }
        
        // Получаем обратный граф
        DirectedGraph reversed = getReverseGraph();
        
        // Второй проход: находим компоненты
        Vector<bool> visitedReversed(V, false);
        Vector<Vector<int>> sccs;
        
        while (!finishOrder.empty()) {
            int vertex = finishOrder.top();
            finishOrder.pop();
            
            if (!visitedReversed[vertex]) {
                Vector<int> componentIndices;
                reversed.DFSCollect(vertex, visitedReversed, componentIndices, reversed);
                
                // Переводим индексы в имена вершин
                Vector<int> componentNames;
                for (size_t i = 0; i < componentIndices.size(); ++i) {
                    componentNames.push_back(vertices_[componentIndices[i]]);
                }
                sccs.push_back(componentNames);
            }
        }
        
        return sccs;
    }
    
    // Вывод SCC
    void printSCC() const {
        Vector<Vector<int>> sccs = findSCC();
        std::cout << "Strongly Connected Components (" << sccs.size() << "):" << std::endl;
        for (size_t i = 0; i < sccs.size(); ++i) {
            std::cout << "  Component " << i + 1 << ": ";
            for (size_t j = 0; j < sccs[i].size(); ++j) {
                std::cout << sccs[i][j];
                if (j < sccs[i].size() - 1) std::cout << ", ";
            }
            std::cout << std::endl;
        }
    }
    
    // Обход в глубину для ориентированного графа
    void DFSDirected(int start, std::ostream& out = std::cout) const {
        if (vertexCount_ == 0) {
            throw GraphException("Graph is empty");
        }
        if (!hasVertex(start)) {
            throw GraphException("Start vertex does not exist");
        }
        
        int startIdx = findVertexIndex(start);
        Vector<bool> visited(vertexCount_, false);
        
        out << "DFS (directed) from vertex " << start << ": ";
        DFSVisit(startIdx, visited, out);
        out << std::endl;
    }
};

#endif // DIRECTED_GRAPH_H