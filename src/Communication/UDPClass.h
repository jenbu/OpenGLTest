#pragma once

#include <pthread.h>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <functional>
#include <memory>
#include <vector>

#include "UDPComm.h"
using namespace UDPClientServer;

typedef void * (*THREADFUNCPTR)(void *);

namespace Communication
{
    class UDPClass
    {

    public:
        UDPClass();
        ~UDPClass();

        int UDPInit(std::function<void(char*)> func);
        void UDPTask();
        void MessageHandler(char* msg);
        
        void SendMsg(char* msg);
        void SendMsg(std::vector<int> vec);
        void SendMsg(std::vector<bool> vec);
        //bool RegisterMsgHandler(std::function<void(char*)> func) { m_Func = func; }

    private:

        std::thread m_Thread;
        std::function<void(char*)> m_Func;
        bool m_Close;

        static std::unique_ptr<UDPServer> m_Server;
        //static UDPServer* m_Server;

    };

}