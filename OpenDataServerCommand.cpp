//
// Created by arye on 15/12/2019.
//

#include <strings.h>
#include "OpenDataServerCommand.h"
#include <mutex>

using namespace std;

static DataBase *data = DataBase::getInstance();

void *OpenDataServerCommand::readFromServer(int *soket) {
  //reading from client
  while (data->getIsRunning() && data->getInstance() != nullptr) {
    char buffer[1024] = {0};
    int valread = read(*soket, buffer, 1024);
    string sim_line(buffer, valread);
    if (data->sim_var_map_lock.try_lock() && data->in_var_map_lock.try_lock()
        && data->getInstance() != nullptr) {
      data->setSimData(sim_line);
    }
  }
  cout << "thread of opening data server ended" << endl;
  return nullptr;
}

double OpenDataServerCommand::execute() {
  //create socket
  struct sockaddr_in serv_address{}, client_adress{};
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) {
    //error
    cerr << "Could not create a socket" << endl;
    return -1;
  }
  
  //bind socket to IP address
  bzero((char *) &serv_address, sizeof(serv_address));
  serv_address.sin_family = AF_INET;
  serv_address.sin_addr.s_addr =
      INADDR_ANY; //give me any IP allocated for my machine
  serv_address.sin_port = htons(this->port);
  
  //the actual bind command
  if (bind(socketfd, (struct sockaddr *) &serv_address, sizeof(serv_address))
      == -1) {
    cerr << "Could not bind the socket to an IP" << endl;
    return -2;
  }

  //making socket listen to the port
  if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max
    // connections)
    cerr << "Error during listening command" << endl;
    return -3;
  } else {
    cout << "Server is now listening ..." << endl;
  }

  // accepting a client
  int clientLength = sizeof(client_adress);
  this->client_socket = accept(socketfd, (struct sockaddr *) &client_adress,
                               (socklen_t *) &clientLength);
  this->client_socket_pointer = &client_socket;
  if (this->client_socket == -1) {
    cerr << "Error accepting client" << endl;
    return -4;
  } else {
    cout << "accepted ..." << endl;
  }

  thread data_server_thread(readFromServer, client_socket_pointer);
  data_server_thread.detach();
  return 0;
}

void OpenDataServerCommand::setParameters(vector<string> params) {
  this->port_string = params[1];
  MathInterpreter *m = new MathInterpreter(DataBase::getInstance()->getInVarMap());
  Expression* e = m->interpret(this->port_string);
  this->port = e->calculate();
  delete e;
  delete m;
}

OpenDataServerCommand::~OpenDataServerCommand() {
  close(this->client_socket);
}
