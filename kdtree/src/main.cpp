#include <iostream>
#include <random>
#include <cmath>
#include "KDnode.h"
#include "KDtree.h"

int main()
{
    KDtree tree = KDtree(2);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(1, 100);

    for (int i = 0; i < 8; i++)
    {
        double x = (int)dis(gen);
        double y = (int)dis(gen);
        KDnode* node = new KDnode(vector<double>{x, y});
        tree.add(node);
    }

    KDnode* node = new KDnode(vector<double>{1.0, 2.0});
    tree.add(node);

    tree.printTree();

    cout << "Searching for node..." << endl;

    if (tree.search(node))
    {
        cout << "Node found!" << endl;
    }
    else
    {
        cout << "Node not found!" << endl;
    }

    KDnode* nodeToFind = new KDnode(vector<double>{2, 7});
    KDnode* nearest = tree.findNearestNeighbor(nodeToFind);
    cout << "Nearest neighbor: ";
    nearest->printNode();
    cout << "Distance: " << sqrt(nearest->distanceSquared(nodeToFind)) << endl;

    // cout << "Removing node..." << endl;
    // tree.remove(node);
    // tree.printTree();
    // if (tree.search(node))
    // {
    //     cout << "Node found!" << endl;
    // }
    // else
    // {
    //     cout << "Node not found!" << endl;
    // }

    return 0;
}
