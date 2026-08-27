#include <iostream>
#include <string>
#include <unistd.h>
#include "parser.h"


class Client {
	public:

		Client(std::string server_addr,
				std::string user,
				std::string password
		      ): server_addr_(server_addr),
		user_(user), 
		password_(password) {
			std::cerr << "Client initialized." << std::endl;
		}

		Client(Client &client) = delete;

		int run() {
			std::string reverse_path;
			std::string forward_path;
			std::string cc_s;
			std::string bcc_s;
			std::string subject;
			std::string data;

			std::cout << "From:" << std::endl;
			std::cin >> reverse_path;
			std::cout << "To:" << std::endl;
			// TODO: Implement multiple paths
			std::cin >> forward_path;
			std::cout << "Cc:" << std::endl;
			std::cin >> cc_s;
			std::cout << "Bcc:" << std::endl;
			std::cin >> bcc_s;
			std::cout << "Subject:" << std::endl;
			std::cin >> subject;
			std::cout << "Message:" << std::endl;
			std::cin >> data;

			std::cerr << "Message received. Mailing now..." << std::endl;
			return 0;
		}


	private:
		std::string server_addr_;
		std::string user_;
		std::string password_;

};

int main(int argc, char ** argv){
	std::string server_addr;
	std::string user;
	std::string password;

	std::cout << "Mail client is running." << std::endl;
	std::cout << "Enter server address." << std::endl;
	std::cin >> server_addr;
	std::cout << "Enter user:" << std::endl;
	std::cin >> user;
	std::cout << "Enter password:" << std::endl;
	std::cin >> password;

	Client client(server_addr, user, password);	
	return client.run();
}
