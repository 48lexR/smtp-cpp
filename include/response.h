#pragma once
#include <stdlib>
#include <stdio>
#include <string>
#include <stdio>

class Response {
	public:
		Response(): code_(int code), msg_(std::move(msg)) {}

		std::string &getMessage() { return msg_; }

		int getCode() { return code_; }
	private:
		std::string msg_;
		int code_;
};
