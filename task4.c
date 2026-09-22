#include <stdio.h>

struct Account
{
    int accountNumber;
    char name[50];
    float balance;
};

void createAccount()
{
    struct Account acc;
    FILE *fp;

    fp = fopen("account.dat", "wb");

    if(fp == NULL)
    {
        printf("File could not be opened.\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &acc.accountNumber);

    printf("Enter Name: ");
    scanf(" %[^\n]", acc.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(acc), 1, fp);

    fclose(fp);

    printf("Account created successfully.\n");
}

void deposit()
{
    struct Account acc;
    FILE *fp;
    float amount;

    fp = fopen("account.dat", "rb+");

    if(fp == NULL)
    {
        printf("Account not found.\n");
        return;
    }

    fread(&acc, sizeof(acc), 1, fp);

    printf("Enter deposit amount: ");
    scanf("%f", &amount);

    if(amount > 0)
    {
        acc.balance += amount;

        fseek(fp, 0, SEEK_SET);
        fwrite(&acc, sizeof(acc), 1, fp);

        printf("Amount deposited successfully.\n");
    }
    else
    {
        printf("Invalid amount.\n");
    }

    fclose(fp);
}

void withdraw()
{
    struct Account acc;
    FILE *fp;
    float amount;

    fp = fopen("account.dat", "rb+");

    if(fp == NULL)
    {
        printf("Account not found.\n");
        return;
    }

    fread(&acc, sizeof(acc), 1, fp);

    printf("Enter withdrawal amount: ");
    scanf("%f", &amount);

    if(amount <= 0)
    {
        printf("Invalid amount.\n");
    }
    else if(amount > acc.balance)
    {
        printf("Insufficient balance.\n");
    }
    else
    {
        acc.balance -= amount;

        fseek(fp, 0, SEEK_SET);
        fwrite(&acc, sizeof(acc), 1, fp);

        printf("Amount withdrawn successfully.\n");
    }

    fclose(fp);
}

void balanceEnquiry()
{
    struct Account acc;
    FILE *fp;

    fp = fopen("account.dat", "rb");

    if(fp == NULL)
    {
        printf("Account not found.\n");
        return;
    }

    fread(&acc, sizeof(acc), 1, fp);

    printf("\n===== ACCOUNT DETAILS =====\n");
    printf("Account Number : %d\n", acc.accountNumber);
    printf("Name          : %s\n", acc.name);
    printf("Balance       : %.2f\n", acc.balance);

    fclose(fp);
}

int main()
{
    int choice;

    createAccount();

    do
    {
        printf("\n===== BANKING SYSTEM =====\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Balance Enquiry\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                deposit();
                break;

            case 2:
                withdraw();
                break;

            case 3:
                balanceEnquiry();
                break;

            case 4:
                printf("Thank you!\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while(choice != 4);

    return 0;
}