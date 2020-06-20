#include "UDPClass.h"


namespace Communication
{
    
    std::unique_ptr<UDPServer> UDPClass::m_Server = std::make_unique<UDPClientServer::UDPServer>("localhost", 20001);

    UDPClass::UDPClass()
    : m_Thread(&UDPClass::UDPTask, this), m_Close(false)

    {
        
    }

    UDPClass::~UDPClass()
    {
        m_Close = true;
    }

    int UDPClass::UDPInit(std::function<void(char*)> func)
    {
        m_Func = func;


        //Med Detach() vil man ikke kunne finne ut når tasken er ferdig med join() lenger, må bruke noen andre mekanismer
        m_Thread.detach();
        
        //if(status != 0)
        //    std::cout << "Some error while creating thread, error code: " << status << std::endl;
        
        return 0;//status;
    }

    void UDPClass::UDPTask()
    {
        std::cout << "Starting UDPTask()" << std::endl;
        char msg[60];
        char response[60] = "Response from OpenGlProj";
        
        //UDPServer m_Server("localhost", 20001);
        //m_Server = new UDPServer("localhost", 20001);
        //m_Server = std::make_unique<UDPClientServer::UDPServer>("localhost", 20001);

        while(!m_Close)
        {
            //TODO timeout for server recv()
            memset(msg, 0, sizeof(msg));
            m_Server->recv(msg, 60);
            MessageHandler(msg);
            
            std::cout << "Sending message" << std::endl;
            m_Server->send(response, 60);
        }

        std::cout << "Exiting UDPTask()" << std::endl; 
    }

    void UDPClass::MessageHandler(char* msg)
    {
        if(m_Func)
            m_Func(msg);
        else
            std::cout << "UDPClass::MessageHandler:  m_Func has not been assigned function!" << std::endl;
    }

    void UDPClass::SendMsg(char* msg)
    {
        m_Server->send(msg, 60);
    }

}