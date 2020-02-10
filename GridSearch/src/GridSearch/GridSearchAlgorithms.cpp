#include "GridSearchAlgorithms.h"
#include <thread>
#include <chrono>
#include <cmath>

namespace gs{
    
    struct CompareNodes
    {
        bool operator()(Node& n1,Node& n2)
        {
            return n1.g + n1.h > n2.g + n2.h;
        }
    };
    
    /*
     Calculate the manhattan distance between two points
     */
    float GridSearchAlgorithms::h_Manhattan(int x1, int y1, int x2, int y2){
        return abs(x1-x2)+abs(y1-y2);
    }
    
    float GridSearchAlgorithms::h_Euclidean(int x1, int y1, int x2, int y2){
        float c = std::sqrt(std::pow(x1-x2, 2)+std::pow(y1-y2, 2));
//        std::cout<<c<<std::endl;
        return c;
    }
    
    float GridSearchAlgorithms::h_Chebyshev(int x1, int y1, int x2, int y2){
        return max(abs(x1-x2), abs(y1-y2));
    }
    /*
     Check that a valid cell is empty for exploration
     */
    inline bool GridSearchAlgorithms::CheckValidCell(Grid& grid, Cell c) {
        if (grid.Contains(c.x, c.y)) return grid(c.x, c.y) == State::Empty;
        return false;
    }
    
    
    /*
     A* search algorithm implementation
     */
    Grid GridSearchAlgorithms::AStarSearch(Grid& grid, Cell start, Cell goal, float(*heuristic)(int,int,int,int), Neighbors neighbors) {
        
        // directional deltas
        const int delta[8][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1} };
        
        
        std::priority_queue<Node, std::vector<Node>, CompareNodes> openNodes;
        std::vector<Node> path;
        
        // Start node
        Node n(start.x, start.y, 0, heuristic(0, 0, goal.x, goal.y));
        openNodes.push(n);
        grid(n.x, n.y) = State::Closed;

        
        std::vector<Node> closedNodes;
        int closedNodeCounter = -1;
        int num_passes = 0;
        
        // Main loop
        while (!openNodes.empty()) {
            
            // Retrieve smallest queue value
            Node node = openNodes.top();
            openNodes.pop();


            // Add node to path
            closedNodes.push_back(node);
            closedNodeCounter++;
            
            
            
//            system("clear");
//            std::cout<<grid<<std::endl;
//            std::this_thread::sleep_for(std::chrono::milliseconds(2));
            
            // Check if goal reached
            if (node == goal) {
                
                std::cout << "Goal reached" << std::endl;
                std::cout<<"Nodes checked: "<<num_passes<<std::endl;
              
                // Construct path
                Node m = node;
                
                while(m.parent_id != -1){
//                    std::cout<<m.x<<","<<m.y<<":"<<m.parent_id<<std::endl;
                    grid(m.x, m.y) = State::Path;
                    m = closedNodes[m.parent_id];
                }
                
                closedNodes.clear();
                openNodes =  std::priority_queue<Node, std::vector<Node>, CompareNodes>();
                
                grid(goal.x, goal.y) = State::Goal;
//                grid(36, 21) = State::Path;
//                grid(37, 21) = State::Goal;
                grid(start.x, start.y) = State::Start;
                
                return grid;
            }
            
            // Else expand search to neighbors
            
            for (int i = 0; i < neighbors; i++) {
                
                if (CheckValidCell(grid, Cell(node.x + delta[i][0], node.y + delta[i][1]))){
                    
                    num_passes++;
                    
                    Node m(node.x + delta[i][0],
                           node.y + delta[i][1],
                           node.g + 1,
                           heuristic(node.x + delta[i][0], node.y + delta[i][1], goal.x, goal.y)
                           );
                    grid(m.x, m.y) = State::Closed;
                    m.parent_id = closedNodeCounter;
                    openNodes.push(m);
                }
            }
            
            
            
        }
        
        std::cout<<"No path found."<<std::endl;
        grid(goal.x, goal.y) = State::Goal;
        grid(start.x, start.y) = State::Start;
        return grid;
    }
    

}
