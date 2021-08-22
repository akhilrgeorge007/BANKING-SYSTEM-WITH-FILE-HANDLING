/* 
BANKING SYSTEM PROGRAM WITH PERSISTENCE
BINARY FILE - data.dat used to store user informations
[Program uses structure, functions,file handling]
                                                 */

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

// Account details structure
struct account_details{
    char name[25];
    char gender;
    char ac_no[15];
    char password[10];
    float balance;
};
struct account_details s; // Global variable of struct declared 

FILE *f; // Global pointer declared for file handling 

void display(struct account_details x);
void view_file();
void add_file(struct account_details x);
int login_verification(char ac[15],char pass[10]);
void login_user();
void user_interface();
void create_user();
void main_window();
void withdraw();
void deposit();
void balance_enq();

// Function to display the structure
void display(struct account_details x){
    printf("\n A/C no: %s",x.ac_no);
    printf("\n Name: %s",x.name);
    printf("\n Gender: %c",x.gender);
    printf("\n Balance: %.2f",x.balance);
}

// View contents of file
void view_file(){
    struct account_details x;
    f=fopen("data.dat","rb+");
    while(fread(&x,sizeof(x),1,f)){
        display(x);
        printf("\n"); 
    }
}

// Update file with the changed value
void update_file(){
    struct account_details x;
    f=fopen("data.dat","rb+");
    while(fread(&x,sizeof(x),1,f)){
        if(strcmp(s.ac_no,x.ac_no)==0){
            fseek(f,ftell(f)-sizeof(s),SEEK_SET);
            fwrite(&s,sizeof(x),1,f);
            break;
        }
    }
    fclose(f);
}

// Appends new user at end of file
void add_file(struct account_details x){
    f=fopen("data.dat","ab+");
    fwrite(&x,sizeof(x),1,f);
    fclose(f);
}

// Login verification checks entered values with values stored in file
int login_verification(char ac[15],char pass[10]){
    f=fopen("data.dat","rb+");
    while(fread(&s,sizeof(s),1,f)){
        if(strcmp(s.ac_no,ac)==0){
            if(strcmp(s.password,pass)==0){
                return(0);
            }
        }  
    }
    return(1);
}

// Verifies if A/C no already present in file or not
int AC_verification(char ac[15]){
    struct account_details x;
    f=fopen("data.dat","rb+");
    while(fread(&x,sizeof(x),1,f)){
        if(strcmp(x.ac_no,ac)==0){
            return(0);
        }  
    }
    return(1);
}

// Login interface
void login_user(){
    system("cls");
    char ac[15];
    char pass[10];
    int res;
    printf("\n ##################################");
    printf("\n  LOGIN ");
    printf("\n ##################################\n");
    printf("\n A/C number:  ");
    gets(ac);
    printf("\n Password:    ");
    gets(pass);
    res = login_verification(ac,pass);
    if(res==0){
        user_interface(); 
    }
    else{
        printf("\n WRONG CREDENTIALS, TRY AGAIN");
        getch();
        login_user();
    }
}

// Logged in User interface
void user_interface(){
    system("cls");
    int ch;
    printf("\n ##################################");
    printf("\n  LOGGED IN TO A/C NO: %s",s.ac_no);
    printf("\n ##################################");
    printf("\n  SERVICES");
    printf("\n ##################################\n");
    printf("\n 1. Withdraw");
    printf("\n 2. Deposit");
    printf("\n 3. Balance enquiry");
    printf("\n 4. Logout");
    printf("\n ENTER CHOICE: ");
    scanf("%d",&ch);
    switch (ch){
        case 1: getchar();
                withdraw();
                break;
        case 2: getchar();
                deposit();
                break;
        case 3: getchar();
                balance_enq();
                break;
        case 4: main_window();
                break;
        default: printf("\n Wrong choice");
                 user_interface();
    }
}

// Withdrawal function
void withdraw(){
    system("cls");
    float amt;
    printf("\n ##################################");
    printf("\n  WITHDRAWAL ");
    printf("\n ##################################\n");
    printf("\n A/C No: %s",s.ac_no);  
    printf("\n ENTER AMOUNT TO WITHDRAWN: ");
    scanf("%f",&amt); 
    if(amt<s.balance-1000){
        s.balance-=amt;
        update_file();
        printf("\n Updated balance: %.2f",s.balance);
        getch();
    }
    else{
        printf("\n Min balance not maintained");
        getch();
    }
    user_interface();
}

// Deposit function
void deposit(){
    system("cls");
    float amt;
    printf("\n ##################################");
    printf("\n  DEPOSIT ");
    printf("\n ##################################\n");
    printf("\n A/C No: %s",s.ac_no);
    printf("\n ENTER AMOUNT TO DEPOSIT: ");
    scanf("%f",&amt);
    s.balance+=amt;
    update_file();
    printf("\n Updated balance: %.2f",s.balance);
    getch();
    user_interface();
}

// Displays A/C Details
void balance_enq(){
    system("cls");
    printf("\n ##################################");
    printf("\n  ACCOUNT DETAILS ");
    printf("\n ##################################\n");
    display(s);
    getch();
    user_interface();
}

// Creates new user
void create_user(){
    system("cls");
    int res;
    float bal;
    printf("\n ##################################");
    printf("\n  NEW USER ");
    printf("\n ##################################\n");

    printf("\n A/C No: ");
    gets(s.ac_no);
    res=AC_verification(s.ac_no);
    if(res==0){
        printf("\n User already exists. Please Try again");
        getch();
        main_window();
    }
    printf("\n Enter name: ");
    gets(s.name); 
    printf("\n Gender(M/F): ");
    scanf("%c",&s.gender);
    getchar();
    printf("\n Enter password: ");
    gets(s.password);
    bal_rep:
    printf("\n Enter deposit amount (min balance-RS.1000)");
    scanf("%f",&bal);
    if(bal<1000){
        printf(" Min balance not satisfied");
        goto bal_rep;
    }
    s.balance=bal;  
    add_file(s);
    printf("\n ##################################");
    printf("\n  USER ADDED SUCCESSFULLY");
    printf("\n ##################################\n");
    getch();
    main_window();
}

// Admin interface to view file contents
void admin_interface(){
    system("cls");
    char pass[10];
    printf("\n ##################################");
    printf("\n  ADMIN LOGIN");
    printf("\n ##################################\n");
    printf("\n Password: ");
    scanf("%s",&pass);
    if(strcmp(pass,"123")==0){
        system("cls");
        printf("\n ##################################");
        printf("\n  FILE CONTENTS (data.dat)");
        printf("\n ##################################\n");
        view_file();
        getch();
        main_window();
    }
    else{
        printf("\n Wrong admin password");
        getch();
        main_window();
    }
}

// Main window 
void main_window(){
    system("cls");
    int ch;
    printf("\n ##################################");
    printf("\n  CITY BANK");
    printf("\n ##################################\n");
    printf("\n 1. LOGIN");
    printf("\n 2. CREATE NEW USER");
    printf("\n 3. ADMIN LOGIN"); 
    printf("\n 4. EXIT");
    printf("\n ENTER CHOICE: ");
    scanf("%d",&ch);
    switch (ch){
        case 1: getchar();
                login_user();
                break;
        case 2: getchar();
                create_user();
                break;
        case 3: getchar();
                admin_interface();
                break;
        case 4: exit(0);
                break;
        default: printf("\n Wrong choice");
                 main_window();
    }
}

void main(){
    main_window();
}
