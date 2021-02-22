#include <iostream>
#include <fstream>


#include "Graph.h"
#include "Graph_StrProcess.h"
#include "session.h"
#include "Session_StrProcess.h"


int main()
{
    
   
    ComputionalGraph* graph = new ComputionalGraph; //创建图
    Graph_StrProcess graphParse(graph);//创建图的输入处理，并绑定图
    graphParse.InputCommand();//处理输入，构造图

    Session* sess = new Session(graph,false); //创建session，与创建好的graph绑定
    Session_StrProcess sessionParse(sess); //创建session的输入处理，并绑定session
    sessionParse.InputCommand();//处理输入，执行命令EVAL,SETCONSTANT,SETANSWER
    
    delete graph;
    delete sess;


    return 0;
}

