#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Entry{
    char phoneNum [31];
    char name [31];
}contact;
typedef struct PhoneBook{
    contact *mainP;
    int numOfEl;
    int realSize;
}PhoneBook;
void dump (char fileName [], PhoneBook *book);
void print(PhoneBook* book);
void init(PhoneBook* book, int size);
void destroy(PhoneBook* book);
bool insert(char name[], char phoneNum[],PhoneBook* book);
char* get (char name[],PhoneBook* book );




int main(){
    struct PhoneBook phone;
    int size;
    char name[31];
    char number[31]; 
    char searchName[31];
    printf("Enter the size of the phonebook: ");
    scanf("%d", &size);
    init(&phone,size);
    for(int i = 0; i < size;i++){
        printf("Enter the name of the #%d contact:\n",i+1);
        scanf("%s", &name);
        printf("Enter the number of the #%d contact: \n", i+1);
        scanf("%s", &number);
        printf(insert(name,number,&phone)? "Succesfull\n" : "Not Succesfull, because list is full!\n");
    }
    printf("Enter the searching name: \n");//Searching 
    scanf("%s", &searchName);
    char * ans = get(searchName,&phone);
    printf(ans == NULL ? "The contact does not exist\n" : "The %s Phone number is %s\n",searchName,ans);// printing the phone number
    //Test the function insert, it can print success,if the scanned name was in list or if you enter a new name - it prints list is full!
    printf("You can change the number of contact, enter the name's contact: \n");
    scanf("%s", &name);
    printf("Enter the number of the contact: \n");
    scanf("%s", &number);
    printf(insert(name,number,&phone)? "Succesfull\n" : "Not Succesfull, because it is full!\n");
    print(&phone);
    dump("output.txt", &phone); //to File 
    destroy(&phone);//DESTROY
    return 0;
} 


/*init() function*/
void init(PhoneBook* book, int size){
    book->realSize = size;
    book->numOfEl = 0;
    book->mainP = (contact*)malloc(size*sizeof(contact));
}
/*destroy() function*/

void destroy(PhoneBook* book){
    free(book->mainP);
}
/*insert() function allows to add new contact*/

bool insert(char name[], char phoneNum[],PhoneBook* book){
    if(isHasName(name,book)!=-1){
            strcpy(book->mainP[isHasName(name,book)].phoneNum,phoneNum);
    }else{
        if(book->numOfEl < book->realSize){
            contact n;
            strcpy(n.name,name);
            strcpy(n.phoneNum,phoneNum);
            book->mainP[book->numOfEl]=n;
            book->numOfEl++;
            return true;
        } else{
            return false;
    }
}
}
/*get() function returns the number of phone*/

char* get(char name[], PhoneBook* book) {
    for(int i = 0; i < book-> numOfEl;i++){
        if(strcmp(book->mainP[i].name,name) == 0){
            return book->mainP[i].phoneNum;
        }
    }return NULL;
}
/*This function checks wheither the Phone Book has already the input name*/

int isHasName(char name[], PhoneBook* book){
    for(int i = 0; i < book-> numOfEl;i++){
        if(strcmp(book->mainP[i].name,name) == 0){
            return i;
        }
    }return -1;
}
/*print() function*/

void print(PhoneBook *book){
    printf("///////////OUTPUT///////////\n");
    for(int i = 0; i < book-> numOfEl;i++){
        printf("%d :::::: %s :::::: %s\n" ,i + 1,book->mainP[i].name,book->mainP[i].phoneNum);
    }
}
/*dump() function for printing the output to the file*/

void dump (char fileName[], PhoneBook* book){
    FILE *file;
    file = fopen(fileName, "w");
    for(int i = 0; i < book-> numOfEl;i++){
        fprintf(file,"%d :::: %s :::: %s\n" ,i + 1,book->mainP[i].name,book->mainP[i].phoneNum);
    }
    fclose(file);
}





