#pragma once
class CIOEventLoop
{
public:
	CIOEventLoop();
	~CIOEventLoop();

	virtual void Start() = 0;

	virtual void Stop() = 0;

protected:
	bool _bRunning;
};

