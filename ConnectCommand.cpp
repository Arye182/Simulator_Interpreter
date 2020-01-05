//
// Created by miri on 26.12.2019.
//
#include "ConnectCommand.h"
#include "Lexer.h"

using namespace std;

/**
 * Ctor.
 * creates a socket.
 */
ConnectCommand::ConnectCommand() {
  this->client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    cerr << "could not create a socket" << endl;
  }
}

/**
 * sentToSim Method - it is actually the thread that sends instructions to
 * the simulator as long as the queue of instructions has pending missions to
 * execute.
 *
 * @param socket is the pointer to the socket.
 */
void *ConnectCommand::sendToSim(int *socket) {
  while (DataBase::getInstance()->getIsRunning() && DataBase::getInstance()
      != nullptr) {
    if (!(DataBase::getInstance()->getUpdateSimQueue()->empty())) {
      string assign = DataBase::getInstance()->getUpdateSimQueue()->front();
      DataBase::getInstance()->getUpdateSimQueue()->pop();
      int sent =
          static_cast <int>(write(*socket, assign.c_str(), assign.size()));
      if (sent == -1) {
        cerr << "error sending assign: " + assign + " message" << endl;
        exit(1);
      }
    }
  }
  return nullptr;
}

/**
 * setParameters of this command will update the ip adress and the port given
 * in the params.
 *
 * @param  param - includes the ip and port.
 */
void ConnectCommand::setParameters(vector<string> param) {
  MathInterpreter *m = new MathInterpreter(DataBase::getInstance()->getInVarMap());
  int p = param[1].find(',');
  string ip_address = param[1].substr(0, p).c_str();
  this->host_address = ip_address;
  string port_string = param[1].substr(p+1, param[1].length());
  Expression* e = m->interpret(port_string);
  this->port = e->calculate();
  delete e;
  delete m;
}

/**
 * the execution of connect Command is to open the communication in front of
 * the simulator and open a thread that will send instructions when needed to
 * the simulator.
 *
 * we detach the thread but we verify the function of the thread has a
 * termination.
 *
 */
double ConnectCommand::execute() {
  sockaddr_in socket_address;
  socket_address.sin_family = AF_INET;
  socket_address.sin_addr.s_addr = inet_addr(this->host_address.c_str());
  socket_address.sin_port = htons(this->port);
  int is_connect = connect(this->client_socket,
                           (struct sockaddr *) &socket_address,
                           sizeof(socket_address));
  if (is_connect == -1) {
    cerr << "could not connect to host server" << endl;
  } else {
    cout << "client is now connected to server" << endl;
  }
  // creating a thread
  thread th1(sendToSim, &client_socket);
  // detaching the thread
  th1.detach();
  return 0;
}

/**
 * Dctor.
 * closes the socket.
 *
 */
ConnectCommand::~ConnectCommand() {
  close(this->client_socket);
}
