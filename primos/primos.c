/*
Um inteiro maior do que 1 e' primo sse admite como divisores 1 e o 
proprio. Dois numeros primos que diferem duas unidades entre si sao 
primos gemeos

- Determinar se input e' primo
- Contar o num primos ate' input (inclusive)
- Escrever o maior primo menor do que o input
- Lista dos pares de primos gemeos ate input (inclusive)
*/
#include <stdio.h>
#include <math.h>

typedef enum{false,true} boolean;
boolean ehPrimo(unsigned int n);
unsigned int contaPrimos(unsigned int n);
unsigned int maiorPrimo(unsigned int n);
void listaGemeos(unsigned int n);
void menu(void);

int main(void){

   unsigned int numero, opc = 1, maiorprimo;
   char resposta[] = "Resposta: ";

   printf("Bemvindo ao prog dos primos\n");
   
   do {
    switch(opc) {
	case 1:
	 printf("numero?\n");
	 scanf("%u",&numero);
	 break;
	case 2:
	 printf("%s%u%s e' primo!\n",resposta,numero,ehPrimo(numero) ? "": " nao");
	 break;
	case 3:
	 printf("%s%u\n",resposta,contaPrimos(numero));
	 break;
	case 4:
	 maiorprimo = maiorPrimo(numero);
	 if(maiorprimo) {
		 printf("%s%u\n",resposta,maiorPrimo(numero));
	 } else {
		printf("%snao existe!\n",resposta);
	}
	 break;
	case 5:
	 printf("%s",resposta);
	 listaGemeos(numero);
	 printf("\n");
	 break;
	default:
	 printf("Opcao nao conhecida\n");
	 break;
    }
    
    menu();
    printf("Opcao?\n");
    scanf("%u",&opc);
   } while(opc != 0);

   printf("FIM.\n");
   return 0;
}

void menu() {
   printf("Menu:\n");
   printf("1 - Introduzir novo numero\n");
   printf("2 - Eh primo?\n");
   printf("3 - Contar primos\n");
   printf("4 - Maior primo\n");
   printf("5 - Lista de gemeos\n");
   printf("0 - Terminar\n");
}

boolean ehPrimo(unsigned int n) {

 unsigned int i;

 if(n%2==0) return n==2;

 for(i=3;i<=ceil(sqrt(n));i+=2) {
  if(n % i == 0)
   return false;
 }

 return n>=2;
}

unsigned int contaPrimos(unsigned int n) {
 unsigned int prms = 0;
 unsigned int i;
 for(i=2;i<=n;i++) {
  if(ehPrimo(i)) {
    prms++;
  }
 }
 
 return prms;
}

unsigned int maiorPrimo(unsigned int n) {
 if(n==0) return 0;

 unsigned int i;
 for(i=n-1;i>=2;i--) {
  if(ehPrimo(i)) {
    return i;
  }
 }

 return 0;
}

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
