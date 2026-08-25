#include "parser.h"

auto Parser::parseHelo(std::string &msg) -> Response& {
	
}

auto Parser::parseFrom(std::string &msg) -> Response& {
	auto isQuit = parseQuit(msg);
	if(isQuit.getCode() == 221){
		return isQuit;
	}

	auto mail_command = parse_mail_command(msg);
	if(mail_command.getCode() != 220){
		return mail_command;
	}

	auto reverse_path = parse_path(msg);
	return reverse_path;
}

auto Parser::parseRcpt(std::string &msg) -> Response& {
	auto isQuit = parseQuit(msg);
	if(isQuit.getCode() == 221){
		return isQuit;
	}

	auto rcpt_command = parse_rcpt_command(msg);
	if(rcpt_command.getCode() != 220){
		return rcpt_command;
	}

	auto forward_path = parse_path(msg);
	return forward_path;
}

auto Parser::parseQuit(std::string &msg) -> Response& {
	if(msg.find("QUIT") != std::string::npos){
		Response q(221, "Service closing transmission channel");
		return q;
	}
	Response r(-1, "Not a QUIT message.");
	return r;
}

auto Parser::

auto Parser::parse_mail_command(std::string &msg) -> Response& {
	// TODO: implement
	if(parseRcpt(msg).getCode() == 220 || parseData(msg).getCode() == 354){
		Response e(503, "Invalid sequence of commands.");	
		return e;
	}

	std::string mail = "MAIL";
	Response fail(500, "Command not recognized.");
	for(uint8_t i = 0; i < 4; i++){
		if(msg[i] != mail[i]){
			return fail;
		}
	}

	size_t index = 0;
	Response &whitespace = parse_whitespace(msg, index);
	if(whitespace.getCode() != 220){
		return fail;
	}

	std::string from = "FROM";
	for(uint8_t i = 0; i < 4; i++){
		if(msg[i+index] != from[i]){
			return fail;
		}
		++index;
	}
	Response& nullspace = parse_nullspace(msg, index);
}

auto Parser::parse_path(std::string &msg) -> Response &{
	
}

auto Parser::parse_nullspace(std::string &msg, size_t &index) -> Response &{
	parse_whitespace(msg, index);
	return index;
}

auto Parser::parse_whitespace(std::string &msg, size_t &index) -> Response& {
	Response fail(550, "Command not recognized.");
	Response success(250, "OK");
	if(msg[index] != ' ' || msg[index] != '\t'){
		return fail;
	}
	for(size_t i = 0; i < msg.size() - index; i++){
		if(msg[i + index] != ' ' || msg[i+index] != '\t'){
			return success;
		}
	}
	return success;
}
