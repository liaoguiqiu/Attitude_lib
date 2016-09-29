#include "data.h"

#include <cmath>
#include <vector>
#include "data.h"


// Example of Extented Kalman Filter
#include "plane.h"
#include "csv.h"
#include "AHRS.h"
#include "imu.h"


INDATA data;
INDATA data_filed;


void INDATA::read()
{
	/*-数据库测试--*/
	CppCSV cs("../test2.csv");

	/*--读取的所有传感数据、kalman计算的结果--*/
	int i = 1;
	while (1)

	{

		int read_s = 0;
		float pr;

		data.len++;


		read_s = cs.GetFloatValue(i, 4, pr);
		data.acc.x.push_back(pr);
		read_s = cs.GetFloatValue(i, 5, pr);
		data.acc.y.push_back(pr);
		read_s = cs.GetFloatValue(i, 6, pr);
		data.acc.z.push_back(pr);

		read_s = cs.GetFloatValue(i, 7, pr);
		data.gyro.x.push_back(pr);
		read_s = cs.GetFloatValue(i, 8, pr);
		data.gyro.y.push_back(pr);
		read_s = cs.GetFloatValue(i, 9, pr);
		data.gyro.z.push_back(pr);

		read_s = cs.GetFloatValue(i, 10, pr);
		data.mag.x.push_back(pr);
		read_s = cs.GetFloatValue(i, 11, pr);
		data.mag.y.push_back(pr);
		read_s = cs.GetFloatValue(i, 12, pr);
		data.mag.z.push_back(pr);

		read_s = cs.GetFloatValue(i, 13, pr);
		data.angle.x.push_back(pr);
		read_s = cs.GetFloatValue(i, 14, pr);
		data.angle.y.push_back(pr);
		read_s = cs.GetFloatValue(i, 15, pr);
		data.angle.z.push_back(pr);

		read_s = cs.GetFloatValue(i, 16, pr);
		data.Q.q1.push_back(pr);
		read_s = cs.GetFloatValue(i, 17, pr);
		data.Q.q2.push_back(pr);
		read_s = cs.GetFloatValue(i, 18, pr);
		data.Q.q3.push_back(pr);
		read_s = cs.GetFloatValue(i, 19, pr);
		data.Q.q4.push_back(pr);


		i++;
		if (read_s == 0)
			break;
	}

}

void INDATA::save(unsigned int cnt)
{



	data_filed.angle.x.push_back(imu_dcm.Roll);
	data_filed.angle.y.push_back(imu_dcm.Pitch);
	data_filed.angle.z.push_back(imu_dcm.Yaw);

}