#pragma once
#include "Graph.h"
#include "Session_StrProcess.h"

class Session
{
private:
    ComputionalGraph* usingGraph; //session当前绑定的Graph
    std::map<std::string,double> parameterValue;
    std::vector<double> answer; //此session输出过的全部answer
    bool ifRestore; //
public:

    //每个session存储每个session运行的parameter值　
    //图存储建立图时的original_parameterValue
    //如果是新创建的session 则把图中存储的原始值赋值给当前session的parameterValue　同时把图中variable节点的value改为当前session的值　也就是图variable节点的原始值
    //如果是已经创建过的session　则直接把当前session的parameterValue赋值给图中节点
    //做改变时　要更新session的parameterValue　同时改变图中节点的value

    friend Session_StrProcess;

    Session(ComputionalGraph* graph_,bool ifRestore_); //构造函数，参数1为绑定的图，参数2为是否是从文件中读取信息创建


    void saveSession(const std::string& path); //保存session的信息到路径path

    ComputionalGraph* bindingGraph(); //返回此session绑定的图

    void changeParameterValue();//将绑定的图中variable节点的值改为当前session存储的variable节点的值

    void EVAL(std::string& command_node, std::vector<std::string>& DevidedCommand); //EVAL操作
    void SETANSWER(std::vector<std::string>& DevidedCommand); //SETANSWER操作
    void SETCONSTANT(std::vector<std::string>& DevidedCommand); //SETCONSTANT操作


};
