# include <stdio.h>
# include <stdlib.h>
struct btreenode 
{
  int data;
  struct btreenode *leftchild;
  struct btreenode *rightchild;
};
struct btreenode *insert(struct btreenode *sr, int num)
{
    struct btreenode *r;
    if(sr == NULL)
    {
        r = (struct btreenode *)malloc(sizeof(struct btreenode));
        r->data = num;
        r->leftchild = NULL;
        r->rightchild = NULL;
        return r;
    }
    else if(num < sr->data)
    {
        sr-> leftchild = insert(sr->leftchild, num);
    }
    else
    {
        sr -> rightchild = insert(sr->rightchild, num);
    }
    return sr;
}
void search(struct btreenode *root, int num, struct btreenode **parent, struct btreenode **x, int *found)
{
    struct btreenode *current;
    current  = root;
    *found = 0;
    *parent = NULL;   
    while(current != NULL)
    {
        if(num == current -> data)
        {
            *found = 1;
            *x = current;
            return;
        }
        if(num > current-> data )
        {
            *parent = current;
            current = current -> rightchild;
        }
        else
        {
            *parent = current;
            current = current-> leftchild;
        }
    }
}
void delete(struct btreenode *root, int num)
{
    int found; char flag;
    struct btreenode *parent, *x, *xsucc;
    if(root == NULL)
    {
        printf("\nTree is empty");
        return;
    }
    parent = x = NULL;
    search(root, num, &parent, &x, &found);
    if(x != NULL)
    {
        printf("\nKey is found\n");
    }
    
    // ********** NODE WITH NO CHILDS ********** //
    
	if(x->leftchild==NULL && x->rightchild==NULL)
    {
    	if(parent->leftchild==x)
    	{
    		parent->leftchild==NULL;
		}
		if(parent->rightchild==x)
    	{
    		parent->rightchild==NULL;
		}
		free(x);
		return;
	}
	
	// ********** NODE WITH ONE CHILD ON LEFT ********** //
    
	if(x->leftchild!=NULL && x->rightchild==NULL)
    {
    	if(parent->leftchild==x)
    	{
    		parent->leftchild==x->leftchild;
		}
		if(parent->rightchild==x)
    	{
    		parent->rightchild==x->leftchild;
		}
		free(x);
		return;
	}
	
	// ********** NODE WITH ONE CHILD ON RIGHT ********** //
    
	if(x->leftchild==NULL && x->rightchild!=NULL)
    {
    	if(parent->leftchild==x)
    	{
    		parent->leftchild==x->rightchild;
		}
		if(parent->rightchild==x)
    	{
    		parent->rightchild==x->rightchild;
		}
		free(x);
		return;
	}
	
    // ********** NODE WITH 2 CHILDS ********** //
    
	if(x->leftchild != NULL && x->rightchild !=NULL)
    {           
        parent = x; 
        xsucc = x -> rightchild;     
        while(xsucc -> leftchild !=NULL)
        {
            parent = xsucc;  
            xsucc = xsucc -> leftchild;
            flag = 'l';
        }  
        if(flag =='l')
        {
            x->data = xsucc->data;
            parent->leftchild = xsucc->rightchild;
        }
        else
        {
            x->data = xsucc->data;
            parent->rightchild = xsucc->rightchild;
        }
    }
}
void inorder(struct btreenode *sr)
{
	if(sr!=NULL)
	{
		inorder(sr->leftchild);
		printf("%i\t",sr->data);
		inorder(sr->rightchild);
	}
}
int main()
{
    struct btreenode *bt;
    int req, num, i=1;
    bt = NULL;
    printf("Enter number of items to be inserted = ");
    scanf("%d", &req);
    while(i <= req)
    {
        printf("\nEnter Data : ");
        scanf("%d", &num);
        bt = insert(bt, num);
        i++;
    }
    printf("\n");
    delete(bt, 10);
    inorder(bt);
    return;
}
