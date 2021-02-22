/*************************************************
Copyright:
Author:         LSH
Date:			2019-06-23
Description:	Node, Placeholder, Variable, Constant 的实现文件
**************************************************/

#include "Node.h"

// 时间戳
unsigned int Node::graph_usetime = 0;
unsigned int Node::graph_gradientUsetime =0;

Node::~Node() = default;


/*************************************************
Function:       void Node::Error
Description:    接收报错信息并throw一个std::runtime_error实例
Calls:          std::runtime_error
Input:          const std::string&
Output:         无
Return:         无
Others:         有throw行为，不进行输出，输出与否交由Session::EVAL处理
*************************************************/
void Node::Error(const std::string& information)
{
    throw std::runtime_error(information);
}

/*************************************************
Function:       const std::string& Node::GetName
Description:    回传该节点名称name的引用
Calls:          无
Input:          无
Output:         无
Return:         name
Others:         无
*************************************************/
const std::string& Node::GetName()
{
    return name;
}

/*************************************************
Function:       double Node::GetValue
Description:    回传该节点的数值value
Calls:          无
Input:          无
Output:         无
Return:         value
Others:         无
*************************************************/
double Node::GetValue()
{
    return value;
}

/*************************************************
Function:       Node* Node::getFather
Description:    回传该节点的指定父节点的指针
Calls:          无
Input:          int index；指定
Output:         无
Return:         father[index]
Others:         无
*************************************************/
Node* Node::getFather(int index)
{
    return father[index];
}

/*************************************************
Function:       void Node::SetValue
Description:    传入并设置该节点数值
Calls:          无
Input:          double _value
Output:         无
Return:         无
Others:         value更动
*************************************************/
void Node::SetValue(double _value)
{
    value = _value;
}

/*************************************************
Function:       double Node::Eval
Description:    外部调用接口；
Calls:          Node::Calculate
Input:          double _value
Output:         无
Return:         value
Others:         value, graph_usetime, node_usetime++更动
*************************************************/
double Node::Eval()
{
    // 表示对图进行了一次计算
    graph_usetime++;
    // 调用内部运算接口
    Calculate();
    return value;
}

/*************************************************
Function:       double Node::Calculate
Description:    内部调用接口
Calls:          无
Input:          无
Output:         无
Return:         true
Others:         各派生类重载
*************************************************/
bool Node::Calculate()
{
    return true;
}


double Node::localGradient(Node* tempfather)
{
    return 0; //除了FnNode节点都无父节点，直接return０即可
}

double Node::Gradient(const std::string& name_of_outputNode)
{
    double result = 0;
    std::vector<Node*>& tempvector = GradientGraph[name_of_outputNode];
    //std::cout<<"节点"<<name<<"对此次输出节点的map size为："<<tempvector.size()<<std::endl;
    for(int i=0; i<tempvector.size(); i++)
    {
        //  std::cout<<"此次计算的是"<<tempvector[i]->GetName()<<"对"<<name<<"的local偏导数: "<<tempvector[i]->localGradient(this)<<std::endl;
        //result += tempvector[i]->localGradient(this)*tempvector[i]->Gradient(name_of_outputNode);
        double temp = tempvector[i]->localGradient(this)*tempvector[i]->Gradient(name_of_outputNode);
        // std::cout<<"节点"<<tempvector[i]->GetName()<<"对本节点"<<name<<"贡献的偏导数为"<<temp<<std::endl;
        result += temp;
        //  std::cout<<"当前result为:"<<result<<std::endl;
    }
    // std::cout<<"节点"<<name<<"对"<<name_of_outputNode<<"的偏导数未被计算过，新值为"<<result<<std::endl;
// std::cout<<"节点"<<name<<"偏导数计算结果为"<<result<<std::endl;
    return result;
}

void Node::initial(const std::string& name_of_outputNode)
{
    return ;
}

void Node::gradientCounter()
{
    graph_gradientUsetime++;
}

void Node::updateGradientGraph(const std::string& name_of_outputNode,Node* newnode)
{
    if((node_pushTime < graph_gradientUsetime)&&(GradientGraph.count(name_of_outputNode)!=0)) //同名GRAD节点
    {
        //   std::cout<<"出现同名节点"<<name_of_outputNode<<' '<<"本节点为"<<name<<std::endl;
        // std::cout<<GradientGraph[name_of_outputNode].size()<<std::endl;
        node_pushTime = graph_gradientUsetime;
        GradientGraph[name_of_outputNode].clear(); //清空
        // std::cout<<"clear完成"<<std::endl;
    }
    //  std::cout<<"节点"<<name<<"对"<<name_of_outputNode<<"求导路径加入孩子节点"<<newnode->GetName()<<std::endl;
    node_pushTime = graph_gradientUsetime;
    GradientGraph[name_of_outputNode].push_back(newnode);
    // std::cout<<"节点"<<name<<"对"<<name_of_outputNode<<"的当前孩子节点个数为"<<GradientGraph[name_of_outputNode].size()<<std::endl;
}

/*************************************************
Function:       void Variable::Assign
Description:    用于ASSIGN实现；同步时间戳、设置assign状态及数值
Calls:          无
Input:          double _value
Output:         无
Return:         无
Others:         node_usetime, assigned, assigned_value更改
*************************************************/
void Variable::Assign(double _value)
{
    // 同步时间戳，保证只在下一次命令中进行赋值
    node_usetime = graph_usetime;
    // 状态调整为assigned
    assigned = true;
    // 以数值形式存储assign值
    assigned_value = _value;
}

/*************************************************
Function:       void Variable::Calculate
Description:    因应ASSIGN调整；同步时间戳、设置assign状态及数值
Calls:          无
Input:          无
Output:         无
Return:         无
Others:         assigned更改
*************************************************/
bool Variable::Calculate()
{
    if (node_usetime == graph_usetime)  // 时间戳同步时不操作
        return true;
    else if(assigned)   // 不同步时检查是否assigned
    {
        value = assigned_value; // 赋值
        assigned = false;   // 修改assign状态
    }
    return true;
}

/*************************************************
Function:       void Placeholder::SetValue
Description:    同步时间戳、读入设置value
Calls:          无
Input:          double _value
Output:         无
Return:         无
Others:         value, node_usetime更改
*************************************************/
void Placeholder::SetValue(double _value)
{
    value = _value;
    /*在一次计算如a=x+y中，先对依赖的Placeholder调用SetValue函数赋值，
    此时graph_usetime储存的是上一次对图计算的次数，+1才是本次计算的次数*/
    node_usetime = graph_usetime + 1;
}

/*************************************************
Function:       void Placeholder::Calculate
Description:    计算函数；检查是否正确赋值
Calls:          Node::Error
Input:          double _value
Output:         无
Return:         true/false
Others:         throw行为
*************************************************/
bool Placeholder::Calculate()
{
    if (node_usetime == graph_usetime)
        return true;    // 说明在当前一次计算中对占位符进行了赋值
    else
        Error("Placeholder missing");   // 报错终止计算
    return false;
}

