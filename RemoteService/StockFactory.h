#pragma once
#include "Uncopyable.hpp"
#include <memory>
#include <string>
#include <map>

class CStock;
class CStockFactory  : private Uncopyable, public std::enable_shared_from_this<CStockFactory>
{
public:
	CStockFactory();
	~CStockFactory();

	std::shared_ptr<CStock> getStock(const std::string & stock);

private:
	void WeakDeleter(const std::weak_ptr<CStockFactory> & weakFactory, CStock * pStock);

private:
	std::map<std::string, std::weak_ptr<CStock>> _stocks;
};

