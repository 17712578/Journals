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

	{
		// STDRFM2GCALL result = RFM2gPoke32(handle, Offset+Index*4,Value) Offset = 0x708840;
		
		STDRFM2GCALL result = RFM2gPoke32(handle, 7378564,33554432) // Booking_Pallet_ID named SPACE " "
		STDRFM2GCALL result = RFM2gPoke32(handle, 7376450,1345388544) // Booking_Pallet_ID_1 named P1
		
		STDRFM2GCALL result = RFM2gPoke32(handle, 7376496,83886080) // Booking_Pallet_Location named P
		STDRFM2GCALL result = RFM2gPoke32(handle, 7376500,1346711600) //Booking_Pallet_Location named PE00
		STDRFM2GCALL result = RFM2gPoke32(handle, 7376504,822083584) //Booking_Pallet_Location named 1
		
		STDRFM2GCALL result = RFM2gPoke32(handle, 7376468,268435456) //Booking_Coil_Bookin named 1 
		
		
		
		
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

void main(){
RFM2G_STATUS result = rfm2gTestApiCommand(); 
	
	
}
