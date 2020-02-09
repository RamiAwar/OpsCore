#include "Grid.h"
#include <stdexcept>

namespace gs {
    
    
    /*
     Initialize to empty grid if no input to constructor
     */
    Grid::Grid(){
        m_Data = std::vector<std::vector<State> >();
        m_Width = 0;
        m_Height = 0;
    }
    
    
    /*
     Construct new grid from 2 dimensional state vector data, and set height width
     */
    Grid::Grid(std::vector<std::vector<State> > data)
    {
        if (data.size() < 1) throw "Input grid is empty.";
        m_Data = data;
        m_Height = data.size();
        m_Width = data[0].size();
    }
    
    
    
    /*
     Empty destructor
     */
    Grid::~Grid() {}
    
    
    
    /*
     Check if the inputted indices are in the bounds of the grid
     */
    bool Grid::Contains(int x, int y){ return (x >= 0 && x < m_Height && y >= 0 && y < m_Width);}
    
    
    
    /*
     Override subscripting operator to allow for faster indexing
     */
    State& Grid::operator()(unsigned row, unsigned col) {
        if (row >= m_Height || col >= m_Width) throw std::out_of_range("Grid subscript out of bounds");
        return m_Data[row][col];
    }
    State Grid::operator()(unsigned row, unsigned col) const {
        if (row >= m_Height || col >= m_Width) throw std::out_of_range("Grid subscript out of bounds");
        return m_Data[row][col];
    }
    
}

