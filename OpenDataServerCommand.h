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
#include "DataBase.h"


class OpenDataServerCommand : public Command {

 private:
  unsigned short port;
  string port_string;
  int client_socket;
  int *client_socket_pointer;

 public:
  OpenDataServerCommand() = default;
  ~OpenDataServerCommand() override;
  static void *readFromServer(int *socket);
  double execute() override;
  void setParameters(vector<string> params) override;
};

#endif //SIMULATUR_INTERPRETER__OPENDATASERVERCOMMAND_H_
