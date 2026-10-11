#include "server.h"

/**
 * The server class
 * It handles the SMTP logic and writes the output to a regular file
 */ 

namespace smtp {

  auto Server::Run(){
    while(true){
      Result recvd_message = Receive(); // calls the c.m. to get our line and the parser to parse it.
      switch state_{
      case INITIAL:
        // failure
        Send(recvd_message.type, recvd_message.hostname); // e.x. "HELO <domain>, It's nice to meet you."
        if (recvd_message.type == HELO) {
          // success
          state_ = HELO_RECVD;
        }
        break;
      case HELO_RECVD:
        Send(recvd_message.type, recvd_message.hostname); // e.x. "220 OK"
        break;
      case MAIL_RECVD:
        break;
      case DATA:
        break;
      case QUIT_RECVD:
        break;
      default:
        break;
      }
      std::string client_hostname = connection_manager_.receive();
    }
  }

  Server::Send(code_t code, std::string message){

  }

  Result Receive(){
    std::string message = connection_manager_.GetMessage();
    Result res = parser_.Parse(message);
  }

} // namespace smtp
