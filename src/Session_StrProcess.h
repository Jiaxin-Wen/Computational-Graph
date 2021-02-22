#pragma once
#include "StrProcess.h"

class Session;

class Session_StrProcess : public StrProcess
{
private:
    Session*& sessionProcessing;

public:
    Session_StrProcess(Session*& session_):sessionProcessing(session_) {}

    /*
    session输入处理：
     EVAL：执行EVAL指令，计算值
     SETANSWER：执行SETANSWER指令，设置值
     SETCONSTANT：执行SETCONSTANT指令，设置值
     close：执行close指令，析构本session
     hangup: 执行hangup执行，暂时挂起本session
    */
    void InputCommand();
};
