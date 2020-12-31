#ifudef _ACCOUNT_H
#def _ACCOUNT_H
#include<string>
using std::string;
class Account
{
  private:
  	string name;
  	string account_no;
  	float balance;
  public:
    string show(string account_no);
    bool save(float number);
    bool charge(float number);

  Account(string name, string account_no, float balance)
  {
    name = name;
    account_no = account_no;
    balance = balance;
  }  

  Account()
  {
    name = "";
    account_no = "";
    balance = 0.0f;
  }

};
#endif