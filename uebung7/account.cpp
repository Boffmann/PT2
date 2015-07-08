#include <iostream>
#include <cassert>
#include <list>
#include <cstdlib>
#include <string>

using namespace std;


class Account {
public:
    Account(long accountNo, double balance, double limit, bool locked); 
    ~Account();

    long accountNo() const { return accountNo_; } 

    virtual void setLimit(double limit) { limit_ = limit; } 
    double getLimit() const { return limit_; }

    virtual bool credit(double amount); 
    virtual bool debit(double amount); 
    virtual double balance() const { return balance_; } 

    void setLock(bool locked) { locked_ = locked; } 
    bool getLock() const { return locked_; }

protected: 
    long accountNo_; 
    double balance_; 
    double limit_; 
    bool locked_;
};

Account::Account(long accountNo, double balance, double limit, bool locked) : 
    accountNo_{accountNo}, 
    balance_{balance}, 
    limit_(limit), 
    locked_{locked} { 
}

Account::~Account() { 
}

bool Account::credit(double amount) {
    assert(amount>=0.0); 

    // cannot use locked account
    if(locked_) return false; 

    balance_ = balance_ + amount; 
    return true; 
}

bool Account::debit(double amount) {
    assert(amount>=0.0); 

    // cannot use locked account
    if(locked_) return false; 
    
    // check if limit is hit
    if(balance_-amount<limit_) return false; 

    // change balance
    balance_ = balance_ - amount; 
    return true; 
}

//----------------------------------------------

class LoggedAccount : public Account{
public:
	LoggedAccount(long accountNo, double balance, double limit, bool locked) : Account(accountNo, balance, limit, locked) {
    protokoll.push_back(std::make_pair("Initial balance", balance));
    protokoll.push_back(std::make_pair("Current balance", balance));
  }

  virtual void setLimit(double limit) { limit_ = limit; updateProtokoll("limit change: ", limit);} 

  virtual bool credit(double amount) {
    assert(amount>=0.0); 

    // cannot use locked account
    if(locked_) return false; 

    updateProtokoll("credit: ", amount);
    balance_ = balance_ + amount; 
    return true; 
}

  virtual bool debit(double amount) {
    assert(amount>=0.0); 

    // cannot use locked account
    if(locked_) return false; 
    
    // check if limit is hit
    if(balance_-amount<limit_) return false; 

    // change balance
    updateProtokoll("debit: ", amount);
    balance_ = balance_ - amount; 
    return true; 
}

  void updateProtokoll(std::string entry1, double entry2){
    auto temp = protokoll.back();
    protokoll.pop_back();
    protokoll.push_back(std::make_pair(entry1, entry2));
    protokoll.push_back(std::make_pair("Current balance: ", balance_));
 }

  std::list<std::pair<std::string, double>> transactions(){
    return protokoll;
  }
	
private:
  //const std::string strAccountNo = "AccountNo: " + std::to_string(accountNo);
  std::list<std::pair<std::string, double>> protokoll;
};

//----------------------------------------------


int main(int argc, char** argv) {
  Account A1(19920, 0.0, -1000.0, false); 
  LoggedAccount A2(20020, 0.0, -1000.0, false);

  A1.credit(500.0);
  A2.credit(500.0);
  A2.debit(100.0);
  A2.setLimit(-2000.);

  for (const auto& x : A2.transactions()) {
    cout << x.first << ": " << x.second << endl;
  }

  return 0; 
}

