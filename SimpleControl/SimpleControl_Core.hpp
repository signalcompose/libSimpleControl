

/**
 * @brief double include guard of `SimpleControl_Core.hpp`
 */
#ifndef SimpleControlSimpleControl_Core_h
#define SimpleControlSimpleControl_Core_h

#include "Serialized.hpp" 

namespace SimpleControl { 

  namespace __SimpleControl_Core{
    
    template < 
        typename ValueType
      , typename OctetType
      , typename SizeType
      , typename Iter      =       ValueType*
      , typename ConstIter = const ValueType* 
    > 
    class __SimpleControl_Core;

#   ifdef Arduino_h
      template < uint8_t, size_t >
#   else
      template <std :: uint8_t, std :: size_t>
#   endif
    class __SimpleControl_Core
    {

      public:
      using value_type = ValueType;
      using octet_type = OctetType;
      using size_type  = SizeType;

      using iterator       = Iter;
      using const_iterator = ConstIter;

      constexpr static size_type SIZE = sizeof(value_type) / sizeof(octet_type);

      private:
      union {
        value_type _value;
        octet_type _octet[ SIZE ];
      } _data;


      public:
      
      __SimpleControl_Core( const value_type& value = 0 ) : 
        _data._value(value)
      {}

      __SimpleControl_Core( const octet_type (&array)[ SIZE ] ) :
        __SimpleControl_Core()
      {
        copy_from( array );
      }

      __SimpleControl_Core( const Serialized& serialdata ) :
        __SimpleControl_Core()
      {
        if( Serialized :: SIZE != SIZE ) return;
        copy_from( serialdata );
      }

      void copy_from( const octet_type (&array)[ SIZE ] ){
        octet_copy( array, array + SIZE, _data._octet );
      }
      
      void copy_from( const value_type& value ){ 
        _data._value = value;
      }

      void copy_to( const octet_type (&array)[ SIZE ] ){ 
        octet_copy( _data._octet, _data._octet + SIZE, array );
      }

      void copy_to( const value_type& value ){ 
        _data._value = value;
      }


