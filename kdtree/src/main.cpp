#include <iostream>
#include <random>
#include <cmath>
#include "KDnode.h"
#include "KDtree.h"

int main()
{
    // Create a vector of KDnode objects with 2D points
    vector<KDnode> points = {
        KDnode(vector<double>{30, 40}),
        KDnode(vector<double>{5, 25}),
        KDnode(vector<double>{70, 70}),
        KDnode(vector<double>{10, 12}),
        KDnode(vector<double>{50, 30}),
        KDnode(vector<double>{35, 45})
    };
    
    // Initialize a KDtree with 2 dimensions
    KDtree tree = KDtree(2);

    // Add points to the KDtree
    tree.add(&points[0]);
    tree.add(&points[1]);
    tree.add(&points[2]);
    tree.add(&points[3]);
    tree.add(&points[4]);
    tree.add(&points[5]);

    // Print the initial tree structure
    cout << "Initial tree : " << endl;
    tree.printTree();
    cout << endl;

    // Add a new node to the tree
    KDnode* node = new KDnode(vector<double>{1.0, 2.0});
    tree.add(node);
    cout << "Adding node : ";
    node->printNode();
    cout << endl;
    cout << "Tree after adding node : ";
    cout << endl;

    // Print the tree after adding the new node
    tree.printTree();
    cout << endl;

    // Search for the newly added node in the tree
    cout << "Searching for node :";
    node->printNode();
    cout << endl;

    if (tree.search(node))
    {
        cout << "Node found in the tree!" << endl;
    }
    else
    {
        cout << "Node not found in the tree!" << endl;
    }

    // Find the nearest neighbor of a given node
    KDnode* nodeToFind = new KDnode(vector<double>{2, 7});
    KDnode* nearest = tree.findNearestNeighbor(nodeToFind);
    cout << "Nearest neighbor of : ";
    nodeToFind->printNode();
    cout << " is : ";
    nearest->printNode();
    cout << endl;
    cout << "Distance: " << sqrt(nearest->distanceSquared(nodeToFind)) << endl;

    // Remove a node from the tree
    KDnode* nodeToRemove = new KDnode(vector<double>{30, 40});
    cout << "Removing node :";
    nodeToRemove->printNode();
    cout << endl;
    tree.remove(nodeToRemove);
    cout << "Tree after removing node : " << endl;
    tree.printTree();
    cout << endl;

    // Search for the removed node in the tree
    cout << "Searching for node :";
    nodeToRemove->printNode();
    cout << endl;
    if (tree.search(nodeToRemove))
    {
        cout << "Node found in the tree!" << endl;
    }
    else
    {
        cout << "Node not found in the tree!" << endl;
    }

    cout << endl;

    // Create a new KDtree and populate it with random nodes
    KDtree tree2 = KDtree(2);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(1, 100);

    for (int i = 0; i < 15; i++)
    {
        double x = (int)dis(gen);
        double y = (int)dis(gen);
        KDnode* node = new KDnode(vector<double>{x, y});
        tree2.add(node);
    }

    // Print the structure of the randomly created tree
    cout << "Creation of a random tree : " << endl;
    tree2.printTree();

    return 0;
}
