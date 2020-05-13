#include "UDPClass.h"


namespace Communication
{
    
    UDPClass::UDPClass(std::function<void()> func)
    {
        myFunc = func;
        myFunc();
    }

    UDPClass::~UDPClass()
    {

    }

    int UDPClass::UDPInit()
    {
        int status = pthread_create(&m_pThread, NULL, (THREADFUNCPTR)&UDPClass::UDPTask, NULL);
        myFunc();
        if(status != 0)
            std::cout << "Some error while creating thread, error code: " << status << std::endl;
        
        return status;
        
    }

    void UDPClass::UDPTask()
    {
        std::cout << "Starting UDPTask()" << std::endl;
        char msg[60];
        char response[60] = "Response from OpenGlProj";
        UDPServer m_Server("localhost", 20001);
        myFunc();
        while(true)
        {
            sleep(2);
            m_Server.recv(msg, 60);
            std::cout << msg << std::endl;
            myFunc();
            
            std::cout << "msg: " << msg    << std::endl
                      << "Sending message" << std::endl;

            m_Server.send(response, 60);
        }
    }

    void UDPClass::MessageHandler(char* msg)
    {
        char abc[10] = "Heisann";
        m_Func(msg);
    }

}