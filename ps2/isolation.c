#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct isolation {

  int value;
  char string[200000];
  struct isolation *left;
  struct isolation *right;
  //struct isolation *tree;
  struct isolation *root;
  //struct isolation *parent;

};



struct isolation *make_root(int value,int n1){
   struct isolation *result = calloc(n1,sizeof(struct isolation));
    
   if(result != NULL){
    result -> left = NULL;
    result -> right = NULL;
    result -> value = value;
    //result -> prent = NULL;
  }
 return result;
}


bool make_tree(struct isolation **root_p, int value,int n1){
   struct isolation *root = *root_p;
   if(root == NULL){
     (*root_p) = make_root(value,n1);
     return true;

    }

    if(value < root -> value){
       return make_tree(&(root->left),value,n1);
    }
    else{
       return make_tree(&(root->right),value,n1);
    }
}


bool check(struct isolation **treea,struct isolation **treeb){
 struct isolation *root1 = *treea;
 struct isolation *root2 = *treeb;
  if((root1 != NULL && root2 == NULL) || (root1 == NULL && root2 != NULL)){
      return false;
  }
  if (root1 -> left == NULL && root1 -> right == NULL && root2 -> left == NULL && root2 -> right == NULL){
        return true;
    }
  if (root1 -> left == NULL && root2 -> left == NULL && root1 -> right != NULL && root2 -> right != NULL){
        return check(&(root1 -> right), &(root2 -> right));
   }
  if (root1 -> left != NULL && root2 -> left != NULL && root1 -> right == NULL && root2 -> right == NULL){
        return check(&(root1 -> left), &(root2 -> left));
    }
    return (check(&(root1 -> left), &(root2 -> left)) && check(&(root1 -> right), &(root2 -> right)));
  }

int main(){

int n1, k;
scanf("%d %d ",&n1,&k);

struct isolation *list = calloc(n1+1,sizeof(struct isolation));

//for(int j = 0; j < n1; j++){
//  for(int i = 0; i < 200000; i++){
//  list[j].string[i] = '\0';
//  }
//}

for(int i = 0; i < n1; i++){
 scanf("%[^\n]",list[i].string);
  char ch = 0;
  scanf("%c",&ch);
}

int pomoc = 0;
for(int i = 0; i < n1; i++){
 list[i].root = NULL;
  for(int j = 0; j < strlen(list[i].string); j++){
    int cislo = 0;
    while(list[i].string[j] != ' ' && list[i].string[j] != '\0'){
     cislo =(list[i].string[j]-48) + 10*cislo;
     j++;
     }
 
     make_tree(&list[i].root,cislo,(n1*k));
 }

//for(int j = 0; j < i; j++){
//if(check(&list[i].root,&list[j].root) == true){
//     pomoc++;
//     break;
//   }
// }
}
 
for(int i = 0; i < n1 - 1; i++){
  for(int j = i+1; j < n1; j++){
    if(check(&list[i].root,&list[j].root) == true){
     pomoc++;
     break;
  }
  else{
   continue;
  }
 }
}
//printf("okk");
printf("%d\n",n1-pomoc);
return 0;
}
