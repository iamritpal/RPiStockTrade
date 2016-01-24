#include <iostream>
#include <unistd.h>
#include <stdlib.h>     /* atoi */

#include "Stocks.hpp"

Stocks* Stocks::m_pInstance = NULL;

Stocks::Stocks(){
   httpGet = httpGet->getInstance();
}

Stocks* Stocks::getInstance()
{
    if (!m_pInstance)           // Only allow one instance of class to be generated.
        m_pInstance = new Stocks();
    return m_pInstance;
}


Stocks::~Stocks(){}

void Stocks::init(void)
{
	int i=0;
	
	stock[i++].setStockTicker("AAPL");
	stock[i++].setStockTicker("MSFT");
	stock[i++].setStockTicker("GOOG");
	stock[i++].setStockTicker("AMD");
	stock[i++].setStockTicker("YHOO");
	stock[i++].setStockTicker("INTC");
	stock[i++].setStockTicker("SLM");
	stock[i++].setStockTicker("FOXA");
	stock[i++].setStockTicker("QQQ");
	stock[i++].setStockTicker("XIV");

	// initialize stock prices	
	for (i=0;i<10;i++)
		stock[i].setStockPrice(0);

   for (i=0;i<10;i++)
   {
      url = "http://www.google.com/finance/info?q=NSE:";
      url += stock[i].getStockTicker();
      httpGet->AddUrlToList(i,url);
   }

}

int Stocks::requestStatus(void)
{
   int i;
	if (httpGet->isRunning())
		httpGet->refresh();
	else
	{
		for (i=0;i<10;i++)
      	rdStockData(i, httpGet->m_data[i]);
		return(1);
	}
	return(0);
}

void Stocks::requestUpdate(void)
{
	int i=0;
	
	httpGet->init();	// Initialize curl request

   for (i=0;i<10;i++)
   {
      httpGet->AddGetRequest(i);
   }

	httpGet->refresh();	// Start request
}

void Stocks::getStockInfo(int ix, StockNode* nodeObj)
{
	nodeObj->setStockPrice(stock[ix].getStockPrice());
	//nodeObj->setStockTicker(stock[ix].getStockTicker());
}

void Stocks::rdStockData(int ix, const std::string& input)
{
   int i = 0;
   int j = 0;
   int line_cnt = 0;
   int str_length = input.size();
   char temp[100];

   if (str_length != 0)
   {
      // start from line # 4
      j=0;
      i=15;
      line_cnt = 4;
      
      //temp[j++] = '\0';
      
      while (i < str_length)
      {
         switch (line_cnt)
         {
            case 4:              // Parse line#4
               // Get the ID
               if (input[i] == '\"')
               {
                  j = 0;
                  i += 9;       // jump to ticker value
                  line_cnt++;
               }
               break;

            case 5:              // Parse line#5 ticker label
               if (input[i] != '\"')
               {
               //   stock.ticker[j++] = input[i];
               }
               else
               {
                  //while (j < 5)
                  //   stock.ticker[j++] = ' ';
                  j = 0;
                  i += 25;
                  line_cnt++;
               }
               break;

            case 6:              // Parse line#7
               if (input[i] != '\"')
               {
                  if (input[i] != '.')
                     temp[j++] = input[i];
               }
               else
               {
                  stock[ix].setStockPrice(atoi(temp));
                  line_cnt++;
                  i = str_length;
               }
               break;

            default:
               break;
         }
         i++;
      }
      //std::cout << "Ticket: " << stock.ticker << std::endl;
      //std::cout << "Last Price: " << stock.lastPrice << std::endl;
   }
}