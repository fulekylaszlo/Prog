#include <iostream>
using namespace std;

class Killer
	{
	public:
	void death(){};
	};

class SerialKiller : public Killer 
	{ 
	public:
	void serialkillerdeath(){};
	};

int main(void)
	{
	Killer* killer;
	SerialKiller* serialkiller; 

	(*serialkiller).death(); 
	(*serialkiller).serialkillerdeath();

	(*killer).death();

	std::cout << "Ééééés lefutott, megjött a gyilkos. :O" << endl;
	};

