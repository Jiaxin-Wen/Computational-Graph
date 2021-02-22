#include "shell.h"


//添加图
void Shell::addGraph(const std::string& newGraphName)
{
    auto it = allGraph.find(newGraphName);
    if(it == allGraph.end())
    {
        //构建新图
        std::cout<<"创建新图："<<newGraphName<<std::endl;
        ComputionalGraph* newGraph = GraphFactory(newGraphName);
        allGraph.insert(make_pair(newGraphName,newGraph));
    }
    else
    {
        std::cout<<"已创建过同名图,创建失败"<<std::endl;
    }
}

ComputionalGraph* Shell::getGraph(const std::string& graphName)
{
    auto it = allGraph.find(graphName);
    if(it != allGraph.end())
    {
        std::cout<<"找到图"<<graphName<<std::endl;
        return it->second;
    }
    else
    {
        std::cout<<"没有找到图"<<graphName<<std::endl;
        return nullptr;
    }
}

//图工厂
ComputionalGraph* Shell::GraphFactory(const std::string& name)
{

    ComputionalGraph* newGraph = new ComputionalGraph;
    Graph_StrProcess parse(newGraph); //处理输入　完成图的构建

    std::cout<<"请完成图的构造输入"<<std::endl;
    parse.InputNumber();
    parse.InputOperation();
    std::cout<<"图构造完毕"<<std::endl;

    return newGraph;

}

void Shell::addSession(const std::string& newSessionName, const std::string& graphName,bool ifRestore)
{
    auto GraphPtr = allGraph.find(graphName);
    if( GraphPtr == allGraph.end())
    {
        std::cout<<"未创建过图"<<graphName<<",无法执行session的绑定。"<<std::endl;
        return;
    }
    else
    {
        auto SessionPtr = allSession.find(newSessionName);
        if( SessionPtr == allSession.end())
        {
            std::cout<<"创建Session: "<<newSessionName<<std::endl;
            Session* newSession = SessionFactory(GraphPtr->second,ifRestore); //创建新的session并绑定
            Session_StrProcess parse(newSession);
            parse.InputCommand();
            if(newSession != nullptr)
                allSession.insert(make_pair(newSessionName,newSession)); //如果没有执行close析构，则存储session
        }
        else
        {
            std::cout<<"已创建过同名session,重新起用"<<std::endl;
            SessionPtr->second->changeParameterValue();
            Session_StrProcess parse(SessionPtr->second);
            parse.InputCommand();
        }
    }
}

Session* Shell::SessionFactory(ComputionalGraph* BindingGraph,bool ifRestore)
{
    //创建并使用新的session
    Session* newSession = new Session(BindingGraph,ifRestore);
    newSession->changeParameterValue();
    return newSession;
}

//save名为sessionName的session
Session* Shell::getSession(const std::string& sessionName)
{
    auto it = allSession.find(sessionName);
    if(it != allSession.end())
    {
        std::cout<<"找到Session: "<<sessionName<<std::endl;
        return it->second;
    }
    else
    {
        std::cout<<"没有找到Session: "<<sessionName<<std::endl;
        return nullptr;
    }

}

Shell::~Shell()
{
    for( auto it : allGraph)
        delete it.second;

    for( auto it : allSession)
        delete it.second;
}
