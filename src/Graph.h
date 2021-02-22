#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include "Node.h"
#include "FnNode.h"
#include "Graph_StrProcess.h"



class ComputionalGraph
{
protected:
 
    std::map<std::string, Node *> NodeMap; //存储图中所有节点
    std::map<std::string, double> original_parameterValue; //存储所有variable节点建图时设置的初始值

public:
    friend Graph_StrProcess;

    //释放内存空间
    ~ComputionalGraph();

    std::map<std::string, double>& get_original_parameterValue();//返回original_parameterValue,用于初始化新建立的session

    Node* getNode(const std::string& NodeName); //返回名为NodeName的node

    //创建P,C,V类型节点
    Node * leavesFactory(char,std::string&);
    //创建Operations节点
    Node * operationsFactory(std::vector<std::string> DevidedCommand);
};
