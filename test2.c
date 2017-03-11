#include <stdlib.h>
#include <stdio.h>
#include "rfm2g_api.h"


#define DEVICE 0/* Place OS specific device name in quotes before
this comment */
RFM2G_STATUS rfm2gTestApiCommand(void)
{
RFM2GHANDLE Handle;
RFM2G_STATUS result;
/* Open the Reflective Memory device */
result = RFM2gOpen( DEVICE, &Handle );
if( result != RFM2G_SUCCESS )
{
	printf( "ERROR: RFM2gOpen() failed.\n" );
	printf( "ERROR MSG: %s\n", RFM2gErrorMsg(result));
	return(-1);
}

	
		// STDRFM2GCALL result = RFM2gPoke32(handle, Offset+Index*4,Value) Offset = 0x708840;
		{	
		STDRFM2GCALL result = RFM2gPoke32(handle, 7378564,33554432) // Booking_Pallet_ID 
		STDRFM2GCALL result = RFM2gPoke32(handle, 7376450,1345388544) // Poke "P1" into Booking_Pallet_ID_1 
		
		STDRFM2GCALL result = RFM2gPoke32(handle, 7376496,83886080) // Booking_Pallet_Location 
		STDRFM2GCALL result = RFM2gPoke32(handle, 7376500,1346711602) //Poke "PE02" into Booking_Pallet_Location
		STDRFM2GCALL result = RFM2gPoke32(handle, 7376504,822083584) // Poke "1" Booking_Pallet_Location
		
		STDRFM2GCALL result = RFM2gPoke32(handle, 7376516,1) //Set Booking_Pallet_BookIn to "True" by inserting a '1'
		sw_delay_ms(500);										 //Delay
		STDRFM2GCALL result = RFM2gPoke32(handle, 7376516,0) //Set it back to "false"
		sw_delay(500);	
		
		STDRFM2GCALL result = RFM2gPoke32(handle, 7376648,-5000) //Speed
		STDRFM2GCALL result = RFM2gPoke32(handle, 7376780,1) //Drive on
		
		}

	/* Place API command example here */
RFM2G_UINT32 Buffer[1];

	RFM2gRead( Handle, 0, Buffer,4);	
	printf("the value is %d", *Buffer[0]);

if( result != RFM2G_SUCCESS )
{
	printf( "ERROR: API command returned error.\n" );
	printf( "ERROR MSG: %s\n", RFM2gErrorMsg(result));
}
/* Close the Reflective Memory device */
RFM2gClose( &Handle );
return(result);
}

void sw_delay_ms(unsigned int delay)
{
	unsigned int i,j,k; // loop counters
	char dummy = 0; // dummy variable to increment to waste time
	for(i=0; i<=delay; i++) { // outer loop
	for(j=0; j< calibration_count; j++) { // calibration loop
	for(k=0; k<0xff; k++) { // inner time wasting loop
	dummy++;
				} // end inner loop
			}// end calibration loop
		} // end outer loop
} // end software delay function

void main(){
RFM2G_STATUS result = rfm2gTestApiCommand(); 
	
	
}
