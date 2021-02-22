#include "StrProcess.h"


std::vector<std::string> StrProcess::InputDevide()
{
    std::string buffer;
    std::vector<std::string> Devided;
    std::getline(std::cin, buffer);
    std::stringstream ss(buffer);
    std::string tmp;
    while (ss >> tmp)
    {
        Devided.push_back(tmp);
    }

    return Devided;
}
