
#include "Request.h"

Request::Request(sockaddr_in address, string request){

	this->address = address;
	cout << "request " << request << endl;
	this->code = request[0];
	cout << "code " << code << endl;
	this->body = request.substr(1, request.length() - 1);
	cout << "body " << body << endl;
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