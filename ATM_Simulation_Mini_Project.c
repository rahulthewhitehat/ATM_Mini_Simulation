#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PIN_LENGTH 5
#define MAX_ACCOUNTS 100

struct account {
    int account_number;
    char name[MAX_NAME_LENGTH];
    char pin[MAX_PIN_LENGTH];
    double balance;
};

struct account accounts[MAX_ACCOUNTS];
int total_accounts = 0;

int validate_account(int account_number, char *pin) {
    for (int i = 0; i < total_accounts; i++) {
        if (accounts[i].account_number == account_number && strcmp(accounts[i].pin, pin) == 0) {
            return i;
        }
    }
    return -1;
}

void display_account_menu(int account_index) {
    printf("\nAccount Menu:\n");
    printf("1. Deposit\n");
    printf("2. Withdraw\n");
    printf("3. Check Balance\n");
    printf("4. Change ATM PIN\n");
    printf("5. Logout\n");
    printf("Enter choice: ");
}

void deposit(int account_index) {
    double amount;
    printf("Enter amount to deposit: ");
    scanf("%lf", &amount);
    accounts[account_index].balance += amount;
    printf("Deposit successful! Current balance: %.2f\n", accounts[account_index].balance);
}

void withdraw(int account_index) {
    double amount;
    printf("Enter amount to withdraw: ");
    scanf("%lf", &amount);
    if (amount > accounts[account_index].balance) {
        printf("Insufficient balance\n");
    } else {
        accounts[account_index].balance -= amount;
        printf("Withdrawal successful! Current balance: %.2f\n", accounts[account_index].balance);
    }
}

void check_balance(int account_index) {
    printf("Current balance: %.2f\n", accounts[account_index].balance);
}

void change_pin(int account_index) {
    char old_pin[MAX_PIN_LENGTH];
    printf("Enter old PIN: ");
    scanf("%s", old_pin);

    if (strcmp(accounts[account_index].pin, old_pin) == 0) {
        char new_pin[MAX_PIN_LENGTH];
        printf("Enter new PIN: ");
        scanf("%s", new_pin);
        strcpy(accounts[account_index].pin, new_pin);
        printf("PIN changed successfully!\n");
    } else {
        printf("Incorrect old PIN\n");
    }
}

int main() {
    while (1) {
        printf("\nATM Menu:\n");
        printf("1. Login\n");
        printf("2. Create Account\n");
        printf("3. Exit\n");
        printf("Enter choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("Enter account number: ");
                int account_number;
                scanf("%d", &account_number);
                char pin[MAX_PIN_LENGTH];
                printf("Enter PIN: ");
                scanf("%s", pin);
                int account_index = validate_account(account_number, pin);
                if (account_index != -1) {
                    printf("Welcome to ATM Program by RS\n");
                    printf("Welcome, %s\n", accounts[account_index].name);
                    while (1) {
                        display_account_menu(account_index);
                        scanf("%d", &choice);
                        switch (choice) {
                            case 1:
                                deposit(account_index);
                                break;
                            case 2:
                                withdraw(account_index);
                                break;
                            case 3:
                                check_balance(account_index);
                                break;
                            case 4:
                                change_pin(account_index);
                                break;
                            case 5:
                                printf("Logged out successfully\n");
                                break;
                            default:
                                printf("Invalid choice\n");
                        }
                        if (choice == 5) {
                            break;
                        }
                    }
                } else {
                    printf("Invalid account number or PIN\n");
                }
                break;
            }
            case 2: {
                if (total_accounts < MAX_ACCOUNTS) {
                    printf("Enter name: ");
                    char name[MAX_NAME_LENGTH];
                    scanf("%s", name);
                    printf("Enter PIN (4 digits only): ");
                    char pin[MAX_PIN_LENGTH];
                    scanf("%s", pin);
                    if (strlen(pin) != 4) {
                        printf("PIN should be 4 digits only\n");
                        break;
                    }
                    double balance = 0.0;
                    accounts[total_accounts].account_number = total_accounts + 1;
                    strcpy(accounts[total_accounts].name, name);
                    strcpy(accounts[total_accounts].pin, pin);
                    accounts[total_accounts].balance = balance;
                    printf("Account created successfully! Your account number is %d\n", accounts[total_accounts].account_number);
                    total_accounts++;
                } else {
                    printf("Maximum number of accounts reached\n");
                }
                break;
            }
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
