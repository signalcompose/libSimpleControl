/**
 *  @file       SimpleControl_Types.hpp
 *  @brief      This file provides a SimpleControl message types.
 *  @author     leico
 *  @date       2020.01.07
 *  $Version:   0$
 *  $Revision:  1$
 *
 */

#ifndef SimpleControlSimpleControl_Types_h
#define SimpleControlSimpleControl_Types_h


#ifdef Arduino_h
#else
#include <cstdint> 
#endif


namespace SimpleControl { 

  using Data = float;

  using Address = 
# ifdef Arduino_h
    uint32_t;
# else
    std :: uint32_t;
# endif

}


#endif /* SimpleControlSimpleControl_Types_h */
