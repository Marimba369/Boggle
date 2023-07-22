#ifndef _PROJECTO_H
#define _PROJECTO_H

#define SIZE_LIS 25
#define SIZE_TABLE 77400
#define  SIZE_WORD 25
#define SIZE_PREFIX 110000
#define SIZE_BOGG 4

struct hash;
enum type;
struct list;
struct pos;
struct chained_list;

typedef struct pos Pos;
typedef struct hash *Hash_PREFIX[SIZE_PREFIX];
typedef struct hash *HashTable[SIZE_TABLE];
typedef struct hash PALAVRA;
typedef enum type PID;
typedef struct list List; 
typedef struct chained_list POINTER;
typedef struct list result;
typedef struct chained_list list_type;


static PID insert_element(HashTable TAB, char *palavra, int size);
static PID read_corncob(HashTable TAB, char *sourc, Hash_PREFIX HTAB_PREFIX);
static void init(HashTable TAB, Hash_PREFIX TAB_PREFIX, int size1, int size2);
static int hash(char *string, int size);
static void swap(char *palavra, int pos, char *prefix);
static PID read_boggle(char *address, char matriz_boggle[][SIZE_BOGG]);
static PID search(PALAVRA *TPALAVRA, char *palavra);
void free_structures(Hash_PREFIX Prefix, HashTable table, list_type *chained);
//void free(HashTable TAB, Hash_PREFIX TAB_PREFIX, Listers *list[]);
//void position_valid(Pos position[]);


#endif 