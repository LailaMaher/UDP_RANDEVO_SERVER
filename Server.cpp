
#include "Server.h"

Server* Server::s_instance = NULL;

Server::Server(){

}

Server* Server::instance(){
	if(!s_instance)
		s_instance = new Server;
	return s_instance;
}

void Server::setDescriptor(int descriptor){
	this->descriptor = descriptor;
	if(descriptor < 0) perror("FAILED TO CREATE SOCKET");
}

int Server::getDescriptor() const{
	return descriptor;
}

void Server::setAddress(){
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT_NUM);
}

struct sockaddr* Server::getAddress() const{
	return (struct sockaddr*) &address;
}

void Server::createSocket(int p){
	PORT_NUM = p;
	setDescriptor( socket(AF_INET, SOCK_DGRAM, 0) ); 
	setAddress();
	if( bind(getDescriptor(), getAddress(), sizeof(address)) < 0 ) 
		perror("BIND ERROR");
}

User* Server::getByIP(string ip){
	pthread_mutex_lock(&users_mutex);

	for(int i=0; i<current_users; i++){
		if(ip.compare(users[i]->getIP()) == 0){
			pthread_mutex_unlock(&users_mutex);
			return users[i];
		}
	}

	pthread_mutex_unlock(&users_mutex);
	return NULL;
}

Request* Server::AcceptRequest(){
	
	char buffer[1024];

	struct sockaddr_in cli_address;
	socklen_t l = sizeof(cli_address);

    if( recvfrom(getDescriptor(), buffer, 1023, 0, (struct sockaddr *)&cli_address, &l) < 0)
    	perror("READ STREAM FAILED");

    string data(buffer);

    Request* new_request = new Request(cli_address, data);

    cout << "Request created" << endl;

	return new_request;
}


User* Server::createUser(Request* request){
	User* new_user = new User;
	new_user->setDescriptor(getDescriptor());
	new_user->setAddress(request->getAddress());
	return new_user;
}

void Server::addUser(User* new_user){

	pthread_mutex_lock(&users_mutex);
	users[current_users] = new_user;
	
	new_user->setIndx(current_users);
	new_user->setID(current_users);

	current_users++;
	pthread_mutex_unlock(&users_mutex);

	new_user->writeToClient("1" + to_string(new_user->getID()));
}

void Server::removeUser(User* rem_user){
	pthread_mutex_lock(&users_mutex);
	users[rem_user->getIndx()] = users[current_users];
	users[current_users]->setIndx(rem_user->getIndx());
	current_users--;
	pthread_mutex_unlock(&users_mutex);
	delete rem_user;
}


User* Server::isExist(int ID){
	pthread_mutex_lock(&users_mutex);

	for(int i=0; i<current_users; i++){
		if(ID == users[i]->getID()){
			pthread_mutex_unlock(&users_mutex);
			return users[i];
		}
	}

	pthread_mutex_unlock(&users_mutex);
	return NULL;
}

void Server::HandleRequest(Request* new_request){

	cout << "Handle new request" << endl;

	char token = new_request->getCode();
	cout << "current token " << token << endl;

	string peer_ID;
	User* peer = NULL; 
	User* client = NULL;
	User* new_user = NULL;

	switch(token){
		case '1':
			cout << "New Connection To Server" << endl;
			new_user = createUser(new_request);
			addUser(new_user);
			break;

		case '2':
			cout << "Initiate Connection with peer" << endl;
			peer_ID = new_request->getBody();
			peer = isExist(stoi(peer_ID));
			if(peer != NULL){
				client = getByIP(new_request->getIP());
				client->connectToPeer(peer);
			}
			break;

		case '3':
			cout << "Acknowledge from sender sending hello to receiver" << endl;
			peer = getByIP(new_request->getBody());
			peer->writeToClient("4");
			break;

		case '4':
			cout << "Acknowledge from receiver sending hello to initiator" << endl;
			peer = getByIP(new_request->getBody());
			peer->writeToClient("5");
			break;

		default:
			cout << "invalid token" << endl;
			cout << "code :" << new_request->getCode() << endl;
			cout << "body :" << new_request->getBody() << endl;
			break;
	}

}
