#include <iostream>
#include "Utility/Handler.hpp"
#include "APHTTP/server/server.hpp"
#include "UTRIP/UTrip.hpp"

#define HOTELS_PATH 1
#define RATINGS_PATH 2

using namespace std;

int main(int argc, char *argv[]) {

	try {
		Server server(1379);
		//todo file path
		UTrip* utrip = new UTrip(argv[HOTELS_PATH],argv[RATINGS_PATH]);
		server.get("/",new Home(utrip));
		server.get("/login",new Static(utrip,"/home/amin/CLionProjects/A7/Src/Pages/Login.html"));
		server.post("/login",new Login(utrip));
		server.get("/logout",new Logout(utrip));
		server.post("/signup",new Signup(utrip));
		server.get("/signup",new Static(utrip,"/home/amin/CLionProjects/A7/Src/Pages/Signup.html"));
		server.get("/hotel",new Description(utrip));
		server.get("/filter",new Star_Filter(utrip));
		server.get("/r_filter",new R_Filter(utrip));
		//server.get("/profile",new Profile(utrip));
		server.setNotFoundErrPage("/home/amin/CLionProjects/A7/Src/Pages/Not_Found.html");
		server.run();
	}catch (Server::Exception &e){
		cerr<<e.getMessage()<<endl;
	} catch (exception &e) {
		cout << e.what() << endl;
	}

	return 0;
}
