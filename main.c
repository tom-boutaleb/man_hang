#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXNUMWORDS 2048
#define MAXWORDLENGTH 64

void show_state(int numLives);

int main()
{
    srand(time(NULL));

    char guessWords[MAXNUMWORDS][MAXWORDLENGTH];
    int wordsReadIn = 0;

    FILE *pToFile = fopen("text.txt", "r");

    if (pToFile == NULL)
    {
        printf("L'ouverture du fichier a échoué");
        return -1;
    }
    

    char input[64];
    
    while (fgets(input, 63, pToFile))
    {
        sscanf(input, "%s", guessWords[wordsReadIn]);
        printf("Scanné: Donnée: %s guessWords[%d]:%s\n", input, wordsReadIn ,guessWords[wordsReadIn]);
        wordsReadIn++;
    }
    
    fclose(pToFile);

    printf("Totale mots lus: %d\n", wordsReadIn);

    //index pour mot aléatoire
    int randomIndex = rand() % wordsReadIn;

    int numLives = 6;
    int numCorrect = 0;
    int oldCorrect = 0;

    int lengthOfWord = strlen(guessWords[randomIndex]);
    int letterGuessed[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    int quit = 0;  

    int loopIndex = 0;

    char guess[16];
    char letterEntered;

    printf("guessWords: %s random int: %d lengthOfWord: %d\n\n",
        guessWords[randomIndex],
        randomIndex,
        lengthOfWord);

    // boucle du jeu
    while (numCorrect < lengthOfWord)
    {
        printf("Mot: ");

        for ( loopIndex = 0; loopIndex < lengthOfWord; loopIndex++)
        {
            if (letterGuessed[loopIndex] ==1)
            {
                printf("%c", guessWords[randomIndex][loopIndex]);
            }
            else
            {
                printf("-");
            } 
        }

        printf("\n");
        show_state(numLives);
        printf("Nombre de lettres trouvées: %d\n", numCorrect);
        printf("Entrez une lettre: \n");
        fgets(guess, 16, stdin);
         
        if (strncmp(guess, "quit", 4) == 0)
        {
            quit = 1;
            break;
        }

        letterEntered = guess[0];
        printf("letterEntered: %c\n", letterEntered);

        oldCorrect = numCorrect;

        for ( loopIndex = 0; loopIndex < lengthOfWord; loopIndex++)
        {
            if (letterGuessed[loopIndex] ==1)
            {
                continue;
            }
            if (letterEntered == guessWords[randomIndex][loopIndex])
            {
                letterGuessed[loopIndex] = 1;
                numCorrect++;
            }
             
        }

        if (oldCorrect == numCorrect)
        {
            numLives--;
            printf("Mauvaise lettre désolé.\n");
            if (numLives == 0)
            {
                break;
            }
            
        }
        else
        {
            printf("Lettre trouvé! :)\n");
        }
        
        
         
         
    }

    if (quit == 1)
    {
        printf("\nVous abandonnez rapidemment !\n");
    }
    else if (numLives == 0)
    {
        show_state(numLives);
        printf("\nDésolé vous avez perdu le mot était: %s\n", guessWords[randomIndex]);
    }
    else
    {
        printf("\nVous avez gagné !\n");
    }
    
    
    
    

    
    return 0;
}

void show_state(int numLives)
{
    switch (numLives)
    {
    case 0:
        printf("  +---+  \n  |   |  \n  O   |  \n /|\\  |  \n / \\  |  \n      |  \n=========\n");
        break;
    case 1:
        printf("  +---+  \n  |   |  \n  O   |  \n /|\\  |  \n /    |  \n      |  \n=========\n");
        break;
    case 2:
        printf("  +---+  \n  |   |  \n  O   |  \n /|\\  |  \n      |  \n      |  \n=========\n");
        break;
    case 3:
        printf("  +---+  \n  |   |  \n  O   |  \n /|   |  \n      |  \n      |  \n=========\n");
        break;
    case 4:
        printf("  +---+  \n  |   |  \n  O   |  \n  |   |  \n      |  \n      |  \n=========\n");
        break;
    case 5:
        printf("  +---+  \n  |   |  \n  O   |  \n      |  \n      |  \n      |  \n=========\n");
        break;
    case 6:
        printf("  +---+\n  |   |  \n      |  \n      |  \n      |  \n      |  \n=========\n");
        break;
    default:
        break;
    }
}