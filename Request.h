
#ifndef REQUEST
#define REQUEST

#include "header.h"

class Request{

	struct sockaddr_in address;
	socklen_t len;
	char code;
	string body;

public:

	Request(sockaddr_in, string);

	string getBody() const;
	struct sockaddr_in getAddress() const;
	char getCode() const;
	string getIP() const;
	string getPort() const;

};



#endif
