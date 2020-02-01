#include "GridSearchAlgorithms.h"

namespace gs{
    
    struct CompareNodes
    {
        bool operator()(Node& n1,Node& n2)
        {
            return n1.getG() + n1.getH() < n2.getG() + n2.getH();
        }
    };
    
    int GridSearchAlgorithms::h_Manhattan(int x1, int y1, int x2, int y2){
        return abs(x1-x2)+abs(y1-y2);
    }
    
    Grid GridSearchAlgorithms::AStarSearch(Grid& grid, Cell start, Cell goal) {

        std::priority_queue<Node, std::vector<Node>, CompareNodes> openNodes;
        
        // Start node
        Node n(0, 0, 0, h_Manhattan(0, 0, goal.x, goal.y));
        openNodes.push(n);
        grid(n.getX(), n.getY()) = State::Closed;
        
        std::cout<<"No path found."<<std::endl;
        return grid;
    }

}
