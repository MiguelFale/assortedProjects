/**
 * Segundo trabalho de Prog1 12-13
 * Autores:
 * Miguel Amorim Falé 43556
 * Tiago Ribeiro      43528
 */

#include <stdio.h>

#define DIM 10
#define DIMX 20

int lePolinomioN ( int n, double vCoef[], int maxDim );
void avaliaPolinomioN ( int n, double vPontos[], int maxDim, double vCoef[],
			int nCoef );
void leVector ( double v[], int n, int maxDim );
double aplicaPolinomio( double v[], int n, double x );
int somaPolinomios ( double v1[], double v2[], double v3[], int n );
int devolveGrau ( double v[], int n );
int comparaZero( double x );
void imprimeFormula ( int nCoef, double v[] );
int combinacaoLinear ( double vCoefP1[], double vCoefP2[],
		       double vCombLinear[], int maxDim );
int prodPolinomios( double v1[], double v2[], double v3[], int n );
void imprimeGrafico( double yval[] );


/**
 * Funcao main
 * Le e guarda os coeficientes de dois polinomios num vector para cada;
 * Avalia os polinomios numa sequencia de pontos para cada, imprimindo as
 * respectivas tabelas;
 * Efetua a adicao, a combinacao linear e o produto entre os dois polinomios,
 * imprimindo as respectivas formulas;
 * Avalia o polinomio2 nos pontos inteiros entre 1 e 20 inclusive, imprimindo
 * a respectiva tabela e grafico.
 */

int main ( void ) {

  double coef_p1[DIM] = {0};
  double coef_p2[DIM] = {0};
  double vPontos[DIMX];
  double somaP1P2[DIM] = {0};
  double combLinear[DIM] = {0};
  double produtoP1P2[DIMX] = {0};
  double vResultados[DIMX] = {0};
  int numcoef_p1;
  int numcoef_p2;
  int numcoef_somaP1P2;
  int numcoef_CombLinearP1P2;
  int numcoef_prodP1P2;
  int grau;
  int i;

  printf ( "Bemvindo ao programa dos polinomios!\n" );

  /* Le os coeficientes do polinomio1. Os dois polinomios sao
     definidos na mesma funcao */
  grau = lePolinomioN ( 1, coef_p1, DIM );
  numcoef_p1 = grau + 1;

  /* Avalia o polinomio1 num conjunto de pontos. Os dois polinomios
     sao avaliados na mesma funcao */
  avaliaPolinomioN ( 1, vPontos, DIMX, coef_p1, numcoef_p1  );

  /* Le e avalia o polinomio2 */
  grau = lePolinomioN ( 2, coef_p2, DIM );
  numcoef_p2 = grau + 1;
  avaliaPolinomioN ( 2, vPontos, DIMX, coef_p2, numcoef_p2 );

  /* Faz a soma entre o polinomio1 e o polinomio2, imprimindo o grau */
  printf ( "polinomio1 + polinomio2:\nGrau: %d\n",
	   grau = somaPolinomios ( coef_p1, coef_p2, somaP1P2, DIM ) );

  /* Imprime a formula da soma */
  numcoef_somaP1P2 = grau + 1;
  imprimeFormula ( numcoef_somaP1P2, somaP1P2 );

  /* Faz a combinacao linear de polinomio1 e polinomio2, imprimindo o grau */
  grau = combinacaoLinear ( coef_p1, coef_p2, combLinear, DIM );
  printf ( "polinomio1 - c * polinomio2:\nGrau: %d\n", grau );

  /* Imprime a formula da combinacao linear */
  numcoef_CombLinearP1P2 = grau + 1;
  imprimeFormula ( numcoef_CombLinearP1P2, combLinear );

  /* Faz o produto entre polinomio1 e polinomio2, imprimindo o grau */
  printf ( "polinomio1 * polinomio2:\nGrau: %d\n",
	   grau = prodPolinomios ( coef_p1, coef_p2, produtoP1P2, DIM ) );

  /* Imprime a formula do produto */
  numcoef_prodP1P2 = grau + 1;
  imprimeFormula ( numcoef_prodP1P2, produtoP1P2 );

  /* Imprime a tabela do polinomio2 no intervalo de 1 a 20 inclusive */
  printf ( "%14c%14s\n", 'X', "Polinomio2(X)" );
  for ( i = 0; i < 20; i++ )
    printf ( "%14.2lf%14.2lf\n", (double)i+1, vResultados[i] = 
	     aplicaPolinomio ( coef_p2, numcoef_p2, (double)i+1 ) );

  printf ( "Grafico simplificado do polinomio2 entre 1 e 20:\n\n" );

  /* Imprime o grafico do polinomio2 no intervalo de 1 a 20 inclusive */
  imprimeGrafico ( vResultados );

  printf ( "Fim.\n" );

  return 0;
}


