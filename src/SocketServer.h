#pragma once

#include "ofMain.h"
#include "ToolsLifeGame.h"
#include "DataLife.h"
#include "ofx\ofxNetwork\src\ofxNetwork.h"

#include <regex>

class SocketServer
{
public:
	SocketServer(DataLife * dataL = nullptr);
	void sendData(string data);
	~SocketServer();

private:
	void run();
	void update();

	int idCli;
	bool servRun;
	bool cliConn;

	thread threadServer;
	ofxTCPServer tcpServer;
	DataLife * dataLife = nullptr;
};


