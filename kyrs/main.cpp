#include "directed_graph.h"
#include "undirected_graph.h"
#include <iostream>

int main() {
    std::cout << "========== DIRECTED GRAPH ==========" << std::endl;
    
    DirectedGraph dg;
    
    dg.addVertex(5);
    dg.addVertex(10);
    dg.addVertex(20);
    dg.addVertex(100);
    dg.addVertex(1);
    
    dg.addEdge(5, 10);
    dg.addEdge(5, 20);
    dg.addEdge(10, 100);
    dg.addEdge(100, 5);
    dg.addEdge(1, 5);
    
    dg.print();
    
    std::cout << std::endl;
    dg.DFSDirected(5);
    
    std::cout << std::endl;
    dg.printSCC();
    
    std::cout << std::endl;
    std::cout << "========== UNDIRECTED GRAPH ==========" << std::endl;
    
    UndirectedGraph ug;
    
    ug.addVertex(5);
    ug.addVertex(10);
    ug.addVertex(20);
    ug.addVertex(1);
    
    ug.addEdge(5, 10);
    ug.addEdge(5, 20);
    ug.addEdge(10, 1);
    
    ug.print();
    
    std::cout << std::endl;
    ug.DFSUndirected(5);
    
    return 0;
}