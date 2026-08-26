#include <iostream>
#include "parser.h"
#include "response.h"
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

/**
 * The server class
 * It handles the SMTP logic and writes the output to a regular file
 */ 
class Server {
	// static constexpr uint16_t BUF_SIZ = 1024;

	public: 
		Server(uint16_t port): port_(port) {}
		// Returns an error code w/ information on failuer
		// 0 on success
		int run(){
			std::cerr << "Server is starting." << std::endl;

			int sock = socket(
					AF_INET,
					SOCK_STREAM,
					0);
			if(sock < 0){
				std::cerr << "Socket failed." << std::endl;
				return 1;
			}

			sockaddr_in address;
			address.sin_family = AF_INET;
			address.sin_port = htons(port_);
			address.sin_addr.s_addr = INADDR_ANY;

			if(bind(sock, 
					(struct sockaddr *) &address,
					sizeof(address)
				 ) < 0 ){
				std::cerr << "FAILED TO BIND TO SOCKET. EXITING." << std::endl;
				close(sock);
				return 1;
			}

			
			if(listen(sock, 5) < 0){
				std::cerr << "FAILED TO LISTEN. EXITING." << std::endl;
				close(sock);
				return 1;
			}
			std::cerr << "Listening on port " << port_ << std::endl;
			while(true){	
				int client_sock = accept(
						sock,
						nullptr,
						nullptr
						);
				std::cerr << "Accepted connection." << std::endl;
				while(true) {
					char buf[1024] = { 0 };
					recv(client_sock, buf, 1024, 0);
					std::string str(buf);
					str = parser.trim_trailing_whitespace(str);
					std::cerr << str << std::endl;
					if(str.compare(std::string("QUIT"))){
						break;
					}
				}
				close(client_sock);
			}
			close(sock);
			return 0; 

		}

		int write_to_file(std::string &fname, std::string &msg){
			std::ofstream f; // output fstream
			f.open(fname, std::ios_base::app); // open the file in append mode
			f << msg;
			f.close();
			std::cout << "Successfully wrote to file." << std::endl;
			return 0;
		}
	
	private:
		uint16_t port_;
		Parser parser;
};

int main(int argc, char ** argv){
	uint16_t port = argc > 1 ? atoi(argv[1]) : 8000;
	Server s(port);	
	return s.run();
}
