#ifndef SERVER_H_
#define SERVER_H_

#include <string>
#include <vector>
#include "connection_manager.h"
#include "parser.h"

namespace smtp {

  typedef unsigned short port_t;

  enum SERVER_STATE {
    INITIAL,
    TRANSATION,
    MAIL_RECVD,
    DATA,
    QUIT_RECVD
  };

  enum COMMAND_TYPE {
    INVALID_COMMAND,
    INVALID_ARGS,
    INVALID_ORDER,
    INITIAL,
    HELO_RECVD,
    MAIL_RECVD,
    RCPT_,
    DATA,
    DATA_LINE,
    QUIT
  };

  class Server{
  public:
    Server(port_t port, std::string hostname): port_(port), hostname_(hostname){
      connection_manager_(port_, hostname_);
      state_ = INITIAL;
    };
    void Run();
    void Send(COMMAND_TYPE command_type, std::string message);
    Result Receive();

  private:
    port_t port_;
    std::string hostname_;
    ConnectionManager connection_manager_;
    Parser parser_;
    SERVER_STATE state_;
    std::string mail_from_buffer_;
    std::vector<std::string> rcpt_to_buffer_;
    std::string data_buffer_;
  }
} // namespace smtp

#endif // SERVER_H_
