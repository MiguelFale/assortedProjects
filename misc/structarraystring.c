#include <stdio.h>
#include <string.h>
#define DIM 4
#define DIM2 10

void proc(int i, int v[], int dim);
int quantos(int seq[], int dim);
int pertence(int elem, int seq[], int dim);
int funcalinec(int v1[], int v2[], int v3[],int dim);
void inverte(char s1[], char s2[]);
int ehIgualInversa(char s[]);
void elimina(char cadeia[], char c);


typedef struct
{
  int numero;
  char name[30];
  int nota;
  char resultado;
} Aluno;

int contaAlunos(Aluno a[], int dim, int i1, int i2);
void melhor(Aluno v[], int nalunos);

int main(void) {
  int a[DIM] = {1,2,3,4};
  int seq[DIM2] = {2,5,7,3,9,4,0,0,0,0};
  int v1[DIM] = {3,6,2,0}, v2[DIM] = {4,2,6,0}, v3[DIM] = {0};
  int lulu;

  /*proc(2,a,DIM);*/
  proc(3,a,DIM);
  printf("%d %d %d %d\n", a[0],a[1],a[2],a[3]);

  printf("2.a) %d\n",quantos(seq,DIM2));
  printf("2.b) %d\n",pertence(6,seq,DIM2));
  printf("2.b) %d\n",pertence(9,seq,DIM2));
  printf("2.c) %d\n",funcalinec(v1,v2,v3,DIM));

  for(lulu=0;lulu<DIM;lulu++) {
    printf("%d\n", v3[lulu]);
  }

  char s1[DIM2] = "roma";
  char s2[DIM2];

  inverte(s1,s2);

  printf("g3 a) %s\n",s2);
  printf("g3 a2) %d\n", ehIgualInversa("roma"));
  printf("g3 a2) %d\n", ehIgualInversa("reler"));

  char s3[DIM2*3] = "Logo que o vi, fugi dele.";
  elimina(s3,'i');
  elimina(s2,'z');
  printf("g3 a3) %s\n", s3);
  printf("g3 a3) %s\n", s2);

/*The left operand of -> must be a pointer; the . operator is used if it is not a pointer.*/
  Aluno pauta[100];

  int tmpcounter;
  for(tmpcounter = 0; tmpcounter < 100;tmpcounter++) {
    pauta[tmpcounter].nota = 0;
  }
  
  pauta[50].nota = 9;
  pauta[66].nota = 17;
  strcpy(pauta[88].name,s1);
  pauta[88].nota = 20;
  strcpy(pauta[99].name,"areeiro");
  pauta[99].nota = 20;

  printf("%d\n",contaAlunos(pauta,100,9,20));
  melhor(pauta,100);
  return 0;
}

void proc(int i, int v[], int dim){
  int j = 0;
  while(j<=i && j < dim) {
    v[j]=v[j+1];
    j++;
  }
}

int quantos(int seq[], int dim) {
  int nelems = 0,counter;

  for(counter=0;counter < dim;counter++) {
    if(seq[counter] != 0) {
      nelems++;
    }
  }

  return nelems;
}

int pertence(int elem, int seq[], int dim) {
  int found = 0, i;

  for(i=0;i < quantos(seq,dim) && !found; i++) {
    if(seq[i] == elem) {
      found = 1;
    }
  }

  return found;
}

int funcalinec(int v1[], int v2[], int v3[],int dim) {
  int i, k=0;

  for(i=0;i < dim;i++) {
    if(pertence(v1[i],v2,dim)) {
      v3[k] = v1[i];
      k++;
    }
  }

  return k;
}

void inverte(char s1[], char s2[]) {
  int size = 0, i;

  while(s1[i] != '\0') {
    i++;
  }

  size = i;

  for(i=0;i < size;i++) {
    s2[i] = s1[size-(i+1)];
  }

  s2[size] = '\0';
}

int ehIgualInversa(char s[]) {
  int size = 0;

  while(s[size] != '\0') {
    size++;
  }

  char s2[size+1];

  strcpy(s2,s);

  inverte(s,s2);

  return strcmp(s,s2) == 0;
}

void elimina(char cadeia[], char c) {
  int aux, k;

  for(aux = 0; cadeia[aux] != '\0'; aux++) {
    if(cadeia[aux] == c) {
      for(k=aux;cadeia[k] != '\0';k++) {
        cadeia[k] = cadeia[k+1];
      }
    }
  }
}

int contaAlunos(Aluno a[], int dim, int i1, int i2) {
  int k, nalunos = 0;

  for(k=0;k < dim; k++) {
    if(a[k].nota >= i1 && a[k].nota <= i2) {
      nalunos++;
    }
  }
  return nalunos;
}

void melhor(Aluno v[], int nalunos) {

  int max = -1,i;
  for(i=0;i < nalunos;i++) {
    if(v[i].nota >= max) {
      max = v[i].nota;
    }
  }
  printf("Nota maxima = %d\n",max);

  for(i=0;i < nalunos;i++) {
    if(v[i].nota == max) {
      printf("%s\n",v[i].name);
    }
  }
}