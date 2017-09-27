#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <malloc.h>

DIR *dir;
struct dirent *ent;
char *a,*b,*c,*d,*e,*f;
double score;
int id;
char *buffer[200];
DIR* dir;
struct dirent *ent;
FILE* fptr;
double av=0;
double t=0;

struct master{
	char name[10];
	int color;
		struct master *nextPtr;
	struct master *right,*from;
};
typedef struct master master;
typedef struct master* masterPtr;
typedef struct master** masterPtrPtr;
void insert2(masterPtrPtr firstPtr,char *value, char *name);

void insert(masterPtr *first,char *value){
	
	masterPtr newPtr,prev,temp;
	

//	if(*first != NULL){
		newPtr=malloc(sizeof(master));
	strcpy(newPtr->name,value);
		newPtr->nextPtr=NULL;
		newPtr->right=NULL;
	
	//	*first=newPtr;
			if (*first == NULL) 
		*first=newPtr;
	// if LL not empty
	else {
		temp=*first;
		while (temp != NULL && strcmp(temp->name,value)<0) {
			prev=temp;
			temp=temp->nextPtr;
		}

		if (temp!=NULL &&  strcmp(temp->name,value)==0) {
		//	printf("existent key"); 
			return ;
		}

		// insert node in a sorted fashion
		if (temp!=NULL )
			newPtr->nextPtr=temp;

		// if value to insert is the least in LL then have header point to node
		if (temp==*first)
			*first=newPtr;
		// otherwise insert node in correct position
		else 
			prev->nextPtr=newPtr;
	}
	
	return ;
	
		
		
	}
	void search(masterPtrPtr first){
		char *a,*b;
		masterPtr hdr=*first;
		  FILE *fp;
   	char temp[300];
char *pt;
while(hdr!=NULL){
	if((fp=fopen("input3.txt", "r"))==NULL){
	return ;
	}


	
	
	while((fgets(temp,200,fp))!=NULL){
		if(strstr(temp,hdr->name)!= NULL){
		
		
		a=strtok(temp,"\n");
		a=strtok(temp, ":");
        a=strtok(NULL,":");
        pt=strtok(a," ");
         pt = strtok (a,",");
            while (pt != NULL ) {
            	 
            	
            	//	printf("\n%s\n",pt);
            		if(strcmp(hdr->name,pt)!=0)
					insert2(first,pt,hdr->name);
			
            		pt=strtok(NULL,",");
            	
                   	 
	}
		
       
        
		
	}
	
	
		
} 
if(fp) 
fclose(fp);
hdr=hdr->nextPtr;
}
return;

	



}

	void insert2(masterPtrPtr firstPtr,char *value, char *name){
		masterPtr temp,newPtr,temp2,prev;
		temp=*firstPtr;
		while(temp!= NULL){
				if(strcmp(name,temp->name)==0){
					newPtr=malloc(sizeof(master));
					strcpy(newPtr->name,value);
					newPtr->nextPtr=NULL;
					if (temp->right == NULL) 
						temp->right=newPtr;
					// if LL not empty
					else {
						temp2=temp->right;
						while (temp2 != NULL && strcmp(temp2->name,value)<0) {
							prev=temp2;
							temp2=temp2->nextPtr;
						}

						if (temp2!=NULL &&  strcmp(temp2->name,value)==0) {
							//	printf("existent key"); 
							return ;
						}

						// insert node in a sorted fashion
						if (temp2!=NULL )
							newPtr->nextPtr=temp2;

						// if value to insert is the least in LL then have header point to node
						if (temp2==temp->right)
							temp->right=newPtr;
						// otherwise insert node in correct position
						else 
							prev->nextPtr=newPtr;
					}
	
					return ;
	
				}
					temp=temp->nextPtr;
					
		}
	}
		



void print(masterPtrPtr current)
{
masterPtr temp;

	if(*current==NULL)
	printf("empty\n");
	else{
		printf("\nlist is:\n");
		
		while(*current!=NULL){
		
			printf("\n%s-->",(*current)->name);
			temp=(*current)->right;
				while(temp!=NULL){
				
			printf("%s,",temp->name);
			temp=temp->nextPtr;
	}
	
		(*current)=(*current)->nextPtr;	
		}
	
	}
	
}
void search2(masterPtrPtr first,char *value){
	masterPtr newPtr,temp2,prev;
	masterPtr temp=*first;
	while(temp!= NULL){
				if(strcmp(value,temp->name)==0){
					newPtr=malloc(sizeof(master));
					strcpy(newPtr->name,value);
					newPtr->nextPtr=NULL;
					if (temp->right == NULL) 
						temp->right=newPtr;
				
					else {
						temp2=temp->right;
						while (temp2 != NULL && strcmp(temp2->name,value)!=0) {
							prev=temp2;
							temp2=temp2->nextPtr;
						}

						if (temp2!=NULL &&  strcmp(temp2->name,value)==0) {
							temp2->color++;
						 
							return ;
						}

					
						if (temp2!=NULL )
							newPtr->nextPtr=temp2;

						// if value to insert is the least in LL then have header point to node
						if (temp2==temp->right)
							temp->right=newPtr;
						// otherwise insert node in correct position
						else 
							prev->nextPtr=newPtr;
					}
	
					return ;
	
				}
					temp=temp->nextPtr;
					
		}
	}
		


	void bfs(masterPtrPtr first){
     	masterPtr temp=*first;
	masterPtr right=temp->right;
	masterPtr from=temp->from;
	masterPtr pn=temp->nextPtr;
	masterPtr pn2=pn->right;
	while(temp !=NULL){
		temp->color=0;
		search2(&temp, temp->name);
		
		while(right!= NULL){
				printf("\nPeriod 1-%s-%s",temp->name,pn->name);
				right->color++;
				search2(&temp, temp->name);
				if(right->color==1){
					printf("\nPeriod  2-->%s-",right->name);
				
			}
					right=right->nextPtr;
					}
						
						while(pn2!= NULL){
				pn2->color++;
				search2(&temp, temp->name);
				if(pn2->color==1){
				//	printf("%s-",pn2->name);
				
			}
				
					pn2=pn2->nextPtr;
				printf("\nPeriod  3-%s",pn2->name);
	
					}
					
		
	
	
	search2(&temp, temp->name);
	
			if(temp->color==0)
			temp=temp->nextPtr;
	
	}
	

	
}
		
	



void main(){
  masterPtr hedar=NULL;
    FILE *fp;
   	char temp[300];

	if((fp=fopen("input3.txt", "r"))==NULL){
		return ;
	}
	while((fgets(temp,300,fp))!=NULL){
		char *pt;
		
		a=strtok(temp,"\n");
		
		a=strtok(temp, ":");
	
            a=strtok(NULL,":");
           
            // printf("\n a  %s",a);
           pt=strtok(a," ");
            pt = strtok (a,",");
           
            	
            while (pt != NULL) {
            	 
            	
            		printf("%s\n",pt);
					insert ( &hedar, pt );
            	
            		
            	
            		
            		pt=strtok(NULL,",");
            	
            	 
	}

    
}

if(fp) 
fclose(fp);

search(&hedar);
bfs(&hedar);
print(&hedar);



}


