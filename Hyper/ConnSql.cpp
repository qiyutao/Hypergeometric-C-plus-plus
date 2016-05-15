#include <iostream>
#include <cstring>
#include "ConnSql.h"

using namespace std;
 
ConnSql::ConnSql()
{
	m_vt = vector<Hyper>();
	m_hdbc = NULL;
	m_henv = NULL;
	m_hstmt = NULL;
}


ConnSql::~ConnSql()
{
	m_vt.clear();
}

void ConnSql::connect()
{
	SQLRETURN ret;

	ret = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &m_henv);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		cout << "alloc handle is error!" << endl;
		return;
	}

	ret = SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		cout << "set evn attr is error!" << endl;
		return;
	}
	
	ret = SQLAllocHandle(SQL_HANDLE_DBC, m_henv, &m_hdbc);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		cout << "alloc handle is error!" << endl;
		return;
	}
	
	ret = SQLConnect(m_hdbc, (SQLCHAR*)"hyper", SQL_NTS, (SQLCHAR*)"sa", SQL_NTS, (SQLCHAR*)"123456", SQL_NTS);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		cout << "connect is error!" << endl;
		return;
	}
}

void ConnSql::close()
{
	if (m_hstmt != SQL_NULL_HSTMT)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
	}

	if (m_hdbc != SQL_NULL_HDBC)
	{
		SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc);
	}

	if (m_henv != SQL_NULL_HENV)
	{
		SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
	}
}

void ConnSql::inData()
{
	Hyper tmp ;
	double part[5];
	char ch[300] = "";
	string name;
	SQLINTEGER cbData;

	connect();
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt) != SQL_SUCCESS)
	{
		cout << "in func inData() allloc handle is failed!" << endl;
		close();
		return ;
	}
	SQLCHAR sql[] = "select * from hypertest";
	if (SQLExecDirect(m_hstmt, (SQLCHAR*)sql, SQL_NTS) == SQL_SUCCESS)
	{
		while (SQLFetch(m_hstmt) == SQL_SUCCESS)
		{
			SQLGetData(m_hstmt, 1, SQL_C_DOUBLE, part, sizeof(double), &cbData);
			SQLGetData(m_hstmt, 2, SQL_C_CHAR, ch, sizeof(ch), &cbData);
			SQLGetData(m_hstmt, 3, SQL_C_DOUBLE, part+1, sizeof(double), &cbData);
			SQLGetData(m_hstmt, 4, SQL_C_DOUBLE, part+2, sizeof(double), &cbData);
			SQLGetData(m_hstmt, 5, SQL_C_DOUBLE, part+4, sizeof(double), &cbData);
			SQLGetData(m_hstmt, 6, SQL_C_DOUBLE, part+3, sizeof(double), &cbData);
			
			name = string(ch);
			tmp = Hyper((int)part[0], name, (int)part[1], (int)part[2], (int)part[3],(int)part[4]);
			m_vt.push_back(tmp);
		}
		close();
		return;
	}
	else
	{
		close();
		return ;
	}
	
}

void ConnSql::outData()
{
	Hyper hy;
	SQLCHAR sql[500] = "";
	string str;
	string sql1 = "update hypertest set cplusplus = ";
	string sql2 = " where DB_ID = ";
	
	connect();
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt) != SQL_SUCCESS)
	{
		cout << "in func inData() allloc handle is failed!" << endl;
		close();
		return ;
	}
	for (int i = 0; i < m_vt.size(); i++)
	{
		hy = m_vt.at(i);
		hy.calculate();
		char tmp[200];
		char id[10];
		sprintf_s(tmp, "%g", hy.getValue());
		sprintf_s(id, "%d", hy.getID());
		//sprintf(tmp, "%lf", hy.getValue());
		str = sql1 + tmp + sql2 + id;
		strcpy((char *)sql, str.c_str());

		if (SQLExecDirect(m_hstmt, (SQLCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
		{
			cout << "update  "<<hy.getName()<<" is failed!" << endl;
			close();
			return;
		}
		//hy.dis_cur();
	}
	close();
}
