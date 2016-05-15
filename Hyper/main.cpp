#include <iostream>
#include <ctime>
#include "Hyper.h"
#include "ConnSql.h"

using namespace std;

int main()
{
	/*clock_t start, finish;
	start = clock();/*/

	ConnSql sql;
	sql.connect();
	sql.inData();
	sql.outData();

	/*finish = clock();
	cout << (finish - start) << endl;
	system("pause");*/
	return 0;
}
