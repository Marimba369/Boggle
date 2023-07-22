#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"boggle.h"
#include<stdbool.h>

#define N 8
#define SIZE 25

//------------------------------------------ PID Information ---------------------------------------------
typedef enum type { TRUE, FALSE, ERROR_FILE, NO_MEMORY, TABLE_FULL, IS_EQUAL, FOUND, NOT_FOUND } PID;

//------------------------------------- Global Variables --------------------------------------------------
static int count_word = 0, count_prefix = 0, count_boggle = 0;
static int ix, jy, k = 0, pos_;
static bool visit[4][4];
static char word[28] = "";
static int vis[4][4];

//-----------------------------HASHTABLE WORDS--------------------------
struct hash
{   
    char palavra[SIZE_WORD];
    PALAVRA *prox;
};

//-------------------------------LIST RESULTS-----------------------------
struct list
{
    char word[SIZE];
    int position[SIZE];
    int position_eleme[SIZE]; // valid position nubers on vis
};

struct chained_list
{
    char found_word[SIZE];
    int character_position[SIZE];

    POINTER *next_character;
};
//--------------------------------------------/-----------------------------------------


result pos; //auxiliar 

/*--------------------------------------------------------------------------------------
Função: Creates the result's List
Devolve: NULL Pointer
/*--------------------------------------------------------------------------------------*/
void *create_chained_list ()
{
    return NULL;
}

void store_elements (list_type **found_words)
{
    list_type *aux = (list_type * )malloc (sizeof(list_type));
    strcpy(aux->found_word, word);

    for (int i = 0; pos.position[i] != -1; i++)
    {
        aux ->character_position[i] = pos.position_eleme[i]; 
    }

    aux ->next_character = *found_words;
    *found_words = aux;
}

/*--------------------------------------------------------------------------------------
Função: Free all struct´s
Devolve: all struct´ś clear
/*--------------------------------------------------------------------------------------*/
void free_structures(Hash_PREFIX Prefix, HashTable table, list_type *chained)
{
    for (list_type *aux_previous = chained, *aux_next = chained->next_character; aux_next != NULL; aux_previous = aux_next, aux_next = aux_next->next_character) 
    {
        free(aux_previous);
    }

    for (int i = 0; i < SIZE_PREFIX; i++)
    {
        if(Prefix[i] != NULL)
        {
            for (PALAVRA *aux_previous = Prefix[i], *aux_next = aux_previous->prox; aux_next != NULL; aux_previous = aux_next, aux_next = aux_next->prox) 
            {
                free(aux_previous);
            }

         }
    }

    for (int i = 0; i < SIZE_TABLE; i++)
    {
        if(table[i] != NULL)
        {
            for (PALAVRA *aux_previous = table[i], *aux_next = aux_previous->prox; aux_next != NULL; aux_previous = aux_next, aux_next = aux_next->prox) 
            {
                free(aux_previous);
            }

         }
    }
    
    
}

/*--------------------------------------------------------------------------------------
Função: change position of the structure
Devolve: switched position struct
/*--------------------------------------------------------------------------------------*/
void troca(int i, int j)
{
    int aux_pos = pos.position[i],  aux_elem = pos.position_eleme[i];

    pos.position[i] = pos.position[j];
    pos.position_eleme[i] = pos.position_eleme[j];

    pos.position[j] = aux_pos;
    pos.position_eleme[j] = aux_elem;
}

/*--------------------------------------------------------------------------------------
Função: Orders de colection
Devolve: colection odenars
/*--------------------------------------------------------------------------------------*/
void ordena()
{
    int i = 1, j = 0;
    
    while( pos.position[j] != -1 &&  pos.position[i] != -1 )
    {
        if( pos.position[i] < pos.position[j] )
        {
            troca(j, i);
        }

        i++;
        
        if( pos.position[i] == -1 )
        {
            j++;
            i = j + 1;
        }
    }
}

/*--------------------------------------------------------------------------------------
Função: copy position to the structure
Devolve: structure filled
/*--------------------------------------------------------------------------------------*/
void copy_position(char matrix[4][4])
{
    int i = 0;
    strcpy(pos.word, word);

    for( int x = 0; x < 4; x++ )
    {
        for( int y = 0; y < 4; y++ )
        {
           if( vis[x][y] != 0 )
           {
                pos.position_eleme[i] = x * 10 + y;
                pos.position[i] = vis[x][y];
                i++;
           }
        }
    }
    pos.position[i] = -1;//delimiter
    
    ordena();
}

/*--------------------------------------------------------------------------------------
Funçã: Print the boggle
Devolve: Element of the screen
/*--------------------------------------------------------------------------------------*/
void print_boggle (char matrix_boggle[][4]){

    for (int i = 0; i < SIZE_BOGG; ++i){
        for (int j = 0; j < SIZE_BOGG; ++j)
            printf("%c ", matrix_boggle[i][j]);
        printf("\n");
    }
        
}

