#include <iostream>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <sstream>

using namespace std;

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
// first arg must be number of nThreads
// second arg must be amount of desired seconds

//
int main(int argc, _TCHAR* argv[]) {
unsigned int nThreads = 1; // default value
unsigned int sec = 0;//default value

#ifdef WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    nThreads = sysinfo.dwNumberOfProcessors;
#endif

if(argc > 1){
  stringstream s(argv[1]);
  s >> sec;
}
else
{
  cout << "How many seconds to keep you warm ?" << endl;
  cin >> sec;
}

if(argc > 2){
  stringstream s(argv[2]);
  s >> nThreads;
}

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
