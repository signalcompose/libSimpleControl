//
//  main.cpp
//  SimpleControl_test
//
//  Created by leico_studio on 2019/08/27.
//  Copyright © 2019 leico_studio. All rights reserved.
//

#include <iostream>
#include <ios>
#include <iomanip>
#include <cstdint>
#include "SimpleControl.hpp"

void print_octet( const std :: uint8_t octet ){
  std :: cout << std :: setfill('0') << std :: setw( 2 ) << std :: hex << static_cast< int >( octet ) << ' ';
}


int main(int argc, const char * argv[]) {


  SimpleControl :: Serialized serialized; 



  union Address{
    SimpleControl :: Address address;
    std :: uint8_t octet[ sizeof( SimpleControl :: Address ) ];
  } address;




  address.address = 0x12345678;

  std :: cout << std :: hex << address.address << std :: endl;
  std :: cout << std :: dec << address.address << std :: endl;

  for( std :: size_t i = 0 ; i < sizeof( SimpleControl :: Address ) ; ++ i )
    print_octet( address.octet[ i ] );
  std :: cout << std :: endl;




  serialized.encode( address.address );

  for( auto it = serialized.begin() ; it != serialized.end() ; ++ it )
    print_octet( *it );
  std :: cout << std :: endl;




  serialized.decode( address.address );

  for( auto i = 0 ; i < sizeof( SimpleControl :: Address ) ; ++ i)
    print_octet( address.octet[ i ] );
  std :: cout << std :: endl;

  std :: cout << std :: hex << address.address << std :: endl;
  std :: cout << std :: dec << address.address << std :: endl;


  std :: cout << "-----------------" << std :: endl;


  union Data{ 
    SimpleControl :: Data data;
    std :: uint8_t octet[ sizeof( SimpleControl :: Data ) ];
  } data;



  data.data = 0.3894f;
  std :: cout << data.data << std :: endl;

  for( std :: size_t i = 0 ; i < sizeof( SimpleControl :: Data ) ; ++ i )
    print_octet( data.octet[ i ] );
  std :: cout << std :: endl;


  serialized.encode( data.data );

  for( auto it = serialized.begin() ; it != serialized.end() ; ++ it )
    print_octet( *it );
  std ::cout << std :: endl;

  serialized.decode( data.data );

  for( auto i = 0 ; i < sizeof( SimpleControl :: Data ) ; ++ i )
    print_octet( data.octet[ i ] );
  std :: cout << std :: endl;

  std :: cout << data.data << std :: endl;
  

  return 0;
}
