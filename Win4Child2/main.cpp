#include <iostream>
#include <windows.h>
#include <vector>
#include <thread>
#include <mutex>


using namespace std;

int PipeInput()
{
    BOOL rpipe;
    DWORD bW,bR;
    char chBufW[256];
    char chBufR[256];
    int i;
    HANDLE hPipe = CreateFile(TEXT("\\\\.\\pipe\\child2"),
                       GENERIC_READ | GENERIC_WRITE,
                       0,
                       NULL,
                       OPEN_EXISTING,
                       0,
                       NULL);
    if(hPipe == INVALID_HANDLE_VALUE)
        cout<<"Error, hfile INVALID_HANDLE_VALUE"<<GetLastError()<<endl;
    BOOL wpipe = WriteFile(hPipe,chBufW,sizeof(chBufW),&bW,NULL);
    if(wpipe == false)
        cout<<"Error, wpipe in WriteFile() "<<endl;

    while(rpipe = ReadFile(hPipe,chBufR,sizeof(chBufR),&bR,NULL) != false)
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

    return i;
}

int PipeInput1()
{
    BOOL rpipe;
    DWORD bW,bR;
    char chBufW[256];
    char chBufR[256];
    int i;
    HANDLE hPipe = CreateFile(TEXT("\\\\.\\pipe\\child2"),
                       GENERIC_READ | GENERIC_WRITE,
                       0,
                       NULL,
                       OPEN_EXISTING,
                       0,
                       NULL);
    if(hPipe == INVALID_HANDLE_VALUE)
        {
            cout<<"Error, hfile INVALID_HANDLE_VALUE"<<GetLastError()<<endl;
            return 0;
        }
    BOOL wpipe = WriteFile(hPipe,chBufW,sizeof(chBufW),&bW,NULL);
    if(wpipe == false)
        cout<<"Error, wpipe in WriteFile() "<<endl;

    while(rpipe = ReadFile(hPipe,chBufR,sizeof(chBufR),&bR,NULL) != false)
    {

        if(rpipe != false)
        {
            //WriteFile(namedpipe,chBuf,sizeof(chBuf),&BufW,NULL);
            cout<<"From Child1 Process by Named -> "<<chBufR<<endl;
            i = atoi(chBufR);
        }
        else
        {
            cout<<"ER";
            break;
        }
    }
    CloseHandle(hPipe);

    return i;
}

HANDLE mutex;

void read(vector<int> &vec)
{
    LPSTR matrix = "C:\\Users\\Gennady\\Desktop\\WinApi\\matrix1.txt";
    HANDLE hfile = CreateFile(matrix,
                       GENERIC_READ,//dwDesiredAccess
                       FILE_SHARE_WRITE | FILE_SHARE_READ,//dwShareMode NULL - no one program can open your file
                       NULL,//lpSecurity
                       OPEN_ALWAYS,//dwCreationDisposition
                       FILE_ATTRIBUTE_NORMAL,
                       NULL
                       );
    char *buf1 = new char[56];
    DWORD dR;
    BOOL read;

        read = ReadFile(hfile,buf1,256,&dR,NULL);
        if(read == false)
            cout<<"False"<<endl;

    string q = string(buf1);
    int count = 0;
    char c[] = "1234567890";
    //vector<int> vec;
    for(int i=0; i<q.size();i++)
    {
        if(q[i]==' ')
        //if(q[i] == ' ' && q[i+1] !=' ' && q[q.size()+1]!=' ')
        {
            count++;
            q[i]--;
        }
        else if(q[i] !=' ')
        {
            vec.push_back(q[i]-48);
        }
    }
}

void write(vector<int> vec, int **x,int n,int m)
{
    cout<<endl;
    int k = 0;
    int s=0;
    cout<<vec.size();
    //cout<<vec[10]<<endl;
    cout<<n/2<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cout<<vec[k]<<"  ";
            x[i][j] = vec[k];
            k++;
        }
    }
    cout<<endl<<"Matrix: "<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cout<<x[i][j]<<"\t";
        }
        cout<<endl;
    }
}



