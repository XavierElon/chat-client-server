#!/usr/bin/python

import socket
import signal
import fileinput
import string
import io
import sys
from thread import *
from socket import *

# Xavier Hollingsworth
# CS 372
# Project 1
# Chatserver program that acts as the chat server for the caht program.


def chat(connection_socket, clientHandle, serverHandle):
	#Hold the message
	message = ""

	# Run until somebody terminates the chat
	while 1:
		received = connection_socket.recv(501)[0:-1]
		if received == "":
			print "Connection closed"
			break

		print "{}> {}".format(clientHandle, received)
		sending = "":
		while len(sending) > 500 or len(sending) == 0:
			sending = raw_input("{}> ".format(serverHandle))

		if sending == "\quit"
			print "Connection terminated"
			break
		connection_socket.send(sending)


def handshake(connection_socket, serverHandle):
	clientHandle = connection_socket.recv(1024)
	connection_socket.send(serverHandle)
	return clientHandle



if __name__ == "__main__":

	if len(sys.argv) != 2:
		print("Please specify a port number")
		exit(1)

	# Create new socket
	serverPort = sys.argv[1]
	serverSocket = socket(AF_INET, SOCK_STREAM)
	serverSocket.bind(('', int(serverPort)))
	serverSocket.listen(1)
	serverHandle = ""

	while len(serverHandle) == 0 or len(serverHandle) > 10:
		serverHandle = raw_input("Enter handle (10 characters or less): ")
		print("Welcome to the chat")
	while 1:
		connection_socket, connectionAddress = serverSocket.accept()
		chat(connection_socket, handshake(connnection_socket, serverHandle), serverHandle)
		connection_socket.close()
