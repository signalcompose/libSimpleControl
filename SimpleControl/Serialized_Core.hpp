/**
 *  @file           Serialized_Core.hpp
 *  @brief          This class provides general functions for serialized SimpleControl data.
 *  @author         leico
 *  @date           2019.08.19
 *  $Version:       0$
 *  $Revision:      1$
 *  @par            
 */




#ifndef SimpleControlSerialized_Core_h
#define SimpleControlSerialized_Core_h

#include "SimpleControl_Types.hpp" 

namespace SimpleControl { 

  /**
   * @brief concealing core class of Serialized
   *
   */
  namespace __Serialized_Core{ 

    /**
     * @brief this class provide basic functions for serialized class
     *
     * @tparam    ValueType     serial data value type
     * @tparam    SizeType      serial data size type
     * @tparam    Iter          iterator of data array default value is `ValueType*`
     * @tparam    ConstIter     const iterator of data array default value is `const ValueType*`
     */
    template < 
      typename ValueType
      , typename SizeType
      , typename Iter       = ValueType*
      , typename ConstIter  = const ValueType*
      > 
      class __Serialized_Core { 

        public:
          using value_type = ValueType; ///< defined serial data value type, used related function args/return values
          using size_type  = SizeType;  ///< defined serial data size type, used related function args/return values

          using iterator       = Iter;      ///< defined serial data iterator, used in related functions
          using const_iterator = ConstIter; ///< defined serial data const iterator, used in relatd functions

          constexpr static size_type SIZE = 5; ///< defined serialzed data size

        protected: 
          value_type _data[ SIZE ]; ///< raw serialized data

        public:

          /** 
           * @brief constructor for value_types
           *
           * basic constructor for Serialized class, other constructors inherits this function
           *
           * @param[in]   v1    value for 1st octet data
           * @param[in]   v2    value for 2nd octet data 
           * @param[in]   v3    value for 3rd octet data 
           * @param[in]   v4    value for 4th octet data
           * @param[in]   v5    value for 5th octet data
           */
          __Serialized_Core ( 
              const value_type v1 = 0
              , const value_type v2 = 0
              , const value_type v3 = 0
              , const value_type v4 = 0
              , const value_type v5 = 0
              ) :
            _data{ v1, v2, v3, v4, v5 }
          {}

          /**
           * @brief copy constructor
           *
           * copy constructor. derived to 
           * __Serialized_Core( const value_type v1, const value_type v2, const value_type v3, const value_type v4, const value_type v5) 
           *
           * @param[in]   other   base of __Serialized_Core class 
           */
          __Serialized_Core ( const __Serialized_Core& other ) :
            __Serialized_Core ( 
                  other._data[ 0 ]
                , other._data[ 1 ]
                , other._data[ 2 ]
                , other._data[ 3 ]
                , other._data[ 4 ]
                )
          {}

          /**
           * @brief constructor from `value_type [ SIZE ]` array
           *
           * constructor from `value_type [ SIZE ]Z array. ignored other size array.
           * also derived to
           * __Serialized_Core( const value_type v1, const value_type v2, const value_type v3, const value_type v4, const value_type v5 )
           *
           *
           * @param[in]   array   reference of `value_type[ SIZE ]`
           */
          __Serialized_Core ( const value_type (&array)[ SIZE ] ) : 
            __Serialized_Core ( 
                array[ 0 ]
                , array[ 1 ]
                , array[ 2 ]
                , array[ 3 ]
                , array[ 4 ]
                )
          {}

          /**
           * @brief constructor from SimpleControl :: Address 
           *
           * constructor from Address variable. This constructor called
           * encode( const Address& input)
           *
           * @param[in]   address   reference of SimpleControl :: Address variable
           */
          __Serialized_Core ( const Address& address ) { encode( address ); }


          /**
           * @brief constructor from SimpleControl :: Data
           *
           * constructor from Data variable. This constructor called
           * encode( const Data& input)
           *
           * @param[in]   data    reference of SimpleControl :: Data variable
           */
          __Serialized_Core ( const Data& data ) { encode( data ); }




          /**
           * @brief data copy from `value_type [ SIZE ]`
           *
           * derived copy( const_iterator begin, const_iterator end, iterator target_begin ) function
           *
           * @param[in]   array   `value_type [ SIZE ]` array. data source.
           */
          void copy_from( const value_type (&array)[ SIZE ] ){ 
            copy( array, array + SIZE, begin() );
          } 

          /** 
           * @brief data copy from same class
           *
           * derived copy( const_iterator begin, const_iterator end, iterator target_begin ) function
           *
           * @param[in]   other   data source of `__Serialized_Core` class 
           */
          void copy_from( const __Serialized_Core& other ){ 
            copy( other.begin(), other.end(), begin() );
          }

          /**
           * @brief encode/copy from SimpleControl :: Address variable
           *
           * called encode( const Address& input ) function
           *
           * @param[in]   address   reference of SimpleControl :: Address variable
           */
          void copy_from( const Address& address ){ encode( address ); }

