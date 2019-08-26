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

namespace SimpleControl { 

  /**
   * @brief concealing core class of Serialized
   *
   */
  namespace __Serialized_Core{ 
   
    /**
     * @brief this class provide basic functions for serialized class
     *
     * @tparam ValueType serial data value type
     * @tparam SizeType  serial data size type
     * @tparam Iter      iterator of data array default value is `ValueType*`
     * @tparam ConstIter const iterator of data array default value is `const ValueType*`
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
       * @param[in] v1 value for 1st octet data
       * @param[in] v2 value for 2nd octet data 
       * @param[in] v3 value for 3rd octet data 
       * @param[in] v4 value for 4th octet data
       * @param[in] v5 value for 5th octet data
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
       * @param[in] other base of __Serialized_Core class 
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
       * @param[in] array reference of `value_type[ SIZE ]`
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
       * @brief data copy from `value_type [ SIZE ]`
       *
       * derived copy( const_iterator begin, const_iterator end, iterator target_begin ) function
       *
       * @param[in] array `value_type [ SIZE ]` array. data source.
       */
      void copy_from( const value_type (&array)[ SIZE ] ){ 
        copy( array, array + SIZE, begin() );
      } 

      /** 
       * @brief data copy from same class
       *
       * derived copy( const_iterator begin, const_iterator end, iterator target_begin ) function
       *
       * @param[in] other data source of `__Serialized_Core` class 
       */
      void copy_from( const __Serialized_Core& other ){ 
        copy( other.begin(), other.end(), begin() );
      }

      /**
       * @brief data copy to `value_type [ SIZE ]` array
       *
       * derived copy( const_iterator begin, const_iterator end, iterator target_begin ) function
       * 
       * @param[out] array copy to `value_type [ SIZE ]` array
       */
      void copy_to( value_type (&array)[ SIZE ] ){
        copy( begin(), end(), array );
      }

      /**
       * @brief data copy to same class
       *
       * derived copy( const_iterator begin, const_iterator end, iterator target_begin ) function
       *
       * @param[out] other copy to `__Serialized_Core` class
       */
      void copy_to( __Serialized_Core& other ){ 
        copy( begin(), end(), other.begin() );
      }

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




    };
  }
}

#endif /* SimpleControlSerialized_Core_h */
