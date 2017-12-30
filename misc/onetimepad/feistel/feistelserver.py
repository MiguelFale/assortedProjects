#!/usr/bin/python

# Turn on debug mode.
import cgi
import cgitb
import bitarray
import os
import sys
from myDES import MyDES
	
def reversefeistel(symmalg,block,rounds, subkeys):
	# Marks current iteration
	current = 0

	if symmalg == "des":
		block = MyDES.IP(block)

	# Block will be split in half
	leftside = False
	rightside = False
	while(current < rounds):
		leftside = bitarray.bitarray(block[0:len(block)/2])
		rightside = bitarray.bitarray(block[len(block)/2:len(block)])

		#perform a substitution
		if symmalg == "des":
			leftside = leftside ^ MyDES.functionf(rightside, subkeys[(rounds-current)-1])

		#permutation
		if symmalg != 'des' or (symmalg == 'des' and current < 15):
			block[0:(len(block)/2)] = rightside
			block[len(block)/2:len(block)] = leftside
		else:
			block[0:(len(block)/2)] = leftside
		
		current = current + 1
	
	#last iteration is permutation only, except for DES
	if symmalg != 'des':
		block[0:(len(block)/2)] = rightside
		block[len(block)/2:len(block)] = leftside
	else:
		block = MyDES.FP(block)
	return block

reload(sys)  
sys.setdefaultencoding('latin-1')
cgitb.enable()

print('Content-type: text/html\n\n')

form = cgi.FieldStorage()
symmalg = form["symmalg"].value
key = form["key"].value
msg = form["msg"].value
subkeys = ''

print("symmalg:"+symmalg+"\n")
print("key:"+key+"\n")
print("Encrypted msg:"+msg+"\n")

# Fill auxiliary vars
if symmalg.startswith('aes'):
	blocksize = 128
	if symmalg.endswith('128'):
		rounds = 10
	elif symmalg.endswith('192'):
		rounds = 12
	elif symmalg.endswith('256'):
		rounds = 14
else:
	blocksize = 64
	if(symmalg.startswith('des')):
		rounds = 16
	else:
		rounds = 48

msgbitarray = bitarray.bitarray()
msgbitarray.frombytes(msg)

# Mother key
keybitarray = bitarray.bitarray()
keybitarray.frombytes(key)

#print "keyarraynoserver"+str(keybitarray)
#print "msgarraynotserver"+str(msgbitarray)

# Subkeys
if symmalg == "des":
	subkeys = MyDES.genSubKeysEnc(keybitarray)

# per each block
index = 0
while(msgbitarray.length() > index):
	#feistel structure
	msgbitarray[index:index+blocksize] = reversefeistel(symmalg,msgbitarray[index:index+blocksize], rounds, subkeys)
	index = index + blocksize

print "Decrypted message:"+msgbitarray.tostring()+"\n"