import sys,re
from datetime import timedelta

def splitandconvert(d,outfile):
	hr = int(d.split(':')[0])
	mint = int(d.split(':')[1])
	sec = int(d.split(':')[2].split(',')[0])
	mil = int(d.split(',')[1])

	# conversion
	d = timedelta(hours=hr,minutes=mint,seconds=sec,milliseconds=mil)

	# adjustment
	d = d+timedelta(seconds=SHIFT_SEC) if FORWARD else d-timedelta(seconds=SHIFT_SEC)

	# conversion
	d = str(d)

	# left padding zero for two digit hours (it'll never exceed 9 hours anyway)
	d = '0'+d

	# microsecond -> milliseconds (just use what you have already)
	d = re.sub("\..*",","+str(mil).zfill(3),d)
	return d

oldfile = sys.argv[1]
newfile = sys.argv[2]
FORWARD = sys.argv[3] if sys.argv[3] == "FORWARD" else False 
SHIFT_SEC = int(sys.argv[4]) if sys.argv[4] else 5


with open(newfile, 'w') as outfile, open(oldfile, 'r') as infile:
	for line in infile:
		listofts = re.findall("\d{2}:\d{2}:\d{2},\d{3}",line)

		if listofts:
			#1
			d = splitandconvert(listofts[0],outfile)
			str1 = d+" --> "

			#2
			d = splitandconvert(listofts[1],outfile)
			str2 = d

			outfile.write(str1+str2+"\n")
		else:
			outfile.write(line)

	outfile.close()
	infile.close()