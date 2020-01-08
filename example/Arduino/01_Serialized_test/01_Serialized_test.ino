
#include "Serialized.hpp"

void setup( void ){

  Serial.begin( 9600 );
  delay( 100 );

  using SimpleControl :: Serialized;

  Serialized :: value_type array[ Serialized :: SIZE ] = { 1, 2, 3, 4, 5 };
  Serialized array_test( array );
  
  Serialized copy_test = array_test;

  for( Serialized :: iterator it = copy_test.begin(), ep = copy_test.end() ;
      it != ep ; ++ it )
    Serial.print( *it );
  Serial.print('\n');

  Serial.println("-----");

  Serialized initial_test{ 5, 4, 3, 2, 1 };

  Serialized copy_from_test;
  copy_from_test.copy_from( initial_test );

  Serialized copy_to_test{ 'a', 'b', 'c', 'd', 'e'};
  
  copy_to_test.copy_to( copy_from_test );
 
  for( int i = 0 ; i < Serialized :: SIZE ; ++ i )
    Serial.print( copy_from_test[ i ] );

  Serial.print( '\n' );
  
  Serial.println( "----" );

  Serialized data_test{ 100, 127, 83, 0, 0b01110000 };
  
  Serial.print( data_test.is_correct() );
  Serial.print( data_test.is_address() );
  Serial.print( data_test.is_data   () );
  Serial.print( '\n' );

  Serialized address_test{ 128, 196, 135, 255, 0b11110000 };

  Serial.print( address_test.is_correct() );
  Serial.print( address_test.is_address() );
  Serial.print( address_test.is_data   () );

  Serial.print( '\n' );
}

void loop( void ){ 
}
