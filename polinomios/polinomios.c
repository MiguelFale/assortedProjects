#include <stdio.h>
#include <math.h>
#define DIM 10
#define DIMX 20
#define DELTA 0.000001

/*CUIDADO COM CASTS IMPLICITOS DE INT PARA UNSIGNED INT!

#include <stdio.h>

int main(void)
{
  unsigned int plus_one = 1;
  int minus_one = -1;

  if(plus_one < minus_one)
    printf("1 < -1");
  else
    printf("boring");

  return 0;
}
imprime 1 < -1 pois o -1 do int e' convertido para MAX do unsigned int durante a comparacao
*/

int comparaZero(double x);
int somaPolinomios(double v1[], double v2[], double v3[], int n);
int prodPolinomios(double v1[], double v2[], double v3[], int n);
double aplicaPolinomio(double v[], unsigned int n, double x);
void imprimeGrafico(double yval[]);

int lePolinomio(unsigned int n, double v[], unsigned int dim);
void imprimePolinomio(double v[], unsigned int dim);
void imprimeFormula(double v[], unsigned int dim);
void avaliaPolinomio(unsigned int n, unsigned int grau, double p[], unsigned int dimx, double v[]);

int main(void){

   double v1[DIM]={0.0}, v2[DIM]={0.0},v3[DIM]={0.0};
   double p1[DIMX]={0.0},p2[DIMX]={0.0};
   int grau1, grau2, grau3;
   printf("Bemvindo ao prog dos polinomios\n");

   /*1. P1*/
   grau1 = lePolinomio(1,v1,DIM);
   

   imprimePolinomio(v1,grau1+1);
   

   avaliaPolinomio(1,grau1,p1,DIMX,v1);
   
   /*2. P2*/
   grau2 = lePolinomio(2,v2,DIM);

   imprimePolinomio(v2,grau2+1);

   avaliaPolinomio(2,grau2,p2,DIMX,v2);

   /*3. soma */
   grau3 = somaPolinomios(v1,v2,v3,DIM);
   printf("polinomio1 + polinomio2:\nGrau: %d",grau3);
   imprimeFormula(v3,grau3+1);


   /*4. comblinear*/

   /*5. produto*/

   /*6. tab pol2*/

   /*7. grafico pol2*/
   return 0;
}

int lePolinomio(unsigned int n, double v[], unsigned int dim){

    unsigned int grau, i;

   printf("Indique grau de pol%u (menor que %u)\n",n,dim);  
   scanf("%u",&grau);

   while(grau >= dim) {
    printf("Indique grau de pol%u (menor que %u!!!!)\n",n,dim);
    scanf("%u",&grau);  
   }

   printf("Indique os %u coefs do pol%u por ordem crescente do expoente\n",grau+1,n);

   for(i = 0; i<=grau ;i++) {
    scanf("%lf",&v[i]);
   }

   return grau;
}

void imprimeFormula(double v[], unsigned int dim) {
  unsigned int i;
  printf("Formula: ");
  for(i = 0; i < dim;i++) {

    if(comparaZero(v[i]) == 0) {
      continue;
    } else if(i==0) {
      printf ("%.3lf ", v[i] );
    } else {
      printf("%s %lf ", (v[i]<0 ? "_" : "+") ,abs(v[i]));
    }
  }
  printf("\n");
}

void imprimePolinomio(double v[], unsigned int dim) {
  unsigned int i;
  for(i = 0; i < dim;i++) {
    printf("v[%u]=%lf\n",i,v[i]);
  }
}

int comparaZero(double x) {
  
  if(-DELTA < x && x < DELTA) {
    return 0;
  } else if(x <= -DELTA) {
    return -1;
  } else {
    return 1;
  }
}

void avaliaPolinomio(unsigned int n, unsigned int grau, double p[], unsigned int dimx,double v[]) {

  unsigned int npontos,i;
  printf("Indique o numero de pontos para avaliar o pol%u (menor que %u)\n",n,dimx);

     scanf("%u",&npontos);

   while(npontos >= dimx) {
    printf("Indique o numero de pontos para avaliar o pol%u (menor que %u!!!!)\n",n,dimx);
    scanf("%u",&npontos);  
   }

    printf("Indique os %u pontos para avaliar pol%u\n",npontos,n);

   for(i = 0; i < npontos ;i++) {
    scanf("%lf",&p[i]);
   }

   if(n==1)
    printf("%14s%14s\n","X","Polinomio1(X)");
  else
    printf("%14s%14s\n","X","Polinomio2(X)");

   for(i=0;i<npontos;i++) {
    /*(14 espacos, 2 casas decimais)*/
      printf("%14.2lf%14.2lf\n",p[i],aplicaPolinomio(v, grau+1, p[i]));
    }
}

double aplicaPolinomio(double v[], unsigned int n, double x) {
  double res = 0.0;
  unsigned int i;

  for(i = 0;i<n;i++) {
    res += v[i] * pow (x, i);
  }

  return res;
}

int somaPolinomios(double v1[], double v2[], double v3[], int n) {
  unsigned int i;
  for(i=0;i<n;i++) {
    v3[i] = v1[i] + v2[i];
  }

  return devolvegrau(v3,n);
}

int devolvegrau(double v[],n) {
    unsigned int i, maxgrau=0;

  for ( i = n-1; i > 0; i-- ) {
    if(comparaZero(v3[i])!=0) {
      maxgrau = i;
      break;
    }
  }

  return maxgrau;
}
/*
 for(i=3;i<=ceil(sqrt(n));i+=2) {
  if(n % i == 0)
   return false;
 }

 return n>=2;
void listaGemeos(unsigned int n) {
 unsigned int i;
 int prevprimo = -1;
 boolean firstpair = false;

 for(i=2;i<=n;i++) {
  if(ehPrimo(i)) {
    if(i-prevprimo == 2) {
     	printf("(%u, %u) ",prevprimo,i);
	firstpair = true;
    }
    prevprimo = i;
  }
 } 

 if(!firstpair) {
	printf("Nenhum");
 }
}
*/