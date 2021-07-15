#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
int num[9];

int deepth;

int diffnum;

int value;

struct Node * pre;
struct Node * next;
struct Node * parent;
}numNode;

int origin[9];

int target[9];

int numNode_num,total_step;
numNode *open,*close;


numNode *create_numNode()
{
return (numNode *)malloc(sizeof(numNode));
}
numNode *open_getfirst(numNode *head);

void open_insert(numNode *head,numNode *item);

void close_append(numNode *head,numNode *item);

int expand(numNode *item);

int print_result(numNode *item);

numNode *copy_numNode(numNode *orgin);
char isNewNode(numNode *open,numNode *close,int num[9]);

void print_num(int num[9]);

int diff(int num[9]);

void init();

void swap(int *a,int *b);
int operate(int num[],int op);
void free_list(numNode *head);

int main ( int argc, char *argv[] )
{

open=create_numNode();
close=create_numNode();
open->pre=open->next=close->pre=close->next=NULL;

init();

numNode *p1;
p1=create_numNode();
p1->parent=NULL;
p1->deepth=0;
int i=0;
for ( i=0; i<9; i++)
{
p1->num[i]=origin[i];
}

open_insert(open,p1);

numNode_num=1;
p1=open_getfirst(open);

while (p1!=NULL)
{
close_append(close,p1);

if(expand(p1))
return EXIT_SUCCESS;

p1=open_getfirst(open);
}

printf("No solution!\n");
return EXIT_SUCCESS;

}

void init ( )
{
while(1)
{
printf("Please Enter Initial State:\nFor example:283164705 stands for\nHere 0 means blank position\n"
"2 8 3\n"
"1 6 4\n"
"7 5\n");

char temp[10];
scanf("%s",temp);
int i=0;
for ( i=0;i<9 && temp[i]-'0'>=0 && temp[i]-'0'<=8; i++)
{
origin[i]=temp[i]-'0';
}

printf("Please Enter Goal State:\nFor example:123804765 stands for\nHere 0 means blank position\n"
"1 2 3\n"
"8 4\n"
"7 6 5\n");
scanf("%s",temp);
int j=0;
for ( j=0; j<9 && temp[j]-'0'>=0 && temp[j]-'0'<=8; j++)
{
target[j]=temp[j]-'0';
}
if ( i==9&&j==9)
{
break;
}
}
}

void open_insert (numNode *head,numNode *item)
{
numNode *p,*q;
p=head->next;
q=head;
while ( p!=NULL && item->value > p->value )
{
q=p;
p=p->next;
}
q->next=item;
item->pre=q;
item->next=p;
if(p!=NULL)
{
p->pre=item;
}
}

numNode * open_getfirst (numNode *head)
{
numNode *p;

if ( head->next == NULL )
{
return NULL;
}
p=head->next;
head->next=p->next;

if ( p->next != NULL )
{
p->next->pre=head;
}
p->pre=NULL;
p->next=NULL;
return p;
}

void close_append (numNode *head,numNode *item)
{
item->next=head->next;
item->pre=head;
head->next=item;

if ( item->next!=NULL )
{
item->next->pre=item;
}
}

int expand (numNode *p1)
{
numNode * p2;
int op=1;
for ( op=1; op<=4; op++)
{
p2=copy_numNode(p1);
operate(p2->num,op);
if(isNewNode(open,close,p2->num)=='N')
{
p2->parent=p1;
p2->deepth=p1->deepth+1;
p2->diffnum=diff(p2->num);
p2->value=p2->deepth+p2->diffnum;
if(p2->diffnum==0)
{
total_step=print_result(p2);
printf("\nTotal step: %d\n",total_step);
free_list(open);
free_list(close);
return 1;
}
else
{
numNode_num++;
open_insert(open,p2);
}
}
else
free(p2);
}
return 0;
}

int operate(int m[], int op)
{
int blank;
blank=0;
while (m[blank]!=0 && blank<9 )
++blank;
if (blank==9)
return 1;

switch (op) {
case 1:
if (blank>2)
swap(m+blank,m+blank-3);
break;
case 2:
if (blank<6)
swap(m+blank,m+blank+3);
break;
case 3:
if (blank!=0 && blank!=3 && blank!=6)
swap(m+blank,m+blank-1);
break;
case 4:
if (blank!=2 && blank!=5 && blank!=8)
swap(m+blank,m+blank+1);
break;
default : return 1;
}
return 0;
}

void swap(int *a, int *b)
{
int c;
c=*a;
*a=*b;
*b=c;
}
numNode * copy_numNode (numNode *origin)
{
numNode *p;
p=create_numNode();
p->deepth=origin->deepth;
p->diffnum=origin->diffnum;
p->value=origin->value;
int i;
for ( i=0; i<9; i++)
{
(p->num)[i]=(origin->num)[i];
}

return p;
}

int diff (int num[9])
{
int i,diffnum=0;
for(i=0;i<9;i++)
if(num[i]!=target[i])
diffnum++;

return diffnum;
}
char isNewNode (numNode *open,numNode *close,int num[9])
{
numNode *p;
int i=0;

p=open->next;
while ( p!=NULL )
{
for ( i=0; i<9; i++)
{
if(p->num[i]!=num[i])
break;
}
if(i==9)
return 'O';

p=p->next;
}

p=close->next;
while ( p!=NULL )
{
for ( i=0; i<9; i++)
{
if(p->num[i]!=num[i])
break;
}
if(i==9)
return 'C';

p=p->next;
}

return 'N';
}

void free_list (numNode *head)
{
numNode *p,*q;//tasin
p=head->next;

while ( p!=NULL )
{
q=p->next;
free(p);
p=q;
}
free(head);
}

void print_num (int num[9])
{
int i;

for ( i=0; i<9; i++)
{
printf("%d\t",num[i]);
}
}

int print_result ( numNode *item)
{//tasin
numNode *p;
int step;
p=item;
if(p!=NULL)
{
step=print_result(p->parent);
printf("\nStep %d:\n",step+1);
print_num(p->num);//t
return step+1;
}
else
{
return -1;
}
}
