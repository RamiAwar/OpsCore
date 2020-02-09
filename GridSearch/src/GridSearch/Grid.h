#pragma once

#include <vector>
#include <iostream>


namespace gs {
    
    enum State { Empty=0, Obstacle=1 , Closed=3, Path=4, Start=5, Goal=6};
    
    class Cell {
    public:
        int x, y;
        Cell(int a, int b) :x(a), y(b) {};
        Cell(){}
    };
    
    
    
    class Node : public Cell {
    public:
        Node(int _x, int _y, int _g, float _h) : Cell(_x, _y) {
            g = _g;
            h = _h;
        }
        
        Node(){}
        
        int g;
        float h;
        
        int parent_id = -1;;
        
    };
    
    class Grid {
        
    public:
        
        Grid();
        Grid(std::vector<std::vector<State> >);
        ~Grid();
        
        State& operator() (unsigned row, unsigned col);        // Subscript operators often come in pairs
        State operator() (unsigned row, unsigned col) const;  // Subscript operators often come in pairs
        
        inline int getWidth() {return m_Width;}
        inline int getHeight() {return m_Height;}
        
        bool Contains(int x, int y); // Checks if indices are in bounds
        
        static std::string CellToString(State& s) {
            std::string out;
            switch (s) {
                case (State::Obstacle):
                    out = "█";
                    break;
                case (State::Closed):
                    out = "░";
                    break;
                case (State::Path):
                    out = '.';
                    break;
                case (State::Start):
                    out = 'S';
                    break;
                case (State::Goal):
                    out = 'G';
                    break;
                default:
                    out = ' ';
            }
            return out;
        }
        
        
    protected:
        
        std::vector<std::vector<State> > m_Data;
        int m_Width;
        int m_Height;
        
    };
    
    
    inline std::ostream& operator<<(std::ostream& stream, Grid& grid) {
        
        for (int i = 0; i < grid.getHeight(); i++) {
            stream << '|';
            for (int j = 0; j < grid.getWidth(); j++) {
                stream << Grid::CellToString(grid(i, j));
            }
            stream << '|' << std::endl;
        }
        
        return stream;
    }
    
    inline bool operator==(const Cell& lhs, const Cell& rhs) {
        return (lhs.x == rhs.x) && (lhs.y == rhs.y);
    }
    
    
}