/**
 * Funcao lePolinomioN
 * Define o grau e os coeficientes de um polinomio, guardando os
 * coeficientes no vector.
 *
 * @param n  numero do polinomio ( 1 ou 2 )
 * @param vCoef  vector que representa o polinomio
 * @param maxDim  dimensao maxima do vector
 * @requires maxDim = DIM
 * @return grau  grau do polinomio
 */

int lePolinomioN ( int n, double vCoef[], int maxDim ) {

  int grau, numCoef;

  printf ( "Indique o grau do polinomio%d (menor que 10):\n", n );

  scanf ( "%d", &grau );

  printf ( "Indique os %d coeficientes do polinomio%d, "
	   "por ordem crescente do expoente:\n", numCoef = grau+1, n );

  /* Trata do preenchimento do vector */
  leVector ( vCoef, numCoef, maxDim );

  return grau;
}


/**
 * Funcao avaliaPolinomioN
 * Le o numero de pontos, guarda os pontos num vector e imprime a tabela
 * de pontos e resultados, de acordo com o polinomio considerado.
 *
 * @param n  numero do polinomio ( 1 ou 2 )
 * @param vPontos  vector de pontos
 * @param maxDim  dimensao maxima do vector dos pontos
 * @param vCoef  vector que representa o polinomio a avaliar
 * @param nCoef  numero de coeficientes do polinomio
 * @requires maxDim = DIMX
 */

void avaliaPolinomioN ( int n, double vPontos[], int maxDim, double vCoef[],
			int nCoef ) {
  int i, numPontos;

  printf ( "Indique o numero de pontos em que quer avaliar "
	   "o polinomio%d (menor que 20):\n", n );
  scanf ( "%d", &numPontos );

  printf ( "Indique os %d pontos em que quer avaliar o polinomio%d:\n",
	   numPontos, n );

  leVector ( vPontos, numPontos, maxDim );

  printf ( "%14c Polinomio%d(X)\n", 'X', n );

  /* Vai imprimir os pontos numa coluna e os valores obtidos noutra */
  /* A condicao i < maxDim impede que sejam impressos valores a mais,
     pelo que so podem ser avaliados e impressos 20 pontos no maximo */
  for ( i = 0; i < numPontos && i < maxDim; i++ )
    printf ( "%14.2lf%14.2lf\n", vPontos[i],
	     aplicaPolinomio ( vCoef, nCoef, vPontos[i] ) );
}


/**
 * Funcao leVector
 * Le e guarda valores introduzidos pelo utilizador num vector.
 *
 * @param v  vector
 * @param n  dimensao definida do vector
 * @param maxDim  dimensao maxima do vector
 */

void leVector ( double v[], int n, int maxDim ) {

  int i;

  /* Se n > maxDim, o vector so vai ser
     preenchido ate ah posicao maxDim - 1 */
  for ( i = 0; i < n && i < maxDim; i++ )
    scanf ( "%lf", &v[i] );
}


/**
 * Funcao aplicaPolinomio
 * Avalia um polinomio num ponto.
 *
 * @param v  vector que representa o polinomio
 * @param n  numero de coeficientes do polinomio, responsavel por controlar
 * o numero de vezes que as operacoes se repetem
 * @param x  ponto
 * @return resultado  valor do polinomio no ponto x
 */

