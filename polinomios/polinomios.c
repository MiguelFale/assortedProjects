#include <stdio.h>
#include <math.h>
#define DIM 10
#define DIMX 20
#define DELTA 0.000001

/*
Para polinomios simples i.e. nao suposta isto: https://en.wikipedia.org/wiki/Laurent_polynomial

CUIDADO COM CASTS IMPLICITOS DE INT PARA int! NAO MISTURAR. usar so para DIMsizes

#include <stdio.h>

int main(void)
{
  int plus_one = 1;
  int minus_one = -1;

  if(plus_one < minus_one)
    printf("1 < -1");
  else
    printf("boring");

  return 0;
}
imprime 1 < -1 pois o -1 do int e' convertido para MAX do int durante a comparacao
*/
typedef enum{false,true} boolean;
int comparaZero(double x);
int somaPolinomios(double v1[], double v2[], double v3[], unsigned int n);
int prodPolinomios(double v1[], double v2[], double v3[], unsigned int dim);
double aplicaPolinomio(double v[], int n, double x);
void imprimeGrafico(double yval[]);

int lePolinomio(unsigned int n, double v[], unsigned int dim);
void imprimePolinomio(double v[], int dim);
void imprimeFormula(double v[], int dim);
void avaliaPolinomio(unsigned int n, int grau, double p[], unsigned int dimx, double v[]);
int comblinear(double v1[], double v2[], double v3[], unsigned int dim);
int devolvegrau(double v[],unsigned int n);

int main(void){

   double v1[DIM]={0.0}, v2[DIM]={0.0},v3[DIM]={0.0},v4[DIM]={0.0},v5[DIM]={0.0};
   double p1[DIMX]={0.0},p2[DIMX]={0.0},p3[DIMX]={0.0};
   int grau1, grau2, grau3, grau4, grau5;
   unsigned int p3k;
   printf("Bemvindo ao prog dos polinomios\n");

   /*1. P1*/
   grau1 = lePolinomio(1,v1,DIM);
   

   imprimePolinomio(v1,grau1+1);
   

   avaliaPolinomio(1,grau1,p1,DIMX,v1);
   
   /*2. P2*/
   grau2 = lePolinomio(2,v2,DIM);

   imprimePolinomio(v2,grau2+1);

   avaliaPolinomio(2,grau2,p2,DIMX,v2);

   /*3. soma. da para fazer uma atribuicao dentro do printf! */
   printf("polinomio1 + polinomio2:\nGrau: %d\n",grau3 = somaPolinomios(v1,v2,v3,DIM));
   imprimeFormula(v3,grau3+1);

   /*4. comblinear*/
   printf("polinomio1 -c * polinomio2:\nGrau: %d\n",grau4 = comblinear(v1,v2,v4,DIM));
   imprimeFormula(v4,grau4+1);

   /*5. produto*/
    printf("polinomio1 * polinomio2:\nGrau: %d\n",grau5 = prodPolinomios(v1,v2,v5,DIM));
   imprimeFormula(v5,grau5+1);

   /*6. tab pol2*/
   printf("%14s%14s\n","X","Polinomio2(X)");
   for(p3k=1;p3k<=DIMX;p3k++) {
    p3[p3k-1] = aplicaPolinomio(v2, grau2+1, (double)p3k);
    printf("%14.2lf%14.2lf\n",(double) p3k,p3[p3k-1]);
   }

   /*7. grafico pol2*/
   printf("Grafico do pol2 1 a 20\n");
   imprimeGrafico(p3);
   return 0;
}

