#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

/*************************************************
Copyright:
Author:         LSH
Date: 			2019-06-23
Description: 	Function 的声明文件
Others:         定义运算符函数类（抽象基类）
**************************************************/

#include "Node.h"
#include <vector>
#include <array>
#include <map>
#include <functional>

class Function
{
protected:
    // 函数指针map（用于工厂方法）
    static std::map<std::string, std::function<Function*(const std::vector<Node*> &,Node*)> > FnMap;

    // 父节点表
    std::vector<Node*> father;
    //与运算符绑定的本节点
    Node* bindingNode;
    // 本计算是否合法
    bool legal;
    // 本节点计算结果
    double result;

    // 计算本运算符 并回传 注意：没有写入result
    virtual double EvalThisPoint() =0;
    // 计算父节点
    void EvalFatherResult();

public:
    // 报错
    static void Error(const std::string& information);

    // 通过名称来创建函数（工厂方法），例如传入"+"，返回一个指向一个AddFn类的实例的指针。
    static Function* Create(const std::string& _optr, const std::vector<Node*> &_father,Node* bindingNode_);

    // 构造
    Function(const std::vector<Node*> &_father, Node* bindingNode_):
        father(_father), bindingNode(bindingNode_), legal(true) {}
    // 抽象类定义
    virtual ~Function() = 0;

    // 回传该节点计算是否合法
    bool GetLegal();
    // 回传该节点计算结果
    double GetResult();

    // 外部调用接口 总计算函数: 计算父节点 计算本运算符
    double Eval();

    // 传入father　根据运算符　求出本节点对此father的偏导数
    virtual double CalPartialGradient(Node* tempfather) =0;

    // 检查传入值是否为合法运算符
    bool isEffectiveOptr(std::string &);
};

#endif // FUNCTION_H_INCLUDED
