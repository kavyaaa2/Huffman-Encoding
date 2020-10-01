#include<iostream>
#include<cmath>
using namespace std;
int n;
struct node
{
    char a;
    int freq;
    struct node *left;
    struct node *right;

};

int parent(int i)
{
    return ((i-1)/2);
}
struct node *buildNode(int num=0, char a=NULL)
{
    //struct node p;
    struct node *temp=(struct node *)malloc(sizeof(struct node));
    temp->a=a;
    temp->freq=num;
    temp->left=NULL;
    temp->right=NULL;
    return temp;

}
void heapify(struct node *root[], int i)
{
    int smallest=i;
    int l = 2*i +1;
    int r = 2*i +2;
    if(l<n && root[l]->freq<root[smallest]->freq)
        smallest=l;
    if(r<n && root[r]->freq<root[smallest]->freq)
        smallest=r;
    if(smallest!=i)
    {
        int c=root[i]->freq;
        char p=root[i]->a;
        struct node *t1=root[i];
        root[i]=root[smallest];
        root[smallest]=t1;
        heapify(root,smallest);
        
    }
     
}
void buildHeap(struct node *root[])
{
    //double j=n;
    int x=n/2 - 1;
    for(int i=x;i>=0;i--)
        heapify(root,i);
}
void heapInsert(struct node *root[],  struct node *p)
{
    n=n+1;
    int i=n-1;
    root[i]=buildNode();
    while(i>0 && root[parent(i)]->freq>(p->freq))
    {
        //cout<<"***"<<endl;
        root[i]->a=root[parent(i)]->a;
        root[i]->freq=root[parent(i)]->freq;
        root[i]->left=root[parent(i)]->left;
        root[i]->right=root[parent(i)]->right;
        i=parent(i);
    }
    if(p->freq == 55)
        cout<<endl<<"Value of i = "<<i<<endl;
    root[i]->freq=p->freq;
    root[i]->a=p->a;
    root[i]->left=p->left;
    root[i]->right=p->right;
}
struct node *extractMin(struct node *root[])
{
    int min=root[0]->freq;
    char c=root[0]->a;
    struct node *temp=(struct node *)malloc(sizeof(struct node));
    temp->freq=min;
    temp->a=c;
    temp->left=root[0]->left;
    temp->right=root[0]->right;
    /*root[0]->freq=root[n-1]->freq;
    root[0]->a=root[n-1]->a;
    root[0]->left=root[n-1]->left;
    root[0]->right=root[n-1]->right;*/
    root[0]=root[n-1];
    n--;
    heapify(root,0);
    return temp;
}
void Huffman(struct node *root[])
{
    int n1=n-1;
    for(int i=0;i<n1;i++){
    struct node *z=buildNode();
    z->left=extractMin(root);
    z->right=extractMin(root);
    z->freq=z->left->freq+z->right->freq;
    
    heapInsert(root,z);
    for(int i=0;i<n;i++)
    {
        cout<<root[i]->freq<<"  ";
    }
    cout<<endl;}
}
void print_inorder(struct node *root)
{
    if (root)
    {
        print_inorder(root->left);
        cout<<root->freq<<" ";
        print_inorder(root->right);
    }
}
void printArr(int arr[], int n) 
{ 
    int i; 
    for (i = 0; i < n; ++i) 
        cout<< arr[i]; 
  
    cout<<"\n"; 
} 
void printCodes(struct node *root, int arr[], int top)  
{ 
    // Assign 0 to left edge and recur 
    if (root->left) { 
  
        arr[top] = 0; 
        printCodes(root->left, arr, top + 1); 
    } 
    if (root->right) { 
  
        arr[top] = 1; 
        printCodes(root->right, arr, top + 1); 
    } 

    if (root->left==NULL && root->right == NULL) { 
  
        cout<< root->a <<": "; 
        printArr(arr, top); 
    } 
} 
int leveloftree(struct node *root)
{
	int max;
	//If root is NULL return 0
	if (root==NULL)
		return 0;
	//Recursive code to calculate level of the tree
	else
	{
		int ltree = leveloftree(root->left);
		int rtree = leveloftree(root->right);
		if (ltree > rtree)
		{
			max = ltree + 1;
			return max;
		}
		else
		{
			max = rtree + 1;
			return max;
		}
	}
}

void currentlevel(struct node *root, int level)
{	//If root is not NULL
	if (root!= NULL)
	{	//If level is 1 print the data
		if (level == 1)
		{
			cout<< root->freq;
		}
		//If level greater than 1, recursive code to pass level-1 to print the level required
		else if (level > 1)
		{ 
			currentlevel(root->left, level-1); 
			currentlevel(root->right, level-1);
		}			
	}
}

void traverse_level(struct node* root)
{	//Variable to store level of tree
	int level = leveloftree(root);
	//Loop to print each level of tree using currentlevel function
        for(int i=1;i<=level;i++)
        {
		currentlevel(root,i);
        cout<<endl;
        }
}
int main()
{
    
    int f;
    cin>>n;
    struct node *root[10000];
    char c;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter character :";
        cin>>c;
        cout<<"Enter frequency :";  
        cin>>f;
        root[i]=buildNode(f,c);
    }
    for(int i=0;i<n;i++)
    {
        cout<<"Char = "<<root[i]->a<<" Freq = "<<root[i]->freq<<endl;
    }
    buildHeap(root);
    cout<<"MinHeap = "<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"Char = "<<root[i]->a<<" Freq = "<<root[i]->freq<<endl;
    }
    
    Huffman(root);
    int arr[100];
    print_inorder(root[0]);
    cout<<endl;
    printCodes(root[0],arr,0);
    cout<<endl;
    traverse_level(root[0]);

}
