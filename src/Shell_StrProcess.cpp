#include "Shell_StrProcess.h"
#include "shell.h"

void Shell_StrProcess::InputCommand()
{

    while(1)
    {
        std::cout<<"请输入指令"<<std::endl;
        std::vector<std::string> DevidedCommand = InputDevide();

        // input : exit 结束程序
        if(DevidedCommand[0] == "exit")
        {
            return;
        }

        // input: restore Graph as graph from XXX.txt //读取数据并创建名为graph的图
        // input: restore Session of graph as sess from XXX-step.ckpt   //读取数据并创建名为sess的绑定graph的Session
        else if (DevidedCommand[0] == "restore" )
        {
            if(DevidedCommand[1] == "Graph")
            {
                freopen(DevidedCommand[5].c_str(),"r",stdin);
                shellProcessing->addGraph(DevidedCommand[3]);//创建图
                freopen("/dev/tty","r",stdin);  //仅适用于linux
                std::cout<<"restore graph结束"<<std::endl;
            }
            else if(DevidedCommand[1] == "Session")
            {
                // std::cout<<"准备restore Session"<<std::endl;
                freopen(DevidedCommand[7].c_str(),"r",stdin);
                //std::cout<<"读取与图"<<DevidedCommand[3]<<"绑定的Session:"<<DevidedCommand[7]<<std::endl;
                shellProcessing->addSession(DevidedCommand[5],DevidedCommand[3],true);
                freopen("/dev/tty","r",stdin); //仅适用于linux
            }
        }
        //input: save sess with step = N //N是训练次数，作为后缀，保存的文件名为：sess-N
        else if (DevidedCommand[0] == "save")
        {
            std::string SessionPath = DevidedCommand[1]+"-"+DevidedCommand[5]+".ckpt";
            Session* SessionToSave = shellProcessing->getSession(DevidedCommand[1]); //找到将要存储的session
            SessionToSave->saveSession(SessionPath);
            std::cout<<"save成功"<<std::endl;
        }
        else if(DevidedCommand[2] == "Graph()")
            // input : graph = Graph()　创建名为graph的图
        {
            shellProcessing->addGraph(DevidedCommand[0]);
        }
        else if(DevidedCommand[2] == "Session()")
            // input: sess = Session() of graph 创建或启用名为sess的Session,与图graph绑定
        {
            // std::cout<<"准备创建Session"<<DevidedCommand[0]<<"-"<<DevidedCommand[4]<<std::endl;
            shellProcessing->addSession(DevidedCommand[0],DevidedCommand[4],false);
        }
    }
}
