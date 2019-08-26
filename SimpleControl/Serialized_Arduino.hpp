/**
 *  @file           Serialized_Arduino.hpp
 *  @brief          This class provides serialized SimpleControl data implementation for Arduino.
 *  @author         leico
 *  @date           2019.08.19
 *  $Version:       0$
 *  $Revision:      1$
 *  @par            
 */

#ifndef SimpleControlSerialized_Arduino_h
#define SimpleControlSerialized_Arduino_h

#include "Serialized_Core.hpp"

namespace SimpleControl { 

  /**
   * @brief for Arduino class, alias of __Serialized_Core< uint8_t, size_t >
   *
   */
  using Serialized_Arduino = __Serialized_Core :: __Serialized_Core< 
      uint8_t
    , size_t 
  >;
}


#endif /* Serialized_Arduino_h */
