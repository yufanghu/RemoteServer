#pragma once
#include "EPoller.h"

class CAcceptPoller : public EPoller
{
public:
	CAcceptPoller();
	~CAcceptPoller();

	virtual void Wait() override;

private:
};

