//
//  socketclient.cpp
//  Empires
//
//  Created by Zoe IAMZOE.io on 1/10/18.
//  Copyright © 2018 Zoe IAMZOE.io. All rights reserved.
//

#include "socketclient.hpp"
#include <arpa/inet.h>

socketclient::socketclient ()
{
    iSocket = socket(AF_INET, SOCK_STREAM, 0);

    memset(&saiAddress, '0', sizeof(saiAddress));

    saiAddress.sin_family = AF_INET;
    saiAddress.sin_port = htons(3000);
    saiAddress.sin_addr.s_addr = INADDR_ANY;

    connect(iSocket, (struct sockaddr *)&saiAddress, sizeof(saiAddress));
}

void socketclient::vSendMessage(std::string input)
{
    send(iSocket, input.c_str(), input.size(), 0);
}
