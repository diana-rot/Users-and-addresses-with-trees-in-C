#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 10

typedef struct node{
  int parent;
  int data;
  int nr_adr;
  char **addr;
  struct node *kids; //primul copil
  struct node *siblings;//fratii
  //struct node *siblings;
}*Node;

typedef struct vnod{
  Node nod;
} Vnod;

typedef struct sort{
  int val;
  int parent;
  int nr_adr;
  char **addr;

}*Sort;

typedef struct users{
  int nr_users;
  int id_user;
  int id_nod;

}Users;

//Exercitiul 1

Sort complete_st(Sort st,int *nr,FILE *fid){
  int n,i=0,j;
  int val, parent, nr_adr;
  fscanf(fid,"%d",&n);
  st=malloc(n*sizeof(struct sort));
  i=0;
  char s[10];

  //pasul 1, am alcatuit structura de ordonare
  while(i<n){
    fscanf(fid,"%d",&val);
    st[i].val=val;
    fscanf(fid,"%d",&parent);
    st[i].parent=parent;
    fscanf(fid,"%d",&nr_adr);
    st[i].nr_adr=nr_adr;
    st[i].addr=malloc(nr_adr*sizeof(char*));

    for(j=0;j<nr_adr;j++){
      fscanf(fid,"%s",s);
      st[i].addr[j]=(char*)malloc(strlen(s)+1);
      //fscanf(fid,"%s",s);
      strcpy(st[i].addr[j],s);
    }

    i++;
  }

  *nr=n;

  return st;
}


Node create_tree(int *parent,int n,Vnod *vn, Sort st){
  int i,j;
  Node root;
  
  //am initializat fiecare nod
  for (i = 0; i < n; i++) { 
    vn[i].nod=malloc(sizeof(struct  node));
    vn[i].nod->data=st[i].val;
    vn[i].nod->parent=st[i].parent;
    vn[i].nod->kids=NULL;
    vn[i].nod->siblings=NULL;
    vn[i].nod->nr_adr=st[i].nr_adr;
    vn[i].nod->addr=malloc(st[i].nr_adr*sizeof(char*));

    for(j=0;j<st[i].nr_adr;j++){
      vn[i].nod->addr[j]=(char*)malloc(MAX_SIZE);
      strcpy(vn[i].nod->addr[j],st[i].addr[j]);
    }

  }
  //creez legaturile
  Node p;
  for (i = 0; i < n; i++){
    if(i==0){
      root=vn[0].nod;
    } 
    else{ 
        //daca parintele are deja un primul copil
        if(vn[vn[i].nod->parent].nod->kids){
          p=vn[vn[i].nod->parent].nod->kids;
          while (p->siblings){
               p=p->siblings;
            }
          p->siblings=vn[i].nod;
        }
        else{
          vn[vn[i].nod->parent].nod->kids=vn[i].nod;
        }
      }
        
    }

  return root;


}
void DFS(Node root, FILE *fod){

  Node q;
  q=root->kids;
  while(q!=NULL){
    DFS(q,fod);
    q=q->siblings;//psrcurgi copii    
  }

  fprintf(fod, "%d",root->data);
  q=root->kids;
  //daca sunt vizitati printezi informatia din parinte
  while(q!=NULL){
    fprintf(fod," %d",q->data);
    q=q->siblings;
  }

  fprintf(fod,"\n");
  
}

//Exercitiul 2

void printh(Node root, FILE *fod,int *n){
  
  Node q;
  int j;
  q=root->kids;

  while(q!=NULL){
    printh(q,fod,n);
    q=q->siblings;//parcurgi copiii 
  }

  (*n)--;
  fprintf(fod, "%d ",root->data);
  
  for(j=0;j<root->nr_adr-1;j++){
    fprintf(fod,"%s ",root->addr[j]);
  }

  fprintf(fod,"%s",root->addr[j]);
  
  if(*n>0){
    fprintf(fod, "\n" ); 
  }
  
}

void create_hierarchy(Node root){
  
  Node q;
  int nradr=0,j,k;
  q=root->kids;

  while(q!=NULL){
    create_hierarchy(q);
    q=q->siblings;//parcurgi copii
  }

  q=root->kids;
  //daca sunt vizitati printezi informatia din parinte
  while(q!=NULL){

    for(k=0;k<q->nr_adr;k++){
      nradr=0;
  
      for(j=0;j<root->nr_adr;j++){

        if(strcmp(root->addr[j],q->addr[k])==0)
          nradr++;
      }

      if(nradr==0){
        root->addr=realloc(root->addr,((root->nr_adr)+1)*sizeof(char*));
        root->addr[root->nr_adr]=(char*)malloc(strlen(q->addr[k])+1);
        strcpy(root->addr[root->nr_adr],q->addr[k]);
        (root->nr_adr)++;
      }
    }
    q=q->siblings;
  }

}

