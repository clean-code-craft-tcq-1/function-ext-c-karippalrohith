/* ******************************************************************************
 ***     \file        Checker.h
 ***     \ingroup     Session2-TCQ
 ***     \author      Rohith K N
 ***
 ***     \brief       Header file for the module
 ***
 ***     \par         File_description
 ***                  This file have the declarations of the variables and methods of the module
 ***
 *****************************************************************************/
#ifndef BMS_MAIN_H_
#define BMS_MAIN_H_
/*=============================================================================
 =======                            INCLUDES                             =======
 ============================================================================*/
 /*------ standard includes -------*/
#include <stdio.h>

#define BMS_ATTRIBUTE_TEMPERATURE_MIN_VALUE            				0u
#define BMS_ATTRIBUTE_TEMPERATURE_LOWER_THRESHOLD_WARN_VALUE        2.25
#define BMS_ATTRIBUTE_TEMPERATURE_UPPER_THRESHOLD_WARN_VALUE        42.75
#define BMS_ATTRIBUTE_TEMPERATURE_MAX_VALUE            				45u

#define BMS_ATTRIBUTE_SOC_MIN_VALUE            						20u
#define BMS_ATTRIBUTE_SOC_LOWER_THRESHOLD_WARN_VALUE       			24u
#define BMS_ATTRIBUTE_SOC_UPPER_THRESHOLD_WARN_VALUE        		42.75
#define BMS_ATTRIBUTE_SOC_MAX_VALUE            						84u

#define BMS_ATTRIBUTE_CHARGE_RATE_MIN_VALUE            				0u
#define BMS_ATTRIBUTE_CHARGE_RATE_LOWER_THRESHOLD_WARN_VALUE  		0.04
#define BMS_ATTRIBUTE_CHARGE_RATE_UPPER_THRESHOLD_WARN_VALUE    	0.76
#define BMS_ATTRIBUTE_CHARGE_RATE_MAX_VALUE            				0.80

typedef enum{
	PRINT_VALUE_TEMPERATURE,
	PRINT_VALUE_STATE_OF_CHARGE,
	PRINT_VALUE_CHARGE_RATE,
	PRINT_VALUE_OUT_OF_RANGE,
	PRINT_VALUE_LOWER_THRESHOLD,
	PRINT_VALUE_UPPER_THRESHOLD,
	PRINT_VALUE_MAX
}print_Values_t;

typedef enum {	FALSE, 
				TRUE
}bool;

typedef enum {
		LANGUAGE_ENGLISH,
		LANGUAGE_GERMAN,
		LANGUAGE_MAX
}language_t;

typedef struct {
    bool temp_Status_b;
    bool soc_Status_b;
    bool chargeRate_Status_b;
    bool bms_Status_b;
	language_t language_e;
} BMS_parameters_s;

char print_Parameters_English[PRINT_VALUE_MAX][] = {'Temperature','State of Charge','Charge Rate','out of range!','reaching Lower Threshold','reaching Higher Threshold'};
char print_Parameters_German[PRINT_VALUE_MAX][] = {'Temperieren','Stand der Abgabe','Gebührensatz','Außer Reichweite!','Erreichen der unteren Schwelle','Erreichen einer höheren Schwelle'};

void BMS_setBMSStatus(bool bms_Status);
void BMS_printParameterStatus(char attribute[],char attribute_Status[]);
bool BMS_checkAttribute_OutOfRange(float bms_attribute, float attribute_Min_Value, float attribute_Max_Value, print_Values_t print_Value);
void BMS_checkAttribute_Threshold_And_Trigger_Warning(float bms_attribute, float attribute_Warn_Lower_Threshold, float attribute_Warn_Upper_Threshold, print_Values_t print_Value);
int BMS_batteryIsOk(float temperature, float soc, float chargeRate,language_t language);

#endif /*BMS_MAIN_H_*/
