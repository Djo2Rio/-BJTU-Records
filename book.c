#include <stdio.h>
#include <stdlib.h>
#include "book.h"
 /*Create an address book application as follows:
1. Define a structure type. The records of the address book include name, phone number, work unit, and email data. The name and phone number cannot be empty.
2. The address book records use linked lists to store records information, the records in the linked list are sorted by name.
3. Provide a menu for the user to select the following options
    1) Read records information from the file to the linked list
    2) Add a record to the linked list in ascending order by name
    3) Delete the specific record in the linked list.
    4) Modify the specific record in the linked list, enter the information you want to modify from the keyboard.
    5) Search a record with a specific name.
    6) Save the records in the linked list to the file.
    7) Exit the program.
4. Define one or more header files (the definition of the structure type, the functions prototype declaration and the constant definition can be placed in header files), 
The address book consists of multiple files (for example, the function related to the menu can be defined in a file, the functions related to linked list can be defined in a file, the functions related to file can be defined in a file).
*/

void display(struct linkedList *list) // work mais a creuser
{
    size_t compt = 0;
    while(list!= NULL)
    {   
        printf(" (%d) My name is %s. I work at %s\n My phone number is %s and my email is %s.\n\n", compt, list->cur->name, list->cur->workunit , list->cur->phone, list->cur->email);
        list = list->next;
        compt+=1;
    }  
}

size_t size(struct linkedList *list)
{
    size_t compt = 0;
    while(list!= NULL)
    {   
       compt+=1;
    } 
    return compt;
}

void deleteRecord(struct linkedList *list, int pos) //work
{
    struct linkedList * temp = list->next;
    size_t compt = 0;
    if( pos == 0)
    {
        *(list) = *(temp);
    }
    else
    {
        while(compt < pos-1)
        {   
            temp = temp->next;
            list = list->next;
            compt+=1;
        }
        list->next = temp->next;
    }
   
    //free(temp);
}

void modifyRecord(struct linkedList *list, int pos) // must be better if i use string // need to fix
{
    int compt = 0;
    while (pos != compt)
    {
        list = list->next;
        compt++;
    }
    char change[MAXNAME];
    printf("This is the  record you want to modify :\n");
    printf(" (%d) My name is %s. I work at %s\n My phone number is %s and my email is %s.\n\n", compt, list->cur->name, list->cur->workunit , list->cur->phone, list->cur->email);
    printf("Witch attribute do you want to change ?\n (0) Name\n (1) Company\n (2) Phone Number\n (3) Mail\n");
    scanf("%d", &compt);
    int i=0;
    switch (compt)
    {
        case 0:
            printf("Please enter the new name\n");
            scanf("%s", &change);
            while(change[i] != '\n' && change[i] < 4)
            {
                printf("%c",change[i]);
                (list->cur->name[i]) = change[i];
                i++;
            }
            break;
        case 1:
            printf("Please enter the new Company name\n");
            scanf("%s", &change);
            while(change[i] != '\n')
            {
                list->cur->workunit[i] = change[i];
                i++;
            }
            break;
        case 2:
            printf("Please enter the Phone Number\n");
            scanf("%s", &change);
            while(change[i] != '\n')
            {
                list->cur->phone[i] = change[i];
                i++;
            }
            break;
        default:
            printf("Please enter the new mail address\n");
            scanf("%s", &change);
            while(change[i] != '\n')
            {
                list->cur->email[i] = change[i];
                i++;
            }
            break;
    }
}

int searchRecord(struct linkedList* list, char name[MAXNAME]) // must be better if i use string // need tofix it
{
    int pos = 0;
    while(list !=NULL)
    {
        int i =0;
        if(*(list->cur->name) == *name)
        {
            return pos;
        }
        pos++;
        list =list->next;
    }
    return -1;
}

void addRecord(struct linkedList *list, struct addressBook *elt) // work normalement
{
    struct linkedList * temp = NULL;
    int i = 0;
    if(list == NULL)
    {
        struct linkedList new = {elt, list};
        *(list) = new;
        return;
    }
    while(list != NULL)
    {
        while((list->cur->name[i]) == (elt->name[i]))
        {
            i++;
        }
        if(elt->name[i] < list->cur->name[i])
        {
            if(temp == NULL)
            {
                struct linkedList newone = {elt, list};
                list = &newone;
                return;
            }
            else
            {
                struct linkedList newtwo = {elt, list};
                temp->next = &newtwo;
                return;
            }
        }
        if(list == NULL)
        {
            struct linkedList newthree = {elt, list};
            temp->next = &newthree;
            return;
        }
        temp = list;
        list=list->next;
    }
    
}

