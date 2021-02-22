#include "session.h"

Session::Session(ComputionalGraph* graph_,bool ifRestore_):usingGraph(graph_),ifRestore(ifRestore_)
{

    if(!ifRestore) //不是restore操作，则直接用图的original值初始化session的参数值即可
    {
        parameterValue = usingGraph->get_original_parameterValue(); //初始化新创建的session
    }
    else //是restore操作，从文件中读取参数值
    {
        int size; //参数个数
        std::cin>>size;

        std::string variableName;
        double variableValue;
        for(int i=0; i<size; i++)
        {
            std::cin>>variableName>>variableValue;
            std::cout<<variableName<<variableValue<<std::endl;
            parameterValue[variableName]=variableValue;

        }
        freopen("/dev/tty","r",stdin); //文件读取后句柄交回
    }


}


void Session::saveSession(const std::string& path)
{
    freopen(path.c_str(),"w",stdout);
    std::cout<<parameterValue.size()<<std::endl; //第一个信息为参数个数
    for(auto it : parameterValue)
    {
        std::cout<<it.first<<' '<<it.second<<std::endl; //存储参数名称和相应的值
    }
    freopen("/dev/tty","w",stdout); //交回句柄
}

ComputionalGraph* Session::bindingGraph()
{
    return usingGraph;
}

//将绑定的图中variable节点的值改为当前session存储的variable节点的值
void Session::changeParameterValue()
{

    for( auto it : parameterValue)
    {
        usingGraph->getNode(it.first)->SetValue(it.second);
    }
}


void Session::EVAL(std::string& command_node, std::vector<std::string>& DevidedCommand)
{
    double ans;
    try
    {
        //特判"EVAL a"语句
        if (DevidedCommand.size() == 2)
        {
            ans = usingGraph->getNode(command_node)->Eval();
            answer.push_back(ans);
        }
        else
        {
            int set_num = atoi(DevidedCommand[2].c_str());
            for (int j = 1; j <= set_num; j++)
            {
                double PHValue = atof(DevidedCommand[2 * j + 2].c_str());  ////PH=placeholder 23333
                std::string PHName = DevidedCommand[2 * j + 1];
                //Placeholder *tmp = static_cast<Placeholder *>(NodeMap[PHName]);
                usingGraph->getNode(PHName)->SetValue(PHValue);
            }
            ans = usingGraph->getNode(command_node)->Eval();
            answer.push_back(ans);
        }

        std::cout << std::fixed << std::setprecision(4) << ans <<std::endl;

    }
    catch(std::runtime_error &e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        answer.push_back(0.0);
    }
}


void Session::SETANSWER(std::vector<std::string>& DevidedCommand)
{
    int Step = atoi(DevidedCommand[2].c_str());

    usingGraph->getNode(DevidedCommand[1])->SetValue(answer[Step-1]); //改变图中节点的值
    auto it = parameterValue.find(DevidedCommand[1]); //更新session绑定的值
    it->second = answer[Step];
    answer.push_back(0.0);
}

void Session::SETCONSTANT(std::vector<std::string>& DevidedCommand)
{
    double TargetValue = atof(DevidedCommand[2].c_str());
    usingGraph->getNode(DevidedCommand[1])->SetValue(TargetValue); //改变图中节点的值
    auto it = parameterValue.find(DevidedCommand[1]); //更新session绑定的值
    it->second = TargetValue;
    answer.push_back(0.0);
}
