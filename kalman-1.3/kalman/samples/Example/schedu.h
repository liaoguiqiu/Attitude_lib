#ifndef  SCHEDU_H
#define  SCHEDU_H

#include <cstdlib>
#include <iostream>
#include <fstream>

#include <cmath>
#include <vector>
#include "data.h"
#include "schedu.h"

// Example of Extented Kalman Filter
#include "plane.h"
#include "csv.h"
using namespace std;


class MYLOOP
{
public:
	unsigned int data_cnt;
	int t0_5ms;
	int t2_5ms;
	MYLOOP()
	{
		t0_5ms = 0;
		t2_5ms = 0;
		data_cnt = 0;
	}
	void main_loop();
	void loop1();
	void loop2();
private:

};

extern MYLOOP loop;


#endif // ! SCHEDU_H
