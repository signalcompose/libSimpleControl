//
//  Serialized.h
//  SimpleControl
//
//  Created by leico_studio on 2019/08/16.
//  Copyright © 2019 leico_studio. All rights reserved.
//

#ifndef SimpleControlSerialized_h
#define SimpleControlSerialized_h


#ifdef Arduino_h
#include "Serialized_Arduino.hpp" 
#else
#include "Serialized_STL.hpp"
#endif

namespace SimpleControl { 

using Serialized = 
#ifdef Arduino_h
Serialized_Arduino;
#else
Serialized_STL;
#endif

}

#endif /* Serialized_h */
