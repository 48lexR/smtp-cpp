#include "parser.h"

namespace smtp {
auto Parser::ParseHelo(std::string msg) -> struct Result {
	if(msg.find("HELO") != 0){
		return Result(ERR_UNKNOWN, "");
	}
  std::string domain = parse_domain(msg);
  return Result(VALID, "");
}

auto Parser::ParseFrom(std::string msg) -> Result {
  return NULL;
}

auto Parser::ParseRcpt(std::string msg) -> Result {
  return NULL;
}

auto Parser::ParseData(std::string msg) -> Result {
	if(trim_trailing_whitespace(msg).compare("DATA")){
		return Result(ERR_CMD, "");
	}
	return Result(VALID, "");
}

auto Parser::ParseQuit(std::string msg) -> struct Result {
	if(msg.find("QUIT") != std::string::npos){	
		return Result(VALID, "");
	}
	return Result(ERR_CMD, "");
}

auto Parser::parse_mail_command(std::string msg) -> Result {}

auto Parser::parse_rcpt_command(std::string msg) -> Result {}

auto Parser::parse_data_command(std::string msg) -> Result {}

auto Parser::trim_trailing_whitespace(std::string &msg) -> std::string {
	std::string WHITESPACE = "\r\n";
	size_t end = msg.find_last_not_of(WHITESPACE);
	return msg.substr(0, end + 1);
}

} // namespace stmp
