#ifndef _MESSAGE_PARSE_H
#define _MESSAGE_PARSE_H
#include <thread>

struct header {
	int pos;
	int type;
	int uid;
	//��ǰΪ�ڼ�����
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

