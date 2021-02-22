#pragma once

#include "Shell_StrProcess.h"
#include "Graph.h"
#include "session.h"



class Shell
{
private:
    std::map<std::string,ComputionalGraph*> allGraph;
    std::map<std::string,Session*> allSession;

public:
    friend Shell_StrProcess;


    //添加图
    void addGraph(const std::string& newGraphName); //外部调用接口
    ComputionalGraph* GraphFactory(const std::string& name); //图工厂

    ComputionalGraph* getGraph(const std::string& graphName);//返回名为graphName的图

    //添加Session
    void addSession(const std::string& newSessionName, const std::string& graphName,bool ifRestore); //增加session
    Session* SessionFactory(ComputionalGraph* BindingGraph,bool ifRestore); //session工厂

    //返回名为sessionName的session
    Session* getSession(const std::string& sessionName);

    ~Shell(); //析构函数
};
