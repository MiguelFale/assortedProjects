#!/usr/bin/python

# Turn on debug mode.
import cgi
import cgitb
import bitarray
import os
import sys

# Note that it is possible to use other symbols, such as characters, instead of bits
# Problems with OTP:
# Both parties need the OTP. How can an (always different) OTP be sent to the receptor in a safe manner? 
# How to generate true random numbers to be used as the OTPs?
# OTP's length must be at least the same as the message's, making it impractical for large messages
# Hard to manage: each OTP must be used only once, safely, and then eliminated to prevent reuse

def onetimepad(msg):
	msgbitarray = bitarray.bitarray()
	msgbitarray.fromstring(msg)

	key = os.urandom(msgbitarray.length()/8)
	keybitarray = bitarray.bitarray()
	keybitarray.fromstring(key)

	#testbitarray = bitarray.bitarray()
	#testbitarray.fromstring("ac")

	return msgbitarray ^ keybitarray
	

reload(sys)  
sys.setdefaultencoding('latin-1')
cgitb.enable()

print('Content-type: text/html\n\n')

form = cgi.FieldStorage()
if "msg" not in form:
	print('<H1>Error</H1>')
	print("Please post msg.")
else:
	print(onetimepad(form["msg"].value))