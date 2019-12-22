//
// Created by arye on 15/12/2019.
//

#include <strings.h>
#include "OpenDataServerCommand.h"
using namespace std;

void *OpenDataServerCommand::readFromServer(int loops, int condition) {
  return nullptr;
}

double OpenDataServerCommand::execute() {
//  //create socket
//  unsigned  short int portl = 5400;
//  struct sockaddr_in serv_address{}, client_adress{};
//
//  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
//
//  if (socketfd == -1) {
//    //error
//    cerr << "Could not create a socket"<<endl;
//    return -1;
//  }
//  //bind socket to IP address
//  ; //in means IP4
//  bzero((char *) &serv_address, sizeof(serv_address));
//  serv_address.sin_family = AF_INET;
//  serv_address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
//  serv_address.sin_port = htons(portl);
//
//
//
//  //TODO
//  //we need to convert our number
//  // to a number that the network understands.
//
//
//  //the actual bind command
//  if (bind(socketfd, (struct sockaddr *) &serv_address, sizeof(serv_address)) == -1) {
//    cerr<<"Could not bind the socket to an IP"<<endl;
//    return -2;
//  }
//
//  //making socket listen to the port
//  if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max
//    // connections)
//    cerr<<"Error during listening command"<<endl;
//    return -3;
//  } else {
//    cout<<"Server is now listening ..."<<endl;
//  }
//
//  // accepting a client
//  int clientLength = sizeof(client_adress);
//  int client_socket = accept(socketfd, (struct sockaddr *)&client_adress,
//      (socklen_t*)&clientLength);
//  if (client_socket == -1) {
//    cerr<<"Error accepting client"<<endl;
//    return -4;
//  } else {
//    cout<<"accepted ..."<<endl;
//  }
//
//  //TODO
//  //thread data_server_thread(readFromServer, 5, 0);
//
//  //reading from client
//  while (true) {
//    char buffer[1024] = {0};
//    int valread = read(client_socket, buffer, 1024);
//    cout << buffer << endl;
//  }
//
//  close(socketfd); //closing the listening socket
//  cout<<"Socket Closed ..."<<endl;
//  //writing back to client
//  //char *hello = "Hello, I can hear you! \n";
//  //send(client_socket , hello , strlen(hello) , 0 );
//  //std::cout<<"Hello message sent\n"<<std::endl;
//  return 0;

return 0;
}

void OpenDataServerCommand::setParameters(vector<string> params) {
  this->port_string = params[0];
}
