import socket
import os
import time

SEPARATOR = "<SEPARATOR>"
BUFFER_SIZE = 1024 
host = "127.0.0.1"
port = 5001

filename = input("Enter orginal html name with .html: ")
filesize = os.path.getsize(filename)


s = socket.socket()
print(f"[+] Trying to connect to {host}:{port}")
s.connect((host, port))
print("[+] Connected.")

notunique=True 
while notunique:
    distname=input("domain name  -")
    s.send(f"{distname}{SEPARATOR}".encode())
    received = s.recv(BUFFER_SIZE).decode()
    isunique = received.split(SEPARATOR)[0]
    if isunique == "YES" :
        notunique =False
        print("yes is unique")
    else:
        print("not unique try again ")
# start sending the file
s.send(f"{filesize}{SEPARATOR}".encode())
discard=s.recv(BUFFER_SIZE)
remsize =filesize

f=open(filename,"rb")
isremaining =True
while isremaining:
    if remsize>0 and remsize >=BUFFER_SIZE :
        bytes_read = f.read(BUFFER_SIZE)
        remsize-=BUFFER_SIZE
        s.send(bytes_read)
    elif remsize >0 and remsize <BUFFER_SIZE:
        bytes_read = f.read(remsize)
        s.send(bytes_read)
        remsize=0
        f.close()
        isremaining=False

f.close()
#time.sleep(1)
iscss =input("Do you need css file (y/n) :")
if iscss == 'n' or iscss == 'N':
    s.send(f"NO{SEPARATOR}".encode())
else :
    s.send(f"YES{SEPARATOR}".encode())
    filename = input("enter orginal css name with .css: ")
    filesize = os.path.getsize(filename)
    s.send(f"{filename}{SEPARATOR}{filesize}{SEPARATOR}".encode())
    remsize =filesize
    discard=s.recv(BUFFER_SIZE)
    f=open(filename,"rb")
    isremaining =True
    while isremaining:
        #print(f'{remsize} {filesize}')
        if remsize>0 and remsize >=BUFFER_SIZE :
            bytes_read = f.read(BUFFER_SIZE)
            remsize-=BUFFER_SIZE
            s.send(bytes_read)
            #print("here1")
        elif remsize >0 and remsize <BUFFER_SIZE:
            bytes_read = f.read(remsize)
            s.send(bytes_read)
            remsize=0
            f.close()
            isremaining=False
            #print("here2")
    f.close()
#print("kooi")
received = s.recv(BUFFER_SIZE).decode()
link = received.split(SEPARATOR)[0]
print("link : ",end="")
print(link)
input("ENTER to exit")
s.close()

