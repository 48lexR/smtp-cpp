#pragma once

#include <iostream>
// #include <stdlib>
#include <string>
#include <cstdint>
#include "result.h"

class Parser {	
	
	public:
		Result parseHelo(std::string msg);
		Result parseFrom(std::string msg);
		Result parseRcpt(std::string msg);
		Result parseQuit(std::string msg);
		Result parseData(std::string msg);
		Result parse_mail_command(std::string msg);
		Result parse_rcpt_command(std::string msg);
		std::string trim_trailing_whitespace(std::string &msg);
		Result parse_path(std::string msg, size_t index);
		Result parse_nullspace(std::string msg, size_t &index);
		Result parse_whitespace(std::string msg, size_t &index);
	private:

		

};
