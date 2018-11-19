#pragma once
#include "IOEventLoop.h"

class CAcceptorLoop : public CIOEventLoop
{
public:
	CAcceptorLoop(int listenfd);
	~CAcceptorLoop();

	virtual void Start() override;

	virtual void Stop() override;
private:
	void handle_accept();
private:
	int _listenfd;
};