/*--------------------------------------------------------------------------------------
Função: Find Words on the Hash Table and Hash Prefix
Devolve: Words 
/*--------------------------------------------------------------------------------------*/
void findWords(char matrix_boggle[][4], Hash_PREFIX TAB_PREFIX, HashTable TAB_WORD, list_type **found_words)
{
    if( strlen(word) > 1 && search(TAB_PREFIX[hash(word, SIZE_PREFIX)], word) == NOT_FOUND )
        return;
    if( ix < 4 && ix >= 0 && jy < 4 && jy >= 0 &&  visit[ix][jy] != true )
    {
               
            visit[ix][jy] = true;
            word[k] = matrix_boggle[ix][jy];
            word[k+1] = '\0';
            k++;

            pos_++;
            vis[ix][jy] = pos_;
            

            if( search(TAB_WORD[hash(word, SIZE_TABLE)], word) == FOUND )
            {
                count_boggle = count_boggle + 1;
                //printf("%s: \n", word);
                copy_position(matrix_boggle);
                store_elements(found_words);
            }
            
            ix--;
            
            findWords(matrix_boggle, TAB_PREFIX, TAB_WORD, found_words);
            ix = ix + 2;
            
            findWords(matrix_boggle, TAB_PREFIX, TAB_WORD, found_words);
            ix--;
            jy--;
            
            findWords(matrix_boggle, TAB_PREFIX, TAB_WORD, found_words);
            jy = jy + 2;
            
            findWords(matrix_boggle, TAB_PREFIX, TAB_WORD, found_words);

            jy--;

            visit[ix][jy] = true;
            vis[ix][jy] = pos_;

            --ix;
            --jy;
            
            findWords(matrix_boggle, TAB_PREFIX, TAB_WORD, found_words);
            ix = ix + 2;
            
            findWords(matrix_boggle, TAB_PREFIX, TAB_WORD, found_words);
            jy = jy + 2;
            
            findWords(matrix_boggle, TAB_PREFIX, TAB_WORD, found_words);
            ix = ix - 2;
            
            findWords(matrix_boggle, TAB_PREFIX, TAB_WORD, found_words);
            ix++;
            jy--;   
            
            
            vis[ix][jy] = 0;
            pos_--;
            k--;
    
            visit[ix][jy] = false;
            word[k] = '\0';
    }
}

/*--------------------------------------------------------------------------------------
Função: Read Boggle
Retorna: Flag Errors
/*--------------------------------------------------------------------------------------*/
PID read_boggle(char *address, char matriz_boggle[][4])
{
    int i = 0;

    FILE *file = fopen(address, "r");
    if( file == NULL )
    {
        return ERROR_FILE;
    }
   
    while( fscanf(file, "%c %c %c %c\n", &matriz_boggle[i][0], &matriz_boggle[i][1], &matriz_boggle[i][2], &matriz_boggle[i][3]) != EOF ) i++;

    fclose(file);
}

/*--------------------------------------------------------------------------------------
Função: create prefix
Devolve: prefix
/*--------------------------------------------------------------------------------------*/
void swap(char *palavra, int pos, char *prefix)
{
    int i;
    for(i = 0; i <= pos; i++) prefix[i] = palavra[i];
    prefix[i] = '\0';
}

/*--------------------------------------------------------------------------------------
Função: Insert element in the table
Retorna: Falg Errors
/*--------------------------------------------------------------------------------------*/
PID insert_element(HashTable TAB, char *palavra, int size)
{
    int h = hash( palavra, size );

    PALAVRA *TPaux = (PALAVRA *)malloc( sizeof(PALAVRA) );

    if( TPaux == NULL )
        return NO_MEMORY;

    strcpy(TPaux->palavra, palavra);

    if( TAB[h] == NULL )
    {        
        TAB[h] = TPaux;
    }
    else
    {
        TPaux->prox = TAB[h]->prox;
        TAB[h]->prox = TPaux;
    }

    return TRUE;
}

/*--------------------------------------------------------------------------------------
Função: init of the struture Hash
Devolve: Hash initializaled
/*--------------------------------------------------------------------------------------*/
void init(HashTable TAB, Hash_PREFIX TAB_PREFIX, int size1, int size2)
{
    int j;
    for(j = 0; j < size1; j++)
        TAB[j] = TAB_PREFIX[j] = NULL;
    for(int i = j; i < size2; i++)
        TAB_PREFIX[i] = NULL;
}

