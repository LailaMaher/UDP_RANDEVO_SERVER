

#ifndef CLIENT
#define CLIENT

#include "Request.h"

class Client{
	
	int PORT_NUM;

	int descriptor;
	struct sockaddr_in address;
	struct sockaddr_in peer_address;

	struct sockaddr_in server_address;

public:

	Client(int);

	void setServer();
	void CreateSocket();
	void setAddress();
	sockaddr* getAddress() const;
	void setDescriptor(int);
	int getDescriptor() const;

	void SendStream(string, bool = true);
	string ReadStream();

	void setPeerAddress(string);
	string getPeerIP() const;

	Request AcceptRequest();
	void handleIncomingRequest(Request*);
	
};



#endif