#ifndef FUNCTIONLIST_H_INCLUDED
#define FUNCTIONLIST_H_INCLUDED

#include "Function.h"
#include <cmath>

class Addition : public Function
{
public:
    using Function::Function;
    double EvalThisPoint() ;
    double CalPartialGradient(Node* tempfather);
};

class Subtraction : public Function
{
public:
    using Function::Function;
    double EvalThisPoint() ;
    double CalPartialGradient(Node* tempfather);
};

class Multipulation : public Function
{
public:
    using Function::Function;
    double EvalThisPoint() ;
    double CalPartialGradient(Node* tempfather);
};

class Division : public Function
{
public:
    using Function::Function;
    double EvalThisPoint() ;
    double CalPartialGradient(Node* tempfather);
};

class SIN : public Function
{
public:
    using Function::Function;
    double EvalThisPoint() ;
    double CalPartialGradient(Node* tempfather);
};

class LOG : public Function
{
public:
    using Function::Function;
    double EvalThisPoint() ;
    double CalPartialGradient(Node* tempfather);
};

class EXP : public Function
{
public:
    using Function::Function;
    double EvalThisPoint() ;
    double CalPartialGradient(Node* tempfather);
};

class TANH : public Function
{
public:
    using Function::Function;
    double EvalThisPoint() ;
    double CalPartialGradient(Node* tempfather);
};

class SIGMOID : public Function
{
public:
    using Function::Function;
    double EvalThisPoint() ;
    double CalPartialGradient(Node* tempfather);
};


class PRINT : public Function
{
public:
    using Function::Function;
    double EvalThisPoint() ;
    double CalPartialGradient(Node* tempfather);
};

class Larger : public Function
{
public:
    using Function::Function;
    double EvalThisPoint() ;
    double CalPartialGradient(Node* tempfather);
};

class Smaller : public Function
{
public:
    using Function::Function;
    double EvalThisPoint() ;
    double CalPartialGradient(Node* tempfather);
};

class LargerOrEqual : public Function
{
public:
    using Function::Function;
    double EvalThisPoint() ;
    double CalPartialGradient(Node* tempfather);
};

class SmallerOrEqual : public Function
{
public:
    using Function::Function;
    double EvalThisPoint() ;
    double CalPartialGradient(Node* tempfather);
};

class Equal : public Function
{
public:
    using Function::Function;
    double EvalThisPoint() ;
    double CalPartialGradient(Node* tempfather);
};

class UnEqual : public Function
{
public:
    using Function::Function;
    double EvalThisPoint() ;
    double CalPartialGradient(Node* tempfather);
};

class COND : public Function
{
public:
    using Function::Function;
    double EvalThisPoint() ;
    double CalPartialGradient(Node* tempfather);
};


class ASSERT : public Function
{
public:
    using Function::Function;
    double EvalThisPoint();
    double CalPartialGradient(Node* tempfather);
};

class BIND : public Function
{
public:
    using Function::Function;
    double EvalThisPoint();
    double CalPartialGradient(Node* tempfather);
};

class ASSIGN : public Function
{
public:
    using Function::Function;
    double EvalThisPoint() ;
    double CalPartialGradient(Node* tempfather);
};

class GRAD : public Function
{
public:
    GRAD(const std::vector<Node*> father_,Node* bindingNode_):Function(father_,bindingNode_)
    {
        Node::gradientCounter(); //GRAD操作计数，实现initial递归过程的剪枝
        bindingNode_->initial(father_[0]->GetName()); //递归初始化图
    }
    double EvalThisPoint();
    double CalPartialGradient(Node* tempfather);
};

class AT : public Function
{
public:
    using Function::Function;
    double EvalThisPoint();
    double CalPartialGradient(Node* tempfather);
};

#endif // FUNCTIONLIST_H_INCLUDED

