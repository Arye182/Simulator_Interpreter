//
// Created by arye on 15/12/2019.
//

#ifndef SIMULATUR_INTERPRETER__OPENDATASERVERCOMMAND_H_
#define SIMULATUR_INTERPRETER__OPENDATASERVERCOMMAND_H_

#include <iostream>
#include <thread>
#include <pthread.h>
#include "Command.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#define PORT 5400

class OpenDataServerCommand : public Command {

 private:
  unsigned short port;
  string port_string;
  int client_socket;
  int* client_socket_pointer;
  //short hz;

 public:
  OpenDataServerCommand() = default;
  static void* readFromServer(int* socket, int loops, int condition);
  /*
 *
 * Create a socket
 * Bind our address to a requested address
 * Listen to incoming connections
 * Accept a connection
 * Write/read to and from the socket
 * Close the socket
 *
 * */
  double execute() override;
  void setParameters(vector <string> params) override ;
};

#endif //SIMULATUR_INTERPRETER__OPENDATASERVERCOMMAND_H_
