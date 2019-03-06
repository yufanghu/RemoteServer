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
	auto aSharedStock = aWeakStock.lock(); //����Ϊshared_ptr �̰߳�ȫ

	if (!aSharedStock){
		//���mapû���򴴽�
		//aSharedStock.reset(new CStock(stock), std::bind(&CStockFactory::WeakDeleter,
		/*	std::weak_ptr<CStockFactory>(shared_from_this()), -1));*/
	}
	return aSharedStock;
}

void CStockFactory::WeakDeleter(const std::weak_ptr<CStockFactory> & weakFactory, CStock * pStock)
{
	auto aSharedFac = weakFactory.lock();
	if (aSharedFac) {
		//�̲߳���ȫ
		_stocks.erase(pStock->key());
	}
}