double aplicaPolinomio( double v[], int n, double x ) {

  int i;
  double resultado = 0, potencia = 1;

  for ( i = 0; i < n; i++ ) {
    resultado += v[i] * potencia;
    potencia *= x;
  }

  return resultado;
}


/**
 * Funcao somaPolinomios
 * Obtem em v3 os coeficientes do polinomio correspondente ah soma dos
 * polinomios representados em v1 e v2.
 * 
 * @param v1  vector do polinomio1
 * @param v2  vector do polinomio2
 * @param v3  vector do polinomio resultante
 * @param n  dimensao maxima dos vectores
 * @requires n <= DIM
 * @return devolveGrau(v3,n)  grau do polinomio representado em v3
 */

int somaPolinomios ( double v1[], double v2[], double v3[], int n ) {

  int i;

  /* Efetua e guarda cada soma numa posicao de v3 */
  for ( i = 0; i < n; i++ )
    v3[i] = v1[i] + v2[i];

  return devolveGrau ( v3, n );
}


/**
 * Funcao devolveGrau
 * Percorre os coeficientes e devolve o grau do polinomio.
 *
 * @param v  vector que representa o polinomio
 * @param n  dimensao maxima do vector
 * @return grau  grau do polinomio
 */

int devolveGrau ( double v[], int n ) {

  int i, grau = 0;

  /* Faz mais sentido contar a partir do
     ultimo elemento para obter o grau */
  for ( i = n-1; i >= 0; i-- )

    /* Se o elemento actual de v for diferente de 0,
       o seu indice vai ser o grau */
    if ( comparaZero(v[i]) != 0 ) {
      grau = i;
      i = -1;
      /* sai do ciclo quando encontra o primeiro valor relevante */
    }

  return grau;
}


/**
 * Funcao comparaZero
 * Compara um valor real com 0 e determina se ele eh positivo, nulo ou
 * negativo.
 *
 * @param x  valor
 * @return marcador  retorna um valor adequado para cada caso
 */

int comparaZero ( double x ) {

  int marcador;
  double delta = 0.000001;

  /* Se x e 0 forem iguais */
  if ( x > -delta && x < delta )
    marcador = 0;

  /* Se x for menor que 0 */
  if ( x <= -delta )
    marcador = -1;

  /* Se x for maior que 0 */
  if ( x >= delta )
    marcador = 1;

  return marcador;
}


/**
 * Funcao imprimeFormula
 * Imprime a formula de um polinomio.
 *
 * @param nCoef  numero de coeficientes do polinomio
 * @param v  vector que representa o polinomio
 */

void imprimeFormula ( int nCoef, double v[] ) {

  int i;
  int saideciclo = 0;

  printf ( "Formula: ");
  for ( i = 0; i < nCoef; i++ ) {

    /* Imprime o primeiro monomio */

    /* Se o primeiro monomio for nulo, o primeiro a ser impresso
       passa a ser o seguinte nao nulo */
    if ( comparaZero(v[i]) == 0 && i == 0 ) {
      while ( i < nCoef && saideciclo != -1 ) {
	i++;

	/* Se foi encontrado um monomio nao nulo */
	if ( comparaZero (v[i] ) != 0 ) {
	  printf ( "%.3lf x**%d", v[i], i );
	  saideciclo = -1;
	}
      } /* fim do while */
    }

    /* Se o primeiro monomio nao for nulo */
    if ( comparaZero(v[i]) != 0 && i == 0 )
      printf ( "%.3lf", v[i] );

    /* imprime os restantes monomios ( se existirem ) */
    if ( i+1 < nCoef ) {

      /* se o proximo coeficiente for negativo */
      if ( v[i+1] < 0 )
	printf ( " - %.3lf x**%d", v[i+1]*-1, i+1 );

      /* se o proximo coeficiente for positivo */
      if ( v[i+1] > 0 )
	printf ( " + %.3lf x**%d", v[i+1], i+1 );

    }

  } /* fim do if principal que percorre todos os coeficientes */

  printf ( "\n" );
}


