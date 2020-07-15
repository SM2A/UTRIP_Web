#ifndef A7_HANDLER_HPP
#define A7_HANDLER_HPP

#include "../APHTTP/server/server.hpp"
#include "../UTRIP/UTrip.hpp"
#include "map"

class Home :  public RequestHandler{
public:
	Home(UTrip* utrip_) : utrip(utrip_){}
	Response* callback(Request* request);
private:
	UTrip* utrip;
};

class Login :  public RequestHandler{
public:
	Login(UTrip* utrip_) : utrip(utrip_){}
	Response* callback(Request* request);
private:
	UTrip* utrip;
};

class Logout :  public RequestHandler{
public:
	Logout(UTrip* utrip_) : utrip(utrip_){}
	Response* callback(Request* request);
private:
	UTrip* utrip;
};

class Signup : public RequestHandler{
public:
	Signup(UTrip* utrip_) : utrip(utrip_){}
	Response* callback(Request* request);
private:
	UTrip* utrip;
};

class Profile :  public RequestHandler{
public:
	Profile(UTrip* utrip_) : utrip(utrip_){}
	Response* callback(Request* request);
private:
	UTrip* utrip;
};

class Star_Filter :  public RequestHandler{
public:
	Star_Filter(UTrip* utrip_) : utrip(utrip_){}
	Response* callback(Request* request);
private:
	UTrip* utrip;
};

class Description :  public RequestHandler{
public:
	Description(UTrip* utrip_) : utrip(utrip_){}
	Response* callback(Request* request);
private:
	UTrip* utrip;
};

#endif