          /**
           * @brief encode/copy from SimpleControl :: Data variable
           *
           * called encode( const Data& input ) function
           *
           * @param[in]   data   reference of SimpleControl :: Data variable
           */
          void copy_from( const Data& data ){ encode( data ); }

          /**
           * @brief data copy to `value_type [ SIZE ]` array
           *
           * derived copy( const_iterator begin, const_iterator end, iterator target_begin ) function
           * 
           * @param[out]    array   copy to `value_type [ SIZE ]` array
           */
          void copy_to( value_type (&array)[ SIZE ] ){
            copy( begin(), end(), array );
          }

          /**
           * @brief data copy to same class
           *
           * derived copy( const_iterator begin, const_iterator end, iterator target_begin ) function
           *
           * @param[out]    other   copy to `__Serialized_Core` class
           */
          void copy_to( __Serialized_Core& other ){ 
            copy( begin(), end(), other.begin() );
          }

          /**
           * @brief decode/copy to SimpleControl :: Address variable
           * 
           * called decode( Address& output ) function
           *
           * @param[out]    address   a SimpleControl :: Address reference to store decoded data
           *
           */
          void copy_to( Address& address ){ decode( address ); }

          /**
           * @brief decode/copy to SimpleControl :: Data variable
           *
           * called decode( Data& output ) function
           *
           * @param[out]    data    a SimpleControl :: Data reference to store decoded data
           */
          void copy_to( Data& data ){ decode( data ); }

          /**
           * @brief implement equal operator from `value_type [ SIZE ]`
           *
           * derived copy_from( const value_type (&array)[ SIZE ] ) function
           * 
           * @param[in] array `value_type [ SIZE ]` array. data source
           *
           * @return reference of this instance
           */
          __Serialized_Core& operator= ( const value_type (&array)[ SIZE ]){ 
            copy_from( array );
            return *this;
          }

          /**
           * @brief implement equal operator from `__Serialized_Core`
           *
           * derived copy_from( const __Serialized_Core& other ) function
           *
           * @param[in] other data source of `__Serialized_Core` class
           *
           * @return reference of this instance
           */
          __Serialized_Core& operator= ( const __Serialized_Core& other ) & { 
            copy_from( other );
            return *this;
          }




          /**
           * @brief data accessor for lhs
           *
           * @note this function no checks out ouf range
           *
           * @param[in]     n     num of data octet
           * @return              reference of nth octet data, it can change data
           */
          value_type&       operator[] ( const size_type n ) &      { return _data[ n ]; }

          /**
           * @brief data accessor for const lhs
           * 
           * @note this function no checks out of range
           *
           * @param[in]     n     num of data octet
           * @return              const reference of nth octet data, could not change
           */
          const value_type& operator[] ( const size_type n ) const& { return _data[ n ]; }


          /**
           * @brief data accessor for rhs
           *
           * @note this function no checked out of range
           *
           * @param[in]     n     num of data octet
           * @return              value of nth octet data, you can change but could not change raw data
           */
          value_type        operator[] ( const size_type n ) &&     { return _data[ n ]; }


          /**
           * @brief provide a iterator for first octet data 
           *
           * @return iterator of first octet data
           */
          iterator begin( void )       { return _data; }
          /**
           * @brief provide a const iterator for first octet data
           *
           * @return const iterator of first octet data
           */
          const_iterator begin( void ) const { return _data; }

          /**
           * @brief provide a iterator for data endpoint
           *
           * @note this iterator provides next point of last octet
           *
           * @return iterator of data endpoint
           */
          iterator end( void )       { return _data + SIZE; }
          /**
           * @brief provide a const iterator for data endpoint
           *
           * @note this iterator provides next point of last octet
           *
           * @return const iterator of data endpoint
           */
          const_iterator end( void ) const { return _data + SIZE; }


          /**
           * @brief clear Serialized data
           *
           * zero cleared serialized data.
           * called encode_core( const Type& input, const bool is_address ) function
           */
          void clear( void ){
            __Serialized_Core();
          }


          /**
           * @brief checking serial data is Address compatible
           *
           * More details of Address type, see SimpleControl Wiki
           *
           * @return true if data is Address compatible, otherwise false
           */
          const bool is_address( void ) const& noexcept { 

            for( const_iterator iter = begin(), stop = end() ; iter != stop ; ++ iter )
              if( *iter < 0b10000000 ) 
                return false;

            if( (*(end() - 1) & 0b11110000) != 0b11110000 ) 
              return false;

            return true;
          }

          /**
           * @brief checking serial data is Data compatible
           *
           * More details of Data type, see SimpleControl Wiki
           *
           * @return true if serial data is Data compatible, otherwise false
           */
          const bool is_data( void ) const& noexcept {
            for( const_iterator iter = begin(), stop = end() ; iter != stop ; ++ iter )
              if( *iter > 0b01111111 )
                return false;

            if( (*(end() - 1) & 0b01110000) != 0b01110000 )
              return false;

            return true;
          }

          /**
           * @brief checking serial data compatible SimpleControl protocol
           *
           * In this function, checking serial data is compatible Address or Data
           *
           * @return true if serial data is compatible Address or Data, otherwise false
           */
          const bool is_correct( void ) const& noexcept { 
            return is_address() || is_data();
          }




