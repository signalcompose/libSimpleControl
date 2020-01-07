//
//  main.cpp
//  Serializer_test
//
//  Created by leico_studio on 2019/08/17.
//  Copyright © 2019 leico_studio. All rights reserved.
//

#include <iostream>
#include <vector>
#include <array> 
#include <list>

#include "Serialized.hpp"

/**
 * @brief dummy class to check copy function
 */
class dummy{

  std :: size_t size( void ){ return 10; }
};



using SimpleControl :: Serialized;


/**
 * @brief a function for output function result
 */
void print( const Serialized :: value_type value ){
  std :: cout << static_cast< int >( value ) << std :: endl;
}

/**
 * @brief a function for output boolean result
 */
void bool_print( const bool value ){ 
  std :: cout << std :: boolalpha << value << std :: endl;
}


int main( void ) {


  {
    Serialized default_constructor_test;
    print(default_constructor_test[ 2 ]);

    Serialized copy_constructor_test( default_constructor_test );
    print(copy_constructor_test[ 4 ]);


    Serialized :: value_type array[ Serialized :: SIZE ] = { 1, 2, 3, 4, 5 };
    Serialized array_constructor_test( array );
    print(array_constructor_test[ 1 ]);

    std :: vector< Serialized :: value_type > vec{ 1, 2, 3, 4, 5, 6, 7 };
    Serialized vec_constructor_test( vec );
    print(vec_constructor_test[ 4 ]);

    std :: array< Serialized :: value_type, Serialized :: SIZE > arr{ 1, 2, 3, 4, 5 };
    Serialized arr_constructor_test( arr );
    print(array_constructor_test[ 0 ]);


    std :: list< Serialized :: value_type > list{ 1, 2, 3, 4, 5, 6 };
    Serialized list_constructor_test( list );
    print(list_constructor_test[ 3 ]);



    //dummy d;
    //Serialized custom_class_test( d );
  }

  Serialized arr = { 1, 2, 3, 4, 5 };


  try{ 
    for( int i = 0 ; i != Serialized :: SIZE + 1 ; ++ i )
      print( arr.at( i ) );
  }
  catch( std :: out_of_range& e ){ 
    std :: cout << e.what() << std :: endl;
  }


  Serialized address_test{ 128, 134, 158, 128, 0b11110110 };
  bool_print( address_test.is_correct() );
  bool_print( address_test.is_address() );
  bool_print( address_test.is_data   () );
 

  Serialized data_test{ 100, 127, 50, 79, 0b01110010 };
  bool_print( data_test.is_correct() );
  bool_print( data_test.is_address() );
  bool_print( data_test.is_data   () );

  return 0;
}
