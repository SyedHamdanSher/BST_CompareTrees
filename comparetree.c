/* compile and run :  gcc -o gg comparetree.c -lm
						./gg
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct treeNode {
	int value;
	struct treeNode* rlink;
	struct treeNode* llink;
};
int count1 = 0,count2 = 0,countn1=0,countn2=0;//global variable
typedef struct treeNode* Node;

//Inserting a element 
Node insert_node(int item, Node root)
{
	Node cur,temp,prev;
	temp = (Node)malloc(sizeof(struct treeNode));
	temp->value = item;
	temp->llink=temp->rlink=NULL;
	if(root == NULL)
		return temp;
	prev = NULL;
	cur = root;
	while(cur != NULL)
	{
		prev = cur;
		if(item < cur->value)
			cur = cur->llink;
		else
			cur = cur->rlink;
	} 
	if(item<prev->value)
		prev->llink=temp;
	else
		prev->rlink=temp;
	return root;
}

//Counting the Nodes in the tree
void count_nodes1(Node root)
{
	if(root == NULL)
		return;
	else
	{
		count_nodes1(root->llink);
		countn1++;
		count_nodes1(root->rlink);
	}
}
void count_nodes2(Node root)
{
	if(root == NULL)
		return;
	else
	{
		count_nodes2(root->llink);
		countn2++;
		count_nodes2(root->rlink);
	}
}

//count the leaves in a tree
void count_leaves1(Node root)
{
	if(root == NULL)
		return;
	count_leaves1(root->llink);
	if(root->llink==NULL && root->rlink==NULL)
		count1++;
	count_leaves1(root->rlink);
}
void count_leaves2(Node root)
{
	if(root == NULL)
		return;
	count_leaves2(root->llink);
	if(root->llink==NULL && root->rlink==NULL)
		count2++;
	count_leaves2(root->rlink);
}

//find height of a tree
int max(int a, int b)
{
	if(a>b)
		return a;
	else
		return b;
}

int height(Node root)
{
	if(root == NULL)
		return 0;
	else
		return(max(height(root->llink),height(root->rlink))+1);
}
//create a copy of a Binary Tree
Node copy(Node root)
{
	Node temp;
	if(root == NULL)
		return NULL;
	temp = (Node)malloc(sizeof(struct treeNode));
	temp->value = root->value;
	temp->llink = copy(root->llink);
	temp->rlink = copy(root->rlink);
	return temp;
}
//creating tree structure
Node creatTree(Node r)
{
	int item,flag=0;
	for(;;)
	{
		printf("\n please insert node, press 0 to insert and 1 to stop inserting : ");
		scanf("%d",&flag);
		if(flag!=0){
			break;
		}
		printf("\n please enter item integer value : ");
		scanf("%d",&item);
		r=insert_node(item,r);
	}
	return r;
}

int compareTrees(Node root1,Node root2)
{
	int item1,item2,flag=0;
	if(root1==NULL)
	{
		return 0;
	}
	item1=root1->value;
	item2=root2->value;
	if(item1==item2)
	{
		flag=compareTrees(root1->llink,root2->llink);
		flag=compareTrees(root1->rlink,root2->rlink);
	}
	else{
		return 999;
	}
}
void results(int c1,int c2,int flag)
{
	if(c1!=c2 || count1!=count2 || countn1!=countn2 || flag==999)
	{
		printf("\nThe given trees are not equal!\n");
	}else{
		printf("\nThe given trees are equal!\n");
	}
}

void main()
{
	int c1,c2,flag=0;
	Node root1=NULL,root2=NULL,copyN=NULL;
	clock_t start_t, end_t;
	double total_t;
	printf("\n creation of two trees and comparing whether they are same or not\n");
	printf("\n create tree 1");
	root1=creatTree(NULL);
	printf("\n create tree 2");
	root2=creatTree(NULL);
	c1=height(root1);
	c2=height(root2);
	count_leaves1(root1);
	count_leaves2(root2);
	count_nodes1(root1);
	count_nodes2(root2);
	start_t = clock();
	flag=compareTrees(root1,root2);
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	results(c1,c2,flag);
	printf("Total time taken by CPU: %f\n", total_t);
	printf("\nCreating an exact copy of first tree and then comparing the copied tree and the original tree\n");
	copyN=copy(root1);
	flag=0;count1 = 0;count2 = 0;countn1=0;countn2=0;
	c1=height(root1);
	c2=height(copyN);
	count_leaves1(root1);
	count_leaves2(copyN);
	count_nodes1(root1);
	count_nodes2(copyN);
	start_t = clock();
	flag=compareTrees(root1,copyN);
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	results(c1,c2,flag);
	printf("Total time taken by CPU: %f\n", total_t);
}