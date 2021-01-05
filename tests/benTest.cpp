/* Every header files working in progress here */
#include "../include/public_header.hpp"
#include "../src/stock.cpp"
#include "../src/objectList.cpp"

int main(){

    vector<Stock*> s_list; // This will store StockList.list
	StockList* stocklist_obj = new StockList("../src/companies.csv"); // Create 'list' inside
	Stock* s; // This will store one stock from s_list;

	s_list = stocklist_obj->GetList(); // Store the list
	s = s_list.at(3); // Get 3rd Stock in the array
    s->SetCurrentPrice(127.00);
    cout << s->GetStockIssuer() << endl;

    delete s;
    s = NULL;
    delete stocklist_obj;
    stocklist_obj = NULL;

    return 0;
}
