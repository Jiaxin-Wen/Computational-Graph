/*************************************************
Copyright:
Author:         LSH
Date: 			2019-06-23
Description: 	Function 的实现文件
**************************************************/

#include "Function.h"
#include "FunctionList.h"

Function::~Function() = default;

/*************************************************
Function:       void Function::Error
Description:    接收报错信息并throw一个std::runtime_error实例
Calls:          std::runtime_error
Input:          const std::string&
Output:         无
Return:         无
Others:         有throw行为，不进行输出
*************************************************/
void Function::Error(const std::string& information)
{
    //std::cout << "ERROR: " << information << std::endl;
    throw std::runtime_error(information);
}

/*************************************************
Function:       template<typename T> Function* newFn
Description:    创建Function实例用函数
Calls:          T::T
Input:          typename T, const std::vector<Node*> &_father, Node* bindingNode_
Output:         无
Return:         T*
Others:         创建Function实例
*************************************************/
template<typename T>
Function* newFn(const std::vector<Node*> &_father, Node* bindingNode_)
{
    return new T(_father,bindingNode_);
}

// 函数指针map，新增函数时需要在下表添加
std::map<std::string, std::function<Function*(const std::vector<Node*> &,Node*)> > Function::FnMap =
{
    {"+",       newFn<Addition>},
    {"-",       newFn<Subtraction>},
    {"*",       newFn<Multipulation>},
    {"/",       newFn<Division>},

    {"SIN",     newFn<SIN>},
    {"LOG",     newFn<LOG>},
    {"EXP",     newFn<EXP>},
    {"TANH",    newFn<TANH>},
    {"SIGMOID", newFn<SIGMOID>},

    {"PRINT",     newFn<PRINT>},

    {">",       newFn<Larger>},
    {"<", 	    newFn<Smaller>},
    {">=",      newFn<LargerOrEqual>},
    {"<=",      newFn<SmallerOrEqual>},
    {"==",      newFn<Equal>},
    {"!=",		newFn<UnEqual>},

    {"COND",    newFn<COND>},

    {"BIND",  newFn<BIND>},
    {"ASSERT", newFn<ASSERT>},

    {"ASSIGN",  newFn<ASSIGN>},

    {"GRAD", newFn<GRAD>},

    {"AT", newFn<AT>}
};

/*************************************************
Function:       Function::Create
Description:    创建Function实例用的工厂
Calls:          NewFn, Function::FnMap
Input:          const std::string& _optr, const std::vector<Node*> &_father, Node* bindingNode_
Output:         无
Return:         Fucntion*
Others:         创建对应_optr的Function实例
*************************************************/
Function* Function::Create(const std::string& _optr, const std::vector<Node*> &_father,Node* bindingNode_)
{
    auto it = FnMap.find(_optr);
    if (it == FnMap.end())
    {
        // 运算符未定义，throw error
        Node::Error("Invalid Operator: " + _optr);
        return nullptr;
    }
    else
        // 调用newFn函数，返回对应实例的指针
        return (it->second)(_father,bindingNode_);
}

bool Function::GetLegal()
{
    return legal;
}

double Function::GetResult()
{
    return result;
}

/*************************************************
Function:       Function::Eval
Description:    外部调用接口；总计算函数
Calls:          EvalFatherResult(); EvalThisPoint();
Input:          无
Output:         无
Return:         double result
Others:         result更动；计算父节点；计算本运算符
*************************************************/
double Function::Eval()
{
    // 先计算父节点
    EvalFatherResult();
    // 计算本节点并赋值
    result = EvalThisPoint();
    // 返回本节点数值
    return result;
}

/*************************************************
Function:       Function::Eval
Description:    内部调用接口；计算父节点
Calls:          Node::Calculate()
Input:          无
Output:         无
Return:         无
Others:         legal更动
*************************************************/
void Function::EvalFatherResult()
{
    for (auto i: father)
    {
        if (!i->Calculate())
            legal = false;  // 即父节点计算有误，本节点亦有误
    }
}

/*************************************************
Function:       Function::isEffectiveOptr
Description:    检查输入字符串是否为合法运算符
Calls:          Function::FnMap
Input:          std::string & _optr
Output:         无
Return:         bool
Others:         无
*************************************************/
bool Function::isEffectiveOptr(std::string & _optr)
{
    return FnMap.count(_optr)!=0;
}

