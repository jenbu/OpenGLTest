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
        UDPClass(std::function<void()> func);
        ~UDPClass();

        int UDPInit();
        void MessageHandler(char* msg);
        void UDPTask();
        bool RegisterMsgHandler(void (*func) (char*)) { m_Func = func; }

    private:
        UDPClass* m_Instance;

        pthread_t m_pThread;
        std::thread m_Thread;
        void (*m_Func)(char*);
        std::function<void()> myFunc;

        static UDPServer m_Server;


    };

}