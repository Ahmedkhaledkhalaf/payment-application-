/**
 * @file card.h
 * @author Ahmed khaled khalaf (khalafawy22899@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#ifndef CARD_H
#define CARD_H

#include <stdio.h>

/****************************** Types Declaration ************************************/

typedef unsigned char uint8_t;

/* Description:
 * Card type creation struct for each user (holds name , exp data and PAN )
 */


typedef struct ST_cardData_t
{
uint8_t cardHolderName[25];
uint8_t primaryAccountNumber[20];
uint8_t cardExpirationDate[6];
}ST_cardData_t;

/* Description:
 * enum contain different states for card data (valid or not)
 */
typedef enum EN_cardError_t
{
OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

/****************************** Functions ProtoTypes ************************************/

/* Description:
 * ask user to enter his name and save it in cardHolderName member in his cardData struct
 * inputs: address of ST_cardData_t
 * output: WRONG_NAME , CARD_OK
 */
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);

/* Description:
 * ask user to enter expiry Date and save it in cardExpirationDate member in his cardData struct
 * inputs: address of ST_cardData_t
 * output: WRONG_EXP_DATE , CARD_OK
 */
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);

/* Description:
 * ask user to enter PAN and save it in PAN member in his cardData struct
 * inputs: address of ST_cardData_t
 * output: WRONG_PAN , CARD_OK
 */
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

#endif /* header guard */