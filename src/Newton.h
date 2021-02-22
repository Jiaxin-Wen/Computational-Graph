#ifndef NEWTON_H_INCLUDED
#define NEWTON_H_INCLUDED

/*************************************************
Copyright:
Author:         LSH
Date: 			2019-06-23
Description: 	Newton (ComputionalGraph 派生) 的声明文件
**************************************************/

#include <iomanip>
#include <string>
#include "Graph.h"
#include "StrProcess.h"

class Newton : public ComputionalGraph
{
private:
    // 目前的x值
    double x_value;
    // 历史中输入函数的幂次的最大值
    int maxterm = 0;
    // 目前输入函数的最大幂次
    int currentterm = 0;
    // 迭代次数
    static const int times = 5;

    // x[n] = x[1] * x[n-1], x^n，x的幂次
    std::vector<Node*> x;
    // 对应次项的系数
    std::vector<Node*> a;
    // t[n] = a[n] * x[n], an*x^n，对应次项
    std::vector<Node*> t;
    // f[n] = t[n] + f[n-1], 降幂的前n项之和，f[currterm]即输入函数在x_value下的值
    std::vector<Node*> f;

    // 函数的计算图建立: 检查计算图是否需要建立新节点，创建并连接新的节点
    void Construct(int term);

public:
    // 析构需要对x, a, t, f节点等删除
    ~Newton();

    // 总框架
    void Frame();
    // 初始化，准备一些边界节点
    void Initialize();
    // 输入方程，调用Construct函数
    void Input(std::vector<std::string> DevidedCommand);
    // 计算一次牛顿法结果并回传，不对x_value赋值
    double Eval();
};

#endif // NEWTON_H_INCLUDED
