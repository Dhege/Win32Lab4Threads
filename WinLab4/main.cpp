#include <iostream>
#include <windows.h>

#define PIPESIZE 256

using namespace std;

int namedPipe()
{
    char pipepath[56] = "\\\\.\\pipe\\name";
    BOOL readf;
    char chBuf[256];
    DWORD BufR, BufW;
    char chBufW[256] = "5";
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
        cout<<"Cannot create pipe (namepipe);"<<endl;
    else
        cout<<"Pipe was created! "<<endl;

    BOOL connectpipe = ConnectNamedPipe(namepipe,NULL);

    if(connectpipe != true)
        cout<<"Error in BOOL connectpipe, which connect NamedPipe ";
    else
        cout<<"Pipe is Connected! "<<endl;

    BOOL wpipe = WriteFile(namepipe,chBufW,sizeof(chBufW),&BufW,NULL);
    if(wpipe == false)
        cout<<"Error, wpipe in WriteFile() "<<endl;
    CloseHandle(namepipe);

    return 0;
}

int CreateChildProcess(LPCSTR process1)
{
    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};

    if (!CreateProcess(NULL, LPSTR(process1), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    {
        cout << "I can't CreateProcess";
        return 0;
    }
    else
        cout << "\nProcess Created!!!\n";

    return 0;
}


int main()
{
    LPCSTR process1 = "C:\\Users\\Gennady\\Downloads\\Win32Lab2018\\WinApiLab3\\Process1\\bin\\Release\\Process1.exe";
    LPCSTR process2 = "C:\\Users\\Gennady\\Downloads\\Win32Lab2018\\WinApiLab4\\Win4Child1\\bin\\Release\\Win4Child1.exe";
    LPCSTR process3 = "C:\\Users\\Gennady\\Downloads\\Win32Lab2018\\WinApiLab4\\Win4Child2\\bin\\Release\\Win4Child2.exe";
    CreateChildProcess(process2);
    CreateChildProcess(process3);
    namedPipe();

    return 0;
}
