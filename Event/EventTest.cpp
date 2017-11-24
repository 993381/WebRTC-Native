#include <iostream>
#include "webrtc/base/event.h"

extern "C" {
#include <sys/time.h>
#include <signal.h>
}

using namespace rtc;
Event e1(0, 0);

void sigcall(int num) {
    std::cout << "signal rcv" << std::endl;
    e1.Set();
}

int main() {
    struct timeval ts, te;

    signal(SIGINT, sigcall);

    gettimeofday(&ts, NULL);
    e1.Wait(-1); // also you can specified Wait(5000) make demo exit most 5s
    gettimeofday(&te, NULL);

    std::cout << "cost time" << te.tv_sec - ts.tv_sec<< std::endl;
    return 0;
}
