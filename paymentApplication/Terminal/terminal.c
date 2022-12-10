/**
 * @file terminal.c
 * @author Ahmed khaled khalaf (khalafawy22899@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <string.h>
#include <stdlib.h>
#include "terminal.h"

/****************************** Functions Definitions ************************************/
/* Description:
 * Gets transaction date  and checks whether the date is valid or not
 * inputs: address of ST_terminalData_t
 * output: TERMINAL_OK , WRONG_DATE
 */
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    printf("\nPlease enter the date of transaction\nnote:the date format must be 'DD/MM/YYYY':\t");
    /*get the transaction date*/
    fflush(stdin);
    gets(termData -> transactionDate);

    if ((strlen(termData -> transactionDate) < 10) || (strlen(termData -> transactionDate) > 10) || (termData -> transactionDate == NULL))
    {
        
        return WRONG_DATE;
    }
    else
    {
        
        return TERMINAL_OK;
    }

}

/* Description:
 * If the card expiration date is before the transaction date will return EXPIRED_CARD,
 * else return TERMINAL_OK.
 * inputs: address of ST_cardData_t , address of ST_terminalData_t
 * output: EXPIRED_CARD , TERMINAL_OK
 */
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    /* cardExpirationDate format is MM/YY
	 * transactionDate format is    --/MM/--YY
	 */

    /* convert date values from characters to integer */
    
    uint8_t* ex_date = cardData->cardExpirationDate; /*pointer to the card expiration date array in structure card holder data*/
    uint8_t* trans_date = &(termData->transactionDate[3]);/*pointer to transaction date array starts from the 4th element(month) MM/YYYY*/
    /* atoi function is a built-in function in string library which converts the charachters to numbers*/
    /*by multibling the MSB of the month by ten and add it to the LSB the result will be a numerical value we could compare it to the other*/
     uint16_t ex_date_month = atoi(ex_date);
     uint16_t ex_date_years = atoi(&ex_date[3]);
     
    
    /*by multibling the MSB of the year by ten and add it to the LSB the result will be a numerical value we could compare it to the other*/
    
    uint8_t trans_date_month =  atoi(trans_date); //+ atoi(trans_date+1);
    uint8_t trans_date_years =   atoi(&trans_date[5]);
    
    

    
    if (trans_date_years < ex_date_years)
    {
        return TERMINAL_OK;
    }
    else if (trans_date_years == ex_date_years && trans_date_month < ex_date_month)
    {
        return TERMINAL_OK;
    }
    
    else
    {
        return EXPIRED_CARD;
    }

}

/* Description:
 * ask for transaction amount and save it in termData->transAmount
 * inputs: address of ST_terminalData_t
 * output: INVALID_AMOUNT , TERMINAL_OK
 */

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    printf("\nPlease enter the the transaction amount:\t");
    scanf("%f", &(termData ->transAmount));

}

/* Description:
 * compare transAmount with maxTransAmount in termData ,if less or equal ok
 * inputs: address of ST_terminalData_t
 * output: EXCEED_MAX_AMOUNT , TERMINAL_OK
 */
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
if (termData ->transAmount > termData ->maxTransAmount)
{
    return EXCEED_MAX_AMOUNT;
}
else
{
    return TERMINAL_OK;
}
}


/* Description:
 * set transMaxAmount in termData , should be float greater than 0
 * inputs: address of ST_terminalData_t , float maxAmount
 * output: INVALID_MAX_AMOUNT , TERMINAL_OK
 */
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
    
    if (maxAmount <= 0)
    {
        return INVALID_MAX_AMOUNT;
    }
    else
    {
        termData ->maxTransAmount = maxAmount;
        return TERMINAL_OK;
        printf("%f",maxAmount);
    }
    
}