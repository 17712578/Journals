#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "rfm2g_api.h"

#if (defined(RFM2G_LINUX))

#ifdef CONFIG_DEVFS_FS
    #define DEVICE_PREFIX   "/dev/rfm2g/"
#else
    #define DEVICE_PREFIX   "/dev/rfm2g"
#endif

    #define PROCFILE         "/proc/rfm2g"

#elif defined(RFM2G_VXWORKS)

    #define DEVICE_PREFIX   "RFM2G_"

#elif defined(SOLARIS)

    #define DEVICE_PREFIX   "/dev/rfm2g"

#elif defined(WIN32)

    #define DEVICE_PREFIX   "\\\\.\\rfm2g"
#else

    #error Please define DEVICE_PREFIX for your driver
#endif

#define DEVICE 0
#define Booking_Pallet_ID	391
#define Booking_Pallet_ID_1 392
#define Booking_Pallet_ID_2 393
#define	Booking_Pallet_ID_3 394
#define Booking_Pallet_ID_4 395
#define Booking_Pallet_Location 396
#define Booking_Pallet_Location_1 397
#define Booking_Pallet_Location_2 398
#define Booking_Pallet_Location_3 399
#define Booking_Pallet_Location_4 400
#define Booking_Pallet_BookIn 401
#define Booking_Pallet_BookOut 402
#define DPSIM__DriveOn_PE019 465
#define DPSIM__DriveOn_PE021 467
#define	DPSIM__DriveOn_PE024 470
#define DPSIM__ScaledRotSpd_PE019 432
#define DPSIM__ScaledRotSpd_PE021 434
#define DPSIM__ScaledRotSpd_PE024 437
#define CcarTR1_ActPos 343
#define Tr1CoilLifterSvoVlv 403
#define Tr1ScaledRotSpd_CC 404
#define Tr1OpenBreak_CC 407



void delay_ms(unsigned int delay);
void Swapstring (void);
void SetPalletName (void);
void SetPalletName (void);

int offset = 0x708840;	
int Pallet_ID = 2;
int Pallet_Location = 5;  
int NewLocation1 = 842024272;
int NewLocation2 = 49;
int True = 16777216;
int False = 0;
int Speed = 4234437;
int NewName[8];
char direction = 0;
RFM2G_STATUS result;
RFM2GHANDLE Handle = NULL;


void Swapstring (void)
{
	char Name[20];
	unsigned int num1 = 0;
	unsigned int num2 = 0;
	unsigned int num3 = 0;
	unsigned int num4 = 0;
    int i;
	
	while ((fgets( Name, sizeof(Name), stdin ) == (char *) NULL ) ||(strlen(Name) < 2)){}
    if (Name[strlen(Name) - 1] == '\n') 
    Name[strlen(Name) - 1] = '\0';
    
    int a = 0;
	for (i = (strlen(Name) - 1); i >= 0; i--)	
	{
	   if (strlen(Name) - a >= 13)
	    { 
	    	num4 = (num4 << 8) + Name[i];
	    	a++;
    	}
        else if(strlen(Name)- a >= 9)
    	{ 
	    	num3 = (num3 << 8) + Name[i];
	    	a++;
    	}
    	else if(strlen(Name)- a >= 5)
    	{ 
	    	num2 = (num2 << 8) + Name[i];
	    	a++;
    	}
    	else if(strlen(Name)- a >= 0)
    	{ 
	    	num1 = (num1 << 8) + Name[i];
	    	a++;
    	}
	}
    
	if(direction == 1)
	{
		result = RFM2gPoke32(Handle, offset + Booking_Pallet_ID_1*4,num1); 	//  Poke the Name of Pallet into variable Booking_Pallet_ID_1 
		result = RFM2gPoke32(Handle, offset + Booking_Pallet_ID_2*4,num2); 	//  Poke the Name of Pallet into variable Booking_Pallet_ID_2
		result = RFM2gPoke32(Handle, offset + Booking_Pallet_ID_3*4,num3); 	//  Poke the Name of Pallet into variable Booking_Pallet_ID_3 
		result = RFM2gPoke32(Handle, offset + Booking_Pallet_ID_4*4,num4); 	//  Poke the Name of Pallet into variable Booking_Pallet_ID_3
	}
	if(direction == 2)
	{
		result = RFM2gPoke32(Handle, offset + Booking_Pallet_Location_1*4,num1); 	//  Poke the Name of Pallet into variable Booking_Pallet_ID_1 
		result = RFM2gPoke32(Handle, offset + Booking_Pallet_Location_2*4,num2); 	//  Poke the Name of Pallet into variable Booking_Pallet_ID_2
		result = RFM2gPoke32(Handle, offset + Booking_Pallet_Location_3*4,num3); 	//  Poke the Name of Pallet into variable Booking_Pallet_ID_3 
		result = RFM2gPoke32(Handle, offset + Booking_Pallet_Location_4*4,num4); 	//  Poke the Name of Pallet into variable Booking_Pallet_ID_3
	}
}	

