/**
 *  @file           Serialized.hpp
 *  @brief          This class provides a format and some functions, to transfer Address or Data class on any serial protocol.
 *  @author         leico
 *  @date           2019.08.19
 *  $Version:       0$
 *  $Revision:      1$
 *  @par            
 * 
 * In Arduino, Serialized class is alias of Serialized_Arduino, the other side Serialized is alias of Serialized_STL.
 * When used this with Arduino, This header includes `Serialized_Arduino.hpp`, otherwise includes `Serialized_STL.hpp`
 */



/**
 * @brief double include guard of `Serialized.hpp`
 */
#ifndef SimpleControlSerialized_h
#define SimpleControlSerialized_h


#ifdef Arduino_h
#include "Serialized_Arduino.hpp" 
#else
#include "Serialized_STL.hpp"
#endif


/**
 * @brief SimpleControl namespace
 *
 * Contains all of SimpleControl functions
 */
namespace SimpleControl { 

/**
 * @brief      Defined Serialzed class
 *
 * In Arduino, Serialized class is alias of Serialized_Arduino, the other side Serialized is alias of Serialized_STL
 *
 * Serialized_Arduino provides functions for `Serialized :: value_type` array, in addition Serialized_STL provides functions for some types,
 *  ex. `std :: vector<Serialized :: value_type >`
 */
using Serialized = 
#ifdef Arduino_h
Serialized_Arduino;
#else
Serialized_STL;
#endif

}

#endif /* Serialized_h */
