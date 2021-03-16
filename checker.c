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
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		LANGUAGE_ENGLISH
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
bool BMS_checkAttribute_OutOfRange(float bms_attribute, float attribute_Min_Value, float attribute_Max_Value, print_Values_t print_Value)
{
	bool retAtributeStatus = FALSE;
	char print_Param[];
	
	print_Param[] = (BMS_parameters_attributes.language_e == LANGUAGE_ENGLISH)?print_Parameters_English[]:print_Parameters_German[];
	
	if(bms_attribute < attribute_Min_Value || bms_attribute > attribute_Max_Value) 
	{
		BMS_printParameterStatus(print_Param[print_Value],print_Param[PRINT_VALUE_OUT_OF_RANGE]);
		retAtributeStatus = TRUE;
		BMS_setBMSStatus(TRUE);									
	}	
	
	return retAtributeStatus;
}

/*---------------------------------------------------------------------------*/
/*     FUNCTION: BMS_printParameterStatus
 */
/*!    \brief   Function to print the parameter out of range
 *
 *
 *     \param    	param[] -> the parameter will be printed
 *     \returns  	void
 *
 *//*------------------------------------------------------------------------*/
void BMS_printParameterStatus(char attribute[],char attribute_Status[])
{
	printf("%s %s\n",attribute,attribute_Status);
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

void BMS_checkAttribute_Threshold_And_Trigger_Warning(float bms_attribute, float attribute_Warn_Lower_Threshold, float attribute_Warn_Upper_Threshold, print_Values_t print_Value)
{
	char print_Param[];
	
	print_Param[] = (BMS_parameters_attributes.language_e == LANGUAGE_ENGLISH)?print_Parameters_English[]:print_Parameters_German[];
	
	if(bms_attribute < attribute_Warn_Lower_Threshold) 
	{
		//Trigger warning for Lower Threshold
		BMS_printParameterStatus(print_Param[print_Value],print_Param[PRINT_VALUE_LOWER_THRESHOLD]);
	}
	
	if(bms_attribute > attribute_Warn_Upper_Threshold) 
	{
		//Trigger warning for Higher Threshold
		BMS_printParameterStatus(print_Param[print_Value],print_Param[PRINT_VALUE_UPPER_THRESHOLD]);
	}
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
int BMS_batteryIsOk(float temperature, float soc, float chargeRate,language_t language) {
	
	BMS_parameters_attributes.language_e = language;
	
	BMS_parameters_attributes.temp_Status_b = BMS_checkAttribute_OutOfRange(temperature,BMS_ATTRIBUTE_TEMPERATURE_MIN_VALUE,BMS_ATTRIBUTE_TEMPERATURE_MAX_VALUE,PRINT_VALUE_TEMPERATURE);
	BMS_parameters_attributes.soc_Status_b = BMS_checkAttribute_OutOfRange(soc,BMS_ATTRIBUTE_SOC_MIN_VALUE,BMS_ATTRIBUTE_SOC_MAX_VALUE,PRINT_VALUE_STATE_OF_CHARGE);
	BMS_parameters_attributes.chargeRate_Status_b = BMS_checkAttribute_OutOfRange(chargeRate,BMS_ATTRIBUTE_CHARGE_RATE_MIN_VALUE,BMS_ATTRIBUTE_CHARGE_RATE_MAX_VALUE,PRINT_VALUE_CHARGE_RATE);
	
	BMS_checkAttribute_Threshold_And_Trigger_Warning(temperature,BMS_ATTRIBUTE_TEMPERATURE_LOWER_THRESHOLD_WARN_VALUE,BMS_ATTRIBUTE_TEMPERATURE_UPPER_THRESHOLD_WARN_VALUE,PRINT_VALUE_TEMPERATURE);
	BMS_checkAttribute_Threshold_And_Trigger_Warning(soc,BMS_ATTRIBUTE_SOC_LOWER_THRESHOLD_WARN_VALUE,BMS_ATTRIBUTE_SOC_UPPER_THRESHOLD_WARN_VALUE,PRINT_VALUE_STATE_OF_CHARGE);
	BMS_checkAttribute_Threshold_And_Trigger_Warning(chargeRate,BMS_ATTRIBUTE_CHARGE_RATE_LOWER_THRESHOLD_WARN_VALUE,BMS_ATTRIBUTE_CHARGE_RATE_UPPER_THRESHOLD_WARN_VALUE,PRINT_VALUE_CHARGE_RATE);
	
	if( TRUE == BMS_parameters_attributes.bms_Status_b) 
	{
		BMS_parameters_attributes.bms_Status_b = FALSE;
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
  assert(BMS_batteryIsOk(25, 70, 0.7,LANGUAGE_ENGLISH));		/*All values in range*/
  assert(!BMS_batteryIsOk(50, 85, 0,LANGUAGE_ENGLISH));			/*All values out of range*/
  assert(!BMS_batteryIsOk(100, 70, 0.7,LANGUAGE_ENGLISH));		/*Temp out of range*/
  assert(!BMS_batteryIsOk(25, 100, 0.7,LANGUAGE_ENGLISH));		/*SOC out of range*/
  assert(!BMS_batteryIsOk(25, 70, 1.5,LANGUAGE_ENGLISH));		/*Charge rate out of range*/
  assert(BMS_batteryIsOk(0, 70, 0.7,LANGUAGE_ENGLISH));			/*Temp out of minimum range*/
  assert(BMS_batteryIsOk(25, 10, 0.7,LANGUAGE_ENGLISH));		/*SOC out of minimum range*/
  assert(BMS_batteryIsOk(25, 70, 0,LANGUAGE_ENGLISH));			/*Charge rate out of minimum range*/
  
  assert(BMS_batteryIsOk(25, 70, 0.7,LANGUAGE_GERMAN));		/*All values in range*/
  assert(!BMS_batteryIsOk(50, 85, 0,LANGUAGE_GERMAN));			/*All values out of range*/
  assert(!BMS_batteryIsOk(100, 70, 0.7,LANGUAGE_GERMAN));		/*Temp out of range*/
  assert(!BMS_batteryIsOk(25, 100, 0.7,LANGUAGE_GERMAN));		/*SOC out of range*/
  assert(!BMS_batteryIsOk(25, 70, 1.5,LANGUAGE_GERMAN));		/*Charge rate out of range*/
  assert(BMS_batteryIsOk(0, 70, 0.7,LANGUAGE_GERMAN));			/*Temp out of minimum range*/
  assert(BMS_batteryIsOk(25, 10, 0.7,LANGUAGE_GERMAN));		/*SOC out of minimum range*/
  assert(BMS_batteryIsOk(25, 70, 0,LANGUAGE_GERMAN));			/*Charge rate out of minimum range*/
}
