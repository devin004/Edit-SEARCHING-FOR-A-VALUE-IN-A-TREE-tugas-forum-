#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    char name[51];
    int value,height;
    struct node* left;
    struct node* right;
};

struct node* root = NULL;

struct node *newData(char name[], int value){
	struct node *temp = (struct node*)malloc(sizeof(struct node));
    strcpy(temp->name, name);
	temp->value = value;
	temp->height = 1;
	temp->left = temp->right = NULL;
	return temp;
}

int getHeight(struct node *root){
	if(!root)
    return 0;
	return root->height;
}

int max(int a, int b){
	return (a < b) ? b : a;
}

int getBalanceFactor(struct node *root){
	if(!root) return 0;
	return getHeight(root->left) - getHeight(root->right);
}

struct node *rightRotate(struct node *y){
	struct node *x = y->left;
	struct node *bwh = x->right;
	
	x->right = y;
	y->left = bwh;
	
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	return x;
}

struct node *leftRotate(struct node *x){
	struct node *y = x->right;
	struct node *bwh = x->left;
	
	y->left = x;
	x->right = bwh;
	
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
	return y;
}

struct node *rebalance(struct node *root){
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	int currBalance = getBalanceFactor(root);
	
	if(currBalance > 1 && getBalanceFactor(root->left) >= 0){
        return rightRotate(root);
    }
	if(currBalance > 1 && getBalanceFactor(root->left) < 0 ){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	
	if(currBalance < -1 && getBalanceFactor(root->right) <= 0){
        return leftRotate(root);
    }
    if(currBalance < -1 && getBalanceFactor(root->right) > 0 ){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}	
	return root;	
}

struct node *succar(struct node *root){
	while(root && root->left) root = root->left;
	return root;
}

struct node * minValueNode(struct node* node) 
{ 
    struct node* current = node; 
    while (current->left != NULL) 
        current = current->left; 
  
    return current; 
} 

struct node* deleteNode(struct node* root, int key) 
{ 
    if (root == NULL){ 
        return root; 
    }
    if ( key < root->value ){ 
        root->left = deleteNode(root->left, key); 
    }
    else if( key > root->value ){ 
        root->right = deleteNode(root->right, key); 
    }
    else{ 
        if( (root->left == NULL) || (root->right == NULL) ) { 
            struct node *temp = root->left ? root->left : root->right; 
            if (temp == NULL) { 
                temp = root; 
                root = NULL; 
            } 
            else{
                *root = *temp;
            }
            free(temp); 
        } 
        else{
            struct node* temp = minValueNode(root->right);
            root->value = temp->value; 
            root->right = deleteNode(root->right, temp->value); 
        } 
    } 
  
    if (root == NULL){
        return root; 
    }
    root->height = 1 + max(getHeight(root->left),getHeight(root->right)); 
    int balance = getBalanceFactor(root); 
    if (balance > 1 && getBalanceFactor(root->left) >= 0){ 
        return rightRotate(root); 
    }    
    if (balance > 1 && getBalanceFactor(root->left) < 0){ 
        root->left =  leftRotate(root->left); 
        return rightRotate(root); 
    } 
  
    if (balance < -1 && getBalanceFactor(root->right) <= 0){
        return leftRotate(root); 
    }
    if (balance < -1 && getBalanceFactor(root->right) > 0){ 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 
        return root; 
} 

struct node* insert(struct node *root, char name[], int value){
    if(!root){
        return newData(name, value);
    }
    else if(root->value > value){
        root->left = insert(root->left, name, value);
    }
    else if(root->value < value){
        root->right = insert(root->right, name, value);
    }
    else return root;
	
	return rebalance(root);
}

void inorder(struct node *root){    
	if(root){
		inorder(root->left);
        printf("Name\t: %s\n", root->name);
        printf("Value\t: %d\n", root->value);
        printf("Height\t: %d\n\n", root->height);
		inorder(root->right);
	}
}

bool validasiNumber(char str[]){
    int point1 = 0, point2 = 0;
    int len = strlen(str);
    for(int i = 0; i < len; i++){
        if((str[i]>='a'&&str[i]<='z')||(str[i]>'A'&&str[i]<='Z')){
            point1 = 1;
        }
        else if(str[i]>='0'&&str[i]<='9'){
            point2 = 1;
        }
        if(point1 == 1 && point2 == 1){
            break;
        }
    }
    if(point1 == 1 && point2 == 1){
        return true;
    }
    return false;
}

struct node* insertElement(){
    char name[100];
    int val;
    
    do{
        printf("Input Name [Must contains alphabet and numeric] : ");
        scanf("%[^\n]", &name);
        getchar();

    }while(!validasiNumber(name));

    do{
        printf("Input Value [Must between 0 and 50000]: ");
        scanf("%d", &val);
    }while(val<0 || val>50000);
    root = insert(root, name, val);
    inorder(root);

    return root;
}

void searchAVL(struct node *root, char name[],char newName[]){    
	if(root){
		searchAVL(root->left, name, newName);
        if(strcmp(root->name, name)==0){
            strcpy(root->name, newName);
            return;
        }
		searchAVL(root->right, name, newName);
        if(strcmp(root->name, name)==0){
            strcpy(root->name, newName);
            return;
        }
	}
}

struct node* updateEle(){
    char str[51];
    char name[51];

    if(root==NULL){
        getchar();
        system("cls");
        return root;
    }
    inorder(root);
    printf("Name to Update : ");
    scanf("%[^\n]", &str);
    getchar();
   
    do{
        printf("Input Name [Must contains alphabet and numeric] : ");
        scanf("%[^\n]", &name);
        getchar();

    }while(!validasiNumber(name));

    searchAVL(root, str, name);
    getchar();
    getchar();
    system("cls");
            
    return root;
}
 
int main(){
    int input = 0;
    do{
        printf("Stuff Store\n");
        printf("1. Insert\n2. Delete by Value\n3. Update Name\n4. View\n5. Exit\n>> ");
        scanf("%d", &input);
        getchar();
        switch (input){
        case 1:
            root = insertElement();
            getchar();
            getchar();
            system("cls");
            break;
        case 2:
            inorder(root);
            int del;
            printf("Input Value : ");
            scanf("%d", &del);
            root = deleteNode(root, del);
            getchar();
            getchar();
            system("cls");
            break;
        case 3:
            root = updateEle();
            break;
        case 4:
            inorder(root);
            getchar();
            system("cls");
            break;
        case 5:
            break;
        }
    } while(input != 5);
       
    return 0;
}
