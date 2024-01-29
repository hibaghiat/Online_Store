// 99385
// 108575
#include <stdio.h>
#include <string.h>
//function that converts a string of characters to all uppercase letters
void uppercase(char c[100]); 
//function that swaps two strings
void swaps(char *a , char *b); 
//function that calculates the user's order
double Make_Order(int *product, int *quantity); 
// funtion that changes user information
void change_user_info(int *a, int *k, char fname[300][10], char lname[300][10], char email[300][30], char password[300][20], char bank_account_number[300][30]);
int main (void){
    int i, w, v=0, f=1, j=0, a, c, s[3], k = -1, N = 0, sign=0, log=0, count=3, product, quantity;
    char email[300][30], fname[300][10], lname[300][10], password[300][20], bank_account_number[300][20], secret_question[300][100], answer[300][100];
    char em[30], passw[20], ans[100], e_signup[30], bank_acc_num_signup[20], yes_no[100];
    int lenght, flag = 0;
    char pass[20], keep[100], bank_account[20]; 
    double balance[300], balance_signup, price, temp, sum=0;
    FILE *inp, *out;

    //we open database.txt to read from it
    inp = fopen("database.txt", "r");
    //we open output.txt (that will be automatically created) to write in it 
    out = fopen("output.txt", "w");

    /*we scan all the user information from the database file (database.txt), we divided the file into multiple two dimentional strings 
    exceplt for the balance that's an array of doubles.
    Then we print the arrays in an output file (output.txt).
   */

    for (i = 0; i < 3; i++)
    {
        fscanf(inp, "%s %s %s %s %s %lf %s %s", email[i], fname[i], lname[i], password[i], bank_account_number[i], &balance[i], secret_question[i], answer[i]);
        fprintf(out, "%s %s %s %s %s %f %s %s", email[i], fname[i], lname[i], password[i], bank_account_number[i], balance[i], secret_question[i], answer[i]);
    }
    fclose(inp);
    fclose(out);
    printf("Login in !");
    printf("Enter Email: ");
    scanf("%s", em);
    //we compare the email entered by the user(em) to the three emails from database
    for (i = 0; i < 3; i++)
    {
        if (strcmp(em, email[i]) == 0)
        {
            k = i;
        }
    }
    if (k == -1)
    {
        //if the email doesn't exist we direct the user to sign up
        sign=2;
    }

    if (k != -1)
    {
        //if the email exists we ask for the password and check if it's right
        printf("\nEnter Password");
        scanf("%s", passw);
        if (strcmp(passw, password[k]) == 0){
            //if the password is the right one we direct the user to choose what actions he/she want to do
            log=3;
            sign=0;
            printf("\nwelcome. Login Success!");
        }
        else{
            lenght = strlen(passw);
            for (j = 0; j < lenght; j++)
            {
                if (strncmp(&passw[j], &password[k][j], 1) == 0)
                {
                    //we check how many characters are the same
                    N++;
                }
                if (passw[j] != passw[j + 1])
                {
                    if ((passw[j] == password[k][j + 1]) && (password[k][j] == passw[j + 1]))
                    {
                        //we check how many consecutive characters are inverted
                        flag = flag + 1;
                    }
                }
            }
        //if all the characters are the same except for the two inverted consecutive characters
        if (lenght == N + 2 && flag == 1){
            printf("\n Answer the following question: %s", secret_question[k]);
            scanf("%s", ans);
            //if the answer is the right one we direct the user to choose what actions he/she wants to do
            if (strcmp(ans, answer[k]) == 0)
        {
            printf("\nwelcome. Login Success!");
            log=3;
        }
            else{
                //we direct the user to sign up
                sign=2;
            }
        }
        else{
            //we direct the user to sign up
            sign=2;
        }
        
    }
    }
    //sign up:
    if(sign==2){
        k=3;
        printf("\nPlease sign up!\n\nEnter your email adress to sign up:\n");
        scanf("%s", e_signup);
        do{
            f=0;
            //we check whether the email already exists
            for (i = 0; i < 3; i++)
            {
                if(strcmp(e_signup, email[i]) == 0)
                    f++;
             }
            if (f!=0){
                printf("\nThis email already exists!/n Please enter a new one: ");
                scanf("%s", e_signup);
                
            }
            //the loop will keep repeting as long as the email already exists
        }while (f!=0);

        //we get the other information once the email is new

        printf("\nEnter your first name: ");
        scanf("%s", fname[k]);
        printf("\nEnter your last name: ");
        scanf("%s", lname[k]);
        printf("\nEnter your password: ");
        scanf("%s", password[k]);
        printf("\nEnter your bank account number: ");
        scanf("%s", bank_acc_num_signup);
        f=1;
        do{
            f=0;
            //we check whether the bank account already exists
            for (i = 0; i < 3; i++){
                if(strcmp(bank_acc_num_signup, bank_account_number[i])==0)
                f++;
            }
            if(f!=0){
                printf("\nThis bank account number already exists!\nPlease enter a different one: ");
                scanf("%s", bank_acc_num_signup);
            }   
            //the loop will keep repeting it's sell as long as the bank account number is not new
        }while (f!=0);

        //we get the rest of the information from the user after getting a new bank account number

        printf("\nEnter your balance: ");
        scanf("%lf", &balance[k]);
        printf("\nEnter a secret question to help you in case you forget your password: ");
        scanf("%s", secret_question[k]);
        printf("\nEnter the answer to your secret question: ");
        scanf("%s", answer[k]);

        //we complete the sign up step once we have all the user info

        strcpy(email[k], e_signup);
        strcpy(bank_account_number[k] , bank_acc_num_signup);
        printf("Sign up successful!");
        count++;
        out=fopen("output.txt","w");

        //we update the contents of the output file

        for (i = 0; i < count; i++)
        {
            fprintf(out, "\n%s %s %s %s %s %f %s %s",email[i], fname[i], lname[i], password[i], bank_account_number[i], balance[i], secret_question[i], answer[i]);
        }
        fclose(out);
        log=3;
    }
    if(log==3){
        do{
            printf("\nwhat do you wish to do?\n1)Logout\n2)Change Account info\n3)Make an order\n4)Delete Account");
            scanf("%d", &w);
            switch (w)
            {
            case 1: //the user chose to log out
                printf("\nYou have successfully logged out!\n");
                //we sort all the user information in alphabetical order starting from the family name
                for(i=0;i<count;i++){

                    for(j=i+1;j<count;j++){
                        
                        if(strcmp( lname[i], lname[j])>0){
                    
                            // swapping the last name
                            swaps( lname[i] , lname[j]);

                            // swapping the first name
                            swaps( fname[i] , fname[j]);

                            // swapping the email
                            swaps( email[i] , email[j]);
                            
                            // swapping the password
                            swaps( password[i] , password[j]);
                            
                            // swapping the bank account number
                            swaps( bank_account_number[i] , bank_account_number[j]);
                            
                            // swapping the balance
                            temp=balance[i];
                            balance[i]=balance[j];
                            balance[j]=temp;
                            
                            // swapping the secret question 
                            swaps( secret_question[i] , secret_question[j]);   
                            
                            // swapping the answer to the secret question
                            swaps( answer[i] , answer[j]);   
                        }                                                                
                    }
                }
                out=fopen("output.txt","w");
                //we update the contents of the output file
                for (i = 0; i < count; i++)
                {
                    fprintf(out, "\n%s %s %s %s %s %f %s %s",email[i], fname[i], lname[i], password[i], bank_account_number[i], balance[i], secret_question[i], answer[i]);
                }
                fclose(out);
                return;
                break;
            case 2: //the user chose to change his/her account information
                do{
            printf("\n\nPress 1 to change your first name\nPress 2 to change your last name\nPress 3 to change your e-mail adress\nPress 4 to change your password\nPress 5 to change your bank account number\n");
            scanf("%d", &a);
            printf("Enter your password to re-authenticate");
            scanf("%s",pass);
            if(strcmp(pass,password[k])==0){
            change_user_info(&a, &k, fname, lname, email, password, bank_account_number);
            out=fopen("output.txt","w");
            //the user chose to log out
            for (i = 0; i < 4; i++)
            {
                printf("\n%s %s %s %s %s %f %s %s",email[i], fname[i], lname[i], password[i], bank_account_number[i], balance[i], secret_question[i], answer[i]);
                fprintf(out, "\n%s %s %s %s %s %f %s %s",email[i], fname[i], lname[i], password[i], bank_account_number[i], balance[i], secret_question[i], answer[i]);
            }
            fclose(out);
            printf("Do you wish to change something else? YES/NO");
            scanf("%s", yes_no);
            uppercase(yes_no);
            }
            else{
                printf("wrong password!");
            }
        } while (strcmp(yes_no, "YES") == 0);
        break;
            case 3: //the user chose to make an order and complete it
            do{
                printf("which item do you wish to purchase");
                printf("\nChoose 1 for books, 2 for Skincare, 3 for watch, 4 for desk, 5 for laptop.");
                scanf("%d",&product);
                printf("\nHow many would you like to purchase");
                scanf("%d",&quantity);
                price=Make_Order( &product, &quantity );
                printf("\nThat costs: %f MAD",price);
                sum=sum+price;
                printf("\nYour TOTAL: %f MAD",sum);
                printf("\nDo you wish to keep on purchasing? Yes or No");
                scanf("%s",keep);
                uppercase(keep);
            }while(strcmp(keep,"YES")==0);
            
            if(balance[k]>sum){
                balance[k]=balance[k]-sum;
                printf("\nYour new balance is: %f MAD",balance[k]);
                out=fopen("output.txt","W");
                for(i=0;i<count;i++){
                    fprintf(out, "\n%s %s %s %s %s %f %s %s",email[i], fname[i], lname[i], password[i], bank_account_number[i], balance[i], secret_question[i], answer[i]);
                }
                fclose(out);
            }
            else{
            for(j=0;j<3;j++){
                if(balance[k]<sum){
                printf("Your balance isn't enough!\n Please enter a different bank account");
                scanf("%s",bank_account);
                f=1;
                do{
                    f=0;
                    for (i = 0; i < count; i++){
                        if(strcmp(bank_account, bank_account_number[i])==0)
                            f++;
                    }
                    if(f!=0){
                        printf("\nThis bank account number is taken!\nPlease enter a different one: ");
                        scanf("%s", bank_account);
                    }   
                }while (f!=0);
                strcpy(bank_account_number[k],bank_account);
                printf("Balance?");
                scanf("%lf",&balance[k]);
                }
                else{
                    balance[k]=balance[k]-sum;
                    printf("\nYour new balance is: %f MAD",balance[k]);
                    out=fopen("output.txt","W");
                    for(i=0;i<count;i++){
                        fprintf(out, "\n%s %s %s %s %s %f %s %s",email[i], fname[i], lname[i], password[i], bank_account_number[i], balance[i], secret_question[i], answer[i]);
                    }
                fclose(out);
                }
            }
            }
            if(j==2 && balance[k]<sum){
                printf("\nYour order has been dropped!");
                return;
            }
            break;
            case 4: //the user chose to delete his/her account
                for(i=k;i<count;i++){
                
                strcpy(email[i],email[i+1]);
                strcpy(fname[i],fname[i+1]);
                strcpy(lname[i],lname[i+1]);
                strcpy(password[i],password[i+1]);
                strcpy(bank_account_number[i],bank_account_number[i+1]);
                balance[i]=balance[i+1];
                strcpy(secret_question[i],secret_question[i+1]);
                strcpy(answer[i],answer[i+1]);
                }  
                out=fopen("output.txt","W");
                for(i=0;i<count-1;i++){
                    fprintf(out, "\n%s %s %s %s %s %f %s %s",email[i], fname[i], lname[i], password[i], bank_account_number[i], balance[i], secret_question[i], answer[i]);
                    }
                fclose(out);
                break;
            }
        }while( (w==2) || (w==3) );
    }
    return 0;
}
void change_user_info(int *a, int *k, char fname[300][10], char lname[300][10], char email[300][30], char password[300][20], char bank_account_number[300][30]){
    char fn[10], ln[10], e[30], pa[20], bank_acc_num[20];
    
            switch (*a)
            {
            case 1:
                printf("\nEnter your new first name : ");
                // scanf("%s", fn[*k]);
                scanf("%s", fn);
                strcpy(fname[*k], fn); 
                break;
            case 2:
                printf("\nEnter a new last name : ");
                // scanf("%s", ln[*k]);
                // strcpy(lname[*k],ln[*k]);
                scanf("%s", ln);
                strcpy(lname[*k],ln);
                break;
            case 3:
                printf("\nEnter a new e-mail adress : ");
                // scanf("%s", e[*k]);
                // strcpy(email[*k],e[*k]);
                scanf("%s", e);
                strcpy(email[*k],e);
                break;
            case 4:
                printf("\nEnter a new password : ");
                // scanf("%s", pa[*k]);
                // strcpy(password[*k],pa[*k]);
                scanf("%s", pa);
                strcpy(password[*k],pa);
                break;
            case 5:
                printf("\nEnter your new bank account : ");
                // scanf("%s", bank_acc_num[*k]);
                // strcpy(bank_account_number[*k],bank_acc_num[*k]);
                scanf("%s", bank_acc_num);
                strcpy(bank_account_number[*k],bank_acc_num);
                 
                break;
            }
}
double Make_Order(int *product, int *quantity){
    double price;

        switch(*product){
            case 1:
            price=*quantity*200;
            break;
            case 2:
            price=*quantity*700;
            break;
            case 3:
            price=*quantity*1000;
            break;
            case 4:
            price=*quantity*4000;
            break;
            case 5:
            price=*quantity*6000;
            break;
        }
        return price;
}
void swaps(char *a , char *b){
    char temp[30];
    strcpy(temp,a);
    strcpy(a,b);
    strcpy(b,temp);
    return;
}
void uppercase(char c[100]){
    int i = 0;
        while (c[i] != '\0'){
            // if character is in lowercase
            // then subtract 32
            if (c[i] >= 'a' && c[i] <= 'z'){
                c[i] = c[i] - 32;
            }
            i++;
    }
}