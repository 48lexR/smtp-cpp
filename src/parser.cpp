#include "parser.h"

auto Parser::parseHelo(std::string msg) -> Result {	
	if(msg.find("HELO") != 0){
		return Result(-1, "");
	}
	// TODO: Get the domain out of the HELO message
	return Result(0, "Hello");	
}


auto Parser::parseQuit(std::string msg) -> Result {
	if(msg.find("QUIT") != std::string::npos){	
		return Result(0, "Service closing transmission channel");
	}	
	return Result(-1, "");
}

auto Parser::parse_rcpt_command(std::string msg) -> Result {
	// TODO: implement
	Result fail(-1, "Command not recognized");

	std::string rcpt("RCPT");
	for(uint8_t i = 0; i < 4; i++){
		if(msg[i] != rcpt[i]){
			return fail;
		}
	}

	size_t index = 4;
	Result whitespace = parse_whitespace(msg, index);
	if(whitespace.getCode()){
		return fail;
	}

	std::string to("TO:");
	for(uint8_t j = 0; j < 3; j++){
		if(to[j] != msg[index]){
			return fail;	
		}
		++index;
	}

	Result path = parse_path(msg, index);
	return path;
}

auto Parser::parse_mail_command(std::string msg) -> Result {
	// TODO: implement
	Result fail(-1, "Command not recognized");

	std::string mail = "MAIL";		
	for(uint8_t i = 0; i < 4; i++){
		if(msg[i] != mail[i]){
			return fail;
		}
	}

	size_t index = 4;
	Result whitespace = parse_whitespace(msg, index);
	if(whitespace.getCode()){
		return fail;
	}

	std::string from = "FROM:";
	for(uint8_t i = 0; i < 5; i++){
		if(msg[index] != from[i]){
			return fail;
		}
		++index;
	}
	Result nullspace = parse_nullspace(msg, index);
	Result path = parse_path(msg, index);
	return path;
}

auto Parser::parse_path(std::string msg, size_t index) -> Result {
	// TODO: Implement
	if(msg[index] != '<'){
		return Result(-1, "");
	}

	return Result(0, "");
}

auto Parser::parse_nullspace(std::string msg, size_t &index) -> Result {
	parse_whitespace(msg, index);
	return Result(250, "");
}

auto Parser::parse_whitespace(std::string msg, size_t &index) -> Result {
	Result fail(-1, "");
	Result success(0, "OK");
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

auto Parser::trim_trailing_whitespace(std::string &msg) -> std::string {
	std::string WHITESPACE = "\r\n";
	size_t end = msg.find_last_not_of(WHITESPACE);
	return msg.substr(0, end + 1);
}

auto Parser::parseData(std::string msg) -> Result {
	if(trim_trailing_whitespace(msg).compare("DATA")){
		return Result(0, "");
	}
	return Result(-1, "Data command received. Please end with ."); 
}
