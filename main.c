#include "./my.h"

int main(int argc, char *argv[])
{
    int tmp = 0;
    t_file toto;
    if (argc != 2)
    {
        return -1;
    }
    
    tmp = read_file(&toto, argv[1]);
    printf("%s\n", toto.file_content[0]);

    srand(time(NULL));
    

    

    //index pour mot aléatoire
    int randomIndex = rand() % tmp;

    int numLives = 6;
    int numCorrect = 0;
    int oldCorrect = 0;

    int lengthOfWord = strlen(toto.file_content[randomIndex]);
    int letterGuessed[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    int quit = 0;  

    int loopIndex = 0;

    char guess[16];
    char letterEntered;

    printf("guessWords: %s random int: %d lengthOfWord: %d\n\n",
        toto.file_content[randomIndex],
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
                printf("%c", toto.file_content[randomIndex][loopIndex]);
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
            if (letterEntered == toto.file_content[randomIndex][loopIndex])
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
        printf("\nDésolé vous avez perdu le mot était: %s\n", toto.file_content[randomIndex]);
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

int read_file(t_file *file, char *str) 
{
    struct stat st;
    char *tmp = NULL;
    int fd = 0;
    int size = 0;
    int i = 0;


	stat(str, &st);
    tmp = malloc(sizeof(char) * st.st_size);
    fd = open(str, O_RDONLY);
    if (fd < 1)
    {
        printf("L'ouverture du fichier a échoué");
        return -1;
    }
    
    read(fd, tmp, st.st_size);
    size = size_eol(tmp);
    file->file_content = malloc(sizeof(char *) * size + 1);
    for (i = 0; i <= size; i++)
    {
    file->file_content[i] = strtok(tmp, "\n");
    }
    printf("Totale mots lus: %d\n", i);
    file->file_content[i] = NULL;
    return i;
}


int size_eol(char *str)
{
    int j = 0;
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == '\n') 
            j++;
    }
    return (j);
}