#pragma once
//#include <stdlib>
#include <iostream>
#include <string>
// #include <stdio>

class Response {
	public:
		Response(int code, std::string &msg): code_(code) {
			msg_ = std::string(msg);
		}

		std::string &getMessage();

		int getCode();
	private:
		std::string msg_;
		int code_;
};
