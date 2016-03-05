#include "SocketServer.h"

SocketServer::SocketServer(DataLife * dataL)
{
	this->dataLife = dataL;
	this->tcpServer.setup(11900, false);
	this->servRun = true;
	this->threadServer = thread(&SocketServer::run, this);
}

void SocketServer::sendData(string data)
{

	if (this->tcpServer.isClientConnected(idCli)) {
		this->tcpServer.send(idCli, data);
	}
}

void SocketServer::run()
{
	fprintf(stderr, "Server Start at 11900\n");

	idCli = 0;
	string dataR;
	while (this->servRun) {
		
		this->tcpServer.waitConnectedClient();
		
		for (int i = 0; i < this->tcpServer.getLastID(); i++) {

			if (this->tcpServer.isClientConnected(i)) {
				idCli = i;
				fprintf(stdout, "Client Add\n");
				fprintf(stdout, "Client id %i \n", this->tcpServer.getLastID());

				while (this->tcpServer.isClientConnected(idCli)) {
					dataR = this->tcpServer.receive(idCli);
					if (dataR != "") {
						//fprintf(stdout, "Data : %s \n", dataR);
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
				fprintf(stdout, "Client Out\n");
			}
		}

		this->tcpServer.sleep(1000);
	}
	fprintf(stderr, "Server close");
}
SocketServer::~SocketServer()
{
}
