#!/bin/bash
# $ represents argument(s), and $# gives the number of them
# if then else fi
# loop value i is accessed by $i and so are regular variables
if [ $# -eq 0 ]
then
	echo Nao inseriu argumentos
else
argsum=0
#$* represents ALL args
	echo Aqui estao os $# argumentos inseridos:
	for i in $*
	do
		echo $i
	done
#you can also use a more C-style for
#but this is bash specific, not plain bourne shell
#you need to add !/bin/bash up there, replacing !bin/sh

	for((i=1;i<=$1;i++))
	do
		argsum=`expr $i + $argsum`
	done
fi

echo "somatorio e' $argsum"

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

while read input1 #reads until ctrl+d
do
	sum=`expr $sum + $input1`
done

echo $sum

sumf=0
sumd=0
for i in `ls`
do
	if [ -f $i ] 
	then
		sumf=`expr $sumf + 1`
	elif [ -d $i ] 
	then
		sumd=`expr $sumd + 1`
	fi
done

echo "$sumf files and $sumd folders"
tds=0
#you can also provide several space-separated paths to find
for size in `find -name "*.sh" -printf "%s\n"`
do
	tds=`expr $tds + $size`	
done

echo "tds is $tds"

