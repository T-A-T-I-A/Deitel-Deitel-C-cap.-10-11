#include <stdio.h>
#include <string.h>
#define SIZE 30

struct attrezzi{
    unsigned int record;
    char name[SIZE];
    int quantita;
    double costo;
};

unsigned int enterChoice(void);
void file();
void newRecord();
void nomeUpdate();
void qUpdate();
void cUpdate();
void deleteRecord();
void stampa();

int main()
{
    unsigned int choice;

    while((choice = enterChoice()) != 0){
        switch(choice){
            case 1:
                file();
                break;
            case 2:
                newRecord();
                break;
            case 3:
                nomeUpdate();
                break;
            case 4:
                qUpdate();
                break;
            case 5:
                cUpdate();
                break;
            case 6:
                deleteRecord();
                break;        
            case 7:
                stampa();
                break;
            default:
                puts("\nScegli opzione: ");
                break;

        }
    }

    return 0;
}

void file()
{
    FILE *fPtr;

    if((fPtr = fopen("hardware.dat", "ab+")) == (NULL)){
        printf("\nImpossibile aprire file.\n");
    }
    else{
        struct attrezzi Att = {0, "", 0, 0.0};
        for(int i = 0; i < 100; i++){
            fwrite(&Att, sizeof(struct attrezzi), 1, fPtr);
        }
    }
    fclose(fPtr);
}

void newRecord()
{
    FILE *fPtr;

    if((fPtr = fopen("hardware.dat", "rb+")) == (NULL)){
        printf("\nImpossibile aprire file.\n");
    }
    else{
        unsigned int account;

        printf("\nInserisci numero di nuovo attrezzo (EOF per fine): ");
        scanf("%u", &account);
            
        struct attrezzi att = {0, "", 0, 0.0};
        fseek(fPtr, (account - 1) * sizeof(struct attrezzi), SEEK_SET);
        fread(&att, sizeof(struct attrezzi), 1, fPtr);

        while(!feof(stdin)){

            if(att.record != 0){
                printf("\nAttrezzo #%u contiene informazioni \n", account);
            }
            else if(account > 0 && account <= 100){
                printf("%s", "Inserisci nome, quantita, costo: ");
                fscanf(stdin, "%29s%d%lf", att.name, &att.quantita, &att.costo);
                att.record = account;
                fseek(fPtr, (account - 1) * sizeof(struct attrezzi), SEEK_SET);
                fwrite(&att, sizeof(struct attrezzi), 1, fPtr);
            }

            printf("\nInserisci numero di nuovo attrezzo (EOF per fine): ");
            scanf("%u", &account);

            fseek(fPtr, (account - 1) * sizeof(struct attrezzi), SEEK_SET);
            fread(&att, sizeof(struct attrezzi), 1, fPtr);
        }
        fclose(fPtr);
    }
}

void nomeUpdate()
{
    FILE *fPtr;
    if((fPtr = fopen("hardware.dat", "rb+")) == (NULL)){
        printf("\nImpossibile aprire file.\n");
    }
    else{
        printf("%s", "Inserisci numero del attrezzo(1 - 100): ");
        unsigned int account;
        scanf("%u", &account);

        fseek(fPtr, (account - 1) * sizeof(struct attrezzi), SEEK_SET);
        struct attrezzi att = {0, "", 0, 0.0};
        fread(&att, sizeof(struct attrezzi), 1, fPtr);

        if(att.record == 0){
            printf("Attrezzo #%u - non ci sono informazioni.", account);
        }
        else{
            printf("%-6u%-29s%-10d%10.2f\n", att.record, att.name, att.quantita, att.costo);

            printf("%s", "Inserisci nuovo nome attrezzo (29 caratteri): ");
            char a[30];
            scanf("%s", a);

            memcpy(att.name, a, SIZE);

            printf("%-6u%-29s%-10d%10.2f\n", att.record, att.name, att.quantita, att.costo);

            fseek(fPtr, (account - 1) * sizeof(struct attrezzi), SEEK_SET);
            fwrite(&att, sizeof(struct attrezzi), 1, fPtr);
        }
    }
    fclose(fPtr);
}

