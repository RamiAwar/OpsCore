#pragma once
#include "Grid.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

namespace gs {
    
    
    class GridSearchIO
    {
    public:
        
        static std::vector<State> ParseLine(std::string line);
        
        static std::vector<std::vector<State> > ReadFromFile(std::string path);
    };
    
}