          /**
           * @brief decode from Serialized data to Data value
           *
           * @param[out] output   address of decode data from Serialized data 
           *
           */
          void decode ( Data& output ){
            decode_core( output );
          }




          /**
           * @brief decode from Serialized data to Address value
           *
           * @param[out] output address of decode data from Serialized data
           */
          void decode ( Address& output ){
            decode_core( output );
          }


          /**
           * @brief encode to Serialized data and store encorded data from Data value
           *
           * @param[in] input original data of Serialized data
           */
          void encode( const Data& input ){
            encode_core( input );
          }


          /**
           * @brief encode to Serialized data and store encorded data from Address value
           *
           * @param[in] input original data of Serialized data
           */
          void encode( const Address& input ){ 
            encode_core( input, true );
          }






        protected:
          /**
           * @brief copy function for serial data
           *
           * @param[in]   begin           start iterator of original data
           * @param[in]   end             endpoint iterator of original data
           * @param[out]  target_begin    start iterator of copy to target
           */
          bool copy( const_iterator begin, const_iterator end, iterator target_begin ){ 

            if( end < begin ) 
              return false;

            while( begin != end )
              *target_begin ++ = *begin ++;

            return true;
          }



          /**
           * @brief decode from Serialized data to Type value
           *
           * @tparam     Type     output value type of this function
           *
           * @param[out] output   address of decode data from Serialized data 
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
           template < typename Type > 
           void decode_core ( Type& output ){
             union {
               Type data;
               value_type octet[ sizeof( Type ) ];
             } converted;

             constexpr value_type bit_7 = 0b01111111;
             constexpr value_type bit_1 = 0b00000001;

             constexpr value_type octet_bit = sizeof( value_type ) * 8 - 1;

             constexpr size_type size = sizeof( Data );
             for( size_type index = 0 ; index < size ; ++ index ){ 

               const value_type lower_byte_mask = ~( bit_1 << ( index % octet_bit ) ) - bit_7;
               const value_type upper_byte_mask = ~( lower_byte_mask << 1 );

               const value_type pos = index + index / octet_bit;

               const value_type lower_byte = ( _data[ pos     ] & lower_byte_mask ) >> index;
               const value_type upper_byte = ( _data[ pos + 1 ] & upper_byte_mask ) << ( octet_bit - index );

               converted.octet[ index ] = upper_byte | lower_byte;
             }

             output = converted.data;
           }


          /**
           *
           * @brief encode value to Serialized class, stored encode data
           *
           * @tparam Type input type value of this function
           *
           * @param[in]   input       a original data to serialized
           * @param[in]   is_address  flag `true` when encode SimpleControl :: Address variable
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
           *  `*` = don't care
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
           *
           * ### header 
           *
           * | address      | data         |
           * | ============ | ============ |
           * | `0b1*******` | `0b0*******` | 
           *
           * * prepend header bit 
           *     -> `byte | header`
           *
           *
           *
           *
           *
           * ### padding
           *
           * | address      | data         |
           * | ============ | ============ |
           * | `0b1111****` | `0b0000****` |
           *
           * * address padding 
           *     -> `MSByte | 0b11110000`
           * * data    padding 
           *     -> `MSByte & 0b00001111`
           *
           */
           template< typename Type>
           void encode_core ( const Type& input, const bool is_address = false ){

             union { 
               Type       data;
               value_type octet[ sizeof( Type ) ];
             } original;

             original.data = input;

             clear();

             constexpr value_type bit_1     = 0b00000001;
             constexpr value_type bit_7     = 0b01111111;
             constexpr value_type bit_top_1 = 0b10000000;

             constexpr value_type octet_bit = sizeof( value_type ) * 8 - 1;

             constexpr value_type header_address = 0b10000000;
             constexpr value_type header_data    = 0b00000000;

             for( int index = 0 ; index < SIZE ; ++ index ){


               const value_type bit             = bit_1 << ( octet_bit - (index % 8) );
               const value_type intermediate    = (bit & bit_7) + ( (bit & bit_top_1) >> octet_bit );
               const value_type upper_byte_mask = intermediate - 1;
               const value_type lower_byte_mask = (index % 8 == 0) ? static_cast< value_type >( ~intermediate) >> 1 : 
                                                                     static_cast< value_type >( ~((intermediate << 1) - 1) );

               const value_type upper_byte_index = index - (index - 1) / 8;
               const value_type lower_byte_index = index == 0 ? 0 : upper_byte_index - 1;

               const value_type upper_byte = (original.octet[ upper_byte_index ] & upper_byte_mask) << index ;
               const value_type lower_byte = (original.octet[ lower_byte_index ] & lower_byte_mask) >> (octet_bit - (index + octet_bit) % 8 ) ;

               _data[ index ] = upper_byte | lower_byte | (is_address ? header_address : header_data) ;
             }


             constexpr value_type padding_address = 0b11110000;
             constexpr value_type padding_data    = 0b00001111;

             value_type& last = *(end() - 1);
             last = is_address ? (last | padding_address) : (last & padding_data);

           }

      };
  }
}

#endif /* SimpleControlSerialized_Core_h */
