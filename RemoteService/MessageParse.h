#ifndef _MESSAGE_PARSE_H
#define _MESSAGE_PARSE_H
#include <thread>

struct header {
	int pos;
	int type;
	int uid;
	//当前为第几个包
	int index;
	//00
	int flag;
};

class CMessageParse
{
public:
	CMessageParse();
	~CMessageParse();

};

#endif

