/**
 * @file server.c
 * @author Ahmed khaled khalaf (khalafawy22899@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <string.h>

#include "server.h"

/*********************************** Globals ****************************************/

/* array containing different accounts, for each acc : balance , state , PAN */

ST_accountsDB_t DATA_BASE[256] = {{4000.00, RUNNING, "4916945627505481"},{12000.50, RUNNING,"4493625375298262"},
{20000.00, RUNNING, "4929101130212489"},{19000.25, RUNNING, "4485846819394224"},{50000.75, RUNNING, "4539780225981447"},
{67050.00, RUNNING,"4485456770455996"},{86000.00, BLOCKED, "4716069021758224"},{13078.30, BLOCKED, "4539207880267326"},
{90000.00, BLOCKED, "4571065954771386"},{74089.00, BLOCKED, "4539101982402479"}};

static uint8_t DB_Acc_Index = 0; /* index of first empty element */

/* transactions array initially filled with zeros */
ST_transaction_t TANSACTION_ARRAY[256] = {0};

static uint8_t TRANS_fill = 0;/* index of first empty element */


/****************************** Functions Definitions ************************************/

uint8_t SearchAccount (ST_cardData_t *cardData)
{
	/*search for an account in server database */

	for(uint8_t i=0; i<10 ; i++)
	{
        /* compare the given PAN with PAN of account[index] */
        uint8_t is = strcmp(cardData->primaryAccountNumber , DATA_BASE[i].primaryAccountNumber);
		if(is == 0)
        {
			return i;
            break;
        }
        
	}
	
	return -1;
}

/* Description:
 * takes PAN from cardData_s and check if an account with this PAN in the accounts array
 * takes transAmount from terminalData_s and compare it with account balance
 * checks if this account is blocked or not
 * save transaction and update balance or return error if array of transactions is full
 * inputs: address of a ST_transaction_t
 * output: FRAUD_CARD , DECLINED_INSUFFECIENT_FUND , DECLINED_STOLEN_CARD
 * INTERNAL_SERVER_ERROR , APPROVED
 */
EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
   
   

   /* after the linear search, if DB_Acc_Index = -1 then PAN doesn't exist */
   if (DB_Acc_Index == -1 || DB_Acc_Index >= 256)
   {
    return FRAUD_CARD;
   }
   
   /* if code comes to this line then PAN is found at account[index] ,
	 * check if its running or blocked */
	else if (DATA_BASE[DB_Acc_Index].state == BLOCKED)
	{
		return DECLINED_STOLEN_CARD;
	}

    /* check if the balance is enough to make the transaction */

    else if ((DATA_BASE[DB_Acc_Index].balance) < (transData->terminalData.transAmount))
	{
		return DECLINED_INSUFFECIENT_FUND;
	}
    /* check if transactions array is full (hence transaction can not be saved) */
	else if (TRANS_fill == 256) /* if account[256] to be filled then array is full */
	{
		return INTERNAL_SERVER_ERROR;
	}
    else
    {
        /* finally , if passed previous tests without return:
	 * save transaction in transactions array
	 * update the balance
	 * return approval
	 */

	/* update balance */
    
	DATA_BASE[DB_Acc_Index].balance -= transData->terminalData.transAmount;
    
	printf("\nYour New Balance is: %f\n",DATA_BASE[DB_Acc_Index].balance);
    

	return APPROVED;
    
    }
    
}
/* Description:
 * takes PAN from cardData and check if it exists in DB or not,
 * if exist copy its value to accountRefrence PAN then return server_ok
 * otherwise put null in accountRefrence PAN and return acc_not_found
 * inputs: address of a ST_cardData_t , address of a ST_accountsDB_t
 * output: ACCOUNT_NOT_FOUND , SERVER_OK
 */
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
    DB_Acc_Index = SearchAccount(cardData->primaryAccountNumber);
    if (DB_Acc_Index == -1 || DB_Acc_Index >=256)
    {
        /* if code comes to this line, then function did not return
	 * when match occurred in the search function , then matching PAN doesn't exist */

	accountRefrence->primaryAccountNumber[0]='\0';
	return ACCOUNT_NOT_FOUND;
    }
    
    else
    {
         
		strcpy(accountRefrence->primaryAccountNumber,cardData->primaryAccountNumber);
			
			
			return SERVER_OK;
		
       
    }

}

