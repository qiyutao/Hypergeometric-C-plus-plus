#include <vector>
#include <windows.h>
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>
#include "Hyper.h"

class ConnSql
{
	public:
		ConnSql();
		~ConnSql();
		void connect();
		void close();
		void inData();
		void outData();

	private:
		vector<Hyper> m_vt;
		SQLHENV m_henv;
		SQLHDBC m_hdbc;
		SQLHSTMT m_hstmt;
};

