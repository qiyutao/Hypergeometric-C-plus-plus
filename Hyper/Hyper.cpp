#include <iostream>
#include "hyper.h"

using namespace std;

Hyper::Hyper()
{
	m_totality = 1;
	m_scsInTotal = 1;
	m_sample = 1;
	m_scsInSmp = 1;
	m_value = 1;
	m_name = "";
}

Hyper::Hyper(int i,string n,int t, int st, int s, int ss)
{
	m_id = i;
	m_name = n;
	m_totality = t;
	m_scsInTotal = st;
	m_sample = s;
	m_scsInSmp = ss;
	m_value = 1;
}

int Hyper::getID()
{
	return m_id;
}

int Hyper::getTotal()
{
	return m_totality;
}

int Hyper::getST()
{
	return m_scsInTotal;
}

int Hyper::getSample()
{
	return m_sample;
}

int Hyper::getSS()
{
	return m_scsInSmp;
}

string Hyper::getName()
{
	return m_name;
}

double Hyper::getValue()
{
	return m_value;
}

void Hyper::setTotal(int t)
{
	m_totality = t;
}

void Hyper::setST(int st)
{
	m_scsInTotal = st;
}

void Hyper::setSample(int s)
{
	m_sample = s;
}

void Hyper::setSS(int ss)
{
	m_scsInSmp = ss;
}

void Hyper::calculate()
{
	int scsInTotal, totality;
	int scsInSmp, sample;

	scsInTotal = m_scsInTotal;
	totality = m_totality;

	scsInSmp = m_scsInSmp;
	sample = m_sample;

	int n = scsInTotal;
	int tmp1 = scsInSmp;
	int tmp2 = sample;

	for (int i = 0; i<n; i++)
	{
		m_value *= (double)tmp2 / tmp1;
		m_value *= (double)scsInTotal / totality;
		totality--;
		scsInTotal--;
		tmp2--;
		tmp1--;
		if (tmp1 == 0)
		{
			tmp1 = m_scsInTotal - m_scsInSmp;
			tmp2 = m_totality - m_sample;
		}
	}
}

void Hyper::input()
{
	cout << "样本总体的容量：";
	cin >> m_totality;

	cout << "样本总体中成功的次数：";
	cin >> m_scsInTotal;

	cout << "样本容量：";
	cin >> m_sample;

	cout << "样本中成功的次数：";
	cin >> m_scsInSmp;
}

void Hyper::display()
{
	cout << "计算结果：" << m_value << endl;
}

void Hyper::dis_cur()
{
	cout << m_name << "  ********  Ok" << endl;
}
