//
//  socketclient.hpp
//  Empires
//
//  Created by Zoe IAMZOE.io on 1/10/18.
//  Copyright © 2018 Zoe IAMZOE.io. All rights reserved.
//

#ifndef socketclient_hpp
#define socketclient_hpp

#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <string>

class socketclient {
public:
    socketclient ();
    void vSendMessage(std::string input);
    
private:
    int iSocket;
    int iSendValue;
    int iNewSocket;
    int iAddressSize;
    sockaddr_in saiAddress;
    sockaddr_in saiServerAddress;
    fd_set sSet;
    char cBuffer[1024] = {0};
};

#endif /* socketclient_hpp */
