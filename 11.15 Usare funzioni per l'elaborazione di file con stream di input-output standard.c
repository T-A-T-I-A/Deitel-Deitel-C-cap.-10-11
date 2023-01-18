#include <stdio.h>
#define SIZE 80

void inputFile(char string[]);
void outputFile(char string[]);

int main()
{
    unsigned int choice;
    char s[20];
    
    printf("Inserisci 1 per scrivere su un file\n"
            "Inserisci 2 per leggere da un file\n"
            "Inserisci 3 per fine.\n");
    scanf("%u", &choice);
    
    while(choice != 3){
        
        if(choice == 1){
            printf("\nInserisci nome del file: ");
            scanf("%19s", s);
            inputFile(s);
        }
        else if(choice == 2){
            printf("\nInserisci nome del file: ");
            scanf("%19s", s);
            outputFile(s);
        }
        else{
            printf("\nInseisci numero valido: ");
        }
        
        printf("\nInserisci 1 per scrivere su un file\n"
            "Inserisci 2 per leggere da un file\n"
            "Inserisci 3 per fine.\n");
        scanf("%u", &choice);
    }
}

void inputFile(char string[])
{
    FILE *fPtr;
    
    if((fPtr = fopen(string, "a+")) == (NULL)){
        printf("\nImpossibile aprire file.\n");
    }
    else{
        int c;
        char sentence[SIZE];
        int i = 0;
    
        printf("Inserisci una riga di testo: ");
    
        while((i < SIZE) && (c = fgetc(stdin)) != EOF){
            sentence[i++] = c;
        }
        sentence[i] = '\0';
    
        fputs(sentence, fPtr);
    }
    fclose(fPtr);
}

void outputFile(char string[])
{
    FILE *fPtr;
    
    if((fPtr = fopen(string, "r")) == (NULL)){
        printf("\nImpossibile aprire file.\n");
    }
    else{
        char s[80];

        fscanf(fPtr, "%79s", s);

        while(!feof(fPtr)){         
            printf("%s\n", s);
            fscanf(fPtr, "%79s", s);
        }
    }
    fclose(fPtr);
}
