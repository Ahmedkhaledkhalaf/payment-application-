/**
 * @file app.c
 * @author Ahmed khaled khalaf (khalafawy22899@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-17
 *
 * @copyright Copyright (c) 2022
 *
 */


#include <stdio.h>

#include "app.h"
typedef float f32_t
extern ST_accountsDB_t DATA_BASE[10];
extern uint8_t DB_Acc_Index;

void main()
{
	appStart();
}

void appStart(void)
{
    uint8_t choice = 0;
    EN_terminalError_t TERMINAL_State;
    EN_transState_t TRANSACTION_State;
    EN_serverError_t SERVER_State;
   ST_transaction_t  User_Data= {{"","",""}, {0,0,""}, APPROVED, 0};

/********************* welcome message **************************/
        printf("\nWelcome to Egypt Future Work digital Bank :)\n");

    while (1)
    {
		/********************* First Block : Card **************************/

		/*take the card holde name */
		/*check wheather the card holder name is valid or no*/
        if (getCardHolderName(&User_Data.cardHolderData) == WRONG_NAME)
        {
			/*if the card holder neme is wrong, the user will find an error message and the program will be reset */
            printf("The name is less than 20 characters or greater than 24. \nOr, contains any special character or numbers.\n");
			printf("Please, enter acceptable name.\n\n");
            continue;
        }
		/*get the card expiry date*/
	   /*check wheather the card expiry date is valid or no*/
        if (getCardExpiryDate(&(User_Data.cardHolderData)) == WRONG_EXP_DATE)
        {
			/*if the card date is wrong, the user will find an error message and the program will break */
            printf("Wrong Expiration Date.\n");
			continue;;
        }
		/*get the card primary access number*/
        
		/*check wheather the card eprimary access number is valid or no*/
        if (getCardPAN(&(User_Data.cardHolderData)) == WRONG_PAN)
        {
			/*if the primary access number is wrong, the user will find an error message and the program will break */
            	printf("Wrong Primary Account Number.\n");
			continue;;
        }


        printf("\nPlease wait until data check ends.....\n");
        printf("\n\t\tWelcome %s !\n\n", User_Data.cardHolderData.cardHolderName);
        printf("Please choose the operation you want!\n");
			printf("1: To Make new Transaction.\n");
			printf("2: To print all the list.\n");
			printf("3: To Exit.\n");
            fflush(stdin);
			scanf("%d",&choice);
switch (choice)
{
case 1:
{
		/********************* Second Block : Terminal **************************/
		/*set max amount*/
		f32_t max_amount = 0;
		printf("\nplease set the max amount:\t");
		fflush(stdin);
		scanf("%f", &max_amount);
        if(setMaxAmount(&(User_Data.terminalData),max_amount) == INVALID_MAX_AMOUNT)
		{
			printf("\ninvalid max amount!\n");
			continue;
		}
		/*check wheather the transactin date is valid date or not*/
		if (getTransactionDate(&User_Data.terminalData) == WRONG_DATE)
		{
			printf("\nworng name\n");
			continue;
		}

		/* check card expiration date */
		if(isCardExpired(&(User_Data.cardHolderData), &(User_Data.terminalData)) ==TERMINAL_OK)
		{
			/*********************** Third Block : Server **************************/
			getTransactionAmount(&User_Data.terminalData); /* ask user to enter it on console */
			/* check transAmount is below maxTransAmount allowed in terminal */
			if (isBelowMaxAmount(&User_Data.terminalData)==TERMINAL_OK)
			{
				
				ST_accountsDB_t account={0,0,""}; /* {balance , AccState , PAN} */

				if(isValidAccount(&User_Data.cardHolderData,&account) == SERVER_OK)
				{
					if (isBlockedAccount(&User_Data.cardHolderData)==SERVER_OK)
					{
						if (isAmountAvailable(&User_Data.terminalData)==SERVER_OK)
						{
							recieveTransactionData(&User_Data);
							printf("succeded transaction\n\n");
							saveTransaction(&User_Data);
							
						}
						else
							printf("Declined, Insufficient Fund\n");
					}
					else
						printf("Declined, Stolen Card\n");
				}
				else
					printf("Declined, Invalid Account\n");
				/**********************************************************************/

			}
			else
				printf("Declined, Amount Exceeding Limit\n");
		}
		else
			printf("Declined, Expired Card\n");

	break;
}
 case 2:
  listSavedTransactions();
  break;

case 3:
 break;

 default:
 printf("\nerror!!!!!!!!!!!\n");
	break;
}

}
}