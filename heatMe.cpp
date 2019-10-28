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
int nThreads = 1; // default value
int sec = 1;//default value

if(argv[1]){
  stringstream s(argv[1]);
  s >> nThreads;
}
if(argv[2]){
  stringstream s(argv[2]);
  s >> sec;
}

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
