#include <iostream>
#include <cmath>
#include <time.h>
#include <ctime>

using namespace std;

inline _int64 HightTime() {
    _asm {
        rdtsc
    }
}

_int64 pft_start;
_int64 pft_finish;

#define SPEED_START_CONSOLE pft_start = HightTime();
#define SPEED_FINISH_CONSOLE pft_finish = HightTime(); cout << pft_finish - pft_start << endl;

#include <Windows.h>  

extern "C" {
#include <Powrprof.h>
}

#include <vector>

#pragma comment(lib, "Powrprof.lib")

typedef struct _PROCESSOR_POWER_INFORMATION {
    ULONG  Number;
    ULONG  MaxMhz;
    ULONG  CurrentMhz;
    ULONG  MhzLimit;
    ULONG  MaxIdleState;
    ULONG  CurrentIdleState;
} PROCESSOR_POWER_INFORMATION, * PPROCESSOR_POWER_INFORMATION;

//int n = 500;

int main()
{
    //unsigned int start_time = clock(); // начальное время
    SPEED_START_CONSOLE
    int n = 500;
    int K = 500;
    double* A = new double[n];
    double times;
    srand(time(NULL));
    for (int i = 0; i < n; i++){
        A[i] = rand() * pow(10, -2);
    }
    for (int i = 0; i < n; i++){
        A[rand() % n] = A[rand() % n] + K;
    }
    SPEED_FINISH_CONSOLE // скорость производительности в тактах
    //unsigned int end_time = clock(); // конечное время
    //unsigned int search_time = end_time - start_time; // искомое время
    //cout << search_time << " second" << endl;

    SYSTEM_INFO si = { 0 };
    GetSystemInfo(&si);

    std::vector<PROCESSOR_POWER_INFORMATION> a(si.dwNumberOfProcessors);
    DWORD dwSize = sizeof(PROCESSOR_POWER_INFORMATION) * si.dwNumberOfProcessors;


    CallNtPowerInformation(ProcessorInformation, NULL, 0, &a[0], dwSize);

    std::cout << a[0].CurrentMhz << " Mhz" << endl; // Тактовая частота

    times = (pft_finish - pft_start) / (a[0].CurrentMhz * 1000000.0);

    std::cout << times << " second";

    pft_finish = 0;
    pft_start = 0;

    a.clear();
    return 0;
}
//cout << A[i] << endl;
