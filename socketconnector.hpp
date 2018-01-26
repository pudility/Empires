//
//  socketconnector.hpp
//  Empires
//
//  Created by Zoe IAMZOE.io on 1/9/18.
//  Copyright © 2018 Zoe IAMZOE.io. All rights reserved.
//

#ifndef socketconnector_hpp
#define socketconnector_hpp

#define PORT 3000

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <SFML/Graphics.hpp>

class socketconnector {
public:
    socketconnector ();
    
    void vSendMessage(std::string input);
    void vDeSeralizeAndSetString( std::string sIn );

    std::string vRead ();
    std::string sSeralizeVector( int first, int second, sf::Color data );
    std::string sPush;
    std::vector<std::string> stringToVector (std::string sInput, char sSplitOn = ' ');
    
    sf::Color sfcGetData () { return sfcData; };
    sf::Color sfcData;

    int iFirst = 0, iSecond = 0;
    int iCounter = 0;
    bool bIsServer;

private:
    int iSocket;
    int iReadValue;
    int iNewSocket;
    int iAddressSize;
    
    sockaddr_in saiAddress;
    fd_set sSet;
    
    char cBuffer[1024] = {0};
    bool bHasSetThreadOnce = false;
    
    std::string sOld = "";
    std::string sRecived = "Recived";
    std::string sSendAlready = "";
    
    void server ();
    void client ();
    void vPrintColor ();
};

#endif /* socketconnector_hpp */
