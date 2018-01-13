//
//  socketconnector.cpp
//  Empires
//
//  Created by Zoe IAMZOE.io on 1/9/18.
//  Copyright © 2018 Zoe IAMZOE.io. All rights reserved.
//

#include "socketconnector.hpp"

bool bGetIsServer ()
{
    //get an input from the user
    std::cout << "Start: ";
    std::string input;
    std::cin >> input;
    std::cout << "Starting: " << input << std::endl;

    bool bIsServer;

    //figure out what the user said
    if (input == "server")
        bIsServer = true;
    else
        bIsServer = false;

    return bIsServer;
}

socketconnector::socketconnector ()
{
    bIsServer = bGetIsServer();

    if (bIsServer)
    {
        iSocket = socket(AF_INET, SOCK_STREAM, 0);

        saiAddress.sin_family = AF_INET;
        saiAddress.sin_port = htons(3000);
        saiAddress.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY is great because it makes your socket listen on all networks

        bind(iSocket, (sockaddr *)&saiAddress, sizeof(saiAddress));
        listen(iSocket, SOMAXCONN);

        iAddressSize = sizeof(saiAddress);
        iNewSocket = accept(iSocket, (struct sockaddr *)&saiAddress, (socklen_t *)&iAddressSize);

        read( iNewSocket, cBuffer, 1024 );
        std::cout << "Got: " << cBuffer << std::endl;
    }
    else
    {
        iSocket = socket(AF_INET, SOCK_STREAM, 0);

        memset(&saiAddress, '0', sizeof(saiAddress));

        saiAddress.sin_family = AF_INET;
        saiAddress.sin_port = htons(3000);
        saiAddress.sin_addr.s_addr = INADDR_ANY;

        connect(iSocket, (struct sockaddr *)&saiAddress, sizeof(saiAddress));

        std::string test = "test";
        send(iSocket, test.c_str(), test.size(), 0);
    }
}

void socketconnector::vSendMessage(std::string input)
{
    if (iCounter == 500)
    {
        iCounter = 0;

        if (bIsServer)
            socketconnector::vDeSeralizeAndSetString(vRead());
        else
        {
            send(iSocket, sPush.c_str(), sPush.size(), 0);
            sPush = "";
        }
    }
    else
        sPush.append(input);
    iCounter++;
}

std::string socketconnector::vRead()
{
    read( iNewSocket, cBuffer, 1024 );
    return cBuffer;
}

std::string socketconnector::sSeralizeVector( int first, int second, sf::Color data )
{
    std::string s = "";

    s.append(std::to_string(first))
    .append(",")
    .append(std::to_string(second))
    .append(":")
    .append(std::to_string(data.r))
    .append(",")
    .append(std::to_string(data.g))
    .append(",")
    .append(std::to_string(data.b))
    .append(" ");

    return s;
}

void socketconnector::vDeSeralizeAndSetString( std::string sIn )
{
    for (auto i: socketconnector::stringToVector(sIn))
    {
        std::vector<std::string> svSplitInput = socketconnector::stringToVector(i, ':');
        if (svSplitInput.size() > 1)
        {
            std::vector<std::string> svSplitSecond = socketconnector::stringToVector(svSplitInput[0], ',');
            std::vector<std::string> svSplitColor = socketconnector::stringToVector(svSplitInput[1], ',');

            if (svSplitSecond.size() > 1 && svSplitColor.size() > 2)
            {
                try
                {
                    sfcData = sf::Color ( std::stoi(svSplitColor[0]),
                                          std::stoi(svSplitColor[1]),
                                          std::stoi(svSplitColor[2]) );
                    std::cout << "Color: " << std::to_string(sfcData.r) << "," << std::to_string(sfcData.g) << "," << std::to_string(sfcData.b) << "\n";
                    iFirst = std::stoi(svSplitSecond[0]);
                    iSecond = std::stoi(svSplitSecond[1]);
                }
                catch (...)
                {
                    continue;
                }
            }
        }
    }
}

std::vector<std::string> socketconnector::stringToVector (std::string sInput, char sSplitOn)
{
    std::string sTest;
    std::vector<std::string> svSplitData;

    if (sSplitOn != ' ')
        std::replace(sInput.begin(), sInput.end(), sSplitOn, ' ');

    std::stringstream ss(sInput);

    while (ss >> sTest)
        svSplitData.push_back(sTest);

    return svSplitData;
}
