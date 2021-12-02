#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    char guessWords[][16] = {
        "green",
        "yellow",
        "purple",
        "windows",
        "linux",
        "apple"
    };

    //index pour mot aléatoire
    int randomIndex = rand() % 6;

    int numLives = 5;
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
            printf("Mauvaise lettre désolé.");
            if (numLives == 0)
            {
                break;
            }
            
        }
        else
        {
            printf("Lettre trouvé! :)");
        }
        
        
         
         
    }

    if (quit == 1)
    {
        printf("\nVous abandonnez rapidemment !\n");
    }
    else if (numLives == 0)
    {
        printf("\nDésolé vous avez perdu le mot était: %s\n", guessWords[randomIndex]);
    }
    else
    {
        printf("\nVous avez gagné !\n");
    }
    
    
    
    

    
    return 0;
}
