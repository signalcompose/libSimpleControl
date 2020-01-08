
#include "SimpleControl.hpp"

void setup( void ){

  Serial.begin( 9600 );
  delay( 100 );


  SimpleControl :: Serialized serialized;

  union Address{
    SimpleControl :: Address address;
    uint8_t octet[ sizeof( SimpleControl :: Address ) ];
  } address;


  address.address = 0x12345678;

  
  Serial.println(address.address, HEX);
  Serial.println(address.address, DEC);

  for( auto i = 0 ; i < sizeof( SimpleControl :: Address ) ; ++ i ){
    Serial.print( address.octet[ i ], HEX );
    Serial.print(' ');
  }
  Serial.print('\n');

  serialized.encode( address.address );

  for( auto it = serialized.begin() ; it != serialized.end() ; ++ it ){ 
    Serial.print( *it, HEX );
    Serial.print(' ');
  }
  Serial.print('\n');

  serialized.decode( address.address );

  for( auto i = 0 ; i < sizeof( SimpleControl :: Address ) ; ++ i ){ 
    Serial.print( address.octet[ i ], HEX );
    Serial.print(' ');
  }
  Serial.print('\n');

  Serial.println( address.address, HEX );
  Serial.println( address.address, DEC );



  Serial.println("---------------");

  union Data{ 
    SimpleControl :: Data data;
    uint8_t octet[ sizeof( SimpleControl :: Data ) ];
  } data;

  data.data = -0.579;
  Serial.println( data.data );

  for( auto i = 0 ; i < sizeof( SimpleControl :: Data ) ; ++ i ){ 
    Serial.print( data.octet[ i ] );
    Serial.print(' ');
  }
  Serial.print('\n');

  serialized.encode( data.data );

  for( auto it = serialized.begin() ; it != serialized.end() ; ++ it ){ 
    Serial.print( *it, HEX );
    Serial.print(' ');
  }
  Serial.print('\n');

  serialized.decode( data.data );

  for( auto i = 0 ; i < sizeof( SimpleControl :: Data ) ; ++ i ){ 
    Serial.print( data.octet[ i ] );
    Serial.print(' ');
  }
  Serial.print('\n');

  Serial.println( data.data );
}

void loop( void ){ 
}