/*--------------------------------------------------------------------------------------
Funçã: Calculates key hash
Retorna: key hash
/*--------------------------------------------------------------------------------------*/
int hash(char *string, int size)
{
    int total = 1;

    for(int i = 0; string[i] != '\0'; i++)
    {
        total +=  ( string[i] << 1 ) * string[i] / ( i + 1 );
    }
    return total % size;
}

/*--------------------------------------------------------------------------------------
Função: Read cornob
Retorna: Flag errors
/*--------------------------------------------------------------------------------------*/
PID read_corncob(HashTable TAB, char *sourc, Hash_PREFIX TAB_PREFIX)
{
    FILE *file = fopen(sourc, "r");
    PID flag;

    int i;
    
    if( file == NULL )
        return ERROR_FILE;

    char palavra[SIZE_WORD];
    char prefix[SIZE_WORD - 1];
    
    while( fscanf(file, "%s \n", palavra) != EOF )
    {
        flag = insert_element(TAB, palavra, SIZE_TABLE);  //input word
        count_word += (flag == TRUE) ? 1 : 0;

        i = 1;
        while( palavra[i + 1] != '\0' ) //input prefix
        {
            swap(palavra, i, prefix); //create prefix

            flag = search(TAB_PREFIX[hash(prefix, SIZE_PREFIX)], prefix);
            count_prefix += (flag == NOT_FOUND ) ? 1 : 0;
            
            if( flag == NOT_FOUND )
                insert_element(TAB_PREFIX, prefix, SIZE_PREFIX);

            i++;
        }
    }

    return TRUE;
}

/*--------------------------------------------------------------------------------------
Funçã: Search the element in the Hash
Retorna: Flag information
/*--------------------------------------------------------------------------------------*/
PID search(PALAVRA *TPALAVRA, char *palavra)
{
    if( TPALAVRA == NULL )
        return NOT_FOUND;
    return ( strcmp(TPALAVRA->palavra, palavra) == 0 ) ? FOUND : search(TPALAVRA->prox, palavra);
}

/*--------------------------------------------------------------------------------------
Função: Print information
Devolve: information in the screen
/*--------------------------------------------------------------------------------------*/
void warning ( PID flag)
{
    switch (flag)

    {
        case TRUE: printf("True");break;
        case FALSE: printf("False");break;
        case ERROR_FILE: printf("File Error...");break;
        case NO_MEMORY: printf("No memory");break;
        case TABLE_FULL: printf("Table is full");break;
        case IS_EQUAL: printf("Equal");break;
        case FOUND: printf("Found");break;
        case NOT_FOUND: printf("Not found");break;
    }
}

/*--------------------------------------------------------------------------------------
                                Fuction Main
/*--------------------------------------------------------------------------------------*/
int main()
{
    HashTable HTAB;
    Hash_PREFIX HTAB_PREF;
    list_type *found_words;
    char *sourc_boggle = "boggle0.txt";
    char matriz_boggle[4][4];
    char *string = "corncob_caps_2023.txt";

    found_words = create_chained_list();
    
    if( read_boggle(sourc_boggle, matriz_boggle) == ERROR_FILE)
    {
        warning(ERROR_FILE);
        exit(ERROR_FILE);
    }

    print_boggle(matriz_boggle);
    printf("\n");
    init(HTAB, HTAB_PREF, SIZE_TABLE, SIZE_PREFIX);

    printf("Lista de palavras encontradas no boggle:\n");
    printf("\n");
    
    if( read_corncob(HTAB, string, HTAB_PREF) != TRUE )
    {
        warning(read_corncob(HTAB, string, HTAB_PREF));
        exit(read_corncob(HTAB, string, HTAB_PREF));
    }
    
    
    memset(visit, 0, sizeof(visit[0][0]) * 4 * 4);
    memset(vis, 0, sizeof(vis[0][0]) * 4 * 4);

    for(ix = 0; ix < 4; ix++)
    {
        for(jy = 0; jy < 4; jy++)
        {
            pos_ = 1;
            findWords(matriz_boggle, HTAB_PREF, HTAB, &found_words);
        }
    }

    for (list_type *aux = found_words; aux != NULL; aux = aux->next_character)
    {
        printf("%s: ", aux->found_word);
        for (int j = 0; aux->found_word[j] != '\0'; j++)
            printf("%c -> [%d : %d] ", aux->found_word[j], aux->character_position[j]/10, aux->character_position[j]%10);
        printf("\n\n");    
    }

    printf("Quantidade de palavras encontradas: %d\n", count_boggle);
    printf("Quantidade de palavras existentes na Tabela Hash: %d\n", count_word);
    printf("Quantidade de prefixos encontrados: %d\n", count_prefix);

    free_structures(HTAB_PREF, HTAB, found_words);
    
    return 0;
}
