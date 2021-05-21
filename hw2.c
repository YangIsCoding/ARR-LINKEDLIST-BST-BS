#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include "headerfile.h"
struct LLnode{
	int data;
	struct LLnode *next;
};

struct BSTnode{
	int data;
	struct BSTnode *lnode,*rnode;
};

struct BSTnode* BSTinsert(struct BSTnode* root,int data){
	if(root == NULL){
		struct BSTnode* p = (struct BSTnode*)malloc(sizeof(struct BSTnode));
		p->data = data;
		p->lnode=NULL;
		p->rnode=NULL;
		return p;
	}
	
	if(root->data > data ){
		root->lnode = BSTinsert(root->lnode,data);
	}
	else if(root->data<data){
		root->rnode = BSTinsert(root->rnode,data);
	}
	return root;
}
int BSTtrave(struct BSTnode* head,int Bnum){
	if(head==NULL){
		return 0;
	}
	struct BSTnode *p = head;
	for(int i=0;i<log2(rand()%Bnum);i++){
		if(p->lnode==NULL||p->rnode==NULL){
			return p->data;
		}
		if(rand()%2==0){
			p= p->lnode;
		}
		else {
			p = p->rnode;
		}
	}
	return p->data;
}

void BSTsearch(struct BSTnode* head,int search){
	/*if(head!=NULL){
		BSTsearch(head->lnode,search);
		if(head->data == search){
			printf("dasd\n");
			return;
		}
		BSTsearch(head->rnode,search);
		
	}*/
	if(head==NULL){
		return ;
	}
	else if(head->data == search){
		return;
	}
	else if(head->data>=search){
		return BSTsearch(head->lnode,search);
	}
	else return BSTsearch(head->rnode,search);
}

struct LLnode* find(struct LLnode* L,int num){
    if(L==NULL){
        return NULL;
    }
    struct LLnode *ptr = L;
    while(ptr){
        if(ptr->data==num){
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}
struct LLnode* LLinsert(struct LLnode* L,int num){
	struct LLnode* f;
	if((f=find(L,num))){
		return NULL;
	}
	struct LLnode* head=(struct LLnode*)malloc(sizeof(struct LLnode));
	head->next = L;
	head->data = num;
	return head;
}

int LLtrave(struct LLnode* head,int Bnum){
	struct LLnode* p = head;
	for(int i=0;i<rand()%Bnum;i++){
		p = p->next;
	}
	return p->data;
}
void LLsearch(struct LLnode* head,int search,int Bnum){
	struct LLnode* ptr = head;
	while(ptr){
		if(ptr->data == search){
			break;
		}
		ptr = ptr->next;
	}
}
int getnum(char *string){
	int res=1;
	for(int i=0;i<string[2]-'0';i++){
		res = res*10;
	}
	return res;
}

int compare(const void *a,const void *b){
	int c = *(int *)a;
	int d = *(int *)b;
	if(c<d)return -1;
	else if(c==d)return 0;
	else return 1;
}
void BinarySearch(int *arr,int search,int Bnum){
	int low = 0,high = Bnum-1;
	while(low<=high){
		int mid = (low+high)/2;
		if(arr[mid]==search){
			break;
		}
		else if(arr[mid]>search){
			high = mid-1;
		}
		else if(arr[mid]<search){
			low = mid+1;
		}
		else return;
	}
	return;
}
int main(int argc,char **argv){
	int Bnum;
	int Qnum;
	int BST=0,BS=0,ARR=0,LL=0;
	struct timeval start;
        struct  timeval end;
        unsigned  long diff;
	int search;
        srand(time(0));


	for(int i=1;i<argc;i++){
		if(strcmp(argv[i],"-d")==0){
			Bnum = getnum(argv[i+1]);	
			printf("get building num:%d\n",Bnum);
		}
		else if(strcmp(argv[i],"-q")==0){
			Qnum = getnum(argv[i+1]);
			printf("get query num:%d\n",Qnum);
		}
		else if(strcmp(argv[i],"-bst")==0){
			BST=1;
			printf("bst on!\n");
		}
		else if(strcmp(argv[i],"-bs")==0){
			BS=1;
			printf("bs on!\n");
		}
		else if(strcmp(argv[i],"-arr")==0){
			ARR=1;	
			printf("arr on!\n");
                }
		else if(strcmp(argv[i],"-ll")==0){
			LL=1;
			printf("ll on!\n");
                }
		else {
			continue;
		}
	}
	if(ARR==1){
		gettimeofday(&start,NULL);
		int arr[Bnum];
		for(int i=0;i<Bnum;i++){
			arr[i] = rand();
		}
		gettimeofday(&end,NULL);
		for(int i=0;i<Bnum;i++){
			for(int j=0;j<i;j++){
				while(arr[i]==arr[j]){
					j=0;
					arr[i]=rand();
				}
			}
		}
		diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
		printf("Using time of Building array %ld ms\n",diff);

		gettimeofday(&start,NULL);
		for(int i=0;i<Qnum;i++){
			search = arr[rand()%Bnum];
			for(int j=0;j<Bnum;j++){
				if(search==arr[j]){
					break;
				}
			}	
		}
		gettimeofday(&end,NULL);
		diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
		printf("Using time of query array %ld ms\n",diff);
	}
	if(BS==1){
		gettimeofday(&start,NULL);
		int arr[Bnum];
                for(int i=0;i<Bnum;i++){
                        arr[i] = rand();
                }
		qsort((void *)arr,Bnum,sizeof(int),compare);
                gettimeofday(&end,NULL);
		for(int i=0;i<Bnum;i++){
                        for(int j=0;j<i;j++){
                                while(arr[i]==arr[j]){
                                        j=0;
                                        arr[i]=rand();
                                }
                        }
                }
		qsort((void *)arr,Bnum,sizeof(int),compare);
                diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
                printf("Using time of Building sorted array %ld ms\n",diff);

		gettimeofday(&start,NULL);
		for(int i=0;i<Qnum;i++){
			search  = arr[rand()%Bnum];
			BinarySearch(arr,search,Bnum);
		}		
		gettimeofday(&end,NULL);
                diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
                printf("Using time of binary search array %ld ms\n",diff);
	}
	if(LL==1){
		gettimeofday(&start,NULL);
		struct LLnode* head = NULL;
		for(int i=0;i<Bnum;i++){
			head = LLinsert(head,rand());
		}
		gettimeofday(&end,NULL);
		diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
                printf("Using time of Building Linkedlist %ld ms\n",diff);

		gettimeofday(&start,NULL);
		for(int i=0;i<Qnum;i++){
			search = LLtrave(head,Bnum);
			LLsearch(head,search,Bnum);
		}
		gettimeofday(&end,NULL);
                diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
                printf("Using time of searching Linkedklist %ld ms\n",diff);
	}
	if(BST==1){
		gettimeofday(&start,NULL);
		struct BSTnode* head = NULL;
		for(int i=0;i<Bnum;i++){
			head = BSTinsert(head,rand());
		}
		gettimeofday(&end,NULL);
                diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
                printf("Using time of Building BST %ld ms\n",diff);

		gettimeofday(&start,NULL);
		for(int i=0;i<Qnum;i++){
			search = BSTtrave(head,Bnum);
			BSTsearch(head,search);
		}
		gettimeofday(&end,NULL);
                diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
                printf("Using time of searching BST %ld ms\n",diff);
	}

}	