/**
 * Funcao combinacaoLinear
 * Faz a combinacao linear de polinomio1 e polinomio2 e guarda os resultados
 * no vector vCombLinear, que representa o polinomio resultante.
 *
 * @param vCoefP1  vector que representa o polinomio1
 * @param vCoefP2  vector que representa o polinomio2
 * @param vCombLinear  vector que guarda os coeficientes resultantes
 * @param maxDim  dimensao maxima dos tres vectores
 * @requires maxDim <= DIM
 * @return devolveGrau(vCombLinear, maxDim)  grau do polinomio resultante
 */

int combinacaoLinear ( double vCoefP1[], double vCoefP2[],
		       double vCombLinear[], int maxDim ) {
  int i;
  double constante;

  printf ( "Indique o valor para a constante real c:\n" );
  scanf ( "%lf", &constante );

  /* Guarda cada resultado numa posicao de vCombLinear */
  for ( i = 0; i < maxDim; i++ )
    vCombLinear[i] = vCoefP1[i] - constante * vCoefP2[i];

  return devolveGrau ( vCombLinear, maxDim );
}


/**
 * Funcao prodPolinomios
 * Faz o produto entre 2 polinomios.
 * 
 * @param v1  vector representante do polinomio 1
 * @param v2  vector representante do polinomio 2
 * @param v3  vector representante do polinomio do resultado
 * @param n  dimensao maxima de v1 e v2
 * @requires n = DIM
 * @requires dimensao maxima de v3 = n*2 = DIMX
 * @return devolveGrau(v3,n*2)  grau do polinomio resultante
 */

int prodPolinomios( double v1[], double v2[], double v3[], int n ) {

  int grauV1 = devolveGrau ( v1, n );
  int grauV2 = devolveGrau ( v2, n );
  int k;
  int j;

  /* Cada elemento de v1 vai multiplicar por todos os elementos de v2 */
  /* Existem posicoes de v3 que vao ser acedidas mais do que uma vez,
     de modo a somar os monomios de grau identico */
  for ( k = 0; k < grauV1+1; k++ )
    for ( j = 0; j < grauV2+1; j++)
      v3[k+j] += v1[k] * v2[j];

  return devolveGrau ( v3, n*2 );
}


/**
 * Funcao imprimeGrafico
 * Imprime um grafico simplificado do polinomio2 no intervalo [1,20]
 *
 * @param yval  vector que contem os valores obtidos pela avaliacao do
 * polinomio2 no intervalo [1,20]
 * @requires dimensao de yval = DIMX
 */

void imprimeGrafico( double yval[] ) {

  int i;

  /* Imprime espaco com traco ou dois espacos, consoante a situacao */
  printf ( "Pos|" );
  for ( i = 0; i < 20; i++ )
    printf ( "%s", comparaZero( yval[i] ) == 1 ? " -" : "  " );

  printf ( "\n   |\nNul|" );
  for ( i = 0; i < 20; i++ )
    printf ( "%s", comparaZero ( yval[i] ) == 0 ? " -" : "  " );

  printf ( "\n   |\nNeg|" );
  for ( i = 0; i < 20; i++ )
    printf ( "%s", comparaZero ( yval[i] ) == -1 ? " -" : "  " );

  printf ( "\n   |\n   |" );

  /* Imprime o eixo horizontal */
  for ( i = 0; i < 20; i++ )
    printf ("__");
  printf ( "\n    " );

  /* Imprime os valores do eixo horizontal */
  for ( i = 1; i <= 20; i++ ) {
    if ( i >= 10 && i < 20 )
      printf ( " %d", i-10 );
    else if ( i == 20 )
      printf ( " %d", i-20 );
    else
      printf ( " %d", i );
  }

  printf ( "\n%24d%20d\n", 10, 20 );

}
