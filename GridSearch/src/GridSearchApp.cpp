#include <vector>

#include "GridSearch/Grid.h"
#include "GridSearchAlgorithms.h"


int main(int argc, char** argv) {


	// Read grid from file


	// Create Grid from 2d array
//    std::vector<std::vector<gs::State> > t = {
//                                    {gs::State::Empty, gs::State::Empty, gs::State::Empty},
//                                    {gs::State::Empty, gs::State::Obstacle, gs::State::Empty},
//                                    {gs::State::Empty, gs::State::Obstacle, gs::State::Empty}
//                                };

    std::vector<std::vector<gs::State> > t;
    std::vector<gs::State> q;
    q.push_back(gs::State::Empty);
    q.push_back(gs::State::Empty);
    q.push_back(gs::State::Empty);
    
    t.push_back(q);
    t.push_back(q);
    t.push_back(q);

	gs::Grid grid(t);
    grid(1,1) = gs::State::Obstacle;
    grid(2,1) = gs::State::Obstacle;
    
	std::cout << grid << std::endl;


	// Perform algorithm on grid
    gs::Grid solution = gs::GridSearchAlgorithms::AStarSearch(grid, gs::Cell(0,0), gs::Cell(2,2));
    
	// Output result
    std::cout<<solution<<std::endl;


	return 0;
}