      /**
       * @brief decode value from Serialized class
       *
       * @param[in] data source of `Serialized` class
       *
       *
       * ### inspection
       *
       * ```
       * decoded data byte     lower byte process                              upper byte process
       *                       Serialized byte    bit mask       bit shift     Serialized byte      bit mask     bit shift 
       * --------------------------------------------------------------------------------------------------------------------
       *           byte(0) = ( (serialdata[ 0 ] & 0111 1111) >>          0 ) | ( (serialdata[ 1 ] & 0000 0001) <<        7 );
       *           byte(1) = ( (serialdata[ 1 ] & 0111 1110) >>          1 ) | ( (serialdata[ 2 ] & 0000 0011) <<        6 );
       *           byte(2) = ( (serialdata[ 2 ] & 0111 1100) >>          2 ) | ( (serialdata[ 3 ] & 0000 0111) <<        5 );
       *           byte(3) = ( (serialdata[ 3 ] & 0111 1000) >>          3 ) | ( (serialdata[ 4 ] & 0000 1111) <<        4 );
       *           byte(4) = ( (serialdata[ 4 ] & 0111 0000) >>          4 ) | ( (serialdata[ 5 ] & 0001 1111) <<        3 );
       *           byte(5) = ( (serialdata[ 5 ] & 0110 0000) >>          5 ) | ( (serialdata[ 6 ] & 0011 1111) <<        2 );
       *           byte(6) = ( (serialdata[ 6 ] & 0100 0000) >>          6 ) | ( (serialdata[ 7 ] & 0111 1111) <<        1 );
       *           byte(7) = ( (serialdata[ 8 ] & 0111 1111) >>          7 ) | ( (serialdata[ 9 ] & 0000 0001) <<        0 );
       * ```
       *
       * ### lower byte mask
       *
       * ```
       * index : lower byte mask   ->   + 1000 0000 ->   - 0000 0001  -> bit inversion
       * -------------------------   --------------   ---------------    ----------------
       *     0 : 0111 1111            0 : 1111 1111    0 : 1111 1110     0 : 0000 0001
       *     1 : 0111 1110            1 : 1111 1110    1 : 1111 1101     1 : 0000 0010
       *     2 : 0111 1100            2 : 1111 1100    2 : 1111 1011     2 : 0000 0100
       *     3 : 0111 1000            3 : 1111 1000    3 : 1111 0111     3 : 0000 1000
       *     4 : 0111 0000            4 : 1111 0000    4 : 1110 1111     4 : 0001 0000
       *     5 : 0110 0000            5 : 1110 0000    5 : 1101 1111     5 : 0010 0000
       *     6 : 0100 0000            6 : 1100 0000    6 : 1011 1111     6 : 0100 0000
       *     7 : 0111 1111            7 : 1111 1111    7 : 1111 1110     7 : 0000 0001
       *     8 : 0111 1110            8 : 1111 1110    8 : 1111 1101     8 : 0000 0010
       *     9 : 0111 1100            9 : 1111 1100    9 : 1111 1011     9 : 0000 0100
       *     ....                     ....             ....              ....
       * ```
       *
       *  lower byte mask + 1000 0000 - 0000 0001  = ~( 0000 0001 << index % 7 )
       *  lower byte mask                          = ~( 0000 0001 << index % 7 ) - 0111 1111
       *
       *
       * ### upper byte mask
       * 
       * ```
       * index : upper byte mask  ->  bit inversion -> left bit shift 
       * ------------------------    --------------    ---------------
       *     0 : 0000 0001            0 : 1111 1110     0 : 0111 1111
       *     1 : 0000 0011            1 : 1111 1100     1 : 0111 1110
       *     2 : 0000 0111            2 : 1111 1000     2 : 0111 1100
       *     3 : 0000 1111            3 : 1111 0000     3 : 0111 1000
       *     4 : 0001 1111            4 : 1110 0000     4 : 0111 0000
       *     5 : 0011 1111            5 : 1100 0000     5 : 0110 0000
       *     6 : 0111 1111            6 : 1000 0000     6 : 0100 0000
       *     7 : 0000 0001            7 : 1111 1110     7 : 0111 1111
       *     8 : 0000 0011            8 : 1111 1100     8 : 0111 1110
       *     9 : 0000 0111            9 : 1111 1000     9 : 0111 1100
       *     ....                     ....              .....
       * ```
       *
       *
       * ~upper byte mask >> 1 =   lower bit mask
       * ~upper byte mask      =   lower bit mask << 1
       *  upper byte mask      = ~(lower bit mask << 1)
       *
       *
       * ### byte index
       *
       * ```
       *         byte index
       * index : lower : upper
       * -----------------------
       *     0 :     0 :     1
       *     1 :     1 :     2
       *     2 :     2 :     3
       *     3 :     3 :     4
       *     4 :     4 :     5
       *     5 :     5 :     6
       *     6 :     6 :     7
       *     7 :     8 :     9
       *     8 :     9 :    10
       *     9 :    10 :    11
       * .....
       * ```
       * 
       * upper byte index = lower byte index + 1
       * lower byte index = index + (index / 7);
       *
       */
      void serial_decode( const Serialized& serialdata ){ 

        octet_type byte = 0;

        const octet_type bit_7 = 0b01111111;
        const octet_type bit_1 = 0b00000001;

        const octet_type carry_limit = sizeof(Serialized :: value_type) * 8 - 1;
        const octet_type octet_bit   = sizeof( octet_type             ) * 8 - 1;

        for( size_type it = 0 ; it != SIZE ; ++ it ){

          const octet_type lower_byte_mask = ~(bit_1 << (it % 7) ) - bit_7;
          const octet_type upper_byte_mask = ~(lower_byte_mask << 1);

          const octet_type pos = it + it / 7;

          const octet_type lower_byte = ( serialdata[ pos     ] & lower_byte_mask ) >> it;
          const octet_type upper_byte = ( serialdata[ pos + 1 ] & upper_byte_mask ) << ( octet_bit - it );

          _data._octet[ it ] = upper_byte | lower_byte;

        }
      }

