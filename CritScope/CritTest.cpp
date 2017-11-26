#include <iostream>
#include "webrtc/base/criticalsection.h"

extern "C" {
#include <pthread.h>
}

using namespace rtc;

class test{
public:
    test(int nb) {
        res_ = nb;
    }

    ~test() {

    }

    int getRes() {
        CritScope crit(&crit_);
        return res_;
    }

    int addRes() {
        CritScope crit(&crit_);
        res_++;
    }

    int delRes() {
        CritScope crit(&crit_);
        res_--;
    }
private:
    int res_;
    CriticalSection crit_;
};

static int global = 0;

void *thread_exea(void *args) {
    test *sec = (test *)args;
    int cnt = 0;
    while (cnt++ < 5) {
        sec->addRes();
        std::cout << "Nb:1 add" << " Res:" << sec->getRes() << std::endl;
        usleep(50);
    }
}

void *thread_exeb(void *args) {
    test *sec = (test *)args;
    int cnt = 0;
    while (cnt++ < 5) {
        sec->delRes();
        std::cout << "Nb:2 del" << " Res:" << sec->getRes() << std::endl;
        usleep(50);
    }
}

int main() {
    int ret = 0;
    test ctx(1);
    pthread_t a, b;

    ret = pthread_create(&a, NULL, thread_exea, &ctx);
    if (ret != 0) {
        std::cout << "failed to create thread a" << std::endl;
        return -1;
    }

    ret = pthread_create(&b, NULL, thread_exeb, &ctx);
    if (ret != 0) {
        std::cout << "failed to create thread b" << std::endl;
        return -1;
    }

    pthread_join(a, NULL);
    pthread_join(b, NULL);
    return 0;
}