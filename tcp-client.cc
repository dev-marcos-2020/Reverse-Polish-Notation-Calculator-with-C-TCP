#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>

#define MAX_LINE 100
#define LINE_ARRAY_SIZE (MAX_LINE+1)

using namespace std;

int main()
{
  int socketDescriptor;
  unsigned short int serverPort;
  struct sockaddr_in serverAddress;
  struct hostent *hostInfo;
  char buf[LINE_ARRAY_SIZE], c;

  cout << "Enter server host name or IP address: ";
  cin.get(buf, MAX_LINE, '\n');

  hostInfo = gethostbyname(buf);
  if (hostInfo == NULL) {
    cout << "problem interpreting host: " << buf << "\n";
    exit(1);
  }

  cout << "Enter server port number: ";
  cin >> serverPort;
  cin.get(c); // dispose of the newline

  socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socketDescriptor < 0) {
    cerr << "cannot create socket\n";
    exit(1);
  }

  serverAddress.sin_family = hostInfo->h_addrtype;
  memcpy((char *) &serverAddress.sin_addr.s_addr,
         hostInfo->h_addr_list[0], hostInfo->h_length);
  serverAddress.sin_port = htons(serverPort);
				
  if (connect(socketDescriptor,
              (struct sockaddr *) &serverAddress,
              sizeof(serverAddress)) < 0) {
    cerr << "cannot connect\n";
    exit(1);
  }

  cout << "\nEnter some lines, and the server will modify them and\n";
  cout << "send them back.  When you are done, enter a line with\n";
  cout << "just a dot, and nothing else.\n";
  cout << "If a line is more than " << MAX_LINE << " characters, then\n";
  cout << "only the first " << MAX_LINE << " characters will be used.\n\n";

  cout << "Input: ";
  cin.get(buf, MAX_LINE, '\n');
  while (cin.get(c) && c != '\n') 
    ; //Loop does nothing except consume the spare bytes


  while (strcmp(buf, ".")) {
    if (send(socketDescriptor, buf, strlen(buf) + 1, 0) < 0) {
      cerr << "cannot send data ";
      close(socketDescriptor); //Note this is just like using files...
      exit(1);
    }

    memset(buf, 0x0, LINE_ARRAY_SIZE);

    if (recv(socketDescriptor, buf, MAX_LINE, 0) < 0) {
      cerr << "didn't get response from server?";
      close(socketDescriptor);
      exit(1);
    }

    cout << "Modified: " << buf << "\n";

    cout << "Input: ";
    cin.get(buf, MAX_LINE, '\n');
    while (cin.get(c) && c != '\n')
      ; //Chomp chomp chomp
  }

  close(socketDescriptor);
  return 0;
}
