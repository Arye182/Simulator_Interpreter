//
// Created by miri on 26.12.2019.
//

#ifndef SIMULATOR_INTERPRETER__CONNECTCOMMAND_H_
#define SIMULATOR_INTERPRETER__CONNECTCOMMAND_H_

#include "Command.h"
#include <iostream>
#include <sys/socket.h>
#include "DataBase.h"
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <pthread.h>

class ConnectCommand : public Command {
  string host_address;
  unsigned short port;
  int client_socket;

 public:
  ConnectCommand();
  void setParameters(vector<string> param) override;
  double execute() override;
  static void *sendToSim(int *socket);
  ~ConnectCommand() override;
};

#endif //SIMULATOR_INTERPRETER__CONNECTCOMMAND_H_