//DWORD WINAPI filew(LPVOID param)
/*int filew()
{
    DWORD result;
	result = WaitForSingleObject(mutex,0);

    int n = 3; int m = 4;
    LPSTR matrix = "C:\\Users\\Gennady\\Desktop\\WinApi\\matrix1.txt";
    HANDLE hfile = CreateFile(matrix,
                       GENERIC_READ,//dwDesiredAccess
                       FILE_SHARE_WRITE | FILE_SHARE_READ,//dwShareMode NULL - no one program can open your file
                       NULL,//lpSecurity
                       OPEN_ALWAYS,//dwCreationDisposition
                       FILE_ATTRIBUTE_NORMAL,
                       NULL
                       );
    char *buf1 = new char[56];
    DWORD dR;
    BOOL read;

        read = ReadFile(hfile,buf1,256,&dR,NULL);
        if(read == false)
            cout<<"False"<<endl;

    cout<<endl<<"buf1: "<<buf1<<endl;
    string q(buf1);
    cout<<endl<<"q 2:"<<q<<endl;
    int count = 0;
    char c[] = "1234567890";
    vector<int> vec;
    for(int i=0; i<q.size();i++)
    {
        if(q[i]==' ')
        //if(q[i] == ' ' && q[i+1] !=' ' && q[q.size()+1]!=' ')
        {
            count++;
            q[i]--;
        }
        else if(q[i] !=' ')
        {
            vec.push_back(q[i]-48);
        }
    }
    cout<<q<<endl;
    int nCount = count;
    cout<<"Number Count: "<<nCount<<endl;
    cout<<"vec: ";
    for(auto &elem:vec)
        cout<<elem;

    cout<<endl;
    int **x = new int*[n];
    for(int i=0; i<n;i++)
        x[i] = new int[m];

    if(vec.size() < n*m)
    {
        for(int i=vec.size();i<(n*m);i++)
            vec.push_back(0);
    }

    int k =0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cout<<vec[k];
            x[i][j] = vec[k];
            k++;
        }
    }
    cout<<endl;
    for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                cout<<x[i][j]<<"\t";
            }
            cout<<endl;
        }
    cout<<endl<<endl;

    int min[n];
    int max[m];int maxi;int uf=0;
    int j=0;

    int minx[n];
    for(int i=0;i<n;i++)
    {
        minx[i]=x[i][0];
        for(int j=0;j<m;j++)
        {
            if(minx[i]>x[i][j])
            {
                minx[i]=x[i][j];
            }
        }
    }
    cout<<"min from string: ";
    for(int i=0;i<n;i++)
        cout<<minx[i];

    for(int j=0;j<m;j++)
    {
        max[j] = x[0][j];
        for(int i=0;i<n;i++)
        {
            if(max[j]>x[i][j])
            {
                max[j]=x[i][j];
            }
        }
    }
    cout<<endl;
    cout<<"max from column: ";
    for(int j=0;j<m;j++)
        cout<<max[j];
    cout<<endl;
    int maxofmin,minofmax;
    maxofmin = minx[0];
    for(int i=0;i<n;i++)
    {
        if(maxofmin<minx[i])
            maxofmin=minx[i];
    }
    cout<<"maxofmin = "<<maxofmin<<endl;

    minofmax = max[0];
    for(int j=0;j<m;j++)
    {
        if(minofmax>max[j])
            minofmax=max[j];
    }
    cout<<"minofmax = "<<minofmax<<endl;

    if (minofmax > maxofmin)
    std::cout << "Sedlovix tochek net" << std::endl;
    else
        std::cout << "Sedlovie tochki = " <<std::endl;
    for (int i = 0; i < n; i++)
    {
        if (minx[i] == maxofmin)
        {
            for (int j = 0; j < m; j++)
            {
                if (max[j] == minofmax)
                    cout << i << " " << j << std::endl;
            }
        }
    }

    delete[]buf1;
    delete[]x;
    //ReleaseMutex(mutex);

    return 0;
}*/

void maxofmin1(int &maxofmin, int *minx,int n)
{
    maxofmin = minx[0];
    for(int i=0;i<n;i++)
    {
        if(maxofmin<minx[i])
            maxofmin=minx[i];
    }
}

void minofmax1(int &minofmax, int *max,int m)
{
    minofmax = max[0];
    for(int j=0;j<m;j++)
    {
        if(minofmax>max[j])
            minofmax=max[j];
    }
}




int main()
{
    Sleep(2010);
    //mutex mtx;
    int n = 3; int m = 4;
    int cThread = 0;
    cThread = PipeInput1();
    cout<<"cThread From Parent Process: "<<cThread<<endl;

    thread t[2];
    //t[0] = thread();

    vector<int> vec;
    t[0] = thread(read,std::ref(vec));
    t[0].join();
    //thread th1(read,std::ref(vec));
    //th1.join();
    for(auto i: vec)
        cout<<i<<" ";
    int **x = new int*[n];
    for(int i=0; i<n;i++)
        x[i] = new int[m];
    write(vec,x,n,m);

    int minx[n] = {0};
    int max[m] = {0};

    thread th2([&minx,x,n,m]()
               {
                   for(int i=0;i<n;i++)
                    {
                        minx[i]=x[i][0];
                        for(int j=0;j<m;j++)
                        {
                            if(minx[i]>x[i][j])
                            {
                                minx[i]=x[i][j];
                            }
                        }
                    }
               });
    thread th3([&max,x,n,m]()
               {
                   for(int j=0;j<m;j++)
                   {
                        max[j] = x[0][j];
                        for(int i=0;i<n;i++)
                        {
                            if(max[j]>x[i][j])
                            {
                                max[j]=x[i][j];
                            }
                        }
                    }
               });
    th2.join();
    th3.join();
    cout<<"min from string: ";
    for(int i=0;i<n;i++)
        cout<<minx[i];

    cout<<endl;
    cout<<"max from column: ";
    for(int j=0;j<m;j++)
        cout<<max[j];
    cout<<endl;

    int maxofmin,minofmax;

    thread th4(maxofmin1,std::ref(maxofmin),&minx[0],n);
    thread th5(minofmax1,std::ref(minofmax),&max[0],m);
    th4.join();
    th5.join();

    cout<<"maxofmin = "<<maxofmin<<endl;
    cout<<"minofmax = "<<minofmax<<endl;

    if (minofmax > maxofmin)
    std::cout << "Sedlovix tochek net" << std::endl;
    else
        std::cout << "Sedlovie tochki = " <<std::endl;
    for (int i = 0; i < n; i++)
    {
        if (minx[i] == maxofmin)
        {
            for (int j = 0; j < m; j++)
            {
                if (max[j] == minofmax)
                    cout << i << " " << j << " : " << x[i][j] << std::endl;
            }
        }
    }


    for (int i = 0; i < n; i++)
    {
        delete [] x[i];
    }
    delete [] x;

    system("pause");
    return 0;
}
