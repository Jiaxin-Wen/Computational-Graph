/*************************************************
Copyright:
Author:         LSH
Date: 			2019-06-23
Description: 	Newton (ComputionalGraph 派生) 的实现文件
**************************************************/

#include "Newton.h"

/*************************************************
Function:       Newton::~Newton()
Description:    析构；需要对new的Node做析构
Calls:          无
Input:          无
Output:         无
Return:         无
Others:         无
*************************************************/
Newton::~Newton()
{
    for(int i=1; i<=maxterm; i++)
    {
        delete x[i];
        delete a[i];
        delete t[i];
        delete f[i];
    }
    delete x[0];
    delete a[0];
    // NodeMap析构由ComputionalGraph负责
}

/*************************************************
Function:       Newton::Frame
Description:    总筐架
Calls:          Initialize; Input; Eval; StrProcess::InputDevide;
Input:          无
Output:         迭代计算结果
Return:         无
Others:         无
*************************************************/
void Newton::Frame()
{
    int n;
    std::cin >> n;
    std::string buffer;
    std::getline(std::cin, buffer); //输入\n
    // 初始化边界节点
    Initialize();
    // 执行指令
    for(int j=0; j<n; j++)
    {
        // 分割命令并读入参数
        Input(StrProcess::InputDevide());
        // 计算并输出
        for(int i=1; i<=times; i++)
        {
            x_value = this->Eval();
            std::cout << std::fixed << std::setprecision(4) << x_value ;
            if(i < times)
                std::cout << " ";
            //std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

/*************************************************
Function:       Newton::Initialize
Description:    创建一些边界节点
Calls:          Constant::Constant; Placeholder::Placeholder; Variable::Variable;
Input:          无
Output:         无
Return:         无
Others:         无
*************************************************/
void Newton::Initialize()
{
    x.clear();
    a.clear();
    t.clear();
    f.clear();
    Node* x0 = new Constant("x0", 1);
    x.push_back(x0);	// x0 is actually useless
    Node* x1 = new Placeholder("x1");
    x.push_back(x1);	// x for input
    Node* a0 = new Variable("a0");
    a.push_back(a0);	// constant term
    t.push_back(a0);	// t0 = a0 * 1
    f.push_back(a0);	// f0 = t0 + 0
}

/*************************************************
Function:       Newton::Construct
Description:    构建计算图
Calls:          Constant::Constant; Placeholder::Placeholder; Variable::Variable;
Input:          int term
Output:         无
Return:         无
Others:         maxterm, currentterm更改
*************************************************/
void Newton::Construct(int term)
{
    // 检查目前函数的幂次是否大于历史最高幂次，如果有则构建新的节点并连入计算图
    // x1较为特别最小从x^2开始创建
    for(int i=std::max(2, maxterm+1); i<=term; i++)
    {
        Node* xi = new FnNode("x"+std::to_string(i), "*", std::vector<Node*> {x[1], x[i-1]});
        x.push_back(xi);
    }
    // 检查目前函数的幂次是否大于历史最高幂次，如果有则构建新的节点并连入计算图
    for(int i=maxterm+1; i<=term; i++)
    {
        std::string str_i = std::to_string(i);
        Node* ai = new Variable("a"+str_i, 0);
        a.push_back(ai);
        Node* ti = new FnNode("t"+str_i, "*", std::vector<Node*> {a[i], x[i]});
        t.push_back(ti);
        Node* fi = new FnNode("f"+str_i, "+", std::vector<Node*> {t[i], f[i-1]});
        f.push_back(fi);
    }
    // 更新历史最大幂次
    if(term > maxterm)
        maxterm = term;
    // 更新目前输入函数的幂次
    currentterm = term;
    // 删除旧的求导与牛顿法节点
    std::vector<std::string> findlist = {"F", "fx", "ratio", "ans"};
    for(std::string i: findlist)
    {
        auto it = NodeMap.find(i);
        if(it != NodeMap.end())
        {
            delete it->second;
            NodeMap.erase(it);
        }
    }
    // 创建目前函数的求导与牛顿法节点
    // G = GRAD f(x)
    Node* F = new FnNode("F", "GRAD", std::vector<Node*> {f[term]});
    NodeMap.insert(std::make_pair("F", F));
    // fx = G AT x
    Node* fx = new FnNode("fx", "AT", std::vector<Node*> {F, x[1]});
    NodeMap.insert(std::make_pair("fx", fx));
    // ratio = f(x) / f'(x)
    Node* ratio = new FnNode("ratio", "/", std::vector<Node*> {f[term], fx});
    NodeMap.insert(std::make_pair("ratio", ratio));
    // ans = x - ratio
    Node* ans = new FnNode("ans", "-", std::vector<Node*> {x[1], ratio});
    NodeMap.insert(std::make_pair("ans", ans));
}

/*************************************************
Function:       Newton::Input
Description:    构建计算图
Calls:          Construct; Variable::SetValue;
Input:          std::vector<std::string> DevidedCommand
Output:         无
Return:         无
Others:         maxterm, currentterm更改
*************************************************/
void Newton::Input(std::vector<std::string> DevidedCommand)
{
    // 读入当前函数最大幂次
    int term = std::stoi(DevidedCommand[0]);
    // 读入x_value (x的初始值)
    x_value = std::stod(DevidedCommand[DevidedCommand.size()-1]);
    // 检查并创建节点
    Construct(term);
    // 读入各项系数(a)
    for(int i=term; i>=0; i--)
    {
        a[i]->SetValue(std::stod(DevidedCommand[term-i+1]));
    }
}

/*************************************************
Function:       Newton::Eval
Description:    计算牛顿法结果
Calls:          Placeholder::SetValue; FnNode->Eval;
Input:          std::vector<std::string> DevidedCommand
Output:         无
Return:         无
Others:         x[1]->value更改，不修改x_value
*************************************************/
double Newton::Eval()
{
    // x初始值设置
    x[1]->SetValue(x_value);
    // 直接计算牛顿法结果
    double ans = NodeMap["ans"]->Eval();
    // 不对x_value赋值，回传
    return ans;
}
