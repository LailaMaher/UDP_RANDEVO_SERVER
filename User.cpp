
#include "User.h"

User::User(){
	setBusy(false);
}

void User::setBusy(bool busy){
	this->busy = busy;
}

bool User::isBusy() const{
	return busy;
}

void User::setIndx(int index){
	this->index = index;
}

int User::getIndx() const{
	return index;
}


void User::setID(int ID){
	this->ID = ID;
}

int User::getID() const{
	return ID;
}

void User::setAddress(struct sockaddr_in address){
	this->address = address;
}

struct sockaddr* User::getAddress() const{
	return (struct sockaddr*) &address;
}

string User::getIP() {
	string ip(inet_ntoa(address.sin_addr));
	return ip;
}

string User::getPort() {
	char port[128];
	sprintf(port, "%u", address.sin_port);
	string port_s(port);
	return port_s;
}

void User::setDescriptor(int descriptor){
	this->descriptor = descriptor;
	if(descriptor < 0) perror("FAILED TO CREATE SOCKET");
}

int User::getDescriptor() const{
	return descriptor;
}

void User::connectToPeer(User* peer){

	if(!peer->isBusy()) {

		setBusy(true);
		peer->setBusy(true);

		writeToClient("1" + peer->getIP() + "/" + peer->getPort());
		peer->writeToClient("2" + getIP() + "/" + getPort());
		
	}

	else writeToClient("busy");
}

void User::writeToClient(string data){
    char buffer[1024];
    strcpy(buffer, data.c_str());
  
    if( sendto(getDescriptor(), buffer, 1023, 0, getAddress(), sizeof(address)) < 0 )
    	perror("SEND STREAM FAILED");
}


string User::readFromClient(){
	char buffer[1024];
	l = sizeof(address);

    if( recvfrom(getDescriptor(), buffer, 1023, 0, getAddress(), &l) < 0)
    	perror("READ STREAM FAILED");
    string data(buffer);
	return data;
}
