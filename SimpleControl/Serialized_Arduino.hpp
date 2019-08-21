//
//  Serialized_Arduino.h
//  Serialized_test
//
//  Created by leico_studio on 2019/08/19.
//  Copyright © 2019 leico_studio. All rights reserved.
//

#ifndef SimpleControlSerialized_Arduino_h
#define SimpleControlSerialized_Arduino_h

#ifdef Arduino_h
#else
#include <cstdint>
#include <algorithm>
#endif

namespace SimpleControl { 

  class Serialized_Arduino{

    public: 
    using value_type = 
#   ifdef Arduino_h
      uint8_t;
#   else
      std :: uint8_t;
#   endif

    using size_type = 
#   ifdef Arduino_h
      size_t;
#   else
      std :: size_t;
#   endif

    using iterator       =       value_type*;
    using const_iterator = const value_type*;

    constexpr static value_type SIZE = 5;

    protected: 
    value_type _data[ SIZE ];

#   ifdef Arduino_h
    bool copy( value_type* begin, value_type* end, value_type* target_begin ){ 

      if( end < begin ) 
        return false;

      while( begin != end )
        *target_begin ++ = *begin ++;

      return true;
    }
#   endif





    public: 

    Serialized_Arduino( 
        const value_type v1 = 0
      , const value_type v2 = 0
      , const value_type v3 = 0
      , const value_type v4 = 0
      , const value_type v5 = 0
    ) :
    _data{ v1, v2, v3, v4, v5 }
    {}

    Serialized_Arduino( const Serialized_Arduino& other ) :
    Serialized_Arduino( 
        other._data[ 0 ]
      , other._data[ 1 ]
      , other._data[ 2 ]
      , other._data[ 3 ]
      , other._data[ 4 ]
    ){}

    Serialized_Arduino( const value_type (&array)[ SIZE ] ) : 
    Serialized_Arduino( 
        array[ 0 ]
      , array[ 1 ]
      , array[ 2 ]
      , array[ 3 ]
      , array[ 4 ]
    ){}


    void copy_from( const value_type (&array)[ SIZE ] ){ 

#     ifdef Arduino_h
      copy
#     else
      std :: copy 
#     endif
      ( array, array + SIZE, begin() );
    } 


    void copy_from( const Serialized_Arduino& other ){ 

#     ifdef Arduino_h
      copy
#     else
      std :: copy
#     endif
      ( other.begin(), other.end(), begin() );
    }



    void copy_to( value_type (&array)[ SIZE ] ){
      
#     ifdef Arduino_h
      copy
#     else
      std :: copy
#     endif
      ( begin(), end(), array );
    }


    
    void copy_to( Serialized_Arduino& other ){ 
#     ifdef Arduino_h
      copy
#     else
      std :: copy
#     endif
      ( begin(), end(), other.begin() );
    }


    template < typename T > 
    Serialized_Arduino& operator= ( const T& other ) & { 
      copy_from( other );
      return *this;
    }

    value_type&       operator[] ( const size_type n ) &      { return _data[ n ]; }
    const value_type& operator[] ( const size_type n ) const& { return _data[ n ]; }
    value_type        operator[] ( const size_type n ) &&     { return _data[ n ]; }

          iterator begin( void )       { return _data; }
    const_iterator begin( void ) const { return _data; }

          iterator end( void )       { return _data + SIZE; }
    const_iterator end( void ) const { return _data + SIZE; }


    const bool is_address( void ) const& noexcept { 
      
      for( const_iterator iter = begin(), stop = end() ; iter != stop ; ++ iter )
        if( *iter < 0b10000000 ) 
          return false;

      if( (*(end() - 1) & 0b11110000) != 0b11110000 ) 
        return false;

      return true;
    }

    const bool is_data( void ) const& noexcept {
      for( const_iterator iter = begin(), stop = end() ; iter != stop ; ++ iter )
        if( *iter > 0b01111111 )
          return false;

      if( (*(end() - 1) & 0b01110000) != 0b01110000 )
        return false;

      return true;
    }

    const bool is_correct( void ) const& noexcept { 
      return is_address() || is_data();
    }
    


  };
}


#endif /* Serialized_Arduino_h */
