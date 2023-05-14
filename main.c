#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Name Erdenechuluun Khuderchuluun
   Neptun code: GTBHX0*/
/*
    My homework is to code text into Morse, decode Morse into text (binary tree
    must be used), give statistics of Latin and Morse characters (dashes, dots). The
    coding/decoding should be controlled by command line switch.
    And have infinitely long history of the results
*/
//Creating binary search tree
typedef struct MorseTree{
    char character;
    struct MorseTree *left;
    struct MorseTree *right;
} MorseTree;
// Morse code dictionary
// that contains character and Morse code
typedef struct{
    char character;
    char *mcode;
} MorseDict;
// Creating history of result
//Function to make new nodes for storing characters of Morse tree
MorseTree *newNode(char item)
{
    MorseTree *tmp =  (MorseTree *)malloc(sizeof(MorseTree));
    tmp->character = item;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}
//initiating binary tree
MorseTree *MorseTree_build(void){
    MorseTree *head = NULL;
    head = newNode(' ');
    head->left = newNode('e');
    head->left->left = newNode('i');
    head->left->right = newNode('a');
    head->left->left->left = newNode('s');
    head->left->left->right = newNode('u');
    head->left->left->left->left = newNode('h');
    head->left->left->left->right = newNode('v');
    head->left->left->right->left = newNode('f');
    head->left->right->left = newNode('r');
    head->left->right->left->left = newNode('l');
    head->left->right->right = newNode('w');
    head->left->right->right->left = newNode('p');
    head->left->right->right->right = newNode('j');
    //right nodes
    head->right = newNode('t');
    head->right->left = newNode('n');
    head->right->left->left = newNode('d');
    head->right->left->right = newNode('k');
    head->right->left->left->left = newNode('b');
    head->right->left->left->right = newNode('x');
    head->right->left->right->left = newNode('c');
    head->right->left->right->right = newNode('y');
    head->right->right = newNode('m');
    head->right->right->left = newNode('g');
    head->right->right->right = newNode('o');
    head->right->right->left->left = newNode('z');
    head->right->right->left->right = newNode('q');
    return head;
}
// adding items to Morse dictionary
MorseDict addItem(char chr, char *str)
{
    MorseDict newItem;
    newItem.character = chr;
    newItem.mcode = str;
    return newItem;
}
// in Morse into text part user may enter Morse code with space
// in order to not confuse some characters like.
// for example: ".." means letter 'i' or double 'e'
// So user have to use space to convert

