#include "Session_StrProcess.h"
#include "session.h"

void Session_StrProcess::InputCommand()
{
    while(1)
    {
        std::vector<std::string> DevidedCommand = InputDevide();
        std::string command_type = DevidedCommand[0];
        if (command_type == "EVAL")
        {
            sessionProcessing->EVAL(DevidedCommand[1],DevidedCommand);
        }
        else if (command_type == "SETCONSTANT")
        {
            sessionProcessing->SETCONSTANT(DevidedCommand);
        }
        else if (command_type == "SETANSWER")
        {
            sessionProcessing->SETANSWER(DevidedCommand);
        }
        else if (command_type == "close")
        {
            std::cout<<"析构session"<<std::endl;
            delete sessionProcessing;
            sessionProcessing = nullptr;
            return ;
        }
        else if (command_type == "hangup")  //暂时结束　挂起此session
        {
            std::cout<<"挂起session"<<std::endl;
            return ;
        }
    }
}
