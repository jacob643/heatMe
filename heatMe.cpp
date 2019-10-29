#include <iostream>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <sstream>

using namespace std;

void parseOptions(int argc, _TCHAR* argv[]);

void func(int* sec) {
  cout << "Hello\n";
  clock_t timer = clock();
  int i = 0;
  while(clock() < (*sec)*1000){
    i++;
    i--;
  }
}

// params
// first arg must be amount of desired seconds
// second arg must be number of nThreads

// globals due to options

unsigned int nThreads = 1; // default value
unsigned int sec = 1;//default value

int main(int argc, _TCHAR* argv[]) {
#ifdef WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    nThreads = sysinfo.dwNumberOfProcessors;
#endif

parseOptions(argc, argv);

cout << nThreads << " threads will heat you up during " << sec << " seconds" << endl;

  clock_t timer;
  HANDLE* t = new HANDLE[nThreads];
  for(int i = 0; i < nThreads; i++){

    t[i] = CreateThread(
      NULL,                                            //LPSECURITY_ATTRIBUTES   lpThreadAttributes,
      0,                                               //SIZE_T                  dwStackSize,
      (LPTHREAD_START_ROUTINE)func,                    //LPTHREAD_START_ROUTINE  lpStartAddress,
      &sec,                                            //__drv_aliasesMem LPVOID lpParameter,
      0,                                               //DWORD                   dwCreationFlags,
      NULL                                             //LPDWORD                 lpThreadId
    );
  }


  for(int i = 0; i < nThreads; i++) {
   WaitForSingleObject(t[i], INFINITE);
}
delete[] t;
  cout << "World!";

  CloseHandle(t);
}

void parseOptions(int argc, _TCHAR* argv[])
{
  for(int i = 1; i < argc; i++)
  {
    string arg;
    stringstream argStream(argv[i]);
    argStream >> arg;
    if (arg == "-s")
    {
      stringstream s(argv[++i]);
      s >> sec;
    }
    else if (arg == "-n")
    {
      stringstream s(argv[++i]);
      s >> nThreads;
    }
    else
    {
      cerr << "Usage: " << argv[0] << " [-n NUMBEROFTHREADS] [-s NUMBEROFSECONDS]\n";
    }
  }
}
