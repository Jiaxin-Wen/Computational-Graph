#include "FunctionList.h"

double Addition::EvalThisPoint()
{
    return father[0]->GetValue() + father[1]->GetValue();
}

double Addition::CalPartialGradient(Node* tempfather)
{
    return 1;
}

double Subtraction::EvalThisPoint()
{
    return father[0]->GetValue() - father[1]->GetValue();
}

double Subtraction::CalPartialGradient(Node* tempfather)
{
    if(father[0]->GetName()==tempfather->GetName())
        return 1;
    else
        return -1;
}

double Multipulation::EvalThisPoint()
{
    return father[0]->GetValue() * father[1]->GetValue();
}

double Multipulation::CalPartialGradient(Node* tempfather)
{
    if(father[0]->GetName()==tempfather->GetName())
        return father[1]->GetValue();
    else
        return father[0]->GetValue();
}

double Division::EvalThisPoint()
{
    if (father[1]->GetValue() == 0.0)
    {
        legal = false;
        Function::Error( "Division by zero" );
        return 0;
    }
    else
    {
        return father[0]->GetValue() / father[1]->GetValue();
    }
}

double Division::CalPartialGradient(Node* tempfather)         //如果出现分母为０的情况　在前期计算值时就已经throw
{
    if (father[0]->GetName()==tempfather->GetName())
        return 1/father[1]->GetValue();
    else
        return (-1*father[0]->GetValue())/(father[1]->GetValue()*father[1]->GetValue());
}

double SIN::EvalThisPoint()
{
    return sin(father[0]->GetValue());
}

double SIN::CalPartialGradient(Node* tempfather)
{
    return cos(father[0]->GetValue());
}

double LOG::EvalThisPoint()
{
    if(father[0]->GetValue() <= 0)
    {
        legal = false;
        Function::Error( "LOG operator's input must be positive" );
        return 0;
    }
    else
    {
        return log(father[0]->GetValue());
    }
}

double LOG::CalPartialGradient(Node* tempfather)
{
    return 1/father[0]->GetValue();
}

double EXP::EvalThisPoint()
{
    return exp(father[0]->GetValue());
}

double EXP::CalPartialGradient(Node* tempfather)
{
    return exp(father[0]->GetValue());
}


double TANH::EvalThisPoint()
{
    return tanh(father[0]->GetValue());
}

double TANH::CalPartialGradient(Node* tempfather)
{
    return 1-tanh(father[0]->GetValue())*tanh(father[0]->GetValue());
}

double SIGMOID::EvalThisPoint()
{
    return 1/(1+exp(-(father[0]->GetValue())));
}

double SIGMOID::CalPartialGradient(Node* tempfather)
{
    int tempResult = 1/(1+exp(-(father[0]->GetValue())));
    return tempResult*(1-tempResult);
}

double PRINT::EvalThisPoint()
{
    std::cout << "PRINT Operator: " << father[0]->GetName() << " = " << father[0]->GetValue() << std::endl;
    return father[0]->GetValue();
}

double PRINT::CalPartialGradient(Node* tempfather)
{
    return 1.0;
}

double Larger::EvalThisPoint()
{
    return father[0]->GetValue() > father[1]->GetValue();
}

double Larger::CalPartialGradient(Node* tempfather)
{
    return 1.0;
}

double Smaller::EvalThisPoint()
{
    return father[0]->GetValue() < father[1]->GetValue();
}

double Smaller::CalPartialGradient(Node* tempfather)
{
   return 1.0;
}

double LargerOrEqual::EvalThisPoint()
{
    return father[0]->GetValue() >= father[1]->GetValue();
}

double LargerOrEqual::CalPartialGradient(Node* tempfather)
{
    return 1.0;
}

double SmallerOrEqual::EvalThisPoint()
{
    return father[0]->GetValue() <= father[1]->GetValue();
}

double SmallerOrEqual::CalPartialGradient(Node* tempfather)
{
    return 1.0;
}

double Equal::EvalThisPoint()
{
    return father[0]->GetValue() == father[1]->GetValue();
}

double Equal::CalPartialGradient(Node* tempfather)
{
    return 1.0;
}

double UnEqual::EvalThisPoint()
{
    return father[0]->GetValue() != father[1]->GetValue();
}

double UnEqual::CalPartialGradient(Node* tempfather)
{
    return 1.0;
}

double COND::EvalThisPoint()
{
    if(father[0]->GetValue() > 0 )
        return father[1]->GetValue();
    else
        return father[2]->GetValue();
}

double COND::CalPartialGradient(Node* tempfather)
{
    return 1.0;
}


double BIND::EvalThisPoint()
{	
	father[1]->GetValue(); 
    return father[0]->GetValue();
}

double BIND::CalPartialGradient(Node* tempfather)
{

}

double ASSERT::EvalThisPoint()
{
    if( father[0]->GetValue() <= 0.0)
    {
        legal = false;
        Function::Error("Assertion failed");
        return 0.0;
    }
    else
    {
        return 0.0;
    }
}

double ASSERT::CalPartialGradient(Node* tempfather)
{
    //
}

double ASSIGN::EvalThisPoint()
{
    father[0]->Assign(father[1]->GetValue());
    return father[1]->GetValue();
}

double ASSIGN::CalPartialGradient(Node* tempfather)
{
    //
}

double GRAD::EvalThisPoint() //GRAD节点本身值可任意给定
{
    return 0.0; 
}

double GRAD::CalPartialGradient(Node* tempfather)  //设置为1
{
    return 1.0;
}

double AT::EvalThisPoint() //AT节点的值即本第一个父节点绑定的GRAD节点对本节点第二个父节点的导数值
{
    return father[1]->Gradient(father[0]->getFather(0)->GetName());//father[1]即x节点 father[0]即g节点
}

double AT::CalPartialGradient(Node* tempfather) //AT本身偏导数值可随意设定
{
    return 1.0;
}


