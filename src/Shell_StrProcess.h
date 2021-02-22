#pragma once
#include "StrProcess.h"


class Shell;

class Shell_StrProcess : public StrProcess
{

private:
    Shell* shellProcessing;

public:
    Shell_StrProcess(Shell* shell_):shellProcessing(shell_) {}

    /*
    shell输入处理：
    exit：结束程序，退出，返回main
    graph = Graph()：创建名为graph的计算图
    sess = Session() of graph：创建名为sess绑定graph的Session
    restore Graph as graph from graph.txt：从graph.txt文件中读取数据，创建名为graph的图
    restore Session of graph as sess from sess-1.ckpt：从sess-1.ckpt文件中读取数据，创建名为sess并与graph绑定的Session
    save sess with step = 2:保存名为sess的进程，step = 2即将保存的文件名设置为sess-2
    */
    void InputCommand();

};
