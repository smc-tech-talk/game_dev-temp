#include "../include/public_header.hpp"
#include "stock.hpp"
#include "transaction.hpp"
#include "csvExtractor.hpp"
#include "player.hpp"
#include "portfolio.hpp"
#include "banking.hpp"
#include <memory>

template<typename T>
void GetUserInput(T &arg, const std::string msg);
vector< std::unique_ptr<Stock> > CreateStocks(int howMany); // Should return vecotr<Stock*> later
void PrintStart(const std::unique_ptr<Date>& date);
void PrintDay(int day, double balance = 0.00);
void PrintTrade();
void PrintPortfolioDemo();
void PrintPortfolioDemo2(Account& account, Player& player);
int main(){

    int PAUSE;
    srand(time(NULL));
    static int day = 1;
    bool isPlaying = true, isDay = true, isTrade = true;
    auto game_time = std::make_unique<Date>();

    string name;
    int age;
    auto official_date = std::make_unique<Date>();
    Player* player;
    auto stocks = CreateStocks(15);
    Portfolio* portfolio = new Portfolio(stocks);

    GetUserInput<std::string&>(name, "Insert player name");
    GetUserInput<int&>(age, "Insert player age");

    player = new Player(name, age, portfolio);

    Account* account;
    account = new Account(player);


    while(isPlaying){
        PrintStart(game_time);
        while(isDay){
            //PrintDay(day, balance);
            //PrintPortfolioDemo2(100, *player);
            while(isTrade){
                PrintTrade();
                std::cout << "Current Hour: "<< game_time->GetHour() << ":00 " << ((game_time->GetHour() < 12) ? "AM" : "PM") << std::endl;
                std::cin >> PAUSE;
                std::cout << "1 Selected!\n" << endl;
                Date::AddGameTime(*(game_time));
                //PrintPortfolioDemo2(100, *player);
                if(game_time->GetHour() == 9)
                    isTrade = false;
            }
            isDay = false;
        }
        isPlaying = false;
    }

    delete player;
    delete portfolio;
    player = NULL;
    portfolio = NULL;

    return 0;
}


vector<std::unique_ptr<Stock>> CreateStocks(int howMany){
    int count;
    vector<std::unique_ptr<Stock>> stocks;
    auto e = std::make_unique<CSVExtractor>("./companies.csv");
    auto r = std::make_unique<RandomNumberGenerator>(1, 400, howMany);
    auto data = e->GetResult();
    auto manyIndex = r->GetNumbers();

    for(int i = 0; i < manyIndex.size(); i++){
        count = manyIndex.at(i);

        Company* c = new Company(data.at(count).at(1), data.at(count).at(2)); // This will be handled by ~Stock()
        auto s = std::make_unique<Stock>(data.at(count).at(0), c);
        stocks.push_back(std::move(s)); // emplace_back() does not work
    }
    return stocks;
}

template <typename T>
void GetUserInput(T& arg, const std::string msg){
    cout << msg << ": \n";
    cin >> arg;
}

/* All Console Printing Functions Here */
void PrintStart(const std::unique_ptr<Date>& date){
    std::cout << "\n" << std::endl;
    std::cout << "\t\t\t********************************************" << std::endl;
    std::cout << "\t\t\t\t\tWelcome to" << std::endl;
    std::cout << " __                  __   __                 ________                         __           " << std::endl;
    std::cout << "|  \\                |  \\ |  \\               |        \\                       |  \\          " << std::endl;
    std::cout << "| $$       ______  _| $$_| $$ _______        \\$$$$$$$$______   ______    ____| $$  ______  " << std::endl;
    std::cout << "| $$      /      \\|   $$ \\$ /       \\         | $$  /      \\ |      \\  /      $$ /      \\ " << std::endl;
    std::cout << "| $$     |  $$$$$$\\\\$$$$$$  |  $$$$$$$         | $$ |  $$$$$$\\ \\$$$$$$\\|  $$$$$$$|  $$$$$$\\" << std::endl;
    std::cout << "| $$     | $$    $$ | $$ __  \\$$    \\          | $$ | $$   \\$$/      $$| $$  | $$| $$    $$" << std::endl;
    std::cout << "| $$_____| $$$$$$$$ | $$|  \\ _\\$$$$$$\\         | $$ | $$     |  $$$$$$$| $$__| $$| $$$$$$$$" << std::endl;
    std::cout << "| $$     \\\\$$    \\  \\$$  $$|       $$          | $$ | $$      \\$$    $$ \\$$    $$ \\$$     \\" << std::endl;
    std::cout << " \\$$$$$$$$ \\$$$$$$$   \\$$$$  \\$$$$$$$           \\$$  \\$        \\$$$$$$$  \\$$$$$$$  \\$$$$$$$" << std::endl;
    std::cout << "\n\t\t\t\tPowered by SMC Tech Talk Team 2021" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "\t\t\t********************************************" << std::endl;
    std::cout << "\n\t\t\tCurrent Time: " << std::endl;
    std::cout << "\t\t\t" << *date << std::endl;
}
void PrintDay(int day, double balance){
    std::cout << "\n" << std::endl;
    std::cout << "\t\t\t\t\t| Day " << day << " |" << std::endl;
    std::cout << "\n"<< std::endl;
    std::cout << "\tYou have $" << balance  << " in your account.\n" << std::endl;
}
void PrintTrade(){
    std::cout << "\n" << std::endl;
    std::cout << "\tWhat would you like to do?\n\n" << endl;
    std::cout << "\t1. Print stock lists" << endl;
    std::cout << "\t2. Buy a stock" << endl;
    std::cout << "\t3. Sell a stock" << endl;
    std::cout << "\t4. Check my portfolio" << endl;
    std::cout << "\t5. Check my banking status" << endl;
    std::cout << "\n"<< std::endl;
}
void PrintPortfolioDemo(){
    std::cout << "\nThis is portfolio demo version\n" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "Income: " << std::endl;
    std::cout << "\nLoss: " << std::endl;
    std::cout << "\nBalance: " << std::endl;
    std::cout << "=============================" << std::endl;
}


void PrintPortfolioDemo2(Account& account, Player& player){
    std::cout << "\n" << player.GetName() << "'s Portfolio:\n" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "Balance: " << account.get_balance() << std::endl;
    std::cout << "\nGain: " << std::endl;
    std::cout << "\nLoss: " << std::endl;
    std::cout << "=============================" << std::endl;
}
