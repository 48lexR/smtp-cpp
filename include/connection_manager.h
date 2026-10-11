#ifndef CONNECTION_MANAGER_H_
#define CONNECTION_MANAGER_H_

#include <string>
#include <vector>
#include "parser.h"

namespace smtp {
  /** The ConnectionManager will handle all of the socket I/O. It calls the parser to do the heavy lifting of... parsing */
  class ConnectionManager {
  public:
  ConnectionManager(port_t port, std::string hostname): port_(port), hostname_(hostname){ }
    // ConnectionManager(ConnectionManager &other) = delete; Will need this line for multithreading
    void Connect();
    void Send(code_t code, std::string message);
    void Receive();

  private:
    port_t port_;
    std::string hostname_;
    Parser parser_;
};

} // namespace smtp


#endif // CONNECTION_MANAGER_H_
