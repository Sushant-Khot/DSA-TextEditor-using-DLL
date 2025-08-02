#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int START=0;
int uc=0;

typedef struct node
{
    char data;
    struct node* prev;
    struct node* next;
}NODE;

void insertLL(NODE **tp,char ch)
{
    NODE* newN=(NODE*)malloc(sizeof(NODE));
    newN->data=ch;
    newN->next=NULL;
    (*tp)->next=newN;
    newN->prev=(*tp);
    (*tp)=newN;
}
// Function to convert an array of characters to a doubly linked list
NODE* arrayToDoublyLinkedList(char arr[], int length, NODE** hp,NODE** tp)
{
    if(length <= 0)
    {
        return NULL;
    }
    if(START==0)
    {
        (*hp)=(NODE*)malloc(sizeof(NODE));
        (*hp)->data = arr[0];
        (*hp)->prev = NULL;
        (*hp)->next = NULL;
        (*tp)=(*hp);
        NODE* current = (*hp);
        for(int i = 1; i < length; ++i)
        {
            NODE* newNode = (NODE*)malloc(sizeof(NODE));
            newNode->data = arr[i];
            newNode->prev = current;
            newNode->next = NULL;
            current->next = newNode;
            current = newNode;
            if(i==(length-1))
                *tp=current;
        }
        START=1;
    }
    else if(START==1)
    {
        if(uc==1)
        {
            char ch;
            ch='\n';
            insertLL(tp,ch);
        }
        if(uc==2)
        {
            char ch;
            ch=' ';
            insertLL(tp,ch);
        }
        for(int i=0;i<length;i++)
        {
            char ch;
            ch=arr[i];
            insertLL(tp,ch);
        }
    }    
}

