#!/bin/bash
# $ represents argument(s), and $# gives the number of them
# if then else fi
# loop value i is accessed by $i and so are regular variables
if [ $# -eq 0 ]
then
	echo Nao inseriu argumentos
else
#$* represents ALL args
	echo Aqui estao os $# argumentos inseridos:
	for i in $*
	do
		echo $i
	done
#you can also use a more C-style for
#but this is bash specific, not plain bourne shell
#you need to add !/bin/bash up there, replacing !bin/sh

	for((i=1;i<=3;i++))
	do
		echo $i
	done
fi

echo Insira dois nums
read num1 #prompt para user
read num2

soma=`expr $num1 + $num2`
echo Resultado: $soma

#o FICHEIRO (f) existe? a DIRETORIA (d) existe?
if [ -f $1 -o -d $1 ]
then
	echo "Existe"
else
	echo "Nao existe"
fi

sum=0
input1=-1
while [ "$input1" != "^D" ]
do
 read input1
 sum=`expr $sum + $input1`
done

echo $sum

