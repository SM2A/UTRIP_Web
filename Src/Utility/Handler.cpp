#include "Handler.hpp"
#include <sstream>
#include <fstream>

#define CONTENT_TYPE "Content-Type"
#define CONTENT_VALUE "text/html"
#define CONNECTION "Connection"
#define CONNECTION_STATUS "close"

using namespace std;

Response *Home::callback(Request *request){

	Response *response = new Response();
	response->setHeader(CONTENT_TYPE, CONTENT_VALUE);
	response->setHeader(CONNECTION,CONNECTION_STATUS);
	string str;
	if (!utrip->is_user_logged_in()) str = redirect("Please login first", "/login", "Login page");
	else {
		try {
			ifstream file_1("/home/amin/CLionProjects/A7/Src/Pages/Home_1.html");
			ifstream file_2("/home/amin/CLionProjects/A7/Src/Pages/Home_2.html");
			stringstream stream_1, stream_2;
			stream_1 << file_1.rdbuf();
			stream_2 << file_2.rdbuf();
			str += stream_1.str();
			str += utrip->show_hotel();
			str += stream_2.str();
		} catch (exception &e) {
			str = redirect(e.what(), "/", "Home page");
			response->setBody(str);
			return response;
		}
	}
	response->setBody(str);
	return response;
}

Response *Login::callback(Request *request) {

	Response *response = new Response();
	response->setHeader(CONTENT_TYPE, CONTENT_VALUE);
	response->setHeader(CONNECTION,CONNECTION_STATUS);
	string str;
	if (utrip->is_user_logged_in()) str = redirect("Please logout first", "/", "Home page");
	else {
		try {
			utrip->login(request->getBodyParam("user_name"), request->getBodyParam("password"));
			str = redirect("Welcome " + request->getBodyParam("user_name") + "!", "/", "Home page");
		} catch (exception &e) {
			str = redirect(e.what(), "/login", "Login page");
			response->setBody(str);
			return response;
		}
	}
	response->setBody(str);
	return response;
}

Response *Logout::callback(Request *request) {

	Response *response = new Response();
	response->setHeader(CONTENT_TYPE, CONTENT_VALUE);
	response->setHeader(CONNECTION,CONNECTION_STATUS);
	string str;
	if (!utrip->is_user_logged_in()) str = redirect("Please login first", "/login", "Login page");
	else {
		try {
			utrip->logout();
			str = redirect("God Bye", "/login", "Login page");
		} catch (exception &e) {
			str = redirect(e.what(), "/", "Home page");
			response->setBody(str);
			return response;
		}
	}
	response->setBody(str);
	return response;
}

Response *Signup::callback(Request *request) {

	Response *response = new Response();
	response->setHeader(CONTENT_TYPE, CONTENT_VALUE);
	response->setHeader(CONNECTION,CONNECTION_STATUS);
	string str;
	if (utrip->is_user_logged_in()) str = redirect("Please logout first", "/", "Home page");
	else {
		try {
			if (request->getBodyParam("password") != request->getBodyParam("re_password")) {
				str = redirect("Password dose not match", "/signup", "Signup page");
				response->setBody(str);
				return response;
			}
			utrip->creat_user(request->getBodyParam("user_name"), request->getBodyParam("password"),
			                  request->getBodyParam("e_mail"));
			str = redirect("Welcome " + request->getBodyParam("user_name") + "!", "/", "Home page");
		} catch (exception &e) {
			str = redirect(e.what(), "/signup", "Signup page");
			response->setBody(str);
			return response;
		}
	}
	response->setBody(str);
	return response;
}

Response *Profile::callback(Request *request) {

	Response *response = new Response();
	response->setHeader(CONTENT_TYPE, CONTENT_VALUE);
	response->setHeader(CONNECTION,CONNECTION_STATUS);
	string str;
	if (!utrip->is_user_logged_in()) str = redirect("Please login first", "/login", "Login page");
	else {
		try {
			char out[3000];
			//todo file path
			ifstream file("/home/amin/CLionProjects/A7/Src/Pages/Profile.html");
			stringstream stream;
			stream << file.rdbuf();
			sprintf(out, stream.str().c_str(),utrip->get_user()->get_user_name().c_str(),
					to_string(utrip->get_user()->get_credit()).c_str());
			str = string(out);
		}catch (exception &e) {
			str = redirect(e.what(), "/profile", "Profile page");
			response->setBody(str);
			return response;
		}
	}
	response->setBody(str);
	return response;
}

