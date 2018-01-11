

#ifndef SERVER
#define SERVER

#include "User.h"
#include "Request.h"
#include <pthread.h>

class Server{
	
	int PORT_NUM, descriptor;
	struct sockaddr_in address;

	static Server* s_instance;

	User* users[100];
	pthread_mutex_t users_mutex;
	int current_users;

	User* createUser(Request*);

	User* isExist(int);
	User* getByIP(string);

	Server();

public:


	static Server* instance();
		
	void setDescriptor(int);
	int getDescriptor() const;

	void setAddress();
	struct sockaddr* getAddress() const;

	void createSocket(int);

	Request AcceptRequest();
	void HandleRequest(Request*);

	void addUser(User*);
	void removeUser(User*);

};



#endif