void SetLocationofPallet(void)
{
	direction = 2;
	printf("Please enter Location of the Pallet: \n"); 					
	Swapstring();
}	

void SetPalletName (void)
{
	direction = 1;
	printf("Please enter Name of the Pallet: \n");
	Swapstring();										
}

RFM2G_STATUS rfm2gTestApiCommand(void)
{


 RFM2G_CHAR     device[40];             /* Name of RFM2G device to use */
    
    RFM2G_INT32    numDevice = 0;

    printf("\n  PCI RFM2g Test2Open\n\n");
    clearerr(stdin);
    printf("Please enter device number: ");

    while ((fgets( device, sizeof(device), stdin ) == (char *) NULL ) ||(strlen(device) < 2))
    {
    }

    sscanf(device, "%d", &numDevice);
    /* if sscanf fails, then numDevice will stay 0 */
    sprintf(device, "%s%d", DEVICE_PREFIX, numDevice);
	/* Open the Reflective Memory device */

result = RFM2gOpen( device, &Handle );
if( result != RFM2G_SUCCESS )
{
	printf( "ERROR: RFM2gOpen() failed.\n" );
	printf( "ERROR MSG: %s\n", RFM2gErrorMsg(result));
	return(-1);
}

		//result = RFM2gPoke32(handle, Offset+Index*4,Value) Offset = 0x708840;
         result = RFM2gPoke32(Handle, offset + Booking_Pallet_ID*4,Pallet_ID); // Constant
		 SetPalletName();
		 
		 result = RFM2gPoke32(Handle, offset + Booking_Pallet_Location*4,Pallet_Location);	// Constant
		 SetLocationofPallet();
		
		 result = RFM2gPoke32(Handle, offset + Booking_Pallet_BookIn*4,True); 	//Set Booking_P
		 sleep(1);//Delay
		 result = RFM2gPoke32(Handle, offset + Booking_Pallet_BookIn*4,False); 	//Set it back to 	
		
		 result = RFM2gPoke32(Handle, offset + DPSIM__ScaledRotSpd_PE021*4,Speed); //Speed
		 result = RFM2gPoke32(Handle, offset + DPSIM__DriveOn_PE021*4,1); //Drive on
	
		 result = RFM2gPoke32(Handle, offset + DPSIM__ScaledRotSpd_PE24*4,Speed); //Speed
		 result = RFM2gPoke32(Handle, offset + DPSIM__DriveOn_PE024*4,1); //Drive on
		 sleep(68);
		 result = RFM2gPoke32(Handle, offset + DPSIM__DriveOn_PE021*4,0); //Drive on
		 result = RFM2gPoke32(Handle, offset + DPSIM__DriveOn_PE024*4,0); //Drive on
		 
		 result = RFM2gPoke32(Handle, offset + Tr1OpenBreak_CC*4,1); //Drive on
		 read = RFM2gPeek32(Handle, offset + TCcarTR1_ActPos*4,1); //Drive on

/* Close the Reflective Memory device */
RFM2gClose( &Handle );

return(result);
} 

void delay_ms(unsigned int delay)
{
    int calibration_count =3;
	volatile unsigned int i,j,k; // loop counters
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
