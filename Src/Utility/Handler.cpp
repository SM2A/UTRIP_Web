#include "Handler.hpp"
#include <sstream>
#include <fstream>

#define CONTENT_TYPE "Content-Type"
#define CONTENT_VALUE "text/html"

using namespace std;

Response *Home::callback(Request *request){

	Response *response = new Response();
	response->setHeader(CONTENT_TYPE, CONTENT_VALUE);
	string str;
	if (!utrip->is_user_logged_in()) str = redirect("Please login first", "/login", "Login page");
	else {
		try {
			str += "<!DOCTYPE html>\n"
			       "<html lang=\"en\">\n"
			       "<head>\n"
			       "    <meta charset=\"UTF-8\">\n"
			       "    <title>Home</title>\n"
			       "</head>\n"
			       "<body>\n"
			       "<div class=\"card\" style=\"overflow: auto\">\n"
			       "    <div class=\"container\">\n"
			       "        <table width=\"95%\">\n"
			       "            <tr height=\"40px\">\n"
			       "                <th width=\"13%\">Image</th>\n"
			       "                <th width=\"27%\">Name</th>\n"
			       "                <th width=\"10%\">Star</th>\n"
			       "                <th width=\"20%\">City</th>\n"
			       "                <th width=\"10%\">Average Rating</th>\n"
			       "                <th width=\"10%\">Total Rooms</th>"
			       "            </tr>";
			str += utrip->show_hotel();
			str += "        </table>\n"
			       "    </div>\n"
			       "</div>\n"
			       "</body>\n"
			       "</html>\n"
			       "\n"
			       "<style>\n"
			       "\n"
			       "    body {background-color: #e3fff5;}\n"
			       "\n"
			       "    .card{\n"
			       "        background-color: white;\n"
			       "        box-shadow: 0 8px 12px 0 rgba(0,0,0,0.2);\n"
			       "        transition: 0.3s;\n"
			       "        width: 90%;\n"
			       "        height: 90%;\n"
			       "        position: absolute;\n"
			       "        top: 50%;\n"
			       "        left: 50%;\n"
			       "        margin-right: -50%;\n"
			       "        transform: translate(-50%, -50%);\n"
			       "        border: 2px solid #ff5533;\n"
			       "        border-radius: 25px;\n"
			       "    }\n"
			       "    \n"
			       "    table{\n"
			       "        text-align: center;\n"
			       "        margin-right: auto;\n"
			       "        margin-left: auto;\n"
			       "    }\n"
			       "\n"
			       "    th,td{\n"
			       "        border-bottom: 1px solid #c1c1c1;\n"
			       "    }\n"
			       "    \n"
			       "    tr:hover {background-color: #e3fff5;}\n"
			       "\n"
			       "    td{\n"
			       "        height: 100px;\n"
			       "    }\n"
			       "\n"
			       "    img {\n"
			       "        width: 100%;\n"
			       "        height: 100%;\n"
			       "    }\n"
			       "\n"
			       "</style>";
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
	string str;
	if (utrip->is_user_logged_in()) str = redirect("Please logout first", "/", "Home page");
	else {
		try {
			utrip->login(request->getBodyParam("user_name"), request->getBodyParam("password"));
			str = redirect("Welcome" + request->getBodyParam("user_name") + "!", "/", "Home page");
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
	string str;
	if (!utrip->is_user_logged_in()) str = redirect("Please login first", "/login", "Login page");
	else {
		try {
			utrip->logout();
			str = redirect("God Bye", "/login", "Login page");
		} catch (exception &e) {
			str = redirect(e.what(), "/signup", "Signup page");
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

	if (!utrip->is_user_logged_in()) return Response::redirect("/login");
	return nullptr;
}

Response *Star_Filter::callback(Request *request) {

	if (!utrip->is_user_logged_in()) return Response::redirect("/login");
	return nullptr;
}

Response *Description::callback(Request *request) {

	Response *response = new Response();
	response->setHeader(CONTENT_TYPE, CONTENT_VALUE);
	string str;
	if (!utrip->is_user_logged_in()) str = redirect("Please login first", "/login", "Login page");
	else {
		ifstream file_1("/home/amin/CLionProjects/A7/Src/Pages/Description_1.html");
		ifstream file_2("/home/amin/CLionProjects/A7/Src/Pages/Description_2.html");
		stringstream stream_1, stream_2;
		stream_1 << file_1.rdbuf();
		stream_2 << file_2.rdbuf();
		str += stream_1.str();
		str += utrip->show_hotel(request->getQueryParam("id"));
		str += stream_2.str();
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
