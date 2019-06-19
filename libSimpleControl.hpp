//
//  libSimpleControl.hpp
//  lei.SerialToSimpleControl
//
//  Created by leico_studio on 2019/06/19.
//

#ifndef libSimpleControl_hpp
#define libSimpleControl_hpp

#include <algorithm> 
#include <vector>
#include <array>

namespace SimpleControl {

  struct Format { 
    unsigned long _address;
    float         _value;
  };

  const static unsigned char FORMAT_SIZE = sizeof( Format );

  class libSimpleControl { 

    private:
 
    using uc_allocator = std :: allocator < unsigned char >;
    using uc_vec       = std :: vector    < unsigned char, uc_allocator >;
    using uc_array     = std :: array     < unsigned char, FORMAT_SIZE >;

    union Core { 
      Format        _format;
      unsigned char _octet[ FORMAT_SIZE ];

      explicit Core ( const Format& format = {0, 0} ) : _format( format ) {}

      explicit Core ( const unsigned char* octet, const size_t size ) { Octet( octet, size ); }

      template < typename T > 
      explicit Core ( const T& octet ){ Octet( octet ); }


      // required 
      // T :: value_type == unsigned char
      // T :: size()     == FORMAT_SIZE
      // T :: begin()
      // T :: end()
      //
      // ex.
      //   std :: vector< unsigned char >
      // , std :: array < unsigned char, FORMAT_SIZE >
      template< typename T>
      void Octet( const T& octet ){ 

        static_assert( std :: is_same< typename T :: value_type, unsigned char > :: value , "This function only available on unsigned char value type" );

        if( octet.size() != FORMAT_SIZE ) return;

        std :: copy( octet.begin(), octet.end(), _octet );
      }

      void Octet( const unsigned char* octet, const size_t size ){ 
        if( size != FORMAT_SIZE ) return;

        std :: copy( octet, octet + FORMAT_SIZE, _octet );
      }
    };


    Core _core;

    
    public: 

    explicit libSimpleControl ( void ){}
    explicit libSimpleControl ( const Format& format )                          : _core( format )                     {}
    explicit libSimpleControl ( const unsigned char* octet, const size_t size ) : _core( octet, size )                {}
    explicit libSimpleControl ( const uc_vec   &vec   )                         : _core( vec   ) {}
    explicit libSimpleControl ( const uc_array &array )                         : _core( array ) {}

    void Address( const unsigned long address ){ _core._format._address = address; }
    void Value  ( const float         value   ){ _core._format._value   = value;   }
    
    const unsigned long Address( void ) const { return _core._format._address; }
    const float         Value  ( void ) const { return _core._format._value;   }



    void Octet ( const unsigned char* octet, const size_t size ) {  _core.Octet( octet, size ); }

    template< typename T >
    void Octet( const T& octet ){ 
      _core.Octet( octet );
    }

    
    const unsigned char* Octet ( void ) const { return _core._octet; }

    


  };

}

#endif /* libSimpleControl_hpp */
