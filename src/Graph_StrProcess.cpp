#include "Graph_StrProcess.h"
#include "Graph.h"


void::Graph_StrProcess::InputCommand()
{
    InputNumber();
    InputOperation();
}

//P,C,V节点创建
void Graph_StrProcess::InputNumber()
{
    int number_num;
    std::cin >> number_num;
    for (int i = 0; i < number_num; i++)
    {
        std::string NewName;
        std::cin >> NewName;
        char type;
        std::cin >> type;
        //按类型动态分配内存空间将之存入NodeMap
        Node *NewPointer=graphProcessing->leavesFactory(type,NewName);//leavesFactory(type,NewName);
        graphProcessing->NodeMap.insert(std::make_pair(NewName,NewPointer));//NodeMap.insert(std::make_pair(NewName, NewPointer));
    }

}

//　Operation节点创建　输入格式与之前相同
void Graph_StrProcess::InputOperation()
{
    int operation_num;
    std::cin >> operation_num;
    std::string buffer;
    std::getline(std::cin, buffer); //输入\n
    for (int i = 0; i < operation_num; i++)
    {
        //将整行命令拆解到vector中
        std::vector<std::string> DevidedCommand = StrProcess::InputDevide();
        Node *NewPointer=graphProcessing->operationsFactory(DevidedCommand);//根据输入创建新节点

        //在NodeMap中添加新创建的节点，对同名节点进行覆盖处理
        auto it = graphProcessing->NodeMap.find(DevidedCommand[0]);
        if ( it == graphProcessing->NodeMap.end())
        {
            graphProcessing->NodeMap.insert(std::make_pair(DevidedCommand[0], NewPointer));
        }
        else
        {
            graphProcessing->NodeMap.erase(it);
            graphProcessing->NodeMap.insert(std::make_pair(DevidedCommand[0], NewPointer));
        }

    }
}
