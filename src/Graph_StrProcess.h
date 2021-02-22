#pragma once

#include "StrProcess.h"

class ComputionalGraph;

class Graph_StrProcess : public StrProcess
{
private:
    ComputionalGraph* graphProcessing;//绑定的计算图

public:
    Graph_StrProcess(ComputionalGraph* graph_):graphProcessing(graph_) {} 

    void InputCommand();//InputCommand重载

    // P,C,V 节点创建
    void InputNumber();

    //　Operation节点创建
    void InputOperation();
};
