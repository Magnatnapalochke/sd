#include <iostream>
#include "bimary_search_tree.h"
int main(){
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(12);
    tree.insert(7);
    tree.insert(5);
    tree.insert(9);
    tree.insert(11);
    tree.output(std::cout);
    std::cout<< tree.getNumberOfNodes()<<"\n";
    tree.inorderWalkIterative();
    tree.walkByLevels();
}