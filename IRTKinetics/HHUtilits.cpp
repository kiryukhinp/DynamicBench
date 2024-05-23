#include "HHUtilits.h"
std::vector<Point2D> HHUtilits::ReadRowFromFile(std::string const &  FileName)
{
        std::vector<Point2D> Row;
        std::string Line;
        std::ifstream in(FileName);
        if (in.is_open())
        {        
            while (std::getline(in, Line))
            {
                Row.emplace_back(std::stod(split(Line)[0]), std::stod(split(Line)[1]));
            }
        }
        return Row;

    }