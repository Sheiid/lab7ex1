/*
 * main.c
 *
 *  Created on: Nov 20, 2017
 *      Author: Sheida
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define L 21

typedef struct product{
char *productname;
char *id;
int price;
struct products *next;
}product_t;


typedef struct producer{
char *name;
char *id;
struct producer *next;
struct product *pro;
}producer_t;

producer_t *readFile1(FILE *);
product_t *readFile2(FILE *,producer_t *);
void output(producer_t *,product_t *);
void freeMemory(producer_t *,product_t *);


int main(int argc,char *argv[]){

producer_t *head1;
product_t *head2;

FILE *fp1,*fp2;



	if (argc != 3){
		printf("ERROR !\n number of parameters!\n");
		return 0;
	}

	fp1=fopen("producer.txt","r");
	if(fp1 == NULL){
		printf("File Producer Can't open\n");
		return 0;
	}
	fp2=fopen("product.txt","r");
	if(fp2 == NULL){
			printf("File Product Can't open\n");
			return 0;
		}
	head1=readFile1(fp1);
	head2=readFile2(fp2,head1);
	output(head1,head2);

//free
	fclose(fp1);
	fclose(fp2);
	freeMemory(head1,head2);




return 0;
}

producer_t *readFile1(FILE *fp){

	producer_t *tmp,*head=NULL;
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
		if(head==NULL){
			tmp->next=NULL;
			head=tmp;
		}else{
		tmp->next=head;
		head=tmp;
	}
	}

	return head;
}
product_t *readFile2(FILE *fp,producer_t *head1){
	char name[L];
	int price;
	char buffId[L];

	product_t *tmp,*head=NULL;
	//producer_t *produce;

	while (fscanf(fp,"%s %s %d",buffId,name,&price)!=EOF){
		tmp=(product_t *)malloc(sizeof(product_t));
		if(tmp==NULL){
			printf("Allocation Error in products\n");
			return 0;
		}
		tmp->id=strdup(buffId);
		tmp->productname=strdup(name);
		tmp->price=price;
		if(strcmp(head1->id,tmp->id)==0){
			if(head1->pro == NULL){
			head1->pro->next=head;
			head=tmp;
			}else{
				head=head1->pro->next;
				tmp=head;
			}
		if(head==NULL){
					tmp->next=NULL;
					head=tmp;
		}else{
		tmp->next=head;
		head=tmp;
		}
	}

return head;
}

void output(producer_t *head1,product_t *head2){
	producer_t *tmp;
	tmp=head1;
	char found[L];

	while (tmp!= NULL){
		if(strcmp(tmp->id,head2->id)==0)
		{
			if(tmp->pro == NULL){
				head2->next=NULL;
				tmp->pro=head2;
				return;
			}else{
				head2->next=tmp->pro;
				tmp->pro=head2;
				return;
			}

		}
	tmp=tmp->next;
	}
	printf("insert the name: \n");
	scanf("%s",found);
	while (tmp != NULL){
		if(strcmp(tmp->name,found)==0){
			while (tmp->pro != NULL){
				printf("%s %d",tmp->pro->productname,tmp->pro->price);
				tmp->pro=tmp->pro->next;
			}
		}
		tmp=tmp->next;
	}

return ;

}
void freeMemory(producer_t *head1,product_t *head2){
	producer_t *produce;
	product_t *product;

	while (head1 != NULL){
		produce=head1;
		head1=produce->next;
		free(produce->id);
		free(produce->name);
		free(produce);
	}
	while (head2 != NULL){
			product=head2;
			head2=product->next;
			free(product->productname);
			free(product->id);
			free(product);
		}
}


