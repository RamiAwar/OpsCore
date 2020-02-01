#pragma once

#include "Grid.h"
#include <queue>

namespace gs{
    
    class Node{
    public:
        Node(int x, int y, int g, int h){
            values[0] = x;
            values[1] = y;
            values[2] = g;
            values[3] = h;
        }
        
        //TODO: Remove?
        inline int getX(){return values[0];}
        inline int getY(){return values[1];}
        inline int getG(){return values[2];}
        inline int getH(){return values[3];}
        
    private:
        int values[4];
    };

	class GridSearchAlgorithms
	{
    public:
        static Grid AStarSearch(Grid& grid, Cell start, Cell goal);
        
    private:
        
        static int h_Manhattan(int x1, int y1, int x2, int y2);
        
	};

}
