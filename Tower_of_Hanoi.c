/********** Tower Of Hanoi ***************************************/
/**** Author  : Yash Kumar Sharma ********************************/
/**** E-mail  : sharma.yash914@gmail.com**************************/
/**** This program is not using stack or recursion data structure /
/**** Data Structure : Doubly Linked Lists ***********************/


#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#define MAX 20			//Maximum Height of the Tower of Hanoi

//Structure for a node
struct node
{
       int num;
       char str[MAX];
       struct node *next;
       struct node *pre;
};

char delete_str[10];

// All functions
void insert_middle(struct node **,int,char a[],int);
void operation(struct node **,int);
char *getstr(struct node **,int);
char *left_str(char *);
char *right_str(char *);

void delete_node(struct node **);
void traverse(struct node **);
void swap(int *,int *,int h,int *,int *);
void display(int a[],int b[],int c[],int);

//main
int main()
{
    int choice,item,h,i,pos,l,m=0,n=0,j;
    char s[]="ABC";
    int A[MAX],B[MAX],C[MAX],*first,*second,*top1,*top2;
    
    printf("Enter the height of tower : ");
    scanf("%d",&h);
    l=h;
    printf("\n");
    for(i=0;i<h;i++)				//Initialize the tower
    {
                    A[i]=h-i;
                    B[i]=0;
                    C[i]=0;
    }
    struct node *p;
    p=(struct node *)malloc(sizeof(struct node));
    p=NULL;
    insert_middle(&p,h,s,1);
    operation(&p,h);
    printf("\n\n");
    system("clear");
    display(A,B,C,h);
    getchar();
    
    while(p!=NULL)
    {
    	getchar();
    	system("clear");
    	delete_node(&p);
    	for(i=0;i<2;i++)
    	{
    		switch(delete_str[i])
    		{
                         case 'A':				//Column A
                              if(i==0)
                              {
                                      top1=&l;
                                      first=&A[0];
                              }
                              else
                              {
                                  top2=&l;
                                  second=&A[0];
                              }
                              break;
                         case 'B':				//Column B
                              if(i==0)
                              {
                                      top1=&m;
                                      first=&B[0];
                              }
                              else
                              {
                                  top2=&m;
                                  second=&B[0];
                              }
                              break;
                         case 'C':				//Column C
                              if(i==0)
                              {
                                      top1=&n;
                                      first=&C[0];
                              }
                              else
                              {
                                  top2=&n;
                                  second=&C[0];
                              }
                              break;
    		}
    	}                      
    	swap(first,second,h,top1,top2);				//swap element between two column
    	display(A,B,C,h);
    }
    printf("      ===DONE===\n");
    return 0;
}

//Function to display the tower of hanoi

void display(int A[],int B[],int C[],int h)
{
     int i;
     for(i=h-1;i>=0;i--)
     {
                        printf("\t");
                        if(A[i]!=0)
                        printf("%d ",A[i]);
                        else
                        printf("  ");
                        if(B[i]!=0)
                        printf("%d ",B[i]);
                        else
                        printf("  ");
                        if(C[i]!=0)
                        printf("%d",C[i]);
                        else
                        printf("  ");
                        printf("\n");
     }
     printf("\t-----\n");
     printf("\tA B C\n\n");
     printf("\n      Press Enter\n");                 
}

// Operations on each transformation

void operation(struct node **start,int h)
{
     int i,k=1,j;
     char st[10],str[10],pre_str[10];
     for(i=1;i<h;i++)
     {
                     for(j=1;j<=pow(2,i);j++)
                     {
                                             if(j%2!=0)
                                             {
                                                       strcpy(st,getstr(start,k));
                                                       strcpy(pre_str,st);
                                             }
                                             strcpy(st,pre_str);
                                             if(j%2!=0)
                                             strcpy(str,left_str(st));
                                             else
                                             strcpy(str,right_str(st));
                    
                                             insert_middle(start,h-i,str,k);
                                             k=k+2;
                     }
                     k=1;
     }
}

// Function to get the element to transform

char *getstr(struct node **start,int k)
{
     int i;
     struct node *p;
     p=*start;
     for(i=1;i<k;i++)
     p=p->next;
     
     return p->str;
}

// Function to tell about the left element

char *left_str(char *s)
{
     char *str,temp;
     str=s;
     temp=str[2];
     str[2]=str[1];
     str[1]=temp;
     
     return str;
}

//Function to tell about the right element

char *right_str(char *s)
{
     char *str,temp;
     str=s;
     temp=str[2];
     str[2]=str[0];
     str[0]=temp;
     
     return str;
}

//Function to insert a node into middle

void insert_middle(struct node **start,int item,char s[],int pos)
{
     int i;
     struct node *p;
     p=(struct node *)malloc(sizeof(struct node));
     strcpy(p->str,s);
     p->num=item;
     if(*start==NULL)
     {
                     p->next=NULL;
                     p->pre=NULL;
                     *start=p;
     }
     else
     {
         struct node *q,*r;
         q=*start;
         for(i=1;i<pos;i++)
         {
                           r=q;
                           q=q->next;
         }
         if(q==*start)
         {
                      p->next=*start;
                      q->pre=p;
                      p->pre=NULL;
                      *start=p;
         }
         else if(q==NULL)
         {
                      r->next=p;
                      p->pre=r;
                      p->next=NULL;
         }
         else
         {
             p->next=q;
             p->pre=r;
             q->pre=p;
             r->next=p;
         }
     }
}

//Function to delete the node

void delete_node(struct node **start)
{
     struct node *p;
     p=*start;
     
     if(p->next!=NULL)
     {                 
                      p->next->pre=*start;
                      *start=p->next;
     }
     else
     {
         *start=NULL;
     }
     strcpy(delete_str,p->str);
     free(p);
     
}

//Function to swap

void swap(int *a,int *b,int h,int *top1,int *top2)
{
     int i,temp;
     
     temp=a[*top1-1];
     a[*top1-1]=b[*top2];
     b[*top2]=temp;
     
     *top1=*top1-1;
     *top2=*top2+1;
}

//Function to traverse the list, if we want
/*
void traverse(struct node **start)
{
     struct node *p;
     p=*start;
     do
     {
              printf("%d %s   ",p->num,p->str);
              p=p->next;
     }while(p!=NULL);
}*/
