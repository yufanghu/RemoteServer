#pragma once

class Channel
{
public:
	Channel(int fd);
	~Channel();
	int get_fd() const { return _fd; }
private:
	int _fd;
};

