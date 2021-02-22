#include "FnNode.h"



bool FnNode::Calculate()
{
    //std::cout << "Calculate\n";
    if (node_usetime == graph_usetime)
    {
        //说明在同一次计算操作中重复调用了该节点
        return true;
    }
    else
    {
        //更新到当前一次计算，以便之后重复调用
        node_usetime = graph_usetime;

        value = fn->Eval();	//注意先后顺序 要先eval才判断legal
        //std::cout << "Calculate END\n";
        return fn->GetLegal();
    }
}

void FnNode::initial(const std::string& name_of_outputNode)
{
   // std::cout<<"进入节点"<<name<<"的initial函数"<<std::endl;
    if (node_gradientUsetime == graph_gradientUsetime) //剪枝
    {
      //  std::cout<<"节点"<<name<<"的偏导数图已被初始化过"<<std::endl;
        return ;
    }
    else
    {
       // std::cout<<"节点"<<name<<"的map还未被初始化,当前信息为: "<<"node_gradientUsetime="<<node_gradientUsetime<<' '<<"graph_gradientUsetime="<<graph_gradientUsetime<<std::endl;;

        node_gradientUsetime = graph_gradientUsetime; //更新
        //std::cout<<"标记更新"<<"node_gradientUsetime="<<node_gradientUsetime<<' '<<"graph_gradientUsetime="<<graph_gradientUsetime<<std::endl;
        for(int i=0; i<father.size(); i++)
        {
            father[i]->updateGradientGraph(name_of_outputNode,this);
            // std::cout<<"递归进入下一层——————————————————"<<std::endl;
            father[i]->initial(name_of_outputNode);
        }
        //	std::cout<<"节点"<<name<<"针对此次输入节点"<<name_of_outputNode<<"的map初始化完毕,"<<"size为"<<GradientGraph[name_of_outputNode].size()<<std::endl;
    }
}

double FnNode::localGradient(Node* tempfather)
{
    return fn->CalPartialGradient(tempfather);
}

double FnNode::Gradient(const std::string& name_of_outputNode)
{
    //FIXME:
  /*  if(allGradient.count(name_of_outputNode)!=0) //剪枝
    {
        int temp=allGradient[name_of_outputNode];
        //std::cout<<"节点"<<name<<"对"<<name_of_outputNode<<"的偏导数已被计算过，值为"<<temp<<std::endl;
        return allGradient[name_of_outputNode];
    }*/
    if(name_of_outputNode==name)
    {
        return 1; //对自身的偏导数
    }
    double result = 0;
    std::vector<Node*>& tempvector = GradientGraph[name_of_outputNode];
    //std::cout<<"节点"<<name<<"对此次输出节点的map size为："<<tempvector.size()<<std::endl;
    for(int i=0; i<tempvector.size(); i++)
    {
      //  std::cout<<"此次计算的是"<<tempvector[i]->GetName()<<"对"<<name<<"的local偏导数: "<<tempvector[i]->localGradient(this)<<std::endl;
        double temp = tempvector[i]->localGradient(this)*tempvector[i]->Gradient(name_of_outputNode);
      //  std::cout<<"节点"<<tempvector[i]->GetName()<<"对本节点"<<name<<"贡献的偏导数为"<<temp<<std::endl;
        result+=temp;
        // std::cout<<"当前result为:"<<result<<std::endl;
    }
   // allGradient[name_of_outputNode]=result; //记录
  //  std::cout<<"节点"<<name<<"对"<<name_of_outputNode<<"的偏导数未被计算过，新值为"<<allGradient[name_of_outputNode]<<std::endl;
    return result;
}
