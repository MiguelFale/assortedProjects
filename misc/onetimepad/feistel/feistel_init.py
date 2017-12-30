from mininet.net import Mininet
from mininet.topolib import TreeTopo
import bitarray
import sys
import argparse
import os
from myDES import MyDES
import time

def feistel(symmalg,block,rounds, subkeys):
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
			leftside = leftside ^ MyDES.functionf(rightside, subkeys[current])

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
	
if __name__ == '__main__':
	reload(sys)  
	sys.setdefaultencoding('latin-1')
	
	# This topology contains 3 hosts; a client(0), a server(1), and an attacker(2)
	tree2 = TreeTopo(depth=1,fanout=3)
	net = Mininet(topo=tree2)
	net.start()
	h1, h2, h3  = net.hosts[0], net.hosts[1], net.hosts[2]
	#h3.cmd("sudo tcpdump -U -n -i any -w record &")
	#print net.links[0],net.links[1],net.links[2]
	#h3.cmd("sudo wireshark &")
	time.sleep(10)
	input = ''
	symmalg = ''
	asymmalg = ''
	blocksize = -1 # determined by the algorithm
	rounds = -1 # determined by the algorithm
	key = ''
	subkeys = ''

	# Parse cli info
	parser = argparse.ArgumentParser(description='Feistel structure.')
	parser.add_argument('symmalg', metavar='symmalg', choices=['des','tdes168','tdes112','tdes56','aes128','aes192','aes256'], type=str, help='The symmetric algorithm')
	parser.add_argument('input', type=str, help='Your message')
	parser.add_argument('-asymmalg', type=str, help='The asymmetric algorithm')
	args = parser.parse_args()

	# Fill auxiliary vars and convert message to bitarray
	if args.symmalg.startswith('aes'):
		blocksize = 128
		if args.symmalg.endswith('128'):
			rounds = 10
		elif args.symmalg.endswith('192'):
			rounds = 12
		elif args.symmalg.endswith('256'):
			rounds = 14
	else:
		blocksize = 64
		if(args.symmalg.startswith('des')):
			rounds = 16
		else:
			rounds = 48

	symmalg = args.symmalg
	input = args.input	
	msgbitarray = bitarray.bitarray()
	msgbitarray.fromstring(input)
	
	# Check min size
	if (msgbitarray.length() < blocksize):
		print 'Extending input to minimum block size ' + str(blocksize)
		#print 'Before: '+str(msgbitarray.tolist())
		msgbitarray.extend(bitarray.bitarray('0')*abs(msgbitarray.length() - blocksize))
		#print 'After: '+str(msgbitarray.tolist())
		
	
	# Padding
	if(msgbitarray.length() % blocksize != 0):
		print 'Padding input to block size ' + str(blocksize)
		#print("Before %s..." % msgbitarray.tolist())
		msgbitarray.extend(bitarray.bitarray('0')*(msgbitarray.length() % blocksize))
		#print("After: %s." % msgbitarray.tolist())
	

	# Keys
	if symmalg == "des":
		key = MyDES.genKey()

	# Mother key
	keybitarray = bitarray.bitarray()
	keybitarray.frombytes(key)

	# Subkeys
	if symmalg == "des":
		subkeys = MyDES.genSubKeysEnc(keybitarray)

	# per each block
	index = 0
	while(msgbitarray.length() > index):
		#feistel structure
		msgbitarray[index:index+blocksize] = feistel(symmalg,msgbitarray[index:index+blocksize], rounds, subkeys)
		index = index + blocksize

	with open("temp.key", 'wb') as output:
    		output.write(keybitarray.tobytes())

	with open("temp.msg", 'wb') as output:
    		output.write(msgbitarray.tobytes())

	
	print ("Ready to send data to %s" % h2.IP())
	# Attacker h3 will be sniffing the communication between h1 and h2
	h2.cmd("sudo service apache2 start")

	print ("Apache2 started on %s..." % h2.IP())
	print ("Attacker %s is sniffing the connection..." % h3.IP())

	print h1.cmd('curl -F "symmalg='+symmalg+'" -F "key=@temp.key" -F "msg=@temp.msg" %s/feistelserver.py' % h2.IP())
	h2.cmd("sudo service apache2 stop")


	os.remove("temp.key")
	os.remove("temp.msg")
	