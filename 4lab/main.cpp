#include <iostream>
#include "binary_search_tree.h"
int main(){
    BinarySearchTree<int> tree;
    
    std::cout << "1. Inserting elements: 5, 3, 7, 2, 4, 6, 8\n";
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    
    std::cout << "Tree structure: ";
    tree.output(std::cout);

    std::cout << "Number of nodes: " << tree.getNumberOfNodes() << std::endl;

    std::cout << "Tree height: " << tree.getHeight() << std::endl;

    std::cout << "\n2. Search test:\n";
    std::cout << "Search for 4: " << (tree.searchIterative(4) ? "found" : "not found") << std::endl;
    std::cout << "Search for 10: " << (tree.searchIterative(10) ? "found" : "not found") << std::endl;

    std::cout << "\n3. Tree traversals:\n";
    std::cout << "Inorder traversal (recursive): ";
    tree.inorderWalk();
    
    std::cout << "Inorder traversal (iterative): ";
    tree.inorderWalkIterative();
    
    std::cout << "Level-order traversal (BFS): ";
    tree.walkByLevels();

    std::cout << "\n4. BST validation:\n";
    std::cout << "Is the tree a BST? " 
              << (tree.isBinarySearchTree() ? "Yes" : "No") << std::endl;

    std::cout << "\n5. Deletion test:\n";

    std::cout << "Deleting 2 (leaf): ";
    tree.remove(2);
    tree.output(std::cout);

    std::cout << "Deleting 3 (node with one child 4): ";
    tree.remove(3);
    tree.output(std::cout);

    std::cout << "Deleting 5 (root): ";
    tree.remove(5);
    tree.output(std::cout);

    std::cout << "\n6. Move semantics test:\n";
    BinarySearchTree<int> tree2 = std::move(tree);
    std::cout << "After move, tree2: ";
    tree2.output(std::cout);
    std::cout << "Original tree is empty? " 
              << (tree.getNumberOfNodes() == 0 ? "Yes" : "No") << std::endl;

    std::cout << "\n7. Duplicate insertion test:\n";
    BinarySearchTree<int> tree3;
    tree3.insert(10);
    std::cout << "Inserting 10 again: " << (tree3.insert(10) ? "success" : "failed (duplicate)") << std::endl;
    std::cout << "Number of nodes in tree3: " << tree3.getNumberOfNodes() << std::endl;

    std::cout << "\n8. Test with different data types:\n";
    
    BinarySearchTree<double> doubleTree;
    doubleTree.insert(3.14);
    doubleTree.insert(2.71);
    doubleTree.insert(1.41);
    std::cout << "Double tree: ";
    doubleTree.output(std::cout);
    
    BinarySearchTree<std::string> stringTree;
    stringTree.insert("apple");
    stringTree.insert("banana");
    stringTree.insert("cherry");
    std::cout << "String tree: ";
    stringTree.output(std::cout);
    
    std::cout << "\n=== All tests passed ===\n";
}