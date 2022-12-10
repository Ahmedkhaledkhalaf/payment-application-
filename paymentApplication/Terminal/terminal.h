/**
 * @file terminal.h
 * @author Ahmed khaled khalaf (khalafawy22899@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#ifndef TERMINAL_H
#define TERMINAL_H

#include "../Card/card.h"
/****************************** Types Declaration ************************************/
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;

typedef struct ST_terminalData_t
{
float transAmount;
float maxTransAmount;
uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;

/****************************** Functions ProtoTypes ************************************/

/* Description:
 * Gets transaction date from __DATE__ macro and arrange it in termData->transactionDate string
 * in DD/MM/YYYY format using static arrange_date function
 * inputs: address of ST_terminalData_t
 * output: WRONG_DATE , TERMINAL_OK
 */
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);

/* Description:
 * If the card expiration date is before the transaction date will return EXPIRED_CARD,
 * else return TERMINAL_OK.
 * inputs: address of ST_cardData_t , address of ST_terminalData_t
 * output: EXPIRED_CARD , TERMINAL_OK
 */
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);

/* Description:
 * ask for transaction amount and save it in termData->transAmount
 * inputs: address of ST_terminalData_t
 * output: INVALID_AMOUNT , TERMINAL_OK
 */

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);

/* Description:
 * compare transAmount with maxTransAmount in termData, if less or equal ok
 * inputs: address of ST_terminalData_t
 * output: EXCEED_MAX_AMOUNT , TERMINAL_OK
 */
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);

/* Description:
 * set transMaxAmount in termData , should be float greater than 0
 * inputs: address of ST_terminalData_t , float maxAmount
 * output: INVALID_MAX_AMOUNT , TERMINAL_OK
 */
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount);

#endif /* header guard */