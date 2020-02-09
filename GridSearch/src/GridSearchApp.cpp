#include <vector>

#include "GridSearch/Grid.h"
#include "GridSearchAlgorithms.h"
#include "GridSearch/GridSearchIO.h"

int main(int argc, char** argv) {


    // Read grid from file
    std::vector<std::vector<gs::State> > t = gs::GridSearchIO::ReadFromFile("gridA.txt");
    
    
    gs::Grid grid(t);
    
	std::cout << grid << std::endl;
    
    // Perform algorithm on grid
    gs::Grid solution = gs::GridSearchAlgorithms::AStarSearch(grid, gs::Cell(1,1), gs::Cell(40,50),
                                                              gs::GridSearchAlgorithms::h_Chebyshev,
                                                              gs::GridSearchAlgorithms::Neighbors4
                                                              );

	// Output result
    std::cout<<solution<<std::endl;

    std::cin.get();
	return 0;
}
