#pragma once
class Uncopyable
{
public:
	Uncopyable() {}
	virtual ~Uncopyable() {}
private:
	Uncopyable(const Uncopyable & another);
	Uncopyable & operator=(const Uncopyable & another);
};

