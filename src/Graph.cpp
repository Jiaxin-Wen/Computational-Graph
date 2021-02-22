#include "Graph.h"

//计算图类，实现计算图整体的相关操作

Node* ComputionalGraph::getNode(const std::string& NodeName)
{
    return NodeMap[NodeName];
}


std::map<std::string, double>& ComputionalGraph::get_original_parameterValue()
{
    return original_parameterValue;
}


Node* ComputionalGraph::leavesFactory(char type,std::string& NewName)
{
    switch (type)
    {
    case 'P':
    {
        return new Placeholder(NewName);
        break;
    }
    case 'C':
    {
        double value;
        std::cin >> value;
        return new Constant(NewName,value);
        break;
    }
    case 'V':
    {
        double value;
        std::cin >> value;
        original_parameterValue.insert(make_pair(NewName,value)); //记录variable节点的原始值
        return new Variable(NewName,value);
        break;
    }
    default:
    {
        std::cout << "leavesFactory ERROR: undefined type.\n";
        return nullptr;
    }
    }
}

Node * ComputionalGraph::operationsFactory( std::vector<std::string> DevidedCommand )
{
    std::vector<Node*>father;
    std::string optr;
    for(int i=2 ; i < DevidedCommand.size() ; i++)
    {
        Function* optr_judge; //判定
        if(optr_judge->isEffectiveOptr(DevidedCommand[i]))
            optr=DevidedCommand[i];
        else
            father.push_back(NodeMap[DevidedCommand[i]]);
    }
    return new FnNode(DevidedCommand[0],optr,father);
}


ComputionalGraph::~ComputionalGraph()
{
    for( auto it : NodeMap) //析构全部节点
    {
        delete it.second;
    }
}

