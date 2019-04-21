/* 
 * Time function learning note  
 * Introduction: 
	========================================================================
	struct timespec {
	time_t tv_sec; // seconds 
	long tv_nsec; // and nanoseconds ����
	};
	========================================================================
	struct timeval {
	time_t tv_sec; // seconds 
	long tv_usec; // microseconds ΢��
	};
	========================================================================
 	#include <sys/time.h>
	int gettimeofday(struct timeval*tv, struct timezone *tz);
	struct timezone{
	int tz_minuteswest; //G.M.T.(Greenwich Mean Time) ����ʱ����ʱ��� 
	int tz_dsttime;     //����ʱ����, ����ʱΪ1
	========================================================================
	#include<time.h>
	int clock_gettime(clockid_t clk_id,struct timespec *tp);
	clk_id : ���������õ�clk_idָ����ʱ��ʱ�䡣
	CLOCK_REALTIME:ϵͳʵʱʱ��,��ϵͳʵʱʱ��ı���ı�, UTC1970-1-1 0:0:0 ��ʼ 
	CLOCK_MONOTONIC:��ϵͳ������һ����ʼ��ʱ,����ϵͳʱ�䱻�û��ı��Ӱ��
	CLOCK_PROCESS_CPUTIME_ID:�����̵���ǰ����ϵͳCPU���ѵ�ʱ��
	CLOCK_THREAD_CPUTIME_ID:���̵߳���ǰ����ϵͳCPU���ѵ�ʱ��
 	========================================================================
 */
#include <stdio.h> 
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

// test latency function
int Latency_cnt(struct timespec *tv1, struct timespec *tv2)
{
	double time_interval = 0;
	long long temp1 = 0, temp2 = 0;
	long long diff = 0;
#if 0
	temp1 = tv1.tv_sec * 1000000000 + tv1->tv_nsec;
	printf("Time 1 = %lld ns\n", temp1);

	temp2 = tv2.tv_sec * 1000000000 + tv2->tv_nsec;
	printf("Time 2 = %lld ns\n", temp2);
#else
	temp1 = tv1->tv_sec * 1000000000 + tv1->tv_nsec;
	printf("Time 1 = %lld ns\n", temp1);

	temp2 = tv2->tv_sec * 1000000000 + tv2->tv_nsec;
	printf("Time 2 = %lld ns\n", temp2);
#endif	
	diff = temp2 - temp1;
	printf("Diff = %lld ns\n", diff);
	
	printf("Time interval = %.3lf s\n", diff / 1000000000.0);
	printf("\t      = %.1lf ms\n", diff / 1000000.0);
	printf("\t      = %.1lf us\n", diff / 1000.0);
	printf("\t      = %lld ns\n", diff);

	return 0;
}

int main()
{	
	int ret;
	struct timeval tv;
	struct timespec ts;
	
	// 1. getrawmonotonic
	clock_gettime(CLOCK_REALTIME, &ts);
	printf("Function clock_gettime : \n");
	// CLOCK_REALTIME: Real time, According to system time (Start from UTC1970-1-1 00:00:00)
	printf("Clk_id [CLOCK_REALTIMERET] -- RET[%d] Time Sec[%ld] nsec[%ld]\n" , ret, ts.tv_sec, ts.tv_nsec);
	clock_gettime(CLOCK_MONOTONIC, &ts);
	// CLOCK_MONOTONIC: Monotonic time, (Start from system init)
	printf("Clk_id [CLOCK_MONOTONIC]   -- RET[%d] Time Sec[%ld] nsec[%ld]\n" , ret, ts.tv_sec, ts.tv_nsec);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
	// CLOCK_PROCESS_CPUTIME_ID: Elapsed time of process to this place.
	printf("Clk_id [CLOCK_PROCESS_CPUTIME_ID]   -- RET[%d] Time Sec[%ld] nsec[%ld]\n" , ret, ts.tv_sec, ts.tv_nsec);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
	// CLOCK_THREAD_CPUTIME_ID: Elapsed time of thread to this place. (process > thread)
	printf("Clk_id [CLOCK_THREAD_CPUTIME_ID]    -- RET[%d] Time Sec[%ld] nsec[%ld]\n" , ret, ts.tv_sec, ts.tv_nsec);
	
	// 2. monotonic time interval test
	{
		struct timespec ts_1, ts_2;
		clock_gettime(CLOCK_MONOTONIC, &ts_1);
		sleep(1);
		clock_gettime(CLOCK_MONOTONIC, &ts_2);
		printf("\nFunction sleep(1): \n");
		Latency_cnt(&ts_1, &ts_2);
		clock_gettime(CLOCK_MONOTONIC, &ts_1);
		usleep(1);
		clock_gettime(CLOCK_MONOTONIC, &ts_2);
		printf("\nFunction usleep(1): \n");
		Latency_cnt(&ts_1, &ts_2);	
		clock_gettime(CLOCK_MONOTONIC, &ts_1);
		usleep(10);
		clock_gettime(CLOCK_MONOTONIC, &ts_2);
		printf("\nFunction usleep(10): \n");
		Latency_cnt(&ts_1, &ts_2);
		clock_gettime(CLOCK_MONOTONIC, &ts_1);
		usleep(100);
		clock_gettime(CLOCK_MONOTONIC, &ts_2);
		printf("\nFunction usleep(100): \n");
		Latency_cnt(&ts_1, &ts_2);
		clock_gettime(CLOCK_MONOTONIC, &ts_1);
		usleep(1000);
		clock_gettime(CLOCK_MONOTONIC, &ts_2);
		printf("\nFunction usleep(1000): \n");
		Latency_cnt(&ts_1, &ts_2);
		clock_gettime(CLOCK_MONOTONIC, &ts_1);
		usleep(10000);
		clock_gettime(CLOCK_MONOTONIC, &ts_2);
		printf("\nFunction usleep(10000): \n");
		Latency_cnt(&ts_1, &ts_2);
		clock_gettime(CLOCK_MONOTONIC, &ts_1);
		usleep(100000);
		clock_gettime(CLOCK_MONOTONIC, &ts_2);
		printf("\nFunction usleep(10000): \n");
		Latency_cnt(&ts_1, &ts_2);
	}
	
	// 3. get time of day
	ret = gettimeofday(&tv, NULL);
	printf("\nFunction gettimeofday: \n");
	printf("RET[%d] Time Sec[%ld] usec[%ld]\n" , ret, tv.tv_sec, tv.tv_usec);
	
	
	
	return 0;
}
