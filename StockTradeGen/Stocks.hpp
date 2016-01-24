#ifndef STOCKS_H
#define STOCKS_H

#include <string>
#include "curl.h"
#include "StockNode.hpp"

class Stocks
{
	private:
		Curl *httpGet;
		StockNode stock[10];
		std::string url;
		Stocks();

	public:
		Stocks* getInstance();
		~Stocks();
		void init(void);
		int requestStatus(void);
		void requestUpdate(void);
		void getStockInfo(int ix, StockNode* nodeObj);
		void rdStockData(int ix, const std::string& input);
        static Stocks* m_pInstance;
};

#endif