void qUpdate()
{
    FILE *fPtr;
    if((fPtr = fopen("hardware.dat", "rb+")) == (NULL)){
        printf("\nImpossibile aprire file.\n");
    }
    else{

    
        printf("%s", "Inserisci numero del Attrezzo(1 -100): ");
        unsigned int account;
        scanf("%u", &account);

        //sposta il puntatore del file al record correto nel file
        fseek(fPtr, (account - 1) * sizeof(struct attrezzi), SEEK_SET);

        //crea un oggetto attrezzi senza informazioni
        struct attrezzi Att = {0, "", 0, 0.0};

        //leggi il record del file
        fread(&Att, sizeof(struct attrezzi), 1, fPtr);

        if(Att.record == 0){
            printf("Attrezzo #%u - non ci sono informazioni.", account);
        }
        else{
            printf("%-6u%-29s%-10d%10.2f\n", Att.record, Att.name, Att.quantita, Att.costo);
            printf("%s", "Inserisci quantità da aggiornare (+ o -): ");
            int q;
            scanf("%d", &q);
            Att.quantita += q;

            printf("%-6u%-29s%-10d%10.2f\n", Att.record, Att.name, Att.quantita, Att.costo);

            //sposta il puntatore del file al record correto nel file
            fseek(fPtr, (account - 1) * sizeof(struct attrezzi), SEEK_SET);
            //scrivi il record aggiornato al posto del vecchio record nel file
            fwrite(&Att, sizeof(struct attrezzi), 1, fPtr);
        }
    }
    fclose(fPtr);
}


void cUpdate()
{
    FILE *fPtr;
    if((fPtr = fopen("hardware.dat", "rb+")) == (NULL)){
        printf("\nImpossibile aprire file.\n");
    }
    else{
    printf("%s", "Inserisci numero del attrezzo(1 - 100): ");
    unsigned int account;
    scanf("%u", &account);

    //sposta il puntatore del file al record corretto nel file
    fseek(fPtr, (account - 1) * sizeof(struct attrezzi), SEEK_SET);   
    struct attrezzi Att = { 0, "", 0, 0.0};
    fread(&Att, sizeof(struct attrezzi), 1, fPtr);

    if(Att.record == 0){
        printf("Attrezzo #%u - non ci sono informazioni.", account);
    }
    else{
        printf("%-6u%-29s%-10d%10.2f\n", Att.record, Att.name, Att.quantita, Att.costo);
        printf("%s", "Inserisci nuovo costo: ");
        double c;
        scanf("%lf", &c);
        Att.costo = c;

        printf("%-6u%-29s%-10d%10.2f\n", Att.record, Att.name, Att.quantita, Att.costo);

        //sposta il puntatore del file al record corretto nel file
        fseek(fPtr, (account - 1) * sizeof(struct attrezzi), SEEK_SET);
        fwrite(&Att, sizeof(struct attrezzi), 1, fPtr);
    }
    }
    fclose(fPtr);
}

void deleteRecord()
{
    FILE *fPtr;
    if((fPtr = fopen("hardware.dat", "rb+")) == (NULL)){
        printf("\nImpossibile aprire file.\n");
    }
    else{
        //ottieni il numero dell'attrezzo da cancellare
        printf("%s", "Inserisci numero dell'attrezzo da cancellare: ");
        unsigned int account;
        scanf("%u", &account);

        fseek(fPtr, (account - 1) * sizeof(struct attrezzi), SEEK_SET);
        struct attrezzi att;
        //leggi il record del file
        fread(&att, sizeof(struct attrezzi), 1, fPtr);

        //stampa un messaggio di errore se attrezzo non esiste
        if(att.record == 0){
            printf("Attrezzo #%u - non trovato.\n", account);
        }
        else{
            
        fseek(fPtr, (account - 1) * sizeof(struct attrezzi), SEEK_SET);
        struct attrezzi blankAtt = {0, "", 0, 0.0};
        //sostituisci il record esistente con il record vuoto
        fwrite(&blankAtt, sizeof(struct attrezzi), 1, fPtr);
        }
    }
    fclose(fPtr);
}


unsigned int enterChoice(void)
{
    printf("%s", "Inserisci la tua opzione: \n"
            "1 - Creare un file di 100 record vuoti\n"
            "2 - Aggiungere nuovo attrezzo\n"
            "3 - Aggiornare nome di un attrezzo\n"
            "4 - Aggiornare quantità di un attrezzo\n"
            "5 - Aggiornare costo di un attrezzo\n"
            "6 - Cancellare un attrezzo\n"
            "7 - per stampare tutti record\n"
            "0 - Chiudi programma.\n");

    unsigned int menuChoice;
    scanf("%u", &menuChoice);
    return menuChoice;
}

void stampa()
{
    FILE *fPtr;
    fPtr = fopen("hardware.dat", "rb"); 
    
    while(!feof(fPtr)){
        struct attrezzi att = {0, "", 0, 0.0};
        fread(&att, sizeof(struct attrezzi), 1, fPtr);
        printf("%u %s %d %lf\n", att.record, att.name, att.quantita, att.costo);
    }
    fclose(fPtr);
}
