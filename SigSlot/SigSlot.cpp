#include <iostream>

#include "webrtc/base/sigslot.h"

using namespace std;

class sender {
    public:
        sigslot::signal2<string, char *> signal_;
        char str[20];
        char a;
    void send() {
                static int val = 0;
                snprintf(str, 20, "%s", "sliver.chen");
                printf("my address is 0x%x\n", &a);
                signal_(this->str, &a);
            
    }

};

class recver : public sigslot::has_slots<> {
    public:
    void OnDanger(string msg, char *p) {
                cout << msg << endl;
                printf("addr:%x\n", p);
            
    }

};

int main(int argc, char **argv) {
        int ret = 0;
        sender s;
        recver r;

        s.signal_.connect(&r, &recver::OnDanger);

        int i = 0;
    while (i++ < 10) {
                s.send();
            
    }

        return 0;

}
