#include <iostream>
#include <cstdio>
using namespace std;

// максимальное количество счетов
const int maxAccounts = 10;
// Checking - здесь описан чековый счет
class Checking
{
public:
	Checking(int initializeAN = 0)
	{
		accountNumber = initializeAN;
		balance = 0.0;
	}

	// функции обращения
	int accountNo()
	{
		return accountNumber;
	}
	double acntBalance()
	{
		return balance;
	}
	// функции транзакций
	void deposit(double amount)
	{
		balance += amount;
	}
	void withdrawal(double amount);

	// функция вывода объекта в cout
	void display()
	{
		cout << "S4et " << accountNumber << " = " << balance << "\n";
	}

protected:
	unsigned accountNumber;
	double balance;
};
// withdrawal - эта функция слишком велика для inline-функции

void Checking::withdrawal(double amount)
{
	if(balance < amount)
	{
		cout << "Nedostato4no deneg: balans raven " << balance << ", summa 4eka ravna " << amount << "\n";
	}
	else
	{
		balance -= amount;
		// eсли баланс падает слишком низко ...
		if(balance < 500.00)
			// ... удержать деньги за обслкживание
			balance -= 0.20;
	}
}
// Savings - здесь описан сберегательный счет
class Savings
{
public:
	Savings(int initialAN = 0)
	{
		accountNumber = initialAN;
		balance = 0.0;
		noWithdrawals = 0;
	}

	// функции обращения
	int accountNo()
	{
		return accountNumber;
	}
	double acntBalance()
	{
		return balance;
	}

	// функции транзакций
	void deposit(double amount)
	{
		balance += amount;
	}
	void withdrawal(double amount);

	// функция вывода объекта в cout
	void display()
	{
		cout << "S4et " << accountNumber << " = " << balance << " (nomer sn9|ti9| = "
			<< noWithdrawals << ")\n";
	}
protected:
	unsigned accountNumber;
	double balance;
	int noWithdrawals;
};

void Savings::withdrawal(double amount)
{
	if(balance < amount)
	{
		cout << "Nedostato4no deneg: balans raven " << balance << ", snimaets9| " << amount << "\n";
	}
	else
	{
		// после первого в месяце снятия денег ...
		if(++noWithdrawals > 1)
		{
			// ... удерживать 5 баксов
			balance -= 5.00;
		}

		// cнять деньги
		balance -= amount;
	}
}

// объявление прототипов
void process(Checking* pChecking);
void process(Savings* pSavings);

// объекты чековых и сберегательных счетов
Checking* chkAcnts[maxAccounts];
Savings* svgAcnts[maxAccounts];

// main - собирает и выводит данные
int main()
{
	// повторять цикл до ввода 'x' или 'X'
	int noChkAccounts = 0;// сдержит количество счетов
	int noSvgAccounts = 0;
	char accountType; // тип счета 'S' или 'C'
	while(1)
	{
		
		cout << "Vvedite S dl9| sberegatelbnb|x s4etov, "
			<< "C dl9| 4ekovb|x, "
			<< "X dl9| vb|xoda:";
		cin >> accountType;
		
		// выйти из цикла, если пользователь введет Х
		if(accountType == 'x' || accountType == 'X')
		{
			break;
		}
		// в противном случае обрабатывать счет
		switch(accountType)
		{
			case 'c':
			case 'C':
				if(noChkAccounts < maxAccounts)
				{
					int acnt;
					cout << "Vvedite nomer s4eta:";
					cin >> acnt;
					chkAcnts[noChkAccounts] = new Checking(acnt);
					process(chkAcnts[noChkAccounts]);
					noChkAccounts++;
				}
				else
				{
					cout << "Dl9| 4ekovb|x s4etov 6olbshe net mesta\n";
				}
				break;
				// сберегательные счета
			case 's':
			case 'S':
				if(noSvgAccounts < maxAccounts)
				{
					int acnt;
					cout << "Vvedite nomer s4eta:";
					cin >> acnt;
					svgAcnts[noSvgAccounts] = new Savings(acnt);
					process(svgAcnts[noSvgAccounts]);
					noSvgAccounts++;
				}
				else
				{
					cout << "Dl9| s6eregatelbnb|x s4etov 6olbdhe net mesta\n";
				}
				break;
			default:
				cout << "Nepon9|tnb|u simvol...n";
		}
	}


// А теперь показать общую сумму
double chkTotal = 0;
cout << "4ekovb|e s4eta:\n";
for(int i = 0; i < noChkAccounts; i++)
{
	chkAcnts[i]->display();
	chkTotal += chkAcnts[i]->acntBalance();
}

double svgTotal = 0;
cout << "S6eregatelbnb|e s4eta:\n";
for(int j = 0; j < noSvgAccounts; j++)
{
	svgAcnts[j]->display();
	svgTotal += svgAcnts[j]->acntBalance();
}

double total = chkTotal + svgTotal;

cout << "Symma po 4ekovb|m s4etam = " << chkTotal << "\n";
cout << "Symma po s6eregatelbnb|m s4etam = " << svgTotal << "\n";
cout << "O6s4a9| symma = " << total << "\n";

return 0;
}

// Обработка(Checking) - ввод данных по чековым счетам
void process(Checking *pChecking)
{
	cout << "Vvedite polozhitelbnoe 4islo dl9| vklada, \n"
		<< "otricatelbnoe dl9| sn9|ti9|, 0 dl9| zaversheni9|\n";
	double transaction;
	do
	{
		cout << " : ";
		cin >> transaction;
		if(transaction > 0)
		{
			pChecking->deposit(transaction);
		}
		if(transaction < 0)
		{
			pChecking->withdrawal(-transaction);
		}
	} while(transaction != 0);
}

// Обработка (Savings) - ввод данных для сберегательных счетов
void process(Savings *pSavings)
{
	cout << "Vvedite polozhitelbnoe 4islo dl9| vklada, \n"
		<< "otricatelbnoe dl9| sn9|ti9|, 0 dl9| zaversheni9|\n";
	double transaction;
	do
	{
		cout << " : ";
		cin >> transaction;
		if(transaction > 0)
		{
			pSavings->deposit(transaction);
		}
		if(transaction < 0)
		{
			pSavings->withdrawal(-transaction);
		}
	} while(transaction != 0);
}
