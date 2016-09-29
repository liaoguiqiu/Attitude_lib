
#include "data.h"
#include "AHRS.h"
 


AHRS_S ahrs;

 

void AHRS_S:: Transform(float itx, float ity, float itz, float *it_x, float *it_y, float *it_z)
{
	*it_x = itx;
	*it_y = ity;
	*it_z = itz;

}

#define ACC_ADJ_EN 1

void AHRS_S:: ahrs_Data_Offset()
{
	{
#if  ACC_ADJ_EN
		//Gyro_CALIBRATE=1;
		//Acc_CALIBRATE =  1;

		if ( Acc_CALIBRATE == 1)
		{
			acc_sum_cnt++;
			sum_temp[A_X] += Acc_I16.x;
			sum_temp[A_Y] += Acc_I16.y;
			sum_temp[A_Z] += Acc_I16.z - 65536 / 8;   // +-8G
			//sum_temp[TEM] += Tempreature;

			if (acc_sum_cnt >= OFFSET_AV_NUM)
			{


				Acc_Offset.x = sum_temp[A_X] / OFFSET_AV_NUM;
				Acc_Offset.y = sum_temp[A_Y] / OFFSET_AV_NUM;
				Acc_Offset.z = sum_temp[A_Z] / OFFSET_AV_NUM;
				//Acc_Temprea_Offset = sum_temp[TEM] / OFFSET_AV_NUM;
				acc_sum_cnt = 0;
				Acc_CALIBRATE = 0;

				//Param_SaveAccelOffset(&Acc_Offset);
				sum_temp[A_X] = sum_temp[A_Y] = sum_temp[A_Z] = sum_temp[TEM] = 0;
			}
		}

#endif

		if (Gyro_CALIBRATE)
		{
			gyro_sum_cnt++;
			sum_temp[G_X] += Gyro_I16.x;
			sum_temp[G_Y] += Gyro_I16.y;
			sum_temp[G_Z] += Gyro_I16.z;
			//sum_temp[TEM] += Tempreature;

			if (gyro_sum_cnt >= OFFSET_AV_NUM)
			{

			 
				Gyro_Offset.x = (float)sum_temp[G_X] / OFFSET_AV_NUM;
				Gyro_Offset.y = (float)sum_temp[G_Y] / OFFSET_AV_NUM;
				Gyro_Offset.z = (float)sum_temp[G_Z] / OFFSET_AV_NUM;
			//	Gyro_Temprea_Offset = sum_temp[TEM] / OFFSET_AV_NUM;
				gyro_sum_cnt = 0;
			//	SendGyroCalData();
			 
				Gyro_CALIBRATE = 0;
				sum_temp[G_X] = sum_temp[G_Y] = sum_temp[G_Z] = sum_temp[TEM] = 0;
			}
		}
	}

}
#define Byte16(Type, ByteH, ByteL)  ((Type)((((uint16_t)(ByteH))<<8) | ((uint16_t)(ByteL))))

