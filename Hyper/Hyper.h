#ifndef _HYPER_H_
#define _HYPER_H_

#include <string>

using namespace std;

class Hyper
{
public:
	Hyper();
	Hyper(int i,string n,int t, int st, int s, int ss);

	int getID();
	int getTotal();
	int getST();
	int getSample();
	int getSS();
	string getName();
	double getValue();

	void setTotal(int t);
	void setST(int st);
	void setSample(int s);
	void setSS(int ss);

	void calculate();

	void input();
	void display();
	void dis_cur();

private:
	int m_id;
	int m_totality;
	int m_scsInTotal;
	int m_sample;
	int m_scsInSmp;
	double m_value;
	string m_name;
};

#endif
