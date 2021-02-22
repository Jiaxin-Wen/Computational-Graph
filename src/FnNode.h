#ifndef FNNODE_H_INCLUDED
#define FNNODE_H_INCLUDED

#include "Node.h"
#include "Function.h"
#include <vector>
#include <string>
#include <memory>

class FnNode : public Node
{
private:
    // 前驱结点
    //std::vector<Node *> m_pre;
    // 结点对应的运算函数
    std::unique_ptr<Function> fn;

public:
    // std::map<std::string,std::vector<Node*>> GradientGraph;//存储某输出节点对应的此节点的upNode //todo!!
    FnNode(const std::string& _name, const std::string& _optr, const std::vector<Node *> &_father) : Node(_name, _father), fn(Function::Create(_optr, _father,this)) {}

    //auto eval() -> value_t final;
    using Node::Eval;
    bool Calculate();

    double localGradient(Node* tempfather);
    double Gradient(const std::string& name_of_outputNode);
    void initial(const std::string& name_of_outputNode);
};



#endif // FNNODE_H_INCLUDED
