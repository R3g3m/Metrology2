#include <iostream>
#include <cstdio>
using namespace std;

// ������������ ���������� ������
const int maxAccounts = 10;
// Checking - ����� ������ ������� ����
class Checking
{
public:
	Checking(int initializeAN = 0)
	{
		accountNumber = initializeAN;
		balance = 0.0;
	}

	// ������� ���������
	int accountNo()
	{
		return accountNumber;
	}
	double acntBalance()
	{
		return balance;
	}
	// ������� ����������
	void deposit(double amount)
	{
		balance += amount;
	}
	void withdrawal(double amount);

	// ������� ������ ������� � cout
	void display()
	{
		cout << "S4et " << accountNumber << " = " << balance << "\n";
	}

protected:
	unsigned accountNumber;
	double balance;
};
// withdrawal - ��� ������� ������� ������ ��� inline-�������

void Checking::withdrawal(double amount)
{
	if(balance < amount)
	{
		cout << "Nedostato4no deneg: balans raven " << balance << ", summa 4eka ravna " << amount << "\n";
	}
	else
	{
		balance -= amount;
		// e��� ������ ������ ������� ����� ...
		if(balance < 500.00)
			// ... �������� ������ �� ������������
			balance -= 0.20;
	}
}
// Savings - ����� ������ �������������� ����
class Savings
{
public:
	Savings(int initialAN = 0)
	{
		accountNumber = initialAN;
		balance = 0.0;
		noWithdrawals = 0;
	}

	// ������� ���������
	int accountNo()
	{
		return accountNumber;
	}
	double acntBalance()
	{
		return balance;
	}

	// ������� ����������
	void deposit(double amount)
	{
		balance += amount;
	}
	void withdrawal(double amount);

	// ������� ������ ������� � cout
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
		// ����� ������� � ������ ������ ����� ...
		if(++noWithdrawals > 1)
		{
			// ... ���������� 5 ������
			balance -= 5.00;
		}

		// c���� ������
		balance -= amount;
	}
}

// ���������� ����������
void process(Checking* pChecking);
void process(Savings* pSavings);

// ������� ������� � �������������� ������
Checking* chkAcnts[maxAccounts];
Savings* svgAcnts[maxAccounts];

// main - �������� � ������� ������
int main()
{
	// ��������� ���� �� ����� 'x' ��� 'X'
	int noChkAccounts = 0;// ������� ���������� ������
	int noSvgAccounts = 0;
	char accountType; // ��� ����� 'S' ��� 'C'
	while(1)
	{
		
		cout << "Vvedite S dl9| sberegatelbnb|x s4etov, "
			<< "C dl9| 4ekovb|x, "
			<< "X dl9| vb|xoda:";
		cin >> accountType;
		
		// ����� �� �����, ���� ������������ ������ �
		if(accountType == 'x' || accountType == 'X')
		{
			break;
		}
		// � ��������� ������ ������������ ����
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
				// �������������� �����
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


// � ������ �������� ����� �����
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

// ���������(Checking) - ���� ������ �� ������� ������
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

// ��������� (Savings) - ���� ������ ��� �������������� ������
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
