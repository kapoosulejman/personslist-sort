#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define max_firstname 50
#define max_lastname 50
#define max_jmbg 13

typedef struct {
    char firstname[max_firstname];
    char lastname[max_lastname];
    char jmbg[14];
} Person;

int testJMBG(char *jmbg) {
    if(strlen(jmbg) != max_jmbg) return 0;
    for(int i = 0; i< max_jmbg; i++) {
        if(!isdigit(jmbg[i])) return 0;
    }
    return 1;
}

void inputPerson(Person *p) {
    printf("Enter the first name: ");
    scanf(" %49s", p->firstname);
    printf("Enter the last name: ");
    scanf(" %49s", p->lastname); 
    do {
        printf("Input JMBG: ");
        scanf(" %13s", p->jmbg);
    } while(!testJMBG(p->jmbg));
}

int compareNames(const void *a, const void *b) {
    return strcmp(((Person *)a)->firstname , ((Person *)b)->firstname);
}
int compareLastnames(const void *a, const void *b) {
    return strcmp(((Person *)a)->lastname , ((Person *)b)->lastname);
}
int compareDate(const void *a, const void *b) {
    return strncmp(((Person *)a)->jmbg , ((Person *)b)->jmbg, 5);
}

int main() {
    int personsNum,option;
    printf("Enter number of persons: ");
    scanf("%d", &personsNum);

    Person *persons = (Person *)malloc(personsNum * sizeof(Person));
    if(!persons) {
        printf("Allocation error.");
        return 1;
    }

    for(int i = 0; i<personsNum; i++) {
        printf("Person %d:\n",i+1);
        inputPerson(&persons[i]);
    }

    printf("Choose way to sort: \n");
    printf("1 - By first name\n");
    printf("2 - By last name\n");
    printf("3 - By date of birth\nOption:");
    scanf("%d" , &option);

    switch(option) {
        case 1:
            qsort(persons,personsNum,sizeof(Person),compareNames);        
        break;
        case 2:
            qsort(persons,personsNum,sizeof(Person),compareLastnames);        
        break;
        case 3:
            qsort(persons,personsNum,sizeof(Person),compareDate);        
        break;
        default: 
            printf("Unavaliable option.\n");
            free(persons);
            return 1;
    }

    printf("\nSorted list:\n");
    printf("%-15s %-15s %-13s\n", "First Name" , "Last Name" , "JMBG");
    printf("--------------------------------------------------\n");
    for(int i =0; i<personsNum; i++) {
        printf("%-15s %-15s %-13s\n", persons[i].firstname,persons[i].lastname,persons[i].jmbg);
    }

    free(persons);
    return 0;
}