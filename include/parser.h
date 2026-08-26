#pragma once

#include <iostream>
// #include <stdlib>
#include <string>
#include "response.h"

class Parser {
	
	public:
		Response &parseHelo(std::string &msg);
		Response &parseFrom(std::string &msg);
		Response &parseRcpt(std::string &msg);
		Response &parseQuit(std::string &msg);
		std::string trim_trailing_whitespace(std::string &msg);
	private:
		Response &parse_mail_command(std::string &msg);
		Response &parse_path(std::string &msg);
		Response &parse_nullspace(std::string &msg);


};
