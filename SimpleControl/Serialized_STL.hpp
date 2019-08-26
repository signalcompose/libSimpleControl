/**
 *  @file           Serialized_STL.hpp
 *  @brief          This class provides serialized SimpleControl data implementation for general C++.
 *  @author         leico
 *  @date           2019.08.19
 *  $Version:       0$
 *  $Revision:      1$
 *  @par            
 */

#ifndef SimpleControlSerialized_STL_h
#define SimpleControlSerialized_STL_h

#include "Serialized_Core.hpp"
#include <utility>
#include <type_traits> 

#include <cstdint>
#include <algorithm>


namespace SimpleControl{ 

  /**
   * @brief this class delived from __Serialized_Core, and provide some stl extension
   *
   * @example Serialized_test/Serialized_test/main.cpp
   * this example tried below functions with `std :: array`, `std :: vector` and `std :: list`
   */
  class Serialized_STL : 
    public __Serialized_Core :: __Serialized_Core<
        std :: uint8_t
      , std :: size_t
    > {

    public:
    using __Serialized_Core :: __Serialized_Core;
    using __Serialized_Core :: copy_from;
    using __Serialized_Core :: copy_to;
    using __Serialized_Core :: operator=;


    /**
     * @brief constructor from any class
     *
     * @note see copy_from( const T& other )
     *
     * This function called default constructor a.k.a __Serialized_Core :: Serialized_Core.
     * After that copied from other to this serial data. To copy data, we call copy_from ( const T& other )
     *
     * @tparam    T       type you want to copy from
     * @param[in] other   const type T reference, your original data
     */
    template < typename T > 
    Serialized_STL( const T& other ) : Serialized_STL() { 
      copy_from( other );
    }


    /**
     * @brief serial data copy function from any type
     *
     * @note this function required
     * * resize
     *   * send array distance size and resize specific distance data size
     * * begin
     *   * returned start point iterator
     * * end
     *   * returned end point iterator
     *
     * @tparam    T      type you want to copy from
     * @param[in] other  const type T reference, your original data
     */
    template < typename T > 
    void copy_from( const T& other ){ 

      T buff = other;

      buff.resize( SIZE );

      std :: copy( buff.begin(), buff.end(), begin() );

    }

    /**
     * @brief specialized copy from function for `std :: array`
     *
     * @param[in] other `const std :: array< value_type, SIZE >` reference type argument, original data
     */
    void copy_from( const std :: array< value_type, SIZE >& other){ 
      std :: copy( other.begin(), other.end(), begin() );
    }


    /**
     * @brief copy serial data to another class function 
     *
     * @note this function required
     * * resize
     *   * send array distance size and resize specific distance data size
     * * clear
     *   * delete or reset all data
     * * begin
     *   * returned start point iterator
     *
     * @tparam      T     type you want to copy to
     * @param[out]  other type T reference, your target data
     */
    template < typename T >
    void copy_to( T& other ){ 

      other.resize( SIZE );

      other.clear();

      std :: copy( begin(), end(), other.begin() );
    }


    /**
     * @brief specialized copy to functon for `std :: array`
     *
     * @param[out] other `std :: array< value_type, SIZE >` type argument, copy target
     */
    void copy_to( std :: array< value_type, SIZE >& other ){ 
      std :: copy( begin(), end(), other.begin() );
    }


    /**
     * @brief copy data from any class
     *
     * @note see copy_from(const T& other)
     *
     * @tparam       T     type you want to copy from
     * @param[in]    other const type T reference, your original data
     * @return             returned this class reference
     */
    template < typename T > 
    Serialized_STL& operator= ( const T& other ){ 
      copy_from( other );
      return *this;
    }


    /**
     * @brief octet accessor with out of range check
     *
     * @note if access over range, this function throw `std :: out_of_range`
     *
     * @param[in] n     position of data octet
     * @return          reference of data octet, you can change specific octet data
     */
    value_type& at( const size_type n ) & {
      
      if( n >= SIZE )
        throw std :: out_of_range( "Serialized at &" );

      return operator[] ( std :: forward< const size_type >( n ) );
    }

    /**
     * @brief octet accessor with out of range check
     *
     * @note if access over range, this function throw `std :: out_of_range`
     *
     * @param[in] n     position of data octet
     * @return          const octet data, you don't change return value
     */
    const value_type at( const size_type n ) const& {

      if( n >= SIZE )
        throw std :: out_of_range( "Serialized at const&" );


      return operator[] ( std :: forward< const size_type >( n ) );
      
    }

    /**
     * @brief octet accessor with out of range check
     *
     * @note if access over range, this function throw `std :: out_of_range`
     *
     * @param[in] n     position of data octet
     * @return          octet data, you can change return value but couldn't change raw data
     */
    value_type at( const size_type n ) && { 

      if( n >= SIZE )
        throw std :: out_of_range( "Serialized at &&" );

      return operator[] ( std :: forward< const size_type >( n ) );
    }

  };
}

#endif /* Serialized_STL_h */
