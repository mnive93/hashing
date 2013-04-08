#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<ctype.h>
#include<unistd.h>
#include<stdlib.h>
#include<malloc.h>
struct list
{
char type[10];
char data[10];
int size;
char value[10];
struct list *next;
};

typedef struct list* listptr;

struct hashtable
{
       int tablesize;
        listptr*thelist;
};
struct hashtable * initialize(struct hashtable *h)
{
       int i;
       
 
      h=(struct hashtable *)malloc(sizeof(struct hashtable));
       h->tablesize=10;
       h->thelist=( listptr* )malloc(h->tablesize*(sizeof(listptr)));
       for(i=0;i<h->tablesize;i++)
       {
//printf("i....%d\n",i);

                                  h->thelist[i]=( struct list* )malloc(sizeof( struct list));
                                  h->thelist[i]->next=NULL;
                                  }       
//display(h);
       return h;

}
void display(struct hashtable *h)
{
     struct list *l;
     int i=0;
//printf("tablesize--%d...\n",h->tablesize);
while(i<h->tablesize)     
{

                                l=h->thelist[i]->next;
//printf("%d..niveeeee",i);
//if(l==NULL)
//printf("lll\n");

                                printf("\n|%3d|",i);
                                while(l!=NULL)
                                {
                                              printf("->%s %s %d %s\t",l->type,l->data,l->size,l->value);
                                              l=l->next;
                                              }
i+=1;
                                              }
}

int hash(char key[10],int tablesize)
{
int len,i,val=0;
len=strlen(key);
//printf("%s\n",key);
for(i=0;i<=len;i++)
{
val+=key[i];
}
//printf("val %d\n",(val%tablesize));

return(val%tablesize);
}

int check_datatype(char str[100],char str2[100])
{
int i=0;
if(strstr(str2,"int")!=0 && strcmp(str,"int")!=0)
return 1;
if(strstr(str2,"float")!=0&& strcmp(str,"float")!=0)
return 2;
if(strstr(str2,"double")!=0&& strcmp(str,"double")!=0)
return 3;
if(strstr(str2,"char")!=0&& strcmp(str,"char")!=0)
return 4;

return i;

}

struct list * find(char str[100],struct hashtable *h)
{
       struct list *L,*pos;
       L=h->thelist[hash(str,h->tablesize)];
       pos=L->next;
//printf("here33 %s\n",str);
       while(pos&& (strcmp(pos->data,str)!=0))
       {
                                 pos=pos->next;
                                 }
       return pos;
}
void update(char str[100],char str2[100],struct hashtable *h)
{
struct list *pos;
pos=find(str2,h);
if(pos!=NULL)
{
strcpy(pos->value,str);
}
}

void insert(int ret,char str[100],int arr,struct hashtable *h)
{
     struct list *pos,*L,*newcell;
   //  pos=find(str,h);
    newcell=(struct list*)malloc(sizeof(struct list));
if(ret==1)
{
strcpy(newcell->type,"int");
strcpy(newcell->data,str);
newcell->size=2*arr;
strcpy(newcell->value,"0");


}
if(ret==2)
{
strcpy(newcell->type,"float");
strcpy(newcell->data,str);
newcell->size=4*arr;
strcpy(newcell->value,"0.0");

}
if(ret==3)
{
strcpy(newcell->type,"double");
strcpy(newcell->data,str);
newcell->size=8*arr;
}
if(ret==4)
{
strcpy(newcell->type,"char");
strcpy(newcell->data,str);
newcell->size=1*arr;
strcpy(newcell->value,"-");
}

L=h->thelist[hash(str,h->tablesize)];
newcell->next=L->next;
L->next=newcell;
//display(h);
}
void delete1(char str[10],struct hashtable *h)
{
     struct list *l,*cur;
     l=h->thelist[hash(str,h->tablesize)];
 //    l=l->next;
     do
     {
               cur=l;
               l=l->next;
               }while(strcmp(l->data,str)!=0);
               cur->next=cur->next->next;
}                           
                                          

