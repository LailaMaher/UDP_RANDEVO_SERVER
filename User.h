
#ifndef USER
#define USER

#include "header.h"

class User{

	int ID, index, descriptor;
	bool busy;
	struct sockaddr_in address;
	socklen_t l;

public:

	User();
	
	void setBusy(bool);
	bool isBusy() const;

	void setID(int);
	int getID() const;

	void setIndx(int);
	int getIndx() const;

	void setDescriptor(int);
	int getDescriptor() const;

	void setAddress(struct sockaddr_in);
	struct sockaddr* getAddress() const;
	string getIP();
	string getPort();

	void writeToClient(string);
	string readFromClient();


	void connectToPeer(User*);

};



#endif
