#include <iostream>
#include <queue>
#include <memory>
#include <string>
#include <csignal>
#include "pthread.h"

#include "webrtc/base/messagequeue.h"
#include "webrtc/base/socketserver.h"
#include "webrtc/base/event.h"

using namespace rtc;
using namespace std;

class MsgData : public MessageData {
    public:
        MsgData(){}
        ~MsgData(){}
    void setStr(string str) {
                unique_str_ = str;
            
    }
    string& getStr() {
                return unique_str_;
            
    }
    private:
        string unique_str_;

};

class MsgHandler : public MessageHandler {
    public:
    virtual void OnMessage(Message* msg) {
        switch(msg->message_id) {
            case 0: {
                                MsgData *data = (MsgData *) msg->pdata;
                                cout << "data:" << data->getStr() << endl;
                            
            } break;
            default: {
                                cout << "unknow id" << msg->message_id << endl;
                            
            } break;
                    
        }
            
    }
    private:


};

class mysocket : public SocketServer {
    public:
    mysocket() {
                event_ = new Event(true, true);
                event_->Reset();
            
    }
    ~mysocket() {
                delete(event_);
            
    }
    virtual bool Wait(int cms, bool process_io) {
                cout << "mysocket wait" << endl;
                event_->Wait(event_->kForever);
            
    }
    virtual void WakeUp() {
                cout << "mysocket wakeup" << endl;
                event_->Set();
            
    }
    virtual Socket* CreateSocket(int type) {
        
            
    }
    virtual Socket* CreateSocket(int family, int type) {

            
    }
    virtual AsyncSocket* CreateAsyncSocket(int type) {
        
            
    }
    virtual AsyncSocket* CreateAsyncSocket(int family, int type) {

            
    }
    private:
        Event *event_;


};

void signalExec(int int_id) {
        cout << "exec signal" << endl;
        exit(-1);

}

int main(int argc, char **argv) {
        int ret = 0;

        signal(SIGINT, signalExec);

        MsgData data;
        data.setStr("sliver");

        MsgHandler handler;

        Message *msg = new Message();
        msg->message_id = 0;
        msg->pdata = &data;
        msg->phandler = &handler;

        mysocket *m_socket = new mysocket();
        MessageQueue queue(m_socket, true);

        Location locate;
        queue.Post(locate, &handler);
        queue.Get(msg);

        return 0;

}

