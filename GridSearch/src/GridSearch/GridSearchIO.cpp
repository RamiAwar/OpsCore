#include "GridSearchIO.h"


namespace gs {
    
    std::vector<State> gs::GridSearchIO::ParseLine(std::string line)
    {
        std::istringstream sline(line);
        int n;
        char c;
        std::vector<State> row;
        while (sline >> n >> c && c == ',') {
            
            if (n == 0) {
                row.push_back(State::Empty);
            }
            else if(n == 1){
                row.push_back(State::Obstacle);
            }
        }
        
        return row;
    }
    
    std::vector<std::vector<State> > gs::GridSearchIO::ReadFromFile(std::string path)
    {
        std::ifstream file(path);
        if (file.is_open())
        {
            //  Comment out these lines when program is working the way you want.
            std::cout << "\n File " << path << " is open" << std::endl;
        }
        else
        {
            std::cout << "\n File " << path << " could not open" << std::endl;
            exit(1);
        }
        
        std::vector<std::vector<State> > board;
        if (file) {
            std::string line;
            while (std::getline(file, line)) {
                std::vector<State> row = ParseLine(line);
                board.push_back(row);
            }
        }
        
        file.close();
        
        return board;
    }
}