void imprimeGrafico(double yval[]) {
  unsigned int i,k;
  boolean firstPos = true,
   firstNul = true,
   firstNeg = true,
   firstBase = true,
   firstNum = true,
   firstNum10 = true;

  /*1 pos, 2 ou 4 ou 6 ou 7 empty, 3 null, 5 neg, 8 x, 9 aux*/
  for(i=1;i<=9;i++) {
    for(k=0;k<DIMX;k++) {
      switch(i) {
        case 1:
            printf("%s",firstPos? "Pos|" : "");
            firstPos = false;
            printf(" %s", comparaZero(yval[k]) == 1 ? "-" : " ");
            break;
        case 2:
        case 4:
        case 6:
          printf("%4s","|");
          break;
        case 3:
            printf("%s",firstNul? "Nul|" : "");
            firstNul = false;
            printf(" %s", comparaZero(yval[k]) == 0 ? "-" : " ");
            break;
        case 5:
            printf("%s",firstNeg? "Neg|" : "");
            firstNeg = false;
            printf(" %s", comparaZero(yval[k]) == -1 ? "-" : " ");
            break;
        case 7:
          if(firstBase) {
            printf("%4s","|");
            firstBase = false;
          }
          printf("__");
          break;
        case 8:
          if(firstNum) {
            printf("%4s"," ");
            firstNum = false;
          }
          printf(" %d",(k+1)%10);
          break;
        default:
          if(firstNum10) {
            printf("%4s"," ");
            firstNum10 = false;
          }
          if((k+1)%10 == 0) {
            printf("%d",k+1);
          } else {
            printf("  ");
          }
          break;
      }
      if(i%2==0 && i < 8) {
        break;
      }
    }
    printf("\n");
  }
}


int prodPolinomios(double v1[], double v2[], double v3[], unsigned int dim) {
    unsigned int i,k;
    double tempsum;
  for(i=0;i<dim;i++) {
    /*calculo de cada d*/
    tempsum = 0.0;
    for(k=0;k<=i;k++) {
      tempsum += v1[k] * v2[i-k];
    }
    v3[i] = tempsum;
  }

  return devolvegrau(v3,dim);
}

int comblinear(double v1[], double v2[], double v3[], unsigned int dim) {
   double c;
   unsigned int i;
   printf("Indique o valor para a constante real c: ");
   scanf("%lf",&c);

  for(i=0;i<dim;i++) {
    v3[i] = v1[i] - c * v2[i];
  }

  return devolvegrau(v3,dim);
}

int lePolinomio(unsigned int n, double v[], unsigned int dim){

    int grau, i;

   printf("Indique grau de pol%u (menor que %u)\n",n,dim);  
   scanf("%d",&grau);

   while(grau >= dim) {
    printf("Indique grau de pol%u (menor que %u!!!!)\n",n,dim);
    scanf("%d",&grau);  
   }

   printf("Indique os %d coefs do pol%u por ordem crescente do expoente\n",grau+1,n);

   for(i = 0; i<=grau ;i++) {
    scanf("%lf",&v[i]);
   }

   return grau;
}

void imprimeFormula(double v[], int dim) {
  int i;
  boolean firstValue = false;
  printf("Formula: ");
  for(i = 0; i < dim;i++) {

    if(comparaZero(v[i]) == 0) {
      continue;
    } else if(!firstValue) {
      printf ("%.3lf ", v[i] );
      firstValue = true;
    } else {
      printf("%s %.3lf ", (v[i]<0 ? "-" : "+") ,fabs(v[i]));
    }

    if(i>0) {
      printf("x**%d ",i);
    }
  }
  printf("\n");
}

void imprimePolinomio(double v[], int dim) {
  int i;
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

void avaliaPolinomio(unsigned int n, int grau, double p[], unsigned int dimx,double v[]) {

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

double aplicaPolinomio(double v[], int n, double x) {
  double res = 0.0;
  unsigned int i;

  for(i = 0;i<n;i++) {
    res += v[i] * pow (x, i);
  }

  return res;
}

int somaPolinomios(double v1[], double v2[], double v3[], unsigned int n) {
  unsigned int i;
  for(i=0;i<n;i++) {
    v3[i] = v1[i] + v2[i];
  }

  return devolvegrau(v3,n);
}

int devolvegrau(double v[],unsigned int n) {

  int i, maxgrau=0;

  if(n==0) return 0; /*previne overflow 0-1 = MAXUI*/

  for ( i = n-1; i > 0; i-- ) {
    if(comparaZero(v[i])!=0) {
      maxgrau = i;
      break;
    }
  }

  return maxgrau;
}