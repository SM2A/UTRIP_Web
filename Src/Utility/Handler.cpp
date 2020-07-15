#include "Handler.hpp"

#define CONTENT_TYPE "Content-Type"
#define CONTENT_VALUE "text/html"

using namespace std;

Response *Home::callback(Request *request) {


}

Response *Login::callback(Request *request) {

	Response *response = new Response();
	response->setHeader(CONTENT_TYPE, CONTENT_VALUE);
	string str;
	if (utrip->is_user_logged_in()) {
		str = "<!DOCTYPE html>\n"
		      "<html>\n"
		      "<head>\n"
		      "    <title>Redirect</title>\n"
		      "    <meta http-equiv=\"refresh\" content=\"3; url = /\"/>\n"
		      "</head>\n"
		      "<body>\n"
		      "<p>Please logout first</p>\n"
		      "<p>You will be redirect to home page in 3 second</p>\n"
		      "<a href=\"/\">If not click here</a>\n"
		      "</body>\n"
		      "</html>\n"
		      "<style>\n"
		      "\n"
		      "    body {background-color: #e3fff5;}\n"
		      "\n"
		      "    p {\n"
		      "        text-align: center;\n"
		      "        color: #ff5533;\n"
		      "        font-size: large;\n"
		      "    }\n"
		      "\n"
		      "    a{\n"
		      "        text-align: center;\n"
		      "        padding-left: 47%;\n"
		      "        font-size: medium;\n"
		      "        color: deepskyblue;\n"
		      "    }\n"
		      "\n"
		      "</style>";
	}else {
		str = "<!DOCTYPE html>\n"
		      "<html>\n"
		      "<head>\n"
		      "    <title>Redirect</title>\n"
		      "    <meta http-equiv=\"refresh\" content=\"3; url = /\"/>\n"
		      "</head>\n"
		      "<body>\n"
		      "<p>Welcome ";
		str += request->getBodyParam("user_name");
		str += "! </p>\n"
		       "<p>You will be redirect to home page in 3 second</p>\n"
		       "<a href=\"/\">If not click here</a>\n"
		       "</body>\n"
		       "</html>\n"
		       "<style>\n"
		       "\n"
		       "    body {background-color: #e3fff5;}\n"
		       "\n"
		       "    p {\n"
		       "        text-align: center;\n"
		       "        color: #ff5533;\n"
		       "        font-size: large;\n"
		       "    }\n"
		       "\n"
		       "    a{\n"
		       "        text-align: center;\n"
		       "        padding-left: 47%;\n"
		       "        font-size: medium;\n"
		       "        color: deepskyblue;\n"
		       "    }\n"
		       "\n"
		       "</style>";
		utrip->login(request->getBodyParam("user_name"), request->getBodyParam("password"));
	}
	response->setBody(str);
	return response;
}

Response *Logout::callback(Request *request) {

	/*if(utrip->is_user_logged_in()) {
		utrip->logout();
		return Response::redirect("/login");
	} else{
		Response* response = new Response();
		response->setHeader(CONTENT_TYPE,CONTENT_VALUE);
		string str = "<script>alert(\"WTF\")</script>";
		response->setBody(str);
		return response;
	}*/
}

Response *Signup::callback(Request *request) {

	Response *response = new Response();
	response->setHeader(CONTENT_TYPE, CONTENT_VALUE);
	string str;
	if (utrip->is_user_logged_in()) {
		str = "<!DOCTYPE html>\n"
		      "<html>\n"
		      "<head>\n"
		      "    <title>Redirect</title>\n"
		      "    <meta http-equiv=\"refresh\" content=\"3; url = /\"/>\n"
		      "</head>\n"
		      "<body>\n"
		      "<p>Please logout first</p>\n"
		      "<p>You will be redirect to home page in 3 second</p>\n"
		      "<a href=\"/\">If not click here</a>\n"
		      "</body>\n"
		      "</html>\n"
		      "<style>\n"
		      "\n"
		      "    body {background-color: #e3fff5;}\n"
		      "\n"
		      "    p {\n"
		      "        text-align: center;\n"
		      "        color: #ff5533;\n"
		      "        font-size: large;\n"
		      "    }\n"
		      "\n"
		      "    a{\n"
		      "        text-align: center;\n"
		      "        padding-left: 47%;\n"
		      "        font-size: medium;\n"
		      "        color: deepskyblue;\n"
		      "    }\n"
		      "\n"
		      "</style>";
	} else {
		str = "<!DOCTYPE html>\n"
		      "<html>\n"
		      "<head>\n"
		      "    <title>Redirect</title>\n"
		      "    <meta http-equiv=\"refresh\" content=\"3; url = /\"/>\n"
		      "</head>\n"
		      "<body>\n"
		      "<p>Welcome ";
		str += request->getBodyParam("user_name");
		str += "! </p>\n"
		       "<p>You will be redirect to home page in 3 second</p>\n"
		       "<a href=\"/\">If not click here</a>\n"
		       "</body>\n"
		       "</html>\n"
		       "<style>\n"
		       "\n"
		       "    body {background-color: #e3fff5;}\n"
		       "\n"
		       "    p {\n"
		       "        text-align: center;\n"
		       "        color: #ff5533;\n"
		       "        font-size: large;\n"
		       "    }\n"
		       "\n"
		       "    a{\n"
		       "        text-align: center;\n"
		       "        padding-left: 47%;\n"
		       "        font-size: medium;\n"
		       "        color: deepskyblue;\n"
		       "    }\n"
		       "\n"
		       "</style>";
		utrip->creat_user(request->getBodyParam("user_name"), request->getBodyParam("password"),
		                  request->getBodyParam("e_mail"));
	}
	response->setBody(str);
	return response;
}

Response *Profile::callback(Request *request) {

	if(!utrip->is_user_logged_in())  return Response::redirect("/login");
	return nullptr;
}

Response *Star_Filter::callback(Request *request) {

	if(!utrip->is_user_logged_in())  return Response::redirect("/login");
	return nullptr;
}

Response *Description::callback(Request *request) {

	if(!utrip->is_user_logged_in())  return Response::redirect("/login");
	return nullptr;
}
