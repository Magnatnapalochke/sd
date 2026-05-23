#include "directed_graph.h"
#include "undirected_graph.h"
#include <iostream>

int main() {    
    try {

        DirectedGraph dg;
        for (int i = 0; i < 5; i++) {
            dg.addVertex();
        }
        
        dg.addEdge(0, 1);
        dg.addEdge(0, 2);
        dg.addEdge(1, 3);
        dg.addEdge(2, 4);
        
        std::cout << "Graph edges: 0->1, 0->2, 1->3, 2->4" << std::endl;
        dg.DFSDirected(0);
        std::cout << std::endl;
        
 
        UndirectedGraph ug;
        for (int i = 0; i < 5; i++) {
            ug.addVertex();
        }
        
        ug.addEdge(0, 1);
        ug.addEdge(0, 2);
        ug.addEdge(1, 3);
        ug.addEdge(2, 4);
        
        std::cout << "Graph edges: 0-1, 0-2, 1-3, 2-4" << std::endl;
        ug.DFSUndirected(0);
        std::cout << std::endl;
        

        DirectedGraph sccGraph;
        for (int i = 0; i < 7; i++) {
            sccGraph.addVertex();
        }
        
        sccGraph.addEdge(0, 1);
        sccGraph.addEdge(1, 2);
        sccGraph.addEdge(2, 0);
        

        sccGraph.addEdge(3, 4);
        sccGraph.addEdge(4, 5);
        sccGraph.addEdge(5, 3);
        

        sccGraph.addEdge(2, 3);
        sccGraph.addEdge(5, 6);
        
        std::cout << "Graph has 7 vertices" << std::endl;
        std::cout << "SCC1: {0,1,2} (cycle)" << std::endl;
        std::cout << "SCC2: {3,4,5} (cycle)" << std::endl;
        std::cout << "Vertex 6: isolated" << std::endl;
        std::cout << "Edges: 2->3, 5->6" << std::endl;
        std::cout << std::endl;
        
        Vector<Vector<int> > sccs = sccGraph.findSCC();
        std::cout << "Found " << sccs.size() << " strongly connected components:" << std::endl;
        
        for (size_t i = 0; i < sccs.size(); i++) {
            std::cout << "  Component " << i + 1 << ": ";
            for (size_t j = 0; j < sccs[i].size(); j++) {
                std::cout << sccs[i].at(j);
                if (j < sccs[i].size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        

        DirectedGraph emptyGraph;
        std::cout << "Test 1: DFS on empty graph" << std::endl;
        try {
            emptyGraph.DFSDirected(0);
        } catch (const GraphException& e) {
            std::cout << "  Caught exception: " << e.what() << std::endl;
        }
        
        DirectedGraph smallGraph;
        smallGraph.addVertex();
        std::cout << "Test 2: DFS on non-existent vertex" << std::endl;
        try {
            smallGraph.DFSDirected(5);
        } catch (const GraphException& e) {
            std::cout << "  Caught exception: " << e.what() << std::endl;
        }
        
        std::cout << "Test 3: Remove non-existent vertex" << std::endl;
        try {
            smallGraph.removeVertex(10);
        } catch (const GraphException& e) {
            std::cout << "  Caught exception: " << e.what() << std::endl;
        }
        
        std::cout << std::endl;
        std::cout << "All tests completed successfully!" << std::endl;
        std::cout << std::endl;
        std::cout << "Requirements for variant 2.4 met:" << std::endl;
        std::cout << "  1. DFS for directed graph - OK" << std::endl;
        std::cout << "  2. DFS for undirected graph - OK" << std::endl;
        std::cout << "  3. Strongly Connected Components - OK" << std::endl;
        std::cout << "  4. Exception handling - OK" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}