/* Description:
 * takes PAN from account reference struct and check if its blocked or not
 * inputs: address of a ST_accountsDB_t
 * output: BLOCKED_ACCOUNT , SERVER_OK
 */
EN_serverError_t isBlockedAccount(ST_cardData_t *cardData)
{
    /* find the matching PAN in accounts array */
	DB_Acc_Index = SearchAccount(cardData);

	

	/* account[index] is the account that has same PAN number we search for
	 * check if its running or not */
	if (DATA_BASE[DB_Acc_Index].state == RUNNING)
		return SERVER_OK;
	else
		return BLOCKED_ACCOUNT;
}


/* Description:
 * take PAN from accountRefrence and check if this account balance enough to make
 * the transAmount in terminalData
 * inputs: address of a ST_accountsDB_t
 * output: BLOCKED_ACCOUNT , SERVER_OK
 */

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    

    /* check if balance is enough to pay the transAmount */
    if ((termData -> transAmount) <= (DATA_BASE[DB_Acc_Index].balance))
    {
        return SERVER_OK;
    }

    else
    {
        return LOW_BALANCE;
    }
}


/* Description:
 * prints all transactions using listSavedTransactions function and
 * takes ST_trasnaction_t struct and saves it in TransactionsDB array
 * inputs: address of a ST_accountsDB_t
 * output: BLOCKED_ACCOUNT , SERVER_OK
 */
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
   /* give transaction sequence number */
   
	transData->transactionSequenceNumber = TRANS_fill+1;

	/* save the transaction in transactionsDB array */
    
    TANSACTION_ARRAY[TRANS_fill].cardHolderData =  transData->cardHolderData;
    
    TANSACTION_ARRAY[TRANS_fill].terminalData =  transData->terminalData;
    
    TANSACTION_ARRAY[TRANS_fill].transactionSequenceNumber =  transData->transactionSequenceNumber;
    
    TANSACTION_ARRAY[TRANS_fill].transState =  transData->transState;
    

	
	
    if (TANSACTION_ARRAY[TRANS_fill].transactionSequenceNumber ==0)
    {
        transData->transState = SAVING_FAILED;
        return SAVING_FAILED;
    }
    else
    {
        /* print all trasnactions */
        
	listSavedTransactions();
    return SERVER_OK;
    TRANS_fill++; /* move this index to the next empty element */

    }


}


/* Description:
 * print all transactions
 * inputs : none
 * outputs: none
 */
void listSavedTransactions(void)
{
    
	uint8_t i;
	printf("\n");
	for (i = 0 ; i <= TRANS_fill ; i++)
	{
        
		printf("#########################\n");
		printf("Transaction Sequence Number: %d\n", TANSACTION_ARRAY[i].transactionSequenceNumber);
		printf("Transaction Date: %s\n",TANSACTION_ARRAY[i].terminalData.transactionDate);
		printf("Transaction Amount: %.2f\n",TANSACTION_ARRAY[i].terminalData.transAmount);

		printf("Transaction State: ");
		TANSACTION_ARRAY[i].transState==APPROVED? printf("APPROVED\n"): \
		TANSACTION_ARRAY[i].transState==DECLINED_INSUFFECIENT_FUND? printf("DECLINED_INSUFFECIENT_FUND\n"):\
		TANSACTION_ARRAY[i].transState==DECLINED_STOLEN_CARD? printf("DECLINED_STOLEN_CARD\n") : \
		TANSACTION_ARRAY[i].transState==FRAUD_CARD? printf("FRAUD_CARD\n") : \
		printf("INTERNAL_SERVER_ERROR\n");

		printf("Terminal Max Amount: %.2f\n",TANSACTION_ARRAY[i].terminalData.maxTransAmount);
		printf("Card Holder Name: %s\n",TANSACTION_ARRAY[i].cardHolderData.cardHolderName);
		printf("PAN: %s\n",TANSACTION_ARRAY[i].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s\n",TANSACTION_ARRAY[i].cardHolderData.cardExpirationDate);
		printf("#########################\n");
	}
}
