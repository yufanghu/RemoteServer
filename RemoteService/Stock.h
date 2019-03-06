#pragma once
#include <string>

class CStock
{
public:
	explicit CStock(const std::string & stock);
	~CStock();
	std::string key() const;

private:
	std::string _key;
};