void readFile(char name[MAXFILE], struct linkedList *list) // NOP
{
    FILE * file;
    file = fopen(name, "r");
    int line = 0;
    int tabula;
    while(!feof(file))
    {
        tabula= fgetc(file);
        if(tabula == '\n')
        {
            line++;
        }
    }
    fclose(file);
    file = fopen(name, "r");
    char namea[MAXNAME];
    char phone[MAXPHONE];
    char email[MAXEMAIL];
    char work[MAXWORK];
    while(line !=0)
    {
        fscanf(file, "%s", &namea);
        fscanf(file, "%s", &phone);
        fscanf(file, "%s", &email);
        fscanf(file, "%s", &work);
        //struct addressBook temp  = {*namea, *phone, *email, *work};
       // addRecord(list, &temp);
        line--;
    }
    
}

void saveRecord( struct linkedList *list, char name[MAXFILE]) // work
{
    FILE *fptr;
    fptr = fopen(name, "w");
    while(list!= NULL)
    {   
        fprintf(fptr, "%s %s %s %s\n", list->cur->name,list->cur->phone, list->cur->email,list->cur->workunit);
        list = list->next;
    }  
}
int main()
{
    struct addressBook ab1 = {"Charles Atan", "(555) 589 9214","Windaube", "charles.atan@gmail.com"};
    struct addressBook ab2 = {"Zidedine Zidane", "(33) 785 874","Real de Madrid", "zidedine.zidane@coupdeboule.fr"};
    struct addressBook ab3 = {"Anakin Skywalker", "(11) 1111 1111","StardKiller", "anakin.skywalker@darkside.sky"};
    struct addressBook ab4 = {"Jesus", "(777) 7777 7777","Sky", "jesus@messi.heaven"};
    struct addressBook ab5 = {"Freddy Mercury", "(485) 452 7851","Queen", "freddy.mercury@killerqueen.com"};
    struct addressBook ab6 = {"Mickael Jackson", "(542) 2566 7852","Whitespirit", "mickael.jackson@grey.com"};
    struct addressBook ab7 = {"Jyu Viole Grace", "(542) 4788 7846","FUG & Wolkaisong", "baam.25@tog.tw"};
    struct addressBook ab8 = {"Eric Clapton", "(777) 7776","Olympia", "eric.clapton@slowhand.com"};
    

    // Linked List    
    struct linkedList list6 = {&ab6,NULL};
    struct linkedList list5 = {&ab5,&list6};
    struct linkedList list4 = {&ab4,&list5};
    struct linkedList list3 = {&ab3,&list4};
    struct linkedList list2 = {&ab2,&list3};
    struct linkedList list1 = {&ab1,&list2};

    //pointer
    struct linkedList * first  =&list1;
    struct addressBook * cur = &ab1;


    int inputs;
     //int tampon;
    display(first);
    //system("cls");
    printf("Hi ! What do you want to do ? (Enter the number corresponding to what you want) \n");
    
    printf("1) Read records information from the file to the linked list\n");
    printf("2) Add a record to the linked list in ascending order by name\n");
    printf("3) Delete the specific record in the linked list.\n");
    printf("4) Modify the specific record in the linked list, enter the information you want to modify from the keyboard.\n");
    printf("5) Search a record with a specific name.\n");
    printf("6) Save the records in the linked list to the file.\n");
    printf("7) Exit the program.\n");
    scanf("%d", &inputs);
    system("cls");
    //printf(" inputs :%d", inputs);
    char mots[MAXNAME];

    switch (inputs)
    {
    case 1:
        printf("Enter a name file ?\n");
        scanf("%s", &mots);
        readFile(mots, first);
        break;
    case 2:
        addRecord(first, &ab7);
        break;
    case 3:
        printf("At witch position is the record you want to delete ?\n");
        scanf("%d", &inputs);
        deleteRecord(first, inputs);
        break;
    case 4:
        printf("At witch position is the record you want to modify?\n");
        scanf("%d", &inputs);
        modifyRecord(first, inputs);                
        break;
    case 5:
        
        printf("Enter a name ?\n");
        scanf("%s", &mots);
        int pos  = searchRecord(first, mots);
        printf("position of %s is %d\n", mots, pos);
        break;
    case 6:
        printf("Enter a name file ?\n");
        scanf("%s", &mots);
        saveRecord(first, mots);
        break;
    
    default:
        return 0;
        break;
    }
    display(first);
    return 0;
}