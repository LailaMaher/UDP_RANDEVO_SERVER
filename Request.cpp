
#include "Request.h"

Request::Request(sockaddr_in address, string request){

	this->address = address;
	this->code = request[0];
	if(request.length() > 1)
		this->body = request.substr(1, request.length() - 1);
	else this->body = "";
	len = sizeof(address);
}

string Request::getBody() const{
	return body;
}

char Request::getCode() const{
	return code;
}

string Request::getIP() const{
	string ip(inet_ntoa(address.sin_addr));
	return ip;
}

string Request::getPort() const{
	char port[128];
	sprintf(port, "%u", address.sin_port);
	string port_s(port);
	return port_s;
}

struct sockaddr_in Request::getAddress() const{
	return address;
}