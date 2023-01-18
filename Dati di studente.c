#include <stdio.h>
#define SIZE_NAME 15
#define SIZE_STUDENT 50

unsigned int stud = 0;

struct studente{
    unsigned int matricola;
    char nome[SIZE_NAME];
    char cognome[SIZE_NAME];
    double mediaEsami;
    unsigned int numEsSostenuti;
};

typedef struct studente Studente;

unsigned int menu(void);
void datiStudenti(Studente *dPtr);
void mediaEsame(Studente *mPtr);
void rMatricola(Studente *dPtr);
void stampa(Studente *dPtr);

int main()
{
    Studente dati[SIZE_STUDENT];
    
    unsigned int choice;
    
    while((choice = menu()) != 5){
        switch(choice){
            case 1:
                datiStudenti(dati);
                break;
            case 2:
                mediaEsame(dati);
                break;
            case 3:
                rMatricola(dati);
                break;
            case 4:
                stampa(dati);
                break;
            default:
                printf("\nInserisci numero valido: \n");
                break;      
        }
    }   
}

void datiStudenti(Studente *dPtr)
{
    int x;
    for(; stud < SIZE_STUDENT; stud++){
        printf("Inserisci\n|MATRICOLA |NOME |COGNOME |MEDIA ESAME |NUMERO ESAMI SOSTENUTI|\n");
        scanf("%u%s%s%lf%u", &dPtr[stud].matricola, dPtr[stud].nome, dPtr[stud].cognome, &dPtr[stud].mediaEsami, &dPtr[stud].numEsSostenuti);
        printf("inserisci 1 per continuare o -1 per fine\t");
        scanf("%d", &x);
        if(x == -1 ){
            stud++;
            break;
        }
    }
}

void mediaEsame(Studente *mPtr)
{
    double *max = &mPtr->mediaEsami;
    
    for(int i = 1; i < stud; i++){
        if(mPtr[i].mediaEsami > *max){
            max = &mPtr[i].mediaEsami;
        }
    }
    
    for(int i = 0; i < stud; i++){
        if(mPtr[i].mediaEsami == *max){
            printf("\nSudente con media esami piu alta\n|MATRICOLA |NOME           |COGNOME          |MEDIA ESAME |NUMERO ESAMI SOSTENUTI|\n %-11u%-16s%-18s%-15.2f%8u\n", 
                    mPtr[i].matricola, mPtr[i].nome, mPtr[i].cognome, mPtr[i].mediaEsami, mPtr[i].numEsSostenuti);
            break;
        }
    }
    
}

void rMatricola(Studente *dPtr)
{
    printf("\nInserisci matricola:   \n");
    int x;
    scanf("%d", &x);
    
    for(int i = 0; i < stud; i++){
        if(x == dPtr[i].matricola){
            printf("\n|MATRICOLA |NOME           |COGNOME         |MEDIA ESAME |NUMERO ESAMI SOSTENUTI|\n\n %-11u%-16s%-18s%-15.2f%8u\n", 
                dPtr[i].matricola, dPtr[i].nome, dPtr[i].cognome, dPtr[i].mediaEsami, dPtr[i].numEsSostenuti);
            break;
        }
    }
}

void stampa(Studente *dPtr)
{
    printf("\n\n|N |MATRICOLA |NOME           |COGNOME        |MEDIA ESAME |NUMERO ESAMI SOSTENUTI|\n");
    for(int i = 0; i < stud; i++){
        printf("%-3d %-11u%-16s%-18s%-15.2f%8u\n", i + 1, dPtr[i].matricola,
             dPtr[i].nome, dPtr[i].cognome, dPtr[i].mediaEsami, dPtr[i].numEsSostenuti);
    }
}

unsigned int menu(void)
{
    unsigned int x;
    printf("\n\n%s\n%s\n%s\n%s\n%s\n%s\n", "SCEGLI: ", 
        "1 per inserire o aggiungere dati dello studente", 
        "2 per ricerca con media esame piu alta", 
        "3 per ricerca con matricola", "4 per stampare tutti i dati","5 per fine: ");
    scanf("%u", &x);
    printf("\e[1;1H\e[2J"); 
    return x;
}