//Exercitiul 3

Users *create_users(Users *user,FILE *us){
  int i,nrusers=0, idus,idnod;
  fscanf(us,"%d",&nrusers);
  user=malloc(nrusers*sizeof(struct users));

  for(i=0;i<nrusers;i++){
    user[i].nr_users=nrusers;
    fscanf(us,"%d",&idus);
    user[i].id_user=idus;
    fscanf(us,"%d",&idnod);
    user[i].id_nod=idnod; 
  }

  return user;
}


Node search_tree(int data,Node root){
  Node q,find;

  if(root==NULL)
    return NULL;
  
  if(root->data==data)
    return root;
  
  q=root->kids;
  find=search_tree(data,q);

  if(find==NULL)
    find=search_tree(data,root->siblings);

  return find;
  
} 



void insert_addr(Node root,Node tree,char addr[],FILE *fod){
  Node p;
  int nradr=0,j;
  nradr=0;

  for(j=0;j<root->nr_adr;j++){
    //daca o gaseste
    if(strcmp(root->addr[j],addr)==0){
      nradr++;
    }
  }
    
    if(nradr==0){//nu a fost gasit
      root->addr=realloc(root->addr,((root->nr_adr)+1)*sizeof(char*));
      root->addr[root->nr_adr]=(char*)malloc(strlen(addr)+1);
      strcpy(root->addr[root->nr_adr],addr);
      (root->nr_adr)++;
      fprintf(fod,"%d ",root->data);
      p=search_tree(root->parent,tree);
      insert_addr(p,tree,addr,fod);

    }

    else{
      fprintf(fod,"%d",root->data);
    }
}

void freen(Node root){
  int j;
  for(j=0;j<root->nr_adr;j++){
    free(root->addr[j]);
    }
  free(root->addr);
  free(root);
}

void users_queries(Node root,FILE *queries,Users *user,FILE *fod){
  //Node n=malloc(sizeof(struct node));
  Node n,p,parent;
  int nrq=0,i=0,iduser,idnod,u=0,nr,j;
  char c[2],addr[10];
  fscanf(queries,"%d",&nrq);
  for(i=0;i<nrq;i++){

    fscanf(queries,"%s",c);

    if(strcmp(c,"q")==0){
      fscanf(queries,"%d",&iduser);
      fscanf(queries,"%s",addr);
      u=user[iduser].id_nod;
      n=search_tree(u,root);
      insert_addr(n,root, addr,fod);
      fprintf(fod,"\n");   
        
    }

    else if(strcmp(c,"f")==0){
      fscanf(queries,"%d",&idnod);
      //salvam in useri parintele in locul nodului
      p=search_tree(idnod,root);
      parent=search_tree(p->parent,root);
      nr=user[1].nr_users;
      for(j=0;j<nr;j++){
        if(user[j].id_nod==idnod){
          user[j].id_nod=p->parent;
    
        }
      }
      if(parent->kids==p){
        if(p->kids==NULL){//nu are copii
        parent->kids=p->siblings;
        freen(p);
      }
    }
  }


}


  
}

void frees(Sort st, int n){
  
  int i,j;
  for(i=0;i<n;i++){
    for(j=0;j<st[i].nr_adr;j++){
      free(st[i].addr[j]); 
    }
    free(st[i].addr);
  }
  free(st);
}






void freet(Node root){

  Node q,p;
  int j;
  q=root->kids;
  while(q!=NULL){
    p=q;
    q=q->siblings;//psrcurgi copii
    freet(p);
  }
  
  for( j=0;j<root->nr_adr;j++){
    free(root->addr[j]);
  }

  free(root->addr);
  free(root);
 
}

int main(){
  FILE *Tree=fopen("./tree.in", "r");
  FILE *Tree_o=fopen("./tree.out", "w");
  FILE *ho=fopen("./hierarchy.out", "w");
  FILE *qo=fopen("./queries.out", "w");
  FILE *user=fopen("./users.in","r");
  FILE *queries=fopen("./queries.in","r");
  int n;
  int *parent=NULL;
  Sort st=NULL;
  //pasul 1 am alcatuit structura de ordonare, citind din fisier
  st=complete_st(st,&n,Tree);
  Vnod *vn;
  vn=malloc(n*sizeof(struct vnod));
  Node t=create_tree(parent,n,vn,st);
  frees(st,n);
  DFS(t,Tree_o); 
  //exercitiul2
  create_hierarchy(t);
  printh(t,ho,&n);
  //exercitiul3
  Users *us=NULL;
  us=create_users(us,user);
  users_queries(t,queries,us,qo);;
  freet(t);
  t=NULL;
  free(vn);
  free(us);
  fclose(Tree);
  fclose(Tree_o);
  fclose(ho);
  fclose(qo);
  fclose(user);
  fclose(queries);
  
  return 0;


}
