//
//  Serialized_STL.hpp
//  Serialized_test
//
//  Created by leico_studio on 2019/08/20.
//  Copyright © 2019 leico_studio. All rights reserved.
//

#ifndef SimpleControlSerialized_STL_h
#define SimpleControlSerialized_STL_h

#include <utility>
#include <type_traits> 

#include "Serialized_Arduino.hpp" 

namespace SimpleControl{ 
  
  class Serialized_STL : public Serialized_Arduino {

    public:

    using Serialized_Arduino :: Serialized_Arduino;

    template < typename T > 
    Serialized_STL( const T& other ) : Serialized_STL() { 
      copy_from( other );
    }

    template < typename T > 
    void copy_from( const T& other ){ 

      T buff = other;

      buff.resize( SIZE );

      std :: copy( buff.begin(), buff.end(), begin() );

    }


    void copy_from( const std :: array< value_type, SIZE >& other){ 
      std :: copy( other.begin(), other.end(), begin() );
    }



    template < typename T >
    void copy_to( T& other ){ 

      other.resize( SIZE );

      other.clear();

      std :: copy( begin(), end(), other.begin() );
    }


    void copy_to( std :: array< value_type, SIZE >& other ){ 
      std :: copy( begin(), end(), other.begin() );
    }

    using Serialized_Arduino :: copy_from;
    using Serialized_Arduino :: copy_to;




    value_type& at( const size_type n ) & {
      
      if( n >= SIZE )
        throw std :: out_of_range( "Serialized at &" );

      return operator[] ( std :: forward< const size_type >( n ) );
    }

    const value_type at( const size_type n ) const& {

      if( n >= SIZE )
        throw std :: out_of_range( "Serialized at const&" );


      return operator[] ( std :: forward< const size_type >( n ) );
      
    }

    value_type at( const size_type n ) && { 

      if( n >= SIZE )
        throw std :: out_of_range( "Serialized at &&" );

      return operator[] ( std :: forward< const size_type >( n ) );
    }




  };
}

#endif /* Serialized_STL_h */
