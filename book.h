#include <stdio.h>
#include <stdlib.h>
#define MAXNAME 30
#define MAXPHONE 15
#define MAXEMAIL 30
#define MAXWORK 20
#define MAXFILE 15

struct addressBook
{
    char name[MAXNAME];
    char phone[MAXPHONE];
    char workunit[MAXWORK];
    char email[MAXEMAIL];
};

struct linkedList
{
    struct addressBook  * cur;
    struct linkedList * next;  
};

void display(struct linkedList *list); 

size_t size(struct linkedList *list);

void readFile(char name[MAXFILE], struct linkedList *list);

void addRecord(struct linkedList *list, struct addressBook *elt);

void deleteRecord(struct linkedList *list, int pos);

void modifyRecord(struct linkedList *list, int pos);

int searchRecord(struct linkedList* list, char name[MAXNAME]);

void saveRecord( struct linkedList *list, char name[MAXFILE]);