import hashlib
import os
import bitarray

class MyDES():
	IPtable = (58, 50, 42, 34, 26, 18, 10, 2,
           60, 52, 44, 36, 28, 20, 12, 4,
           62, 54, 46, 38, 30, 22, 14, 6,
           64, 56, 48, 40, 32, 24, 16, 8,
           57, 49, 41, 33, 25, 17,  9, 1,
           59, 51, 43, 35, 27, 19, 11, 3,
           61, 53, 45, 37, 29, 21, 13, 5,
           63, 55, 47, 39, 31, 23, 15, 7)

	EPtable = (32,  1,  2,  3,  4,  5,
            4,  5,  6,  7,  8,  9,
            8,  9, 10, 11, 12, 13,
           12, 13, 14, 15, 16, 17,
           16, 17, 18, 19, 20, 21,
           20, 21, 22, 23, 24, 25,
           24, 25, 26, 27, 28, 29,
           28, 29, 30, 31, 32,  1)

	FPtable = (40, 8, 48, 16, 56, 24, 64, 32,
           39, 7, 47, 15, 55, 23, 63, 31,
           38, 6, 46, 14, 54, 22, 62, 30,
           37, 5, 45, 13, 53, 21, 61, 29,
           36, 4, 44, 12, 52, 20, 60, 28,
           35, 3, 43, 11, 51, 19, 59, 27,
           34, 2, 42, 10, 50, 18, 58, 26,
           33, 1, 41,  9, 49, 17, 57, 25)

	PC1table = (57, 49, 41, 33, 25, 17,  9,
                 1, 58, 50, 42, 34, 26, 18,
                10,  2, 59, 51, 43, 35, 27,
                19, 11,  3, 60, 52, 44, 36,
                63, 55, 47, 39, 31, 23, 15,
                 7, 62, 54, 46, 38, 30, 22,
                14,  6, 61, 53, 45, 37, 29,
                21, 13,  5, 28, 20, 12,  4)
 
    	PC2table= (14, 17, 11, 24,  1,  5,  3, 28,
               15,  6, 21, 10, 23, 19, 12,  4,
               26,  8, 16,  7, 27, 20, 13,  2,
               41, 52, 31, 37, 47, 55, 30, 40,
               51, 45, 33, 48, 44, 49, 39, 56,
               34, 53, 46, 42, 50, 36, 29, 32)

	sBox = 8*[64*[0]]
 
	sBox[0] = (14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
            0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
            4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
           15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13)
 
	sBox[1] = (15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
            3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
            0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
           13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9)
 
	sBox[2] = (10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
           13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
           13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
            1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12)
 
	sBox[3] = ( 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
           13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
           10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
            3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14)
 
	sBox[4] = ( 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
           14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
            4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
           11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3)
 
	sBox[5] = (12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
           10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
            9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
            4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13)
 
	sBox[6] = ( 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
           13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
            1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
            6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12)
 
	sBox[7] = (13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
            1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
            7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
            2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11)

	PFtable = (16,  7, 20, 21, 29, 12, 28, 17,
            1, 15, 23, 26,  5, 18, 31, 10,
            2,  8, 24, 14, 32, 27,  3,  9,
           19, 13, 30,  6, 22, 11,  4, 25)

	def foo(self):
		print('Hello, World')

	@staticmethod
	def IP(block):
		out = bitarray.bitarray()
		for pos in MyDES.IPtable:
			out.append(block[pos-1])
		return out

	@staticmethod
	def FP(block):
		out = bitarray.bitarray()
		for pos in MyDES.FPtable:
			out.append(block[pos-1])
		return out

	@staticmethod
	def genKey():
		p = "123456"
		s = os.urandom(8)
		c = 100
		dkLen = 8
		hash = "SHA-1"
		return MyDES.PBKDF1(p, s, c, dkLen, hash)

	@staticmethod
	def PBKDF1(p, s, c, dkLen, hash):
		if (dkLen > 16 and hash == "MD5") or (dkLen > 20 and hash == "SHA-1"):
			print "derived key too long"
			return -1

		i = 0
		temp = p+s
		while(i < c):
			if hash == "MD5":
				temp = hashlib.md5(temp).digest()
			elif hash == "SHA-1":
				temp = hashlib.sha1(temp).digest()
			i += 1

		return temp[0:dkLen]

	@staticmethod	
	def genSubKeysEnc(keybitarray):
		subkeys = list()
		newkeybitarray = MyDES.PC1(keybitarray)
		lefthalf = newkeybitarray[0:newkeybitarray.length()/2]
		righthalf = newkeybitarray[newkeybitarray.length()/2:newkeybitarray.length()]

		i = 0
		while(i < 16):
			tempcount = 0
			# only shift left once
			if i+1 == 1 or i+1== 2 or i+1 == 9 or i+1 == 16:
				#"{0:b}".format(int(a.to01(),2)).zfill(8)
				newkeybitarray[0:newkeybitarray.length()/2] = bitarray.bitarray("{0:b}".format(MyDES.rol(int(lefthalf.to01(),2),1,newkeybitarray.length()/2)).zfill(newkeybitarray.length()/2))
				newkeybitarray[newkeybitarray.length()/2:newkeybitarray.length()] = bitarray.bitarray("{0:b}".format(MyDES.rol(int(righthalf.to01(),2),1,newkeybitarray.length()/2)).zfill(newkeybitarray.length()/2))
			# shift left twice
			else:
				newkeybitarray[0:newkeybitarray.length()/2] = bitarray.bitarray("{0:b}".format(MyDES.rol(int(lefthalf.to01(),2),2,newkeybitarray.length()/2)).zfill(newkeybitarray.length()/2))
				newkeybitarray[newkeybitarray.length()/2:newkeybitarray.length()] = bitarray.bitarray("{0:b}".format(MyDES.rol(int(righthalf.to01(),2),2,newkeybitarray.length()/2)).zfill(newkeybitarray.length()/2))
			subkeys.append(MyDES.PC2(newkeybitarray))
			i += 1

		return subkeys
		
	@staticmethod
	def PC1(keybitarray):
		out = bitarray.bitarray()
		for pos in MyDES.PC1table:
			out.append(keybitarray[pos-1])
		return out

	@staticmethod
	def PC2(subkeybitarray):
		out = bitarray.bitarray()
		for pos in MyDES.PC2table:
			out.append(subkeybitarray[pos-1])
		return out

	@staticmethod
	def functionf(hblockbitarray,subkeybitarray):
		# Expansion
		expandedblock = bitarray.bitarray()
		for pos in MyDES.EPtable:
			expandedblock.append(hblockbitarray[pos-1])

		# Key mixing
		expandedblock = expandedblock ^ subkeybitarray
		
		# Substitution
		k = 0
		ff = 0
		substitutedblock = bitarray.bitarray()
		while(k < 48): 
			substitutedblock[ff:ff+4] = bitarray.bitarray("{0:b}".format(MyDES.extractfromsBox(MyDES.sBox[k/6],expandedblock[k:k+6])).zfill(4))
				
			k = k + 6
			ff = ff + 4

		# Permutation
		permutatedblock = bitarray.bitarray()
		for pos in MyDES.PFtable:
			permutatedblock.append(substitutedblock[pos-1])

		return permutatedblock

	@staticmethod
	def extractfromsBox(sboxtuple,sixbitblock):
		row = (bitarray.bitarray(str(int(sixbitblock[0]))) ^ bitarray.bitarray('0')) + (bitarray.bitarray(str(int(sixbitblock[5]))) ^ bitarray.bitarray('0'))
		yindex = 16*int(row.to01(),2)

		column = (sixbitblock[1:5] ^ bitarray.bitarray('0000'))
		xindex = int(row.to01(),2)

		return sboxtuple[yindex+xindex]
		

	# Rotate left: 0b1001 --> 0b0011
	rol = staticmethod(lambda val, r_bits, max_bits: \
	    (val << r_bits%max_bits) & (2**max_bits-1) | \
	    ((val & (2**max_bits-1)) >> (max_bits-(r_bits%max_bits))))
	 
	# Rotate right: 0b1001 --> 0b1100
	ror = staticmethod(lambda val, r_bits, max_bits: \
	    ((val & (2**max_bits-1)) >> r_bits%max_bits) | \
	    (val << (max_bits-(r_bits%max_bits)) & (2**max_bits-1)))