void AHRS_S:: ahrs_Data_Prepare(float T,int cnt)
{
	//	float auto_offset_temp[3];


	ahrs_Data_Offset(); //校准函数


	//Acc_I16.x = (Byte16(int16_t, buffer[0], buffer[1]));    // Acc.X
	//Acc_I16.y = (Byte16(int16_t, buffer[2], buffer[3]));    // Acc.Y
	//Acc_I16.z = (Byte16(int16_t, buffer[4], buffer[5]));    // Acc.Z

	//Gyro_I16.x = (Byte16(int16_t, buffer[8], buffer[9]));    // Gyr.X
	//Gyro_I16.y = (Byte16(int16_t, buffer[10], buffer[11]));   // Gyr.Y
	//Gyro_I16.z = (Byte16(int16_t, buffer[12], buffer[13]));    // Gyr.Z


	Acc_I16.x = data.acc.x[cnt]*8192;    // Acc.X
	Acc_I16.y = data.acc.y[cnt]*8192;    // Acc.Y
	Acc_I16.z = data.acc.z[cnt]*8192;    // Acc.Z

	Gyro_I16.x = data.gyro.x[cnt] ;    // Gyr.X
	Gyro_I16.y = data.gyro.y[cnt]  ;   // Gyr.Y
	Gyro_I16.z = data.gyro.z[cnt]  ;    // Gyr.Z

	//Tempreature = ((((int16_t)mpu6050_buffer[6]) << 8) | mpu6050_buffer[7]); //tempreature
	//TEM_LPF += 2 *3.14f *T *(Tempreature - TEM_LPF);
	//Ftempreature = TEM_LPF/340.0f + 36.5f;

	//======================================================================
	if (++filter_cnt_gyro > FILTER_NUM_G)
	{
		filter_cnt_gyro = 0;

	}


	if (++filter_cnt > FILTER_NUM_A)
	{
		filter_cnt = 0;
	 
	}
 
	//10 170 4056
	/* 得出校准后的数据 */
	ahrs_tmp[A_X] = (Acc_I16.x - Acc_Offset.x);
	ahrs_tmp[A_Y] = (Acc_I16.y - Acc_Offset.y);
	ahrs_tmp[A_Z] = (Acc_I16.z - Acc_Offset.z);
	ahrs_tmp[G_X] = Gyro_I16.x - Gyro_Offset.x;//
	ahrs_tmp[G_Y] = Gyro_I16.y - Gyro_Offset.y;//
	ahrs_tmp[G_Z] = Gyro_I16.z - Gyro_Offset.z;//


	/* 更新滤波滑动窗口数组 */
	FILT_BUF_A[DIR_X][filter_cnt] = ahrs_tmp[A_X];
	FILT_BUF_A[DIR_Y][filter_cnt] = ahrs_tmp[A_Y];
	FILT_BUF_A[DIR_Z][filter_cnt] = ahrs_tmp[A_Z];
	FILT_BUF_G[DIR_X][filter_cnt_gyro] = ahrs_tmp[G_X];
	FILT_BUF_G[DIR_Y][filter_cnt_gyro] = ahrs_tmp[G_Y];
	FILT_BUF_G[DIR_Z][filter_cnt_gyro] = ahrs_tmp[G_Z];



	//======================================================================
}

void  AHRS_S:: ahrs_data_filt(float T)
{
	u8 i;
	s32 FILT_TMP[ITEMS] = { 0, 0, 0, 0, 0, 0, 0 };
	 
	for (i = 0; i<FILTER_NUM_A; i++)
	{
		      
		         
		FILT_TMP[A_X] += FILT_BUF_A[DIR_X][i];
		FILT_TMP[A_Y] += FILT_BUF_A[DIR_Y][i];
		FILT_TMP[A_Z] += FILT_BUF_A[DIR_Z][i];

	}


	mpu_fil_tmp[A_X] = (float)(FILT_TMP[A_X]) / (float)FILTER_NUM_A;
	mpu_fil_tmp[A_Y] = (float)(FILT_TMP[A_Y]) / (float)FILTER_NUM_A;
	mpu_fil_tmp[A_Z] = (float)(FILT_TMP[A_Z]) / (float)FILTER_NUM_A;
	 
	for (i = 0; i<FILTER_NUM_G; i++)
	{



		FILT_TMP[G_X] += FILT_BUF_G[DIR_X][i];
		FILT_TMP[G_Y] += FILT_BUF_G[DIR_Y][i];
		FILT_TMP[G_Z] += FILT_BUF_G[DIR_Z][i];
	}
	 
	mpu_fil_tmp[G_X] = (float)(FILT_TMP[G_X]) / (float)(FILTER_NUM_G);
	mpu_fil_tmp[G_Y] = (float)(FILT_TMP[G_Y]) / (float)(FILTER_NUM_G);
	mpu_fil_tmp[G_Z] = (float)(FILT_TMP[G_Z]) / (float)(FILTER_NUM_G);


	/*坐标转换*/
	Transform(mpu_fil_tmp[A_X], -mpu_fil_tmp[A_Y],- mpu_fil_tmp[A_Z], & Acc.x, & Acc.y, & Acc.z);
	Transform(mpu_fil_tmp[G_X], -mpu_fil_tmp[G_Y],- mpu_fil_tmp[G_Z], & Gyro.x, & Gyro.y, & Gyro.z);

	//	 Gyro_deg.x =  Gyro.x *TO_ANGLE;
	//	 Gyro_deg.y =  Gyro.y *TO_ANGLE;
	//	 Gyro_deg.z =  Gyro.z *TO_ANGLE;
	 Gyro_deg.x =  Gyro.x   ;
	 Gyro_deg.y =  Gyro.y   ;
	 Gyro_deg.z =  Gyro.z   ;
	//  MPU9250G_1000dps



}









 