#include <stdio.h>
#include <stdlib.h>

struct listNode{
    char data;
    struct listNode *nextPtr;
};

typedef struct listNode LISTNODE;
typedef LISTNODE *LISTNODEPTR;

void insert(LISTNODEPTR *, char);
char delete(LISTNODEPTR *, char);
int isEmpty(LISTNODEPTR);
void printList(LISTNODEPTR);
void instructions(void);

main(){
    LISTNODEPTR starPtr = NULL;
    int choice;
    char item;

    //Exibe o menu
    instructions();
    printf("?");
    scanf("%d", &choice);

    while(choice != 3){
        switch(choice){
        case 1:
            printf("Digite um caractere");
            scanf("\n%c", &item);
            insert(&starPtr, item);
            printList(starPtr);
            break;

        case 2:
            if(!isEmpty(starPtr)){
                printf("Digite o caractere a ser removido: ");
                scanf("\n%c", &item);

                if(delete(&starPtr, item)){
                    printf("%c removido \n", item);
                    printList(starPtr);
                }else{
                    printf("Nao encontrado\n", item);
                }
            }else{
                printf("A lista esta vazia\n");
            }
            break;

        default:
            printf("Escolha invalida\n");
            instructions();
            break;
        }
        printf("?");
        scanf("%d", &choice);
    }

    printf("Fim do programa");


    return 0;

}

//Imprime as instrucoes
void instructions(void){
    printf("Digite sua escolha: \n"
           "1 para inserir um elemento na lista\n"
           "2 para remover um elemento da lista\n"
           "3 para finalizar\n");
}

//Inserir valor na lista de forma ordenada
void insert(LISTNODEPTR *sPtr, char value){
    LISTNODEPTR newPtr, previousPtr, currentPtr;

    newPtr = malloc(sizeof(LISTNODE));

    if(newPtr != NULL){
        newPtr->data = value;
        newPtr->nextPtr = NULL;

        previousPtr = NULL;
        currentPtr = *sPtr;

        while(currentPtr != NULL && value > currentPtr->data){
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        if(previousPtr == NULL){
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        }else{
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        }
    }else{
        printf("%c nao inserido. Nao existe memoria disponivel\n", value);
    }
}

//Remove um elemento da lista
char delete(LISTNODEPTR *sPtr, char value){
    LISTNODEPTR previousPtr, currentPtr, tempPtr;

    if(value == (*sPtr)->data){
        tempPtr = *sPtr;
        *sPtr = (*sPtr)->nextPtr;   //Retira do no
        free(tempPtr);  //Remove o temporario
        return value;
    }else{
        previousPtr = *sPtr;
        currentPtr = (*sPtr)->nextPtr;

        while(currentPtr != NULL && currentPtr->data != value){
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        if(currentPtr != NULL){
            tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            free(tempPtr);
            return value;
        }
    }
    return '\0';
}

//Checa se a lista esta vazia
int isEmpty(LISTNODEPTR sPtr){
    return sPtr == NULL;
}

//Imprime a lista
void printList(LISTNODEPTR currentPtr){
    if(currentPtr == NULL){
        printf("A lista esta vazia\n");
    }else{
        printf("A lista e: \n");
        while(currentPtr != NULL){
            printf("%c --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }
        printf("NULL\n");
    }
}
