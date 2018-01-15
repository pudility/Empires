//
//  rules.hpp
//  Empires
//
//  Created by Zoe IAMZOE.io on 1/14/18.
//  Copyright © 2018 Zoe IAMZOE.io. All rights reserved.
//

#ifndef rules_h
#define rules_h

#include <iostream>
#include "person.h"

class rules {
public:
    static int const iTeams = 2;
    static bool const bRandomStart = true;
    bool vOnContact (Person *pPersonOne, Person *pPersonTwo) {
        if ( !pPersonOne || !pPersonTwo )
            return false;    // TODO: Handle this error
        
        // Gives person two a slight advantage ( wins ties ) because they are the defending force.
        return pPersonOne->GetStrength() > pPersonTwo->GetStrength();
    }
};

#endif /* rules_h */
