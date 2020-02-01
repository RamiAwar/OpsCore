#include "Grid.h"
#include <stdexcept>

namespace gs {


	Grid::Grid(std::vector<std::vector<State>> data)
	{
		if (data.size() < 1) throw "Input grid is empty.";
		m_Data = data;
		m_Width = data.size();
		m_Height = data[0].size();
	}

 	Grid::~Grid() {}

	int Grid::getWidth()
	{
		return m_Width;
	}

	int Grid::getHeight()
	{
		return m_Height;
	}

	State& Grid::operator()(unsigned row, unsigned col) {
		if (row >= m_Height || col >= m_Width) throw std::out_of_range("Grid subscript out of bounds");
		return m_Data[row][col];
	}

	State Grid::operator()(unsigned row, unsigned col) const {
		if (row >= m_Height || col >= m_Width) throw std::out_of_range("Grid subscript out of bounds");
		return m_Data[row][col];
	}

}