Response *Star_Filter::callback(Request *request) {

	Response *response = new Response();
	response->setHeader(CONTENT_TYPE, CONTENT_VALUE);
	response->setHeader(CONNECTION,CONNECTION_STATUS);
	string str;
	if (!utrip->is_user_logged_in()) str = redirect("Please login first", "/login", "Login page");
	else {
		try {
			utrip->add_star_filter(stoi(request->getQueryParam("min")),stoi(request->getQueryParam("max")));
			str = "<!DOCTYPE html>\n"
			      "<html>\n"
			      "   <head>\n"
			      "      <meta http-equiv = \"refresh\" content = \"0; url=/\"/>\n"
			      "   </head>\n"
			      "</html>";
		}catch (exception &e) {
			str = redirect(e.what(), "/", "Home page");
			response->setBody(str);
			return response;
		}
	}
	response->setBody(str);
	return response;
}

Response *Description::callback(Request *request) {

	Response *response = new Response();
	response->setHeader(CONTENT_TYPE, CONTENT_VALUE);
	response->setHeader(CONNECTION,CONNECTION_STATUS);
	string str;
	if (!utrip->is_user_logged_in()) str = redirect("Please login first", "/login", "Login page");
	else {
		try {
		ifstream file_1("/home/amin/CLionProjects/A7/Src/Pages/Description_1.html");
		ifstream file_2("/home/amin/CLionProjects/A7/Src/Pages/Description_2.html");
		stringstream stream_1, stream_2;
		stream_1 << file_1.rdbuf();
		stream_2 << file_2.rdbuf();
		str += stream_1.str();
		str += utrip->show_hotel(request->getQueryParam("id"));
		str += stream_2.str();
		}catch (exception &e) {
			str = redirect(e.what(), "/", "Home page");
			response->setBody(str);
			return response;
		}
	}
	response->setBody(str);
	return response;
}

string redirect(string msg, string rtn_path, string rtn_page) {

	char out[1000];
	//todo file path
	ifstream file("/home/amin/CLionProjects/A7/Src/Pages/Redirect.html");
	stringstream stream;
	stream << file.rdbuf();
	sprintf(out, stream.str().c_str(), rtn_path.c_str(), msg.c_str(), rtn_page.c_str(), rtn_path.c_str());
	return string(out);
}

Response *Static::callback(Request *request) {

	Response *response = new Response();
	response->setHeader(CONTENT_TYPE, CONTENT_VALUE);
	response->setHeader(CONNECTION,CONNECTION_STATUS);
	string str;
	if (utrip->is_user_logged_in()) str = redirect("Please logout first", "/", "Home page");
	else {
		ifstream file(file_path);
		stringstream stream;
		stream << file.rdbuf();
		str = stream.str();
	}
	response->setBody(str);
	return response;
}

Response *R_Filter::callback(Request *request) {

	Response *response = new Response();
	response->setHeader(CONTENT_TYPE, CONTENT_VALUE);
	response->setHeader(CONNECTION,CONNECTION_STATUS);
	string str;
	if (!utrip->is_user_logged_in()) str = redirect("Please login first", "/login", "Login page");
	else {
		try {
			utrip->remove_filter();
			str = "<!DOCTYPE html>\n"
			      "<html>\n"
			      "   <head>\n"
			      "      <meta http-equiv = \"refresh\" content = \"0; url=/\"/>\n"
			      "   </head>\n"
			      "</html>";
		}catch (exception &e) {
			str = redirect(e.what(), "/", "Home page");
			response->setBody(str);
			return response;
		}
	}
	response->setBody(str);
	return response;
}

Response *Charge::callback(Request *request) {

	Response *response = new Response();
	response->setHeader(CONTENT_TYPE, CONTENT_VALUE);
	response->setHeader(CONNECTION,CONNECTION_STATUS);
	string str;
	if (!utrip->is_user_logged_in()) str = redirect("Please login first", "/login", "Login page");
	else {
		try {
			utrip->add_credit(stof(request->getBodyParam("amount")));
			str = "<!DOCTYPE html>\n"
			      "<html>\n"
			      "   <head>\n"
			      "      <meta http-equiv = \"refresh\" content = \"0; url=/profile\"/>\n"
			      "   </head>\n"
			      "</html>";
		}catch (exception &e) {
			str = redirect(e.what(), "/profile", "Profile page");
			response->setBody(str);
			return response;
		}
	}
	response->setBody(str);
	return response;
}
