#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define L 21

typedef struct product{
char *productname;
char *id;
int price;
struct product *next;
}product_t;


typedef struct producer{
char *name;
char *id;
struct producer *next;
struct product *pro;
}producer_t;

producer_t *readFile1(FILE *);
producer_t *readFile2(FILE *,producer_t *);
producer_t *findproducerbyId (producer_t *,char *);
void output(producer_t *);
void freeMemory(producer_t *);


int main(int argc,char *argv[]){

producer_t *head1;
product_t *head2;

FILE *fp1,*fp2;



	if (argc != 3){
		printf("ERROR !\n number of parameters!\n");
		return 0;
	}

	fp1=fopen("produce.txt","r");
	if(fp1 == NULL){
		printf("File Produce Can't open\n");
		return 0;
	}
	fp2=fopen("product.txt","r");
	if(fp2 == NULL){
			printf("File Product Can't open\n");
			return 0;
		}
	head1=readFile1(fp1);
	head1=readFile2(fp2,head1);
	output(head1);

//free
	fclose(fp1);
	fclose(fp2);
	freeMemory(head1);




return 0;
}

producer_t *readFile1(FILE *fp){

	producer_t *tmp,*head=NULL,*tmp2=NULL;
	char name[L];
	char id[L];
	while (fscanf(fp,"%s %s",name,id)!=EOF){
		//malloc struct
		tmp=(producer_t *)malloc(sizeof(producer_t));
		if(tmp == NULL){
			printf("Memory allocation Error in producers\n");
			return 0;
		}
		tmp->name=strdup(name);
		tmp->id=strdup(id);
		tmp->pro = NULL;
		tmp->next=NULL;
		if(head==NULL){
			head=tmp;
		}else{
		tmp2=head;
		// tmp2 mizarim ta tahe list
		while (tmp2->next != NULL){
			tmp2=tmp2->next;

		}
		//tail insertion
		tmp2->next=tmp;

	}
	}

	return head;
}
producer_t *readFile2(FILE *fp,producer_t *head1){
	char name[L];
	int price;
	char buffId[L];

	product_t *tmp;


	producer_t *producer=NULL;

	while (fscanf(fp,"%s %s %d",buffId,name,&price)!=EOF){

		producer=findproducerbyId (head1,buffId);
		if(producer!=NULL){
			//create node product first allocate them

			tmp=(product_t *)malloc(sizeof(product_t));
				if(tmp==NULL){
					printf("Allocation Error in products\n");
					return 0;
				}
				tmp->id=strdup(buffId);
				tmp->productname=strdup(name);
				tmp->price=price;
				tmp->next=NULL;
				if(producer->pro == NULL){
					producer->pro=tmp;
				}else{
					//head insertion
					tmp->next=producer->pro;
					producer->pro=tmp;
				}
		}

	}

return head1;
}

void output(producer_t *head){
	producer_t *tmp=head;

	char found[L];
	do{

	printf("enter the name of the product: \n");
	scanf("%s",found);
	while (tmp->next != NULL){
		if(strcpy(tmp->name,found)==0){

			while(tmp->pro->next != NULL){
			printf(" %s ",tmp->pro->productname);
			printf(" %d ",tmp->pro->price);

			}

		}
		tmp=tmp->next;
	}
	}while(strcmp(found,"stop")!=0);

return ;

}
void freeMemory(producer_t *head1){
	producer_t *produce=head1;

	while (produce->next != NULL){

		free(produce->id);
		free(produce->name);
		free(produce->pro);


	}
	free(produce);

}
producer_t *findproducerbyId (producer_t *head,char *id){
	producer_t *tmp=NULL;
	producer_t *tmp2=head;

	//int found=0;

	while(tmp2 !=NULL && tmp==NULL){ //(found==1) but Don't use!
		if(strcmp(id,tmp2->id)==0){
			tmp=tmp2;


		}else{
			tmp2=tmp2->next;
		}


	}
return tmp;
}

