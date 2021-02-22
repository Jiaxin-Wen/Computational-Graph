#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <sstream>




class StrProcess
{
public:
    static std::vector<std::string> InputDevide();
    virtual void InputCommand() = 0;
};



