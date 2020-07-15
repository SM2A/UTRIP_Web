/*
#include <iostream>
#include "Utility/Command_Parser.hpp"

#define HOTELS_PATH 1
#define RATINGS_PATH 2

using namespace std;

int main(int argc, char *argv[]) {

	Command_Parser *parser = new Command_Parser(argv[HOTELS_PATH],argv[RATINGS_PATH]);

	string command;
	while (getline(cin, command)) {
		try {
			parser->get_command(command);
		} catch (exception &e) {
			cout << e.what() << endl;
		}
	}

	return 0;
}*/

#include <iostream>
#include "APHTTP/server/server.hpp"

using namespace std;

int main(int argc, char *argv[]) {

	try {
		Server server(8585);
		server.get("/",new ShowPage("/home/amin/Desktop/main.html"));
		server.run();
	}catch (Server::Exception &e){
		cerr<<e.getMessage()<<endl;
	} catch (exception &e) {
		cout << e.what() << endl;
	}

	return 0;
}