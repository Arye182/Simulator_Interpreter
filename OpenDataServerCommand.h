//
// Created by arye on 15/12/2019.
//

#ifndef EX3_ME__OPENDATASERVERCOMMAND_H_
#define EX3_ME__OPENDATASERVERCOMMAND_H_

#include <iostream>
#include <thread>
#include "Command.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>

class OpenDataServerCommand : public Command {

 private:
  unsigned short port;
  short hz;

 public:
  OpenDataServerCommand(string port, string hz);
  static void* readFromServer(void* params);
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
};

#endif //EX3_ME__OPENDATASERVERCOMMAND_H_
