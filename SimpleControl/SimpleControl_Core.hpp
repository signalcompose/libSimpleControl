

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
        _data{value}
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
       * @param[in] serialdata source of `Serialized` class
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
       * @param[out] output of `Serialized` class
       *
       *
       * ### inspection
       *
       * ```
       * serial data byte   lower byte process                       upper byte process
       *                    data byte        bitmask     bit shift    data byte        bit mask    bit shift
       * ---------------------------------------------------------------------------------------------------
       *         data(01) = databyte[  0 ] & 0b0111 1111 >>       0 | databyte[  * ] & 0b0000 0000 <<      *
       *         data(02) = databyte[  0 ] & 0b1000 0000 >>       7 | databyte[  1 ] & 0b0011 1111 <<      1
       *         data(03) = databyte[  1 ] & 0b1100 0000 >>       6 | databyte[  2 ] & 0b0001 1111 <<      2
       *         data(04) = databyte[  2 ] & 0b1110 0000 >>       5 | databyte[  3 ] & 0b0000 1111 <<      3
       *         data(05) = databyte[  3 ] & 0b1111 0000 >>       4 | databyte[  4 ] & 0b0000 0111 <<      4
       *         data(06) = databyte[  4 ] & 0b1111 1000 >>       3 | databyte[  5 ] & 0b0000 0011 <<      5
       *         data(07) = databyte[  5 ] & 0b1111 1100 >>       2 | databyte[  6 ] & 0b0000 0001 <<      6
       *         data(08) = databyte[  6 ] & 0b1111 1110 >>       1 | databyte[  * ] & 0b0000 0000 <<      *
       *         data(09) = databyte[  7 ] & 0b0111 1111 >>       0 | databyte[  * ] & 0b0000 0000 <<      *
       *         data(10) = databyte[  7 ] & 0b1000 0000 >>       7 | databyte[  8 ] & 0b0011 1111 <<      1
       *         data(11) = databyte[  8 ] & 0b1100 0000 >>       6 | databyte[  9 ] & 0b0001 1111 <<      2
       *         data(12) = databyte[  9 ] & 0b1110 0000 >>       5 | databyte[ 10 ] & 0b0000 1111 <<      3
       *         data(13) = databyte[ 10 ] & 0b1111 0000 >>       4 | databyte[ 11 ] & 0b0000 0111 <<      4
       *         data(14) = databyte[ 11 ] & 0b1111 1000 >>       3 | databyte[ 12 ] & 0b0000 0011 <<      5
       *         data(15) = databyte[ 12 ] & 0b1111 1100 >>       2 | databyte[ 13 ] & 0b0000 0001 <<      6
       *         data(16) = databyte[ 13 ] & 0b1111 1110 >>       1 | databyte[  * ] & 0b0000 0000 <<      *
       *         data(17) = databyte[ 14 ] & 0b0111 1111 >>       0 | databyte[  * ] & 0b0000 0000 <<      *
       *         data(18) = databyte[ 14 ] & 0b1000 0000 >>       7 | databyte[ 15 ] & 0b0011 1111 <<      1
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
       * ### lower byte mask
       *
       * ```
       * index: lower byte mask  ->  << index % 8 == 0 ? 1 : 0    <-  index % 8 == 0 ? ~(upper byte mask + 1) :  <-    + 0000 0001   <-  index: upper byte mask 
       *                                                                ~((upper byte mask + 1 << 1) - 1)              
       * ----------------------     -----------------------------     ------------------------------------------    ---------------      -----------------------
       *     0: 0111 1111            00: 1111 1110 (<< 1)              00:   1111 1110 ~(0000 0001)                 00:  0000 0001        00: 0000 0000       
       *     1: 1000 0000            01: 1000 0000                     01:   1000 0000   ~(0111 1111)               01:  0100 0000        01: 0011 1111       
       *     2: 1100 0000            02: 1100 0000                     02:   1100 0000   ~(0011 1111)               02:  0010 0000        02: 0001 1111       
       *     3: 1110 0000            03: 1110 0000                     03:   1110 0000   ~(0001 1111)               03:  0001 0000        03: 0000 1111       
       *     4: 1111 0000            04: 1111 0000                     04:   1111 0000   ~(0000 1111)               04:  0000 1000        04: 0000 0111       
       *     5: 1111 1000            05: 1111 1000                     05:   1111 1000   ~(0000 0111)               05:  0000 0100        05: 0000 0011       
       *     6: 1111 1100            06: 1111 1100                     06:   1111 1100   ~(0000 0011)               06:  0000 0010        06: 0000 0001       
       *     7: 1111 1110            07: 1111 1110                     07:   1111 1110   ~(0000 0001)               07:  0000 0001        07: 0000 0000       
       *     8: 0111 1111            08: 1111 1110 (<< 1)              08:   1111 1110 ~(0000 0001)                 08:  0000 0001        08: 0000 0000       
       *     9: 1000 0000            09: 1000 0000                     09:   1000 0000   ~(0111 1111)               09:  0100 0000        09: 0011 1111 
       *    10: 1100 0000            10: 1100 0000                     10:   1100 0000   ~(0011 1111)               10:  0010 0000        10: 0001 1111
       *    11: 1110 0000            11: 1110 0000                     11:   1110 0000   ~(0001 1111)               11:  0001 0000        11: 0000 1111
       *    12: 1111 0000            12: 1111 0000                     12:   1111 0000   ~(0000 1111)               12:  0000 1000        12: 0000 0111
       *    13: 1111 1000            13: 1111 1000                     13:   1111 1000   ~(0000 0111)               13:  0000 0100        13: 0000 0011
       *    14: 1111 1100            14: 1111 1100                     14:   1111 1100   ~(0000 0011)               14:  0000 0010        14: 0000 0001
       *    15: 1111 1110            15: 1111 1110                     15:   1111 1110   ~(0000 0001)               15:  0000 0001        15: 0000 0000
       *    16: 0111 1111            16: 1111 1110 (<< 1)              16:   1111 1110 ~(0000 0001)                 16:  0000 0001        16: 0000 0000
       * ```
       *
       * lower byte mask = index % 8 == 0 ? ~(upper byte mask + 1) >> 1 : ~(upper byte mask + 1 << 1 - 1);
       *
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
       *     7 : *                 7
       *     8 : *                 8
       *     9 : 8                 8
       *    10 : 9                 9
       *    11 : 10               10
       *    12 : 11               11
       *    13 : 12               12
       *    14 : 13               13
       *    15 : *                14
       *    16 : *                15
       *    17 : 15               15
       *    18 : 16               16
       * ```
       *
       * `*` don't care
       *
       * upper byte index = index - (index - 1) / 8
       *
       *
       *
       * ### lower byte array index
       *
       * ```
       *
       * index:  array index   ->  index - 1: array index  ->  index: index == 0 ? 0 : index - (index - 1) / 8 - 1
       * --------------------      -----------------------     -------------------------------
       *     0:   0    0                  -1:  0   +1              0:  0
       *     1:   0   -1                   0:  0   -0              1:  0
       *     2:   1                        1:  1                   2:  1
       *     3:   2                        2:  2                   3:  2
       *     4:   3                        3:  3                   4:  3
       *     5:   4                        4:  4                   5:  4
       *     6:   5                        5:  5                   6:  5
       *     7:   6                        6:  6                   7:  6
       *     8:   7                        7:  7                   8:  7
       *     9:   7   -2                   8:  7   -1              9:  7
       *    10:   8                        9:  8                  10:  8
       *    11:   9                       10:  9                  11:  9
       *    12:  10                       11: 10                  12: 10
       *    13:  11                       12: 11                  13: 11
       *    14:  12                       13: 12                  14: 12
       *    15:  13                       14: 13                  15: 13
       *    16:  14                       15: 14                  16: 14
       *    17:  14   -3                  16: 14   -2             17: 14
       * ```
       *
       * lower byte index = index == 0 ? 0 : index - (index - 1) / 8 - 1
       *
       *
       */

      void serial_encode( Serialized& output ){


        constexpr octet_type bit_1     = 0b00000001;
        constexpr octet_type bit_7     = 0b01111111;
        constexpr octet_type bit_top_1 = 0b10000000;

        constexpr octet_type octet_bit = sizeof( octet_type ) * 8 - 1;

        for( size_type it = 0 ; it < Serialized :: SIZE ; ++ it ){

          const octet_type bit             = bit_1 << ( 7 - (it % 8) );
          const octet_type intermediate    = bit & bit_7 + ( (bit & bit_top_1) >> 7 );
          const octet_type upper_byte_mask = intermediate - 1;
          const octet_type lower_byte_mask = (it % 8 == 0) ? (~intermediate >> 1) : (~(intermediate << 1 - 1));

          const octet_type upper_byte_index = it - (it - 1) / 8;
          const octet_type lower_byte_index = it == 0 ? 0 : upper_byte_index - 1;

          const octet_type upper_byte = _data._octet[ upper_byte_index ] & upper_byte_mask >> it ;
          const octet_type lower_byte = _data._octet[ lower_byte_index ] & lower_byte_mask << (octet_bit - it) ;

          output[ it ] = upper_byte | lower_byte;
        }

      }

      

      protected:
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
