import socket
import os
import traceback
from threading import Thread
import signal
from sys import exit
import http.server
import socketserver
cons=-1
BUFFER_SIZE = 1024
SEPARATOR = "<SEPARATOR>"

def clientThread(client_socket, address):
	global cons
	cons+=1
	isnt_unique = True
	isnt_unique_flag=True
	while isnt_unique :
		isnt_unique_flag=False
		received = client_socket.recv(BUFFER_SIZE).decode()
		filename = received.split(SEPARATOR)[0]
		#print(filename)
		namefile=open('namefile','r+')
		for line in namefile:
			#print("line")
			if filename == line.strip():
				client_socket.send(f"NO{SEPARATOR}".encode())
				isnt_unique_flag=True
				break
		#print("herex")
		if isnt_unique_flag == False :
			namefile.write((filename))
			namefile.write("\n")
			client_socket.send(f"YES{SEPARATOR}".encode())
			isnt_unique =False
		namefile.close()
	os.mkdir((filename))
	received = client_socket.recv(BUFFER_SIZE).decode()
	#print(received)
	client_socket.send(f"discard{SEPARATOR}".encode())
	filesize = received.split(SEPARATOR)[0]
	htmlname=filename+'/index.html'
	filesize = int(filesize)

	remsize =filesize
	f=open(htmlname,"wb")
	isremaining =True
	while isremaining:
		if remsize>0 and remsize >BUFFER_SIZE :
			bytes_read = client_socket.recv(BUFFER_SIZE)
			#print(bytes_read)
			remsize-=BUFFER_SIZE
			f.write(bytes_read)
		elif remsize >0 and remsize <=BUFFER_SIZE:
			bytes_read = client_socket.recv(remsize)
			#print(bytes_read)

			f.write(bytes_read)
			remsize=0
			f.close()
			isremaining=False
				

	received = client_socket.recv(BUFFER_SIZE).decode()
	#print(received)
	iscss = received.split(SEPARATOR)[0]
	iscss_flag=False
	if iscss == "YES":
		received = client_socket.recv(BUFFER_SIZE).decode()
		#print(received)
		cssname = received.split(SEPARATOR)[0]
		filesize = received.split(SEPARATOR)[1]
		client_socket.send(f"discard{SEPARATOR}".encode())
		cssfile=filename+'/'+cssname
		filesize = int(filesize)
		remsize=filesize
		f=open(cssfile,"wb")
		isremaining =True
		#print(f'{remsize} {filesize}')
		while isremaining:
			#print(f'{remsize} {filesize}')
			if remsize>0 and remsize >BUFFER_SIZE :
				bytes_read = client_socket.recv(BUFFER_SIZE)
				remsize-=BUFFER_SIZE
				f.write(bytes_read)
			elif remsize >0 and remsize <=BUFFER_SIZE:
				bytes_read = client_socket.recv(remsize)
				f.write(bytes_read)
				remsize=0
				f.close()
				isremaining=False
				break
		f.close()
	#print("outhere")
	client_socket.send(f"127.0.0.1:8080/{filename}".encode())	
	print(f"[+] 127.0.0.1:8080/{filename} is alive , owner : {address}")
	client_socket.close()
	print(f"[+] {address} is disconnected.")		


def webserver():
	PORTI = 8080
	Handler = http.server.SimpleHTTPRequestHandler
	class QuietHandler(http.server.SimpleHTTPRequestHandler):
		def log_error(self, format, *args):
			pass
	with socketserver.TCPServer(("", PORTI), QuietHandler) as httpd:
		print("serving at port", PORTI)
		httpd.serve_forever()





SERVER_HOST = "0.0.0.0"
SERVER_PORT = 5001

if __name__ == "__main__":
	print("\t\t\t[ Server ]")
	try :
		currentpath=os.getcwd()

		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		#s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	
		s.bind((SERVER_HOST, SERVER_PORT))
	
		s.listen(5)
		print(f"[*] Listening as {SERVER_HOST}:{SERVER_PORT}")
		Thread(target=webserver).start()
	
		while True:
			client_socket, address = s.accept() 
			print(f"[+] {address} is connected.")
			try:
	  			Thread(target=clientThread, args=(client_socket, address)).start()
			except:
				print("Thread did not start.")
				#traceback.print_exc()
	except KeyboardInterrupt: s.close() ;
s.close()




