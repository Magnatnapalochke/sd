#include <iostream>
#include "directed_graph.h"
#include "undirected_graph.h"

void printSCC(const Vector<Vector<int> >& sccs) {
    std::cout << "Strongly Connected Components:\n";
    for (size_t i = 0; i < sccs.size(); i++) {
        std::cout << "Component " << i + 1 << ": ";
        for (size_t j = 0; j < sccs[i].size(); j++) {
            std::cout << sccs[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void printComponents(const Vector<Vector<int> >& components) {
    std::cout << "Connected Components:\n";
    for (size_t i = 0; i < components.size(); i++) {
        std::cout << "Component " << i + 1 << ": ";
        for (size_t j = 0; j < components[i].size(); j++) {
            std::cout << components[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    try {
        std::cout << "=== Graph Operations Demo ===\n\n";
        
        // ========== DIRECTED GRAPH ==========
        std::cout << "1. Directed Graph:\n";
        DirectedGraph digraph;
        
        // Add vertices (0-5)
        for (int i = 0; i < 6; i++) {
            digraph.addVertex();
        }
        
        // Add edges
        digraph.addEdge(0, 1);
        digraph.addEdge(0, 2);
        digraph.addEdge(1, 3);
        digraph.addEdge(2, 3);
        digraph.addEdge(3, 4);
        digraph.addEdge(4, 0);
        digraph.addEdge(4, 5);
        
        // Basic operations check
        std::cout << "Is graph empty? " << (digraph.isEmpty() ? "Yes" : "No") << std::endl;
        std::cout << "Does vertex 3 exist? " << (digraph.hasVertex(3) ? "Yes" : "No") << std::endl;
        std::cout << "Does edge (4,5) exist? " << (digraph.hasEdge(4, 5) ? "Yes" : "No") << std::endl;
        
        // Depth-First Search
        digraph.DFS(0);
        
        // Find Strongly Connected Components
        Vector<Vector<int> > sccs = digraph.findSCC();
        printSCC(sccs);
        
        // Remove vertex
        std::cout << "Now vertices count: " << digraph.getVertexCount() << std::endl;
        std::cout << "\nRemoving vertex 5:\n";
        digraph.removeVertex(5);
        std::cout << "Now vertices count: " << digraph.getVertexCount() << std::endl;
        
        std::cout << "\n----------------------------------------\n";
        
        // ========== UNDIRECTED GRAPH ==========
        std::cout << "\n2. Undirected Graph:\n";
        UndirectedGraph undigraph;
        
        for (int i = 0; i < 5; i++) {
            undigraph.addVertex();
        }
        
        undigraph.addEdge(0, 1);
        undigraph.addEdge(0, 2);
        undigraph.addEdge(1, 3);
        undigraph.addEdge(2, 3);
        undigraph.addEdge(3, 4);
        
        std::cout << "Is graph empty? " << (undigraph.isEmpty() ? "Yes" : "No") << std::endl;
        std::cout << "Does edge (0,2) exist? " << (undigraph.hasEdge(0, 2) ? "Yes" : "No") << std::endl;
        std::cout << "Does edge (2,0) exist? " << (undigraph.hasEdge(2, 0) ? "Yes" : "No") << std::endl;
        
        // Depth-First Search
        undigraph.DFS(0);
        
        // Find Connected Components
        Vector<Vector<int> > components = undigraph.findConnectedComponents();
        printComponents(components);
        
        // ========== EXCEPTION HANDLING ==========
        std::cout << "\n3. Exception Handling:\n";
        try {
            undigraph.addEdge(10, 20);
        } catch (const GraphException& e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
        
        try {
            undigraph.removeVertex(100);
        } catch (const GraphException& e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
        
    } catch (const GraphException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}