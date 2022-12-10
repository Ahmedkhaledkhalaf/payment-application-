/**
 * @file card.c
 * @author Ahmed khaled khalaf (khalafawy22899@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <string.h>
#include "card.h"

/****************************** Functions Definitions ************************************/

/* Description:
 * ask user to enter his name and save it in cardHolderName member in his cardData struct
 * inputs: address of ST_cardData_t
 * output: WRONG_NAME , CARD_OK
 */
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    uint8_t i=0; /* loop counter */
    
    printf("please enter the card holder name\nnote: the name must be 20 characters at least, and 24 characters at most\nCard holder name:\t");
    /* taking user's name */
    fflush(stdin);
    gets(cardData -> cardHolderName);
    
    /* required tests:
	 * name between 20 and 24 characters
	 * additional test: characters contains alphabets and spaces only
	 */
    if ((strlen(cardData ->cardHolderName) < 20) || (cardData -> cardHolderName == NULL) ||(strlen(cardData ->cardHolderName) > 24))
    {
        return WRONG_NAME;
    }
    
    else 
    {
        
        /*check if the name contains special characters*/
	while (cardData->cardHolderName[i] != NULL)
	{
		/* characters is not alphabet or space then return wrong name */
		if (!((cardData->cardHolderName[i] >= 'a' && cardData->cardHolderName[i] <= 'z') || 
			  (cardData->cardHolderName[i] >= 'A' && cardData->cardHolderName[i] <= 'Z') || 
			  (cardData->cardHolderName[i] == ' ')))
		{
			return WRONG_NAME;
		}
		++i;
	}
    return OK;
    }


}


/* Description:
 * ask user to enter expiry Date and save it in cardExpirationDate member in his cardData struct
 * inputs: address of ST_cardData_t
 * output: WRONG_EXP_DATE , CARD_OK
 */
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    /* taking card expiration date */
    printf("\nplease enter the card expiration date\nnote: the date format must be 'MM/YY'\nExpiratin date:\t");
    fflush(stdin);
    gets(cardData -> cardExpirationDate);


    /* required tests:
	 * wrong format
	 * date is null
	 * date is 5 characters test
	 * additional test: MM value from 1 to 12
	 * additional test: numeric characters
	 */

	/* check format and date is null test and 5 digits */
    if ((strlen(cardData ->cardExpirationDate)<5) || (cardData -> cardExpirationDate == NULL))
    {
        return WRONG_EXP_DATE;
    }

    /* if character MMYY not between '0' and '9'
			 * (if date is null test will return wrong from first character check)
			 */

    else if (((cardData->cardExpirationDate[0] < '0' ) || (cardData->cardExpirationDate[0] > '1' ) ) && ((cardData->cardExpirationDate[1] < '0' ) || (cardData->cardExpirationDate[1] > '9' ))\
     || (cardData->cardExpirationDate[2] != '/'))
     {
        return WRONG_EXP_DATE;
     }


     /* additional test MM from 1 to 12 */

     else if (cardData->cardExpirationDate[0] == '1' )  /* MS digit = 1 */
     {
        /* then LS digit must be from 0 to 2 */
        if (cardData->cardExpirationDate[1] > '2' )
        {
             return WRONG_EXP_DATE;
        }
        
        else 
        {
            /* if date passed the previous tests , then card is ok */
            return OK;
        }
     }
     
    
    else 
    {
        /* if date passed the previous tests , then card is ok */
        return OK;
    }
}


/* Description:
 * ask user to enter PAN and save it in PAN member in his cardData struct
 * inputs: address of ST_cardData_t
 * output: WRONG_PAN , CARD_OK
 */

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
     /* taking card PAN */
    printf("\nplease enter the card's Primary Account Number:\t");
    fflush(stdin);
    gets(cardData -> primaryAccountNumber);
   
    if ((strlen(cardData ->primaryAccountNumber)<16) || (cardData -> cardExpirationDate == NULL) || (strlen(cardData ->primaryAccountNumber) > 19))
    {
        return WRONG_PAN;
    }
    
    else 
    {
        return OK;
    }
}