#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct node{
int start_addr,end_addr;
char id;
struct node* next;};

struct memory{
struct node *next;
}free_list[1000],process_list;

int u,l;

void initialize()
{
	 
	process_list.next=NULL;
	
	 
	int i;
	struct node *next;
	 
	for(i=l;i<u;i++){
		free_list[i].next=NULL;
	}
	 
	next=(struct node*) malloc(1*(sizeof (struct node)));
	next->start_addr=0;
	next->end_addr=(1<<u)-1;
	free_list[u].next= next;
	 
}
void allocator(char pid,int psize)
{ 	
    int i = 0,j,k;
    while(1)
    {
      j = (1<<i);
      if(j>=psize) 
      break;
      i++;
    }
    
    k = (i<l) ? l : i;
    i=k;
    while(i <= u)
    {
    if(free_list[i].next == NULL)
    {
      i = i + 1;
    }
    else
    {
    
     if(i==k) 
     {
      struct node* temp=free_list[i].next;
      free_list[i].next=free_list[i].next->next;
      temp->id=pid;
      temp->next=process_list.next;
      process_list.next=temp;
      return;
     }
     else
     {
       struct node* top=free_list[i].next;
       struct node* p=(struct node*) malloc(sizeof(struct node));
       p->start_addr=( (top->end_addr+top->start_addr)/2)+1;
       p->end_addr=top->end_addr;
       top->end_addr=(top->end_addr+top->start_addr)/2;
       free_list[i].next=free_list[i].next->next;
       //free(top);
       p->next=free_list[i-1].next;
       free_list[i-1].next=top;
       free_list[i-1].next->next=p;
       i--;
      }
     }
     
   }
        
   printf("we cant allocate %c\n",pid); 

}


void deallocator(char c){

	struct node *process_node,*prev=NULL;
	process_node=process_list.next;
	while(process_node->id!=c){
		prev=process_node;
		process_node=process_node->next;
	}

	if(prev==NULL){
		process_list.next=process_node->next;}
	else{
		prev->next=process_node->next;
	}


	int size=process_node->end_addr-process_node->start_addr+1,i=0;

	while(size>1){
		size=size>>1;
		i++;
	}


	while(1){
		int start_addr,req_start_addr;
		start_addr=process_node->start_addr;
		req_start_addr= ( (start_addr>>i)%2==0) ? start_addr+(1<<i) : start_addr-(1<<i);

		struct node *temp=free_list[i].next;
		prev=NULL;
		while(temp!=NULL && temp->start_addr!=req_start_addr){
			prev=temp;
			temp=temp->next;
		}

		if(temp==NULL) {

			process_node->next=free_list[i].next;
			free_list[i].next=process_node;
			return;
		}

		if(prev==NULL) {

			free_list[i].next=temp->next;
		}
		else{
			prev->next=temp->next;
		}
		i=i+1;
		free(temp);
		process_node->start_addr=(start_addr <req_start_addr) ? start_addr : req_start_addr;
		process_node->end_addr= process_node->start_addr+ (1<<i)-1;
	}

}


void print(int x, int y)
{

int start=0;
while(start<(1<<y))
{
    struct node* temp=process_list.next;
   while(temp!=NULL)
     {
        if(temp->start_addr ==start)
          {
            printf("process - %c:%d\n",temp->id,temp->end_addr-temp->start_addr+1);
            start=temp->end_addr+1;
          }
        temp=temp->next;
     }
   if(temp!=NULL)
    continue;

 int i=x;
   while(i<=y)
   {
      struct node* temp=free_list[i].next;
       while(temp!=NULL)
       {
        if(temp->start_addr ==start)
          {
            printf("hole:%d\n",temp->end_addr-temp->start_addr+1);
            start=temp->end_addr+1;
          }
        temp=temp->next;
      }
    i++;
   }
   

}

}

void main(){

scanf("%d%d",&l,&u);
initialize();
allocator('A',100);
//print(l,u);printf("\n\n");
allocator('B',200);
//print(l,u);printf("\n\n");
allocator('C',100);
//print(l,u);printf("\n\n");
allocator('D',200);
//print(l,u);printf("\n\n");
allocator('E',100);
//print(l,u);printf("\n\n");
allocator('F',200);
//print(l,u);printf("\n\n");
deallocator('A');
//print(l,u);printf("\n\n");

deallocator('C');
print(l,u);printf("\n\n");

}