char charFinder(char *s, MorseTree *head)
{
    int size = strlen(s);
    MorseTree *ptr = head;
     //dot is left, dash is right
    for (int i = 0; i<size; i++)
    {
        if(s[i] == '.')
        {
            ptr = ptr->left;
        }
        if(s[i] == '-')
        {
            ptr = ptr->right;
        }
    if(ptr == NULL )
    {
        printf("Wrong Morse code!\n");
        return;
    }
}
    return ptr->character;

}
// creating txt file to store history
void history_init()
{
    FILE * fp ;
    fp = fopen ("history.txt", "w") ; /* file open  */
    fprintf (fp,"History begins:") ; /* writing */
    fclose(fp) ; /* closing */
}
// add string to history
// opening file
// printing string to the file
void add_history_string(char *y)
{
  FILE *afp;
  afp = fopen("history.txt", "a");
  fputs(y, afp);
  fputs(" ", afp);
  fclose(afp);
}
// add characters to history
// opening file
// printing character to the file
void add_history_char(char y)
{
  FILE *afp;
  afp = fopen("history.txt", "a");
  fputc(y, afp);
  fclose(afp);
}
void add_history_mcode(char *y1)
{
  FILE *afp;
  afp = fopen("history.txt", "a");
  fputs(" ",afp);
  fputs(y1, afp);
  fclose(afp);
}
void history_space()
{
  FILE *afp;
  afp = fopen("history.txt", "a");
  fputs("\n", afp);
  fclose(afp);
}
void print_history()
{
    FILE *rfp;
    char c;
    rfp = fopen("history.txt", "r");
    while(fscanf(rfp,"%c",&c) == 1){
        printf("%c",c);}
    fclose(rfp);
}
void del(MorseTree *root)
{
    if(root == NULL) /* empty tree : nothing to delete */
    {return ;}
    del(root->left); /* post - order traversal */
    del(root ->right);
    free (root);
}
int main()
{
    //Initiating binary search tree
    MorseTree *header;
    header = MorseTree_build();
    //Morse dictionary
    MorseDict characters[26];
    characters[0] = addItem('a',".-");
    characters[1] = addItem('b',"-...");
    characters[2] = addItem('c',"-.-.");
    characters[3] = addItem('d',"-..");
    characters[4] = addItem('e',".");
    characters[5] = addItem('f',"..-.");
    characters[6] = addItem('g',"--.");
    characters[7] = addItem('h',"....");
    characters[8] = addItem('i',"..");
    characters[9] = addItem('j',".---");
    characters[10] = addItem('k',"-.-");
    characters[11] = addItem('l',".-..");
    characters[12] = addItem('m',"--");
    characters[13] = addItem('n',"-.");
    characters[14] = addItem('o',"---");
    characters[15] = addItem('p',".--.");
    characters[16] = addItem('q',"--.-");
    characters[17] = addItem('r',".-.");
    characters[18] = addItem('s',"...");
    characters[19] = addItem('t',"-");
    characters[20] = addItem('u',"..-");
    characters[21] = addItem('v',"...-");
    characters[22] = addItem('w',".--");
    characters[23] = addItem('x',"-..-");
    characters[24] = addItem('y',"-.--");
    characters[25] = addItem('z',"--..");
    history_init();
    char *s = (char *) malloc(100);
    int menuselection;
    do {
        printf("0. Print the statistic\n" "1. Convert text into Morse\n" "2. Morse code into text\n" "3. History of results\n" "4. Exit\n" ": ");
        scanf("%d", &menuselection);
        switch (menuselection) {
            case 0:
                    printf("Statistic of Latin and Morse characters\n");
                     for (int i = 0; i<26; i++)
                    {
                        printf("%c <-> %s\n",characters[i].character,characters[i].mcode);
                    }
                    break;
            case 1:
                    printf("Give a text to convert\n");
                    scanf(" %[^\t\n]s",s);
                    int len = strlen(s);
                    char *hc = (char *) malloc(1);
                    hc[0] = '\0';
                    // Checking if the capital characters
                    add_history_string(s);
                    for (int i = 0; i < len; i++)
                    {
                        if (s[i]>='A' && s[i]<='Z')
                        {
                            s[i] = s[i] + 'a' - 'A';
                        }
                    }
                    printf("Result: ");
                    //searching morse code from the dictionary
                    //make comparison
                    for (int i = 0; i < len; i++)
                    {
                        for (int j = 0; j < 26; j++)
                        {
                            if(s[i] == characters[j].character)
                            {
                                printf("%s ", characters[j].mcode);
                                add_history_mcode(characters[j].mcode);
                            }
                        }
                    }
                    history_space();
                    printf("%s",hc);
                    break;
            case 2:;
                char s1[100];
                //get strings from user
                printf("Give a Morse code to convert\n");
                scanf(" %[^\t\n]s ",s1);
                char *token;
                int s1len = strlen(s1);
                char *newS1 = (char *) malloc(s1len* sizeof(char));
                for (int i = 0; i <s1len; i++)
                {
                    newS1[i] = s1[i];
                }
                newS1[s1len] = '\0';
                // strtok function separates string by a certain character
                // therefore, i had to make new string to store the string from user
                token = strtok(s1, " ");
                int hi = 0;
                printf("Result: ");
                char *hstr = (char*) malloc((sizeof(token)+1) * sizeof(char));
                while(token != NULL)
                    {
                        printf("%c",charFinder(token, header));
                        add_history_char(charFinder(token, header));
                        token = strtok(NULL, " ");
                    }

                // Making new string for storing characters to history
                hstr[hi] = '\0';
                add_history_mcode(newS1);
                history_space();
                printf("\n");
                break;
            case 3:
                    print_history();
                    break;
            case 4: break;
            default: break;
        }
        printf("\n");          /* cosmetic line break */
    } while (menuselection != 4);
    //freeing strings and binary
    del(header);

    return 0;
}
