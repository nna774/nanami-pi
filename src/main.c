#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "GUI_BMPfile.h"

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    DEV_Module_Exit();

    exit(0);
}


int main(void)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);
    return 0;
}
