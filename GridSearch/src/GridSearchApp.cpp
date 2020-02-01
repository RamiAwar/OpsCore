#include <vector>

#include "GridSearch\Grid.h"



int main(int argc, char** argv) {


	// Read grid from file


	// Create Grid from 2d array
	std::vector<std::vector<gs::State>> t = { 
									{gs::State::Empty, gs::State::Empty, gs::State::Empty}, 
									{gs::State::Empty, gs::State::Obstacle, gs::State::Empty}, 
									{gs::State::Empty, gs::State::Obstacle, gs::State::Empty}
								};


	gs::Grid grid(t);
	std::cout << grid << std::endl;


	// Perform algorithm on grid


	// Output result
	


	return 0;
}