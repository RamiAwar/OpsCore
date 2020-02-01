#pragma once

#include <vector>
#include <iostream>

namespace gs {

	enum class State { Empty, Obstacle };

	class Cell {
	public:
		int row, col;
		Cell(int x, int y) :row(x), col(y) {};
	};
	
	class Grid {

	public:
		Grid(std::vector<std::vector<State>>);
		~Grid(); 

		State& operator() (unsigned row, unsigned col);        // Subscript operators often come in pairs
		State operator() (unsigned row, unsigned col) const;  // Subscript operators often come in pairs

		int getWidth();
		int getHeight();

		static std::string cellToString(State& s) {
			std::string out;
			switch (s) {
				case State::Obstacle:
					out = "#";
					break;
				default:
					out = ".";
			}
			return out;
		}
		
	protected:

		std::vector<std::vector<State>> m_Data;
		int m_Width;
		int m_Height;

	};


	inline std::ostream& operator<<(std::ostream& stream, Grid& grid) {

		for (int i = 0; i < grid.getWidth(); i++) {
			stream << "  |   ";
			for (int j = 0; j < grid.getHeight(); j++) {
				stream << Grid::cellToString(grid(i, j)) << "   ";
			}
			stream << "|" << std::endl;
		}

		return stream;
	}


}