// Function to print the doubly linked list
void printDoublyLinkedList(NODE** hp)
{
    NODE* current = *hp;
    while (current != NULL)
    {
        printf("%c", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to free the memory allocated for the doubly linked list
void freeDoublyLinkedList(NODE** hp)
{
    NODE* current = (*hp);
    while (current != NULL)
    {
        NODE* temp = current;
        current = current->next;
        free(temp);
    }
}

void write(char cA[])
{
    if(START!=0)
    {
        printf("\n1.to start with a newline 2.to start with a space : \n");
        scanf("%d",&uc);
    }
    printf("\nEnter Anything : \n");
    scanf(" %[^;]s", cA);
    int c;
    while ((c = getchar()) != ';' && c != EOF);
}

void print(char* cA)
{
    printf("Entered : \n");
    printf("%s",cA);
}

void deletecontent(NODE **hp,NODE **tp,int dc)
{
    
    if(dc==1)
    {
        NODE *p;
        if(*hp==*tp && *hp!=NULL)
        {
            free(*hp);
            *hp=NULL;
        }
        else
        {
            p=*tp;
            *tp=(*tp)->prev;
            p->prev->next=NULL;
            p->prev=NULL;
            free(p);
        }
    }

    if(dc==2)
    {
        NODE *p,*q,*r;
        p=*tp;
        while(p->data!=' ' && p!=*hp)
        {
            p=p->prev;
        }
        if(p==*hp)
        {
            freeDoublyLinkedList(hp);
            *hp=NULL;
        }
        else
        {
        q=p->next;
        p=p->prev;
        while(q!=NULL)
        {
            q=q->next;
            free(r);
            r=q;
        }
        p->next=NULL;
        *tp=p;
        }
    }

    if(dc==3)
    {
        NODE *p,*q,*r;
        p=*tp;
        while(p->data!='\n' && p!=*hp)
        {
            p=p->prev;
            
        }
        if(p==*hp)
        {
            freeDoublyLinkedList(hp);
            *hp=NULL;
        }
        else
        {
            q=p->next;
            p=p->prev;
            while(q!=NULL)
            {
                q=q->next;
                free(r);
                r=q;
            }
            p->next=NULL;
            *tp=p;
        }
    }
}

void delete(NODE **hp,NODE **tp)
{
    int dc;
    printf("\n1.Delete last character 2.Delete Last word 3.Delete last line :");
    scanf("%d",&dc);
    if(dc==1 || dc==2 || dc==3)
    {
        deletecontent(hp,tp,dc);

    }
}

void copyList(NODE **cbh,NODE **cbt,NODE **nhp,NODE **ntp)
{
    
    NODE *t,*p;
    (*nhp)=(NODE*)malloc(sizeof(struct node));
    (*nhp)->data=(*cbh)->data;
    (*nhp)->next=NULL;
    (*nhp)->prev=NULL;
    (*ntp)=(*nhp);
    p=(*nhp);
    t=(*cbh)->next;
    while(t!=NULL && t!=(*cbt)->next)
    {
        NODE *nodep=(NODE*)malloc(sizeof(NODE));
        nodep->data=t->data;
        nodep->next=NULL;
        nodep->prev=NULL;
        while(p->next!=NULL)
            p=p->next;
        p->next=nodep;
        nodep->prev=p;
        (*ntp)=nodep;
        nodep=NULL;
        t=t->next;
    }
}

void cutncopy(NODE **hp,NODE** tp,NODE** cbh,NODE** cbt)
{
    int st,en,choice;
    NODE *p,*q;
    p=*hp;
    q=*hp;
    printf("\nEnter the starting and ending position of selection : ");
    scanf("%d%d",&st,&en);
    printf("1.CUT 2.COPY : ");
    scanf("%d",&choice);
    st=st-1;
    en=en-1;
    if(choice==1)
    {
    while(st>0)
    {
        p=p->next;
        st=st-1;
    }
    while(en>0)
    {
        q=q->next;
        en=en-1;
    }
    
        p->prev->next=q->next;
        q->next->prev=p->prev;
        p->prev=q->next=NULL;
    

    *cbh=p;
    *cbt=q;
    }
    else if(choice==2)
    {
        while(st>0)
        {
            p=p->next;
            st=st-1;
        }
        
        while(en>0)
        {
            q=q->next;
            en=en-1;
        }
        
        NODE **pp,**qp;
        pp=&p;
        qp=&q;
        copyList(pp,qp,cbh,cbt);
    }
}

void paste(NODE **hp,NODE **tp,NODE **cbh, NODE **cbt,NODE **nhp,NODE **ntp)
{
    int pos,choice;
    NODE *p;
    if(*cbh==NULL)
    {
        printf("\nClipboard is empty!!No Copy or Cut operation done...In order to use paste.");
    }
    else
    {
        printf("\n1.Paste at Start 2.Paste at End 3.Paste at any given position : ");
        scanf("%d",&choice);
        copyList(cbh,cbt,nhp,ntp);
        switch(choice)
        {
            case 1:
                // copyList(hp,tp,cbh,cbt,nhp,ntp);
                (*hp)->prev=*ntp;
                (*ntp)->next=*hp;
                *hp=*nhp;
                break;
            case 2:
                // copyList(hp,tp,cbh,cbt,nhp,ntp);
                (*tp)->next=*nhp;
                (*nhp)->prev=*tp;
                *tp=*ntp;
                break;
            case 3:
                printf("\nEnter the paste position : ");
                scanf("%d",&pos);
                
                p=*hp;
                
                // copyList(hp,tp,cbh,cbt,nhp,ntp);
                
                while(--pos)
                {
                    p=p->next;
                }
                p->prev->next=*nhp;
                (*nhp)->prev=p->prev;
                (*ntp)->next=p;
                p->prev=*ntp;
                break;
        } 
    }
}

int main()
{
    char cA[1024];
    int choice;

    NODE *head,*tail,*cbhead,*cbtail,*nhead,*ntail;
    NODE **hp,**tp,**cbh,**cbt,**nhp,**ntp;
    
    hp=&head;
    tp=&tail;
    cbh=&cbhead;
    cbt=&cbtail;
    nhp=&nhead;
    ntp=&ntail;

    do
    {
        printf("\nEnter your choice : \n1.Write 2.Display 3.EXIT 4.DELETE 5.CUT/COPY 6.PASTE : \n");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                write(cA);
                int arrayLength=0;
                arrayLength=strlen(cA);
                // arrayLength=strlen(cA);
                arrayToDoublyLinkedList(cA, arrayLength,hp,tp);
                break;
            case 2:
                print(cA);
                printf("\nDoubly Linked List: \n");
                printDoublyLinkedList(hp);
                break;
            case 3:
                printf("\nThanks for using Text editor!!");
                exit(0);
            case 4:
                delete(hp,tp);
                break;
            case 5:
                cutncopy(hp,tp,cbh,cbt);
                break;
            case 6:
                paste(hp,tp,cbh,cbt,nhp,ntp);
                break;
            default:
                printf("\nEnter a valid choice : ");
        }
    }while (choice!=3);
    freeDoublyLinkedList(hp);
    return 0;
}
