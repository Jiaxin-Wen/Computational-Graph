#include <iostream>
#include <fstream>

#include "shell.h"
#include "Shell_StrProcess.h"


int main()
{ 
    Shell* shell = new Shell; //创建shell
    Shell_StrProcess* parse = new Shell_StrProcess(shell); //创建shell的输入处理类并绑定shell
    parse->InputCommand(); //处理输入，执行相应动作
    
    delete shell; 
    delete parse;
    return 0;
}

