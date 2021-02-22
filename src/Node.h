#pragma once

/*************************************************
Copyright:
Author:         LSH
Date: 			2019-06-23
Description: 	Node抽象类; 节点的抽象, 派生出: Constant, PlaceHolder, Variable (本文件声明) 与 FnNode类(其他文件中声明)
**************************************************/

#include <string>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <memory>
#include <iomanip>/*小数位控制*/
#include <cmath>/*数学函数*/

// 节点基类，是构成计算图的基本元素
class Node
{
protected:
    // [new]该节点名称
    std::string name;
    // 储存节点数值
    double value;
    // 储存该节点依赖的上一级节点
    std::vector<Node *> father;

    /*计数器 node_usetime和graph_usetime
    Placeholder中，作用是判断本次计算中是否对该节点赋了值
    其他节点中，作用是同一次计算中反复对其进行调用时，直接返回已有结果而非重复计算*/

    /*储存除目标节点计算过程外，该节点上一次调用是在第几步计算操作时，如a=x+y，b=a-z，
    EVAL a 2 x 1.0 y 2.0，是第一次对图进行计算，先对x、y进行赋值，因此对a计算时，x上一次调用是在第一步计算操作
    EVAL b 2 x 1.0 y 0.0，是第二次对图进行计算，此时a的上一次调用是在第一步计算操作*/
    // 计数器
    unsigned int node_usetime = 0;
    // 计数器 储存当前是第几次对图进行计算操作(计算一次目标结点就是对图进行一次计算)
    static unsigned int graph_usetime;
    //实现求偏导数的initial过程的剪枝
    unsigned int node_gradientUsetime =0;
    //辅助实现initial　处理同名节点重复创建GRAD的情况
    unsigned int node_pushTime = 0;
    //存储当前是第几次进行GRAD的导数图创建操作
    static unsigned int graph_gradientUsetime;
    //存储某输出节点对应的此节点的upNode
    std::map<std::string,std::vector<Node*>> GradientGraph;

public:
    // [edit] 报错函数不进行输出，throw一个runtime_error，输出与否交由Session::EVAL处理
    static void Error(const std::string& information);
    // [new] P, V, C constructor, 提高代码复用
    Node(const std::string& _name, double _value = 0.0): name(_name), value(_value) {};
    // [new] FnNode(operation) constructor, 计算节点用构造函数
    Node(const std::string& _name, std::vector<Node *> _father): name(_name), father(std::move(_father)) {}
    // 抽象类
    virtual ~Node() = 0;

    // 回传节点名称
    const std::string& GetName();
    //返回value的值，用在其他节点需要访问该节点的value时
    double GetValue();
    // 回传父节点指针用接口
    Node* getFather(int index);
    // [new] 数值设置接口，提高代码复用
    virtual void SetValue(double _value);

    //在外部调用(graph.cpp里调用)，使用计算图，将图计算的计数器增加1，调用本对象的内部函数Calculate进行计算，并返回计算结果，详见Node.cpp中定义
    double Eval();
    //计算本节点的值，返回计算是否成功，详见说明文档	// 视作内部计算调用的函数，不影响node_usetime和graph_usetime
    virtual bool Calculate();

    // [new] 一系列用于偏导数的函数
    virtual double localGradient(Node*);
    virtual double Gradient(const std::string&);
    virtual void initial(const std::string&); //初始化偏导数的图
    static void gradientCounter();//计数器　用于initial偏导数图时的剪枝
    void updateGradientGraph(const std::string& name_of_outputNode,Node* newnode);

    // [new] 实现ASSIGN功能需要，由Variable重载
    virtual void Assign(double)
    {
        Error("Invalid ASSIGN");
    }

    // [delete] void PrintValue(int precision = 4); 无用接口，可以用GetValue取代
    // [delete] friend std::ostream &operator<<(std::ostream &os, Node output); 无用接口，与前述功能重复
};

//常量
class Constant : public Node
{
public:
    using Node::Node;
    // [new] 确保Constant类的数值不能被使用者更改
    void SetValue(double _value)
    {
        Error("Constant couldn't be set");
    }
};

//变量
class Variable : public Node
{
private:
    // [new] ASSIGN功能，true表示该节点已经被ASSIGN，预设为false
    bool assigned = false;
    // [new] ASSIGN功能，存的数值为被ASSIGN的值
    double assigned_value;
public:
    // 构造函数，初始化value
    using Node::Node;
    // [new] ASSIGN功能，由ASSIGN::EvalThisPoint()调用
    void Assign(double _value);
    bool Calculate();
};

//占位
class Placeholder : public Node
{
public:
    //更新value和node_usetime的值
    using Node::Node;
    // 重载 因为used_time需要更改
    void SetValue(double _value);
    // 重载 因为used_time需要检查
    bool Calculate();
};

// [delete] Operation, SpecialOperation, Print, Condition (运算符类)，改采用FnNode结合Function替代
