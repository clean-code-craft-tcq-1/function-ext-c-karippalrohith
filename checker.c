/* ******************************************************************************
 ***
 ***     \file        Checker.c
 ***     \ingroup     Session2-TCQ
 ***     \author      Rohith K N
 ***
 ***     \brief       Main file to check BMS
 ***
 ***     \par         File_description
 ***                  This file explores more about functions
 ***
 *****************************************************************************/
 
/*=============================================================================
 =======                            INCLUDES                             =======
 ============================================================================*/
 /*------ standard includes -------*/
#include <stdio.h>
#include <assert.h>

/*------ module includes --------*/
#include "checker.h"

/*=============================================================================
 =======               DEFINES & MACROS FOR GENERAL PURPOSE              =======
 =============================================================================*/

/*=============================================================================
 =======                       CONSTANTS  &  TYPES                       =======
 =============================================================================*/

/*=============================================================================
 =======                VARIABLES & MESSAGES & RESSOURCEN                =======
 ==============================================================================*/
static BMS_parameters_s BMS_parameters_attributes = {
		false,
		false,
		false,
		false
};
/*=============================================================================
 =======                              METHODS                            =======
 =============================================================================*/

/*---------------------------------------------------------------------------*/
/*     FUNCTION: BMS_checkAttribute_OutOfRange
 */
/*!    \brief   Function to check the range of parameters
 *
 *
 *     \param    	bms_attribute -> the parameter for which range needs to be checked
					attribute_Min_Value -> Lower range of the parameter
					attribute_Max_Value -> Upper range of the parameter
					param[]	-> Parameter name to be printed
 *     \returns  	void
 *
 *//*------------------------------------------------------------------------*/
bool BMS_checkAttribute_OutOfRange(float bms_attribute, float attribute_Min_Value, float attribute_Max_Value, char param[])
{
	bool retAtributeStatus = false;
	if(bms_attribute < attribute_Min_Value || bms_attribute > attribute_Max_Value) 
	{
		BMS_printParameterStatus_As_OutOfRange(param);
		retAtributeStatus = true;
		BMS_setBMSStatus(true);									
	}	
	
	return retAtributeStatus;
}

/*---------------------------------------------------------------------------*/
/*     FUNCTION: BMS_printParameterStatus_As_OutOfRange
 */
/*!    \brief   Function to print the parameter out of range
 *
 *
 *     \param    	param[] -> the parameter will be printed
 *     \returns  	void
 *
 *//*------------------------------------------------------------------------*/
void BMS_printParameterStatus_As_OutOfRange(char param[])
{
	printf("%s out of range!\n",param);
}

/*---------------------------------------------------------------------------*/
/*     FUNCTION: BMS_setBMSStatus
 */
/*!    \brief   Function to set BMS status 
 *
 *
 *     \param    	bms_Status -> will be set as TRUE if any parameter is out of range
 *     \returns  	void
 *
 *//*------------------------------------------------------------------------*/
void BMS_setBMSStatus(bool bms_Status)
{
	BMS_parameters_attributes.bms_Status_b = bms_Status;			/*If any parameter out of range, set bms_Status_b as TRUE*/
}

/*---------------------------------------------------------------------------*/
/*     FUNCTION: BMS_batteryIsOk
 */
/*!    \brief   Function to test BMS parameters 
 *
 *
 *     \param    	temperature -> temperature value
					soc -> state of charge value
					chargeRate -> charge rate value
 *     \returns  int (0 or 1)
 *
 *//*------------------------------------------------------------------------*/
int BMS_batteryIsOk(float temperature, float soc, float chargeRate) {
	
	BMS_parameters_attributes.temp_Status_b = BMS_checkAttribute_OutOfRange(temperature,BMS_ATTRIBUTE_TEMPERATURE_MIN_VALUE,BMS_ATTRIBUTE_TEMPERATURE_MAX_VALUE,"Temperature");
	BMS_parameters_attributes.soc_Status_b = BMS_checkAttribute_OutOfRange(soc,BMS_ATTRIBUTE_SOC_MIN_VALUE,BMS_ATTRIBUTE_SOC_MAX_VALUE,"State of Charge");
	BMS_parameters_attributes.chargeRate_Status_b = BMS_checkAttribute_OutOfRange(chargeRate,BMS_ATTRIBUTE_CHARGE_RATE_MIN_VALUE,BMS_ATTRIBUTE_CHARGE_RATE_MAX_VALUE,"Charge Rate");
	
	if( true == BMS_parameters_attributes.bms_Status_b) 
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/*---------------------------------------------------------------------------*/
/*     FUNCTION: main
 */
/*!    \brief   Function to test BMS parameters 
 *
 *
 *     \param    none
 *     \returns  int
 *
 *//*------------------------------------------------------------------------*/
int main() {
  assert(BMS_batteryIsOk(25, 70, 0.7));			/*All values in range*/
  assert(!BMS_batteryIsOk(50, 85, 0));			/*All values out of range*/
  assert(!BMS_batteryIsOk(100, 70, 0.7));		/*Temp out of range*/
  assert(!BMS_batteryIsOk(25, 100, 0.7));		/*SOC out of range*/
  assert(!BMS_batteryIsOk(25, 70, 1.5));			/*Charge rate out of range*/
}
