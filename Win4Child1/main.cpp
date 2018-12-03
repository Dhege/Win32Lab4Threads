#include <iostream>
#include <windows.h>
#include <cstdlib>

#define PIPESIZE 256

using namespace std;

string PipeInput(char *chBufR,int size)
{
    BOOL rpipe;
    DWORD bW,bR;
    char chBufW[256];
    //char chBufR[256];
    int i;
    HANDLE hPipe = CreateFile(TEXT("\\\\.\\pipe\\name"),
                       GENERIC_READ | GENERIC_WRITE,
                       0,
                       NULL,
                       OPEN_EXISTING,
                       0,
                       NULL);
    if(hPipe == INVALID_HANDLE_VALUE)
        {
            //cout<<"Error, hfile INVALID_HANDLE_VALUE"<<GetLastError()<<endl;
            return "Error, hfile INVALID_HANDLE_VALUE\n";
        }
    BOOL wpipe = WriteFile(hPipe,chBufW,sizeof(chBufW),&bW,NULL);
    if(wpipe == false)
        cout<<"Error, wpipe in WriteFile() "<<endl;

    while(rpipe = ReadFile(hPipe,chBufR,size,&bR,NULL) != false)
    {

        if(rpipe != false)
        {
            //WriteFile(namedpipe,chBuf,sizeof(chBuf),&BufW,NULL);
            cout<<"From Parent Process by Named -> "<<chBufR<<endl;
            i = atoi(chBufR);
        }
        else
        {
            cout<<"ER";
            break;
        }
    }
    CloseHandle(hPipe);

    return chBufR;
}

int namedPipe(char *chBufW,int size)
{
    char pipepath[56] = "\\\\.\\pipe\\child2";
    BOOL readf;
    char chBuf[256];
    DWORD BufR, BufW;
    //char chBufW[256] = "2";
    HANDLE namepipe = CreateNamedPipe(pipepath,   //pointer to pipe name
                    PIPE_ACCESS_DUPLEX,  //pipe open mode
                    PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,    //The pipe mode
                    PIPE_UNLIMITED_INSTANCES,    //The maximum number of instances that can be created for this pipe
                    PIPESIZE,    //The number of bytes to reserve for the output buffer
                    PIPESIZE,    //The number of bytes to reserve for the input buffer
                    NMPWAIT_USE_DEFAULT_WAIT,
                    NULL
                    );
    if(namepipe == INVALID_HANDLE_VALUE)
        {
            cout<<"Cannot create pipe (namepipe);"<<endl;
            return 0;
        }
    else
        cout<<"Pipe was created! "<<endl;

    BOOL connectpipe = ConnectNamedPipe(namepipe,NULL);

    if(connectpipe != true)
        cout<<"Error in BOOL connectpipe, which connect NamedPipe ";
    else
        cout<<"Pipe is Connected! "<<endl;

    BOOL wpipe = WriteFile(namepipe,chBufW,size,&BufW,NULL);
    if(wpipe == false)
        cout<<"Error, wpipe in WriteFile() "<<endl;
    CloseHandle(namepipe);

    return 0;
}

int main()
{
    char chBuf[256];
    //char chBuf1[256] = "LOLKEK";
    int size = 256;
    PipeInput(chBuf,256);
    cout<<endl<<"Your chBuf: "<<chBuf<<endl;
    Sleep(1000);
    namedPipe(chBuf,256);

    //int cThread = PipeInput();
    //HANDLE th[cThread];


    system("pause");
    return 0;
}
