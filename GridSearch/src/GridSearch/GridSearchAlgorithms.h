#pragma once

#include "Grid.h"
#include <queue>

namespace gs{
    
    class GridSearchAlgorithms
    {
    public:
        
        const enum Neighbors{
            Neighbors4 = 4,
            Neighbors8 = 8
        };
        
        static Grid AStarSearch(Grid& grid, Cell start, Cell goal, float(*heuristic)(int,int,int,int), Neighbors neighbors=Neighbors4);
//        static Grid AStarSearchStepped(Grid& grid, Cell start, Cell goal);
        
        static float h_Manhattan(int x1, int y1, int x2, int y2);
        static float h_Euclidean(int x1, int y1, int x2, int y2);
        static float h_Chebyshev(int x1, int y1, int x2, int y2);
        
    private:
        
        static bool CheckValidCell(Grid& grid, Cell c);
    };
    
}
