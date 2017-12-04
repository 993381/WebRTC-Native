#include <iostream>
#include <memory>
#include <string>
#include <csignal>
#include "pthread.h"

#include "webrtc/base/sharedexclusivelock.h"

using namespace rtc;
using namespace std;

SharedExclusiveLock *lock;
static int val = 0;

void *thread_write(void *args) {
        int cnt = 0;
    for (; cnt < 5; cnt++) {
                lock->LockExclusive();
                val++;
                lock->UnlockExclusive();
            
    }

}

void *thread_read(void *args) {
        int cnt = 0;
    for (; cnt < 5; cnt++) {
                lock->LockShared();
                cout << "read val:" << val << endl;
                lock->UnlockShared();
            
    }

}

int main(int argc, char **argv) {
        int ret = 0;
        pthread_t t_write, t_read;

        lock = new SharedExclusiveLock();
        ret = pthread_create(&t_write, NULL, thread_write, NULL);
    if (ret < 0) {
                cout << "create thread write failed"<< endl;
                return -1;
            
    }

        ret = pthread_create(&t_read, NULL, thread_read, NULL);
    if (ret < 0) {
                cout << "create thread read failed"<< endl;
                return -1;
            
    }

        pthread_join(t_write, NULL);
        pthread_join(t_read, NULL);

        return 0;

}

