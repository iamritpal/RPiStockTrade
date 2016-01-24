#ifndef STOCKNODE_H
#define STOCKNODE_H

class StockNode
{
	private:
		std::string ticker;		// 5 character per stock ticker
		int price;

	public:
		StockNode();
		~StockNode();
		int getStockPrice(void);
		void setStockPrice(int priceValue);
		void setStockTicker(const std::string &str);
		const std::string& getStockTicker(void);
};

#endif