
#include "stock_utils.h"
// #include "src/quote.hpp"
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <thread>
#include <string.h>

#include <dirent.h>

#include <istream>

// compile by the command: 
// g++ time_utils.cpp curl_utils.cpp quote.cpp spot.cpp analitza_main_stocks.cpp -o anal_main -lcurl

std::string file = "/var/www/inversions/output/pertiles.txt";

vector<std::string> main_ticks = { "^IXIC", "^GSPC", "^DJI", "META", "TSLA", "HPE", "PSX", "SU.PA", "RIOT",
"GOOGL", "GME", "INTC", "IBM", "QCOM", "ASML", "TSM", "NVDA", "005930.KS", "NFLX", "MSFT",
"LPL", "HLF", "AAPL", "0P0000XV9S.BO",
"BTC-EUR", "ADA-EUR", "ETH-EUR", "EUR=X", "GC=F", "CL=F" };


int main() {
    PrintMainStocks(main_ticks, file);
}

