TCP chat client program that allows a client and server to exchange messages

#Execute server
You can run the server by typing the folllowing command in terminal:
	python chatserve.py <port number>

the port number is the port you want the communication to occur at
an example is:
	python chatserve.py 60001

#Compile client program
Run the following command to compile the client program:
	make client

#Run client
Now you can run the client program. To do so include the hostname of the server program and the server port number.
	./chatclient <hostname> <port number>

For example I ran it on the flip1 servers so I would type:
	./chatclient flip1.engr.oregonstate.edu 60001

#Terminate
Type \quit to terminate the chat program
