/**
 * @file server.h
 * @author Ahmed khaled khalaf (khalafawy22899@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>

#include "../Terminal/terminal.h"

#ifndef SERVER_H
#define SERVER_H


/****************************** Types Declaration ************************************/
typedef unsigned int uint32_t;


typedef enum EN_transState_t
{
APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR, FRAUD_CARD
}EN_transState_t;

typedef enum EN_serverError_t
{
SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t;



typedef struct ST_transaction_t
{
ST_cardData_t cardHolderData;
ST_terminalData_t terminalData;
EN_transState_t transState;
uint32_t transactionSequenceNumber;
}ST_transaction_t;


typedef enum EN_accountState_t
{
     RUNNING,
     BLOCKED
}EN_accountState_t;
typedef struct ST_accountsDB_t
{
     float balance;
     EN_accountState_t state;
     uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

/****************************** Functions ProtoTypes ************************************/

/* Description:
 * takes PAN from cardData_s and check if an account with this PAN in the accounts array
 * takes transAmount from terminalData_s and compare it with account balance
 * checks if this account is blocked or not
 * save transaction and update balance or return error if array of transactions is full
 * inputs: address of a ST_transaction_t
 * output: FRAUD_CARD , DECLINED_INSUFFECIENT_FUND , DECLINED_STOLEN_CARD
 * INTERNAL_SERVER_ERROR , APPROVED
 */
EN_transState_t recieveTransactionData(ST_transaction_t *transData);


/* Description:
 * takes PAN from cardData and check if it exists in DB or not,
 * if exist copy its value to accountRefrence PAN then return server_ok
 * otherwise put null in accountRefrence PAN and return acc_not_found
 * inputs: address of a ST_cardData_t , address of a ST_accountsDB_t
 * output: ACCOUNT_NOT_FOUND , SERVER_OK
 */
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence);

/* Description:
 * takes PAN from account reference struct and check if its blocked or not
 * inputs: address of a ST_accountsDB_t
 * output: BLOCKED_ACCOUNT , SERVER_OK
 */
EN_serverError_t isBlockedAccount(ST_cardData_t *cardData);

/* Description:
 * take PAN from accountRefrence and check if this account balance enough to make
 * the transAmount in terminalData
 * inputs: address of a ST_terminalData_t
 * output: BLOCKED_ACCOUNT , SERVER_OK
 */
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);

/* Description:
 * prints all transactions using listSavedTransactions function and
 * takes ST_trasnaction_t struct and saves it in TransactionsDB array
 * inputs: address of a ST_transaction_t
 * output: BLOCKED_ACCOUNT , SERVER_OK
 */
EN_serverError_t saveTransaction(ST_transaction_t *transData);

/**
 * Description: function that search for the PAN of the account in the data base (using linear search algorithm)
 */
uint8_t SearchAccount (ST_cardData_t *cardData);


/* Description:
 * print all transactions
 * inputs : none
 * outputs: none
 */
void listSavedTransactions(void);
#endif /* header guard */