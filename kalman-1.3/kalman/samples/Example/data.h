#ifndef DATA_H
#define DATA_H



#include <iostream>
#include <fstream>

#include <cmath>
#include <vector>





using namespace std;


#define GIRO_BAS2000  2000
#define ACC_4G  4000
#define MAG_8GUSS  8

struct VET3f
{
	vector<float> x;
	vector<float> y;
	vector<float> z;
};


struct VET4f
{
	vector<float> q1;
	vector<float> q2;
	vector<float> q3;
	vector<float> q4;
};


class INDATA
{
public:

	VET3f acc;
	VET3f gyro;
	VET3f mag;
	VET3f angle;
	VET4f Q;
	int  len;




	void save(unsigned int cnt);
	void read();
	INDATA()
	{
		len = 0;
		;
	}  









private:

};
 
extern INDATA data;

extern INDATA data_filed;



#endif