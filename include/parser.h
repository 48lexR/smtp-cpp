#pragma once

#include <iostream>
// #include <stdlib>
#include <string>
#include <cstdint>
#include "result.h"

namespace smtp {

/** Enum to identify types of messages */
enum MESSAGE_TYPE {
  INVALID,
  MAIL,
  RCPT,
  DATA,
  QUIT
};

/** Error codes ot pass up errors to the SocketManager*/
enum ERROR_CODE {
  VALID,
  ERR_UNK,
  ERR_CMD,
  ERR_ARG
};

/** Helper class to pass messages up to the SocketManager */
class Result {

public:
  Result(ERROR_CODE code, std::string message): code_(code), message_(message){}
  ERROR_CODE getCode(){ return code_; }
  std::string getMessage(){ return message_; };
private:
  ERROR_CODE code_;
  std::string message_;

};

/** The actual meat and potatoes of the Parser class */
class Parser {

public:
  Result ParseCommand(std::string msg);
  Result ParseHelo(std::string msg);
  Result ParseFrom(std::string msg);
  Result ParseRcpt(std::string msg);
  Result ParseQuit(std::string msg);
  Result ParseData(std::string msg);

private:
  Result parse_mail_command(std::string msg);
  Result parse_rcpt_command(std::string msg);
  std::string trim_trailing_whitespace(std::string &msg);
  Result parse_path(std::string msg, size_t index);
  Result parse_nullspace(std::string msg, size_t &index);
  Result parse_whitespace(std::string msg, size_t &index);

};

} // namespace smtp