void words_separate(char str[100],struct hashtable *h)
{
int k,k1;
int j=0;
int flag=0,p=0;
char temp[10],temp2[10];
int ret;
struct list *pos;
char str2[100];
int array_value=1;
for(k=0;k<=strlen(str);k++)
{
if((ispunct(str[k])||str[k]=='\0'||str[k]==' '))// this separates the line into words if "any punctuation  like ", ; + =" is encountered"
{
str2[j]='\0';
j=0;
k1=k;
if(str[k1]=='=')
{

p=0;
strcpy(temp2,str2); // if b=10 then str2 has the value of "b"
k1+=1;
if(isdigit(str[k1]))//this checks the value "after '=' and sees if it is a digit"
{
flag=1;//if its a digit na flag=1;
while(isdigit(str[k1])||str[k1]=='.')
{temp[p]=str[k1];
p+=1;
k1+=1;}
temp[p]='\0'; // temp now is equal to "10"
}
//this checks the value "after '=' and sees if it is a alphabet"
if(isalpha(str[k1])) //if b=a 
{
flag=2;//if its a alphabet na flag=2;
while(isdigit(str[k1])||isalpha(str[k1]))
{
temp[p]=str[k1];
p+=1;
k1+=1;
}
temp[p]='\0'; //temp is now 'a'
pos=find(temp,h);//the place where 'a' is stored is retrieved
strcpy(temp,pos->value);//we are now copying the value of 'a' to 'temp'
}
}
k1=k;

if(str[k1]=='[')
{
k1+=1;
array_value=atoi(&str[k1]);
}

if(str2[0]!='\0' && isalpha(str2[0]))
{

ret=check_datatype(str2,str);
pos=find(str2,h);
if(ret)
{
pos=find(str2,h);
//printf("%shereee2222\n",str2);

if( pos==NULL)
{
//printf("%shereee\n",str2);
insert(ret,str2,array_value,h);
}
}
//pos=find(str2,h);
if(flag==1&& str2[0]!='\0'&&pos==NULL)//this is used to prevent duplication thats why checking for pos==-1;
{
update(temp,temp2,h); // if b=10 means temp=10,temp2=b;
flag=0;
}
if(flag==2&& str2[0]!='\0') //if b=a since b and a are already present in the table no need to check for duplication!
{
update(temp,temp2,h); // if temp=(the value of a ) ,temp2=b;
flag=0;
}
//display(h);
}
}
else
str2[j++]=str[k];
}
}
int main(int argc,char*argv[])
{
 struct hashtable *h;
int fd,ch;
char buf;
fd=open(argv[1],O_RDONLY);
char str[100];
int i=0,n=0;
struct list *pos;
h=initialize(h);
do
{
printf("\n1.Create\n2.Insert\n3.Modify\n4.Delete\n5.Display\n6.Search\n7.Exit\n");
scanf("%d",&ch);
if(ch==1)
{
while(read(fd,&buf,1))
{
if(buf=='\n'||buf=='\0')
{
str[i]='\0';
i=0;
words_separate(str,h);
}
else
str[i++]=buf;
}
printf("The symbol table is created\n");
}
if(ch==2)
{
char str3[100];
printf("enter a statement\n");
gets(str3);
gets(str3);
words_separate(str3,h);
display(h);
printf("The value has been inserted\n");
}
if(ch==3)
{
char str3[100];
char num[10];
printf("enter the variable name \n");
scanf("%s",str3);
pos=find(str3,h);
printf("enter  the new value!\n");
scanf("%s",num);
strcpy(pos->value,num);
display(h);
printf("The value has been modified!\n");
}
if(ch==4)
{

char str3[100];
printf("enter the variable name \n");
scanf("%s",str3);
delete1(str3,h);
display(h);
printf("The value has been deleted!\n");

}
if(ch==5)
{
printf("---SYMBOL TABLE---\n");
printf("Datatype\tVariable\tSize\tValue\tAddress\n");
display(h);
}
if(ch==6)
{

char str3[100];
printf("enter the variable name \n");
scanf("%s",str3);
pos=find(str3,h);
if(pos!=NULL)
{
printf("Details:\n");
printf("DATATYPE:%s\n",pos->type);
printf("SIZE:    %d\n",pos->size);
printf("VALUE:   %s\n",pos->value);
}
else
printf("Value not found!!\n");

}
}while(ch!=7);
return 0;
}
