

/** 
 * @brief double include guard of `SimpleControl.hpp`
 */
#ifndef SimpleControlSimpleControl_h
#define SimpleControlSimpleControl_h

#include "SimpleControl_Core.hpp"


namespace SimpleControl { 

using Address = 
#ifdef Arduino_h
  __SimpleControl_Core :: __SimpleControl_Core<unsigned long, uint8_t, size_t>
#else
  __SimpleControl_Core :: __SimpleControl_Core<unsigned long, std :: uint8_t, std :: size_t >
#endif
;
}

#endif /* SimpleControlSimpleControl_h */
