#include <stdio.h>

struct old{
    unsigned int acct;
    char fName[15];
    char lName[15];
    double bal;
} Old;

int menu();
void newAccount();
void newTrans();
void aggiorna();

int main()
{
    int choice; 

    while((choice = menu()) != 3){
        switch(choice){
            case 1:
                newAccount();
                break;
            case 2:
                newTrans();
                break;
            default:
                printf("Inserisci numero valido: \n\n");
                break;
        }
    }

}

int menu()
{
    int x;
    printf("Inserisci numero indicativo: \n"
            "1 - Nuovo account\n"
            "2 - Nuova transazione\n"
            "3 - Fine: \n");
    scanf("%d", &x);
    return x;
}

void newAccount()
{
    FILE *fPtr;

    if((fPtr = fopen("oldmast.dat", "a+")) == NULL){
        puts("Impossibile aprire file.");
    }
    else{
        puts("Inserisci account, nome cognome, balance");
        puts("Inserisci EOF per fine");
        printf("%s", "? ");

        scanf("%u%14s%14s%lf", &Old.acct, Old.fName, Old.lName, &Old.bal);

        while(!feof(stdin)){
            fprintf(fPtr, "%u %s %s %.2f\n", Old.acct, Old.fName, Old.lName, Old.bal);
            printf("%s", "? ");
            scanf("%u%14s%13s%lf", &Old.acct, Old.fName, Old.lName, &Old.bal);
        }

        fclose(fPtr);
        aggiorna();
    }
}

void newTrans()
{
    FILE *tPtr;

    if((tPtr = fopen("trans.dat", "w")) == NULL){
        puts("Impossibile aprire file.");
    }
    else{
        FILE *oPtr;
        if((oPtr = fopen("oldmast.dat", "r")) == (NULL)){
            printf("Impossibile aprire file\n");
        }  
        unsigned int acc;
        double bal;

        puts("Inserisci account, balance");
        puts("Inserisci EOF per fine");
        printf("%s", "? ");
        scanf("%u%lf", &acc, &bal);

        while(!feof(stdin)){

            while(!feof(oPtr)){

                fscanf(oPtr, "%u%14s%14s%lf", &Old.acct, Old.fName, Old.lName, &Old.bal);

                if(Old.acct == acc){
                    
                    break;
                }
            }

            if(Old.acct == acc){
                fprintf(tPtr, "%u %.2f\n", acc, bal);
                printf("%s", "? ");
            }
            else{
                printf("%s", "Inserisci il numero di conto dal record della transazione");
            }
            rewind(oPtr);
            scanf("%u%lf", &acc, &bal);
        }

        fclose(tPtr);
        fclose(oPtr);
        aggiorna();

    }
}

void aggiorna()
{
    void copy();
    FILE *nPtr;

    if((nPtr = fopen("newmast.dat", "w")) == NULL){
        puts("Impossibile aprire file.");
    }
    else{
        FILE *oldPtr = fopen("oldmast.dat", "r");
        FILE *transPtr = fopen("trans.dat", "r");
        unsigned int transAcct;
        double transBal;

        fscanf(oldPtr, "%u%14s%14s%lf", &Old.acct, Old.fName, Old.lName, &Old.bal);

        while(!feof(oldPtr)){
            rewind(transPtr);
            
            double NewBal = Old.bal;

            fscanf(transPtr, "%u%lf", &transAcct, &transBal);
            
            while(!feof(transPtr)){
                
                if(transAcct == Old.acct){
                    NewBal += transBal;
                }
                fscanf(transPtr, "%u%lf", &transAcct, &transBal);
            }

            fprintf(nPtr, "%u %s %s %lf\n", Old.acct, Old.fName, Old.lName, NewBal);
            fscanf(oldPtr, "%u%14s%14s%lf", &Old.acct, Old.fName, Old.lName, &Old.bal);

        }

        fclose(transPtr);
        fclose(oldPtr);
        fclose(nPtr);
        copy();
        transPtr = fopen("trans.dat", "w");
    }
}

void copy()
{
    FILE *nPtr, *oPtr;

    nPtr = fopen("newmast.dat", "r");
    oPtr = fopen("oldmast.dat", "w");

    fscanf(nPtr, "%u%14s%14s%lf", &Old.acct, Old.fName, Old.lName, &Old.bal);

    while(!feof(nPtr)){
        fprintf(oPtr, "%u %s %s %lf\n", Old.acct, Old.fName, Old.lName, Old.bal);
        fscanf(nPtr, "%u%14s%14s%lf", &Old.acct, Old.fName, Old.lName, &Old.bal);
    }

    fclose(oPtr);
    fclose(nPtr);

}
