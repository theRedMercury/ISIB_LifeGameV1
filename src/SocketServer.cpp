#include "SocketServer.h"

SocketServer::SocketServer(DataLife * dataL)
{
	this->dataLife = dataL;
	this->tcpServer.setup(this->dataLife->portServer, false);
	this->servRun = true;
	this->threadServer = thread(&SocketServer::run, this);
}

void SocketServer::sendData(string data)
{
	if (this->tcpServer.isClientConnected(idCli)) {
		this->tcpServer.sendToAll(data);
	}
}

void SocketServer::run()
{
	cout << "Server start at " << this->tcpServer.getPort() << endl;
	idCli = 0;
	string dataR;
	while (this->servRun) {
		
		this->tcpServer.waitConnectedClient();
		
		for (int i = 0; i < this->tcpServer.getLastID(); i++) {

			if (this->tcpServer.isClientConnected(i)) {
				idCli = i;
				cout << "Client Add ID :" << this->tcpServer.getLastID() << endl;

				while (this->tcpServer.isClientConnected(idCli)) {
					dataR = this->tcpServer.receive(idCli);
					if (dataR != "") {
						regex self_regex("SpeedLife ([0-9]+)",regex_constants::ECMAScript | regex_constants::icase);
						smatch match;
						if (regex_search(dataR, match, self_regex )) {
							//std::cout << (unsigned int)stoul(match[1]) << " ok ok \n";
							this->dataLife->speedLifeGame = (unsigned int) stoul(match[1]);
						}
						//this->tcpServer.send(idCli, "You sent: " + dataR);
					}
					this->tcpServer.sleep(50);
					
				}
				cout << "Client Out" << endl;
			}
		}
		this->tcpServer.sleep(1000);
	}
	cout << "Server close" << endl;
}

SocketServer::~SocketServer()
{
}
