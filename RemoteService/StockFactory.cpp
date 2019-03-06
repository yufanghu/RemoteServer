#include "StockFactory.h"
#include "Stock.h"
#include <functional>
CStockFactory::CStockFactory()
{
}


CStockFactory::~CStockFactory()
{
}

std::shared_ptr<CStock> CStockFactory::getStock(const std::string & stock)
{
	std::weak_ptr<CStock> & aWeakStock = _stocks[stock];
	auto aSharedStock = aWeakStock.lock(); //提升为shared_ptr 线程安全

	if (!aSharedStock){
		//如果map没有则创建
		//aSharedStock.reset(new CStock(stock), std::bind(&CStockFactory::WeakDeleter,
		/*	std::weak_ptr<CStockFactory>(shared_from_this()), -1));*/
	}
	return aSharedStock;
}

void CStockFactory::WeakDeleter(const std::weak_ptr<CStockFactory> & weakFactory, CStock * pStock)
{
	auto aSharedFac = weakFactory.lock();
	if (aSharedFac) {
		//线程不安全
		_stocks.erase(pStock->key());
	}
}
