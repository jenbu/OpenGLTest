#pragma once

#include <pthread.h>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <functional>

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
        void MessageHandler(char* msg);
        void UDPTask();
        //bool RegisterMsgHandler(std::function<void(char*)> func) { m_Func = func; }

    private:
        UDPClass* m_Instance;

        pthread_t m_pThread;
        std::thread m_Thread;
        //void (*m_Func)(char*);
        std::function<void(char*)> m_Func;
        bool m_Close;

        int m_TestInt;

        static UDPServer m_Server;


    };

}