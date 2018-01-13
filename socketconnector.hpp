//
//  socketconnector.hpp
//  Empires
//
//  Created by Zoe IAMZOE.io on 1/9/18.
//  Copyright © 2018 Zoe IAMZOE.io. All rights reserved.
//

#ifndef socketconnector_hpp
#define socketconnector_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
#include <fstream>
#include <utility>
#include <boost/algorithm/string/join.hpp>
#include <SFML/Graphics.hpp>

class socketconnector {
public:
    socketconnector ();
    void vSendMessage(std::string input);
    std::string vRead ();
    std::string sSeralizeVector( int first, int second, sf::Color data );
    void vDeSeralizeAndSetString( std::string sIn );
    std::vector<std::string> stringToVector (std::string sInput, char sSplitOn = ' ');
    sf::Color sfcGetData () { return sfcData; };
    int iFirst = 0, iSecond = 0;
    sf::Color sfcData;
    std::string sPush;
    bool bIsServer;
    int iCounter = 0;

private:
    int iSocket;
    int iReadValue;
    int iNewSocket;
    int iAddressSize;
    sockaddr_in saiAddress;
    fd_set sSet;
    char cBuffer[1024] = {0};
    std::string sOld = "";
};

#endif /* socketconnector_hpp */
