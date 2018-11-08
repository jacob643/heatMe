#include <iostream>
#include <time.h>
#include <windows.h>
#include <string.h>

using namespace std;

void func(string wow) {
  cout << "Hello ";
  wow = "!";
  clock_t timer;
  timer = clock();
  while(clock() < 100);
}

void join(HANDLE t) {
  WaitForSingleObject(t, INFINITE);
  return;
}

int main(int argc, _TCHAR* argv[]) {
    clock_t timer;
    string wow;

    HANDLE t = CreateThread(
    NULL,                                            //LPSECURITY_ATTRIBUTES   lpThreadAttributes,
    0,                                               //SIZE_T                  dwStackSize,
    (LPTHREAD_START_ROUTINE)func,                    //LPTHREAD_START_ROUTINE  lpStartAddress,
    &wow,                                         //__drv_aliasesMem LPVOID lpParameter,
    0,                                               //DWORD                   dwCreationFlags,
    NULL                                             //LPDWORD                 lpThreadId
  );

  join(t);
  cout << "World";
  cout << wow << endl;

  CloseHandle(t);
}
