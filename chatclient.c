/* Name: Xavier Hollingsworth
** Date: 7/26/19
** Description: A client-server application written in C and Python
** Sources: Beej's Guide
*/

#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>

// Function to create address information
struct addrinfo *getAddress(char *address, char *port)
{
  struct addrinfo hints;
  struct addrinfo *server;
  int status;

  // First make sure the struct is empty
  memset(&hints, 0, sizeof(hints));

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM; // TCP Stream

  status = getaddrinfo(address, port, &hints, &server);
  // Pulled straight from Beej's Guide for handling an error
  if (status != 0)
  {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }
  return server;
}

// This function is also pulled straight from Beej's Guide on page 24. Here we simply create a socket and make sure it is created. An error is displayed if not.
int createSocket(struct addrinfo *server)
{
  // Socket file descriptor
  int socketfd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);

  if(socketfd == -1)
  {
    fprintf(stderr, "Socket not created.\n");
    exit(1);
  }
  
  return socketfd;
}

// Same as function above except we are connecting the socket now
void connectSocket(int socketfd, struct addrinfo *connection)
{

  int connectionStatus = connect(socketfd, connection->ai_addr, connection->ai_addrlen);
  // Check to see if there was an error connecting and if not return connection status
  if(connectionStatus== -1)
  {
    fprintf(stderr, "Socket connection failed.\n");
    exit(1);
  }
}

int chat(int socketfd, char *client, char *server)
{
  // Buffers
  char inputBuffer[500];
  char outputBuffer[500];

  // Clear stdin
  fgets(inputBuffer, sizeof(inputBuffer), stdin);

  while(1)
  {
    // Clear the buffers
    memset(inputBuffer, 0, sizeof(inputBuffer));
    memset(outputBuffer, 0, sizeof(outputBuffer));

    // Print client's name to terminal
    printf("%s> ", client);
    // Retrieve input
    fgets(inputBuffer, sizeof(inputBuffer), stdin);

    // If user enters quit the chat will terminate
    if(strcmp(inputBuffer, "\\quit\n") == 0)
    {
      break;
    }


    // Get number of bytes being sent
    int numBytes = send(socketfd, inputBuffer, strlen(inputBuffer), 0);
    if(numBytes == -1)
    {
      fprintf(stderr, "Data not sent correctly.\n");
      exit(1);
    }

    // Check for receiving errors
    int receivingStatus = recv(socketfd, outputBuffer, 500, 0);
    if(receivingStatus == -1)
    {
      fprintf(stderr, "Data not received correctly.\n");
      exit(1);
    }

    else if(receivingStatus == 0)
    {
      printf("Connection has been terminated by the server.\n");
      break;
    }
    else
    {
      printf("%s> %s\n", server, outputBuffer);
    }

  }

  close(socketfd);
  printf("Connection closed.\n");
}

// This function preserves the client's and server's names for the chat
void saveState(int socketfd, char *clientname, char *servername)
{
  int client = send(socketfd, clientname, strlen(clientname), 0);
  int server = recv(socketfd, servername, 10, 0);

}





int main(int argc, char *argv[]) {
  char clientHandle[10];
  char serverHandle[10];

  // Error checking for 3 arguments [command] [server] [port]
  if (argc != 3)
  {
    fprintf(stderr, "Incorrect usage. Try ./chatcliet <server address> <port nubmer>\n");
    exit(1);
  }
  
  // Retrieve client user name
  printf("Enter a handle that is less than 10 characters in length.\n");
  scanf("%s", clientHandle);
  
  // Loop until handle is less than 10 characters
  while(strlen(clientHandle) > 10)
  {
  	printf("Handle too long. Make sure it is less than 10 characters in length: ");
	scanf("%s", clientHandle);
  }

  struct addrinfo *server = getAddress(argv[1], argv[2]);
  int socketfd = createSocket(server);
  connectSocket(socketfd, server);

  saveState(socketfd, clientHandle, serverHandle);
  chat(socketfd, clientHandle, serverHandle);

  freeaddrinfo(server);


}