      /**
       *
       * @brief encode value to Serialized class
       *
       * @param[out] store of `Serialized` class
       *
       *
       * ### inspection
       *
       * ```
       * serial data byte   lower byte process                       upper byte process
       *                    data byte     bitmask       bit shift    data byte     bit mask      bit shift
       * ---------------------------------------------------------------------------------------------------
       *         data(01) = databyte[ 0 ] & 0b0111 1111 >>       0 | databyte[ * ] & 0b0000 0000 <<      0
       *         data(02) = databyte[ 0 ] & 0b1000 0000 >>       7 | databyte[ 1 ] & 0b0011 1111 <<      1
       *         data(03) = databyte[ 1 ] & 0b1100 0000 >>       6 | databyte[ 2 ] & 0b0001 1111 <<      2
       *         data(04) = databyte[ 2 ] & 0b1110 0000 >>       5 | databyte[ 3 ] & 0b0000 1111 <<      3
       *         data(05) = databyte[ 3 ] & 0b1111 0000 >>       4 | databyte[ 4 ] & 0b0000 0111 <<      4
       *         data(06) = databyte[ 4 ] & 0b1111 1000 >>       3 | databyte[ 5 ] & 0b0000 0011 <<      5
       *         data(07) = databyte[ 5 ] & 0b1111 1100 >>       2 | databyte[ 6 ] & 0b0000 0001 <<      6
       *         data(08) = databyte[ 6 ] & 0b1111 1110 >>       1 | databyte[ 7 ] & 0b0000 0000 <<      7
       *         data(09) = databyte[ 7 ] & 0b0111 1111 >>       0 | databyte[ * ] & 0b0000 0000 <<      0
       *         data(10) = databyte[ 7 ] & 0b1000 0000 >>       7 | databyte[ 8 ] & 0b0011 1111 <<      1
       * ```
       *
       * ### upper byte mask
       *
       * ```
       * index: upper byte mask   -> + 0000 0001    <-  (0000 0001 << (7 - (index % 8))) & 0111 1111 +     <- index:  0000 0001 << (7 - (index % 8))
       *                                                (0000 0001 << (7 - (index % 8))) & 1000 0000 >> 7
       * -----------------------    ---------------     -------------------------------------------------     ---------------------------------------
       *     0: 0000 0000              0000 0001                     0000 0001                                    0:  1000 0000
       *     1: 0011 1111              0100 0000                     0100 0000                                    1:  0100 0000
       *     2: 0001 1111              0010 0000                     0010 0000                                    2:  0010 0000
       *     3: 0000 1111              0001 0000                     0001 0000                                    3:  0001 0000
       *     4: 0000 0111              0000 1000                     0000 1000                                    4:  0000 1000
       *     5: 0000 0011              0000 0100                     0000 0100                                    5:  0000 0100
       *     6: 0000 0001              0000 0010                     0000 0010                                    6:  0000 0010
       *     7: 0000 0000              0000 0001                     0000 0001                                    7:  0000 0001
       *     8: 0000 0000              0000 0001                     0000 0001                                    8:  1000 0000
       *     9: 0011 1111              0100 0000                     0100 0000                                    9:  0100 0000
       * ```
       *
       *                     bit = 0000 0001 << (7 - (index % 8))
       * upper byte mask = ( bit & 0111 1111 +  (bit & 1000 0000) >> 7 ) - 1
       *
       *
       * ### upper byte array index
       *
       * ```
       * index : array index -> n - (n - 1) / 8
       * -------------------    --------
       *     0 : *                 0
       *     1 : 1                 1
       *     2 : 2                 2
       *     3 : 3                 3
       *     4 : 4                 4
       *     5 : 5                 5
       *     6 : 6                 6
       *     7 : 7                 7
       *     8 : *                 8
       *     9 : 8                 8
       *    10 : 9                 9
       *    11 : 10               10
       *    12 : 11               11
       *    13 : 12               12
       *    14 : 13               13
       *    15 : 14               14
       *    16 : *                15
       *    17 : 15               15
       *    18 : 16               16
       * ```
       *
       * `*` don't care
       *
       * upper byte index = index - (index - 1) / 8
       *
       */

      void serial_encode( Serialized& output ){


        constexpr octet_type bit_1 = 0b00000001;

        octet_type msb;
        octet_type lsb;
        octet_type pos;
        octet_type carry = 0;

        for( size_type it = 0 ; it != SIZE ; ++ it ){

          const octet_type calc = ~( bit_1 << ( ( 6 + it ) % 7 ) ) << 1;
          msb = ~calc + 0b00000010;
          lsb = (calc - 0b01111111) << 1;

          pos = it - ((it + 7) / 8);

          output[ it ] =  _data._octet[ pos ] & msb |  _data._octet[ pos + 1 ] & lsb;



        }
/*
        byte1  = _data._octet[ 0 ] & 0b1111 1110 | _data._octet[ 1 ] & 0b0000 0000;
        byte2  = _data._octet[ 0 ] & 0b0000 0001 | _data._octet[ 1 ] & 0b1111 1100;
        byte3  = _data._octet[ 1 ] & 0b0000 0011 | _data._octet[ 2 ] & 0b1111 1000;
        byte4  = _data._octet[ 2 ] & 0b0000 0111 | _data._octet[ 3 ] & 0b1111 0000;
        byte5  = _data._octet[ 3 ] & 0b0000 1111 | _data._octet[ 4 ] & 0b1110 0000;
        byte6  = _data._octet[ 4 ] & 0b0001 1111 | _data._octet[ 5 ] & 0b1100 0000;
        byte7  = _data._octet[ 5 ] & 0b0011 1111 | _data._octet[ 6 ] & 0b1000 0000;
        byte8  = _data._octet[ 6 ] & 0b0111 1111 | _data._octet[ 7 ] & 0b0000 0000;
        byte9  = _data._octet[ 7 ] & 0b1111 1110 | _data._octet[ 8 ] & 0b0000 0000;
        byte10 = _data._octet[ 7 ] & 0b0000 0001 | _data._octet[ 8 ] & 0b1111 1100;
*/           
        
      }

      

      protected;
      bool octet_copy( const_iterator begin, const_iterator end, iterator target_begin ){
        
        if( end < begin ) 
          return false;

        while( begin != end )
          *target_begin ++ = * begin ++;

        return true;
      }
      
    };
  }
}


#endif /* SimpleControlSimpleControl_Core_h */
