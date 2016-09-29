#include "schedu.h"
#include "imu.h"
#include "AHRS.h"
#include "magnet.h"
#include "data.h"
MYLOOP loop;

void MYLOOP::main_loop()
{
	while (1)
	{
		data_cnt++;
		t2_5ms++;
		 
		if (t2_5ms == 1)
		{
			t2_5ms = 0;
			loop1();
		}
		 
		if (data_cnt >= (data.len-2))
			break;
	}



}


void MYLOOP::loop1()
{
	float data_time5 = 0.0025;

	ahrs.ahrs_Data_Prepare(data_time5,data_cnt);			//mpu6轴传感器数据处理
	mag_s.Read_Mag_Data(data_cnt);

	ahrs.ahrs_data_filt(data_time5);
	mag_s.filt_data();


	
	imu_dcm.IMUupdate(0.5f *data_time5, ahrs.Gyro_deg.x, ahrs.Gyro_deg.y, ahrs.Gyro_deg.z,
		ahrs.Acc.x, ahrs.Acc.y, ahrs.Acc.z,
		&imu_dcm.Roll, &imu_dcm.Pitch, &imu_dcm.Yaw);

	data.save( data_cnt);
  


}

void MYLOOP::loop2()
{



}