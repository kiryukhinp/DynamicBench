#pragma once
#include <iostream>
#include <vector>
#include "Point2D.h"
#include <string>
#include <fstream>
#include "Auxiliary.hpp"


class HHUtilits
{   
public:
    static std::vector<Point2D> ReadRowFromFile(std::string const &  FileName);
    
};