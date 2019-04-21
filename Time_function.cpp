// Linux time function learning note  

#include <stdio.h> 
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

/* 
struct timespec {
time_t tv_sec; // seconds 
long tv_nsec; // and nanoseconds 
};
struct timeval {
time_t tv_sec; // seconds 
long tv_usec; // microseconds 
};
*/

int main()
{	
	int ret;
	struct timeval tv;
	struct timespec ts;
/*
	#include<time.h>
	int clock_gettime(clockid_t clk_id,struct timespec *tp);
	clk_id : ���������õ�clk_idָ����ʱ��ʱ�䡣
	CLOCK_REALTIME:ϵͳʵʱʱ��,��ϵͳʵʱʱ��ı���ı�, UTC1970-1-1 0:0:0 ��ʼ 
����CLOCK_MONOTONIC:��ϵͳ������һ����ʼ��ʱ,����ϵͳʱ�䱻�û��ı��Ӱ��
����CLOCK_PROCESS_CPUTIME_ID:�����̵���ǰ����ϵͳCPU���ѵ�ʱ��
����CLOCK_THREAD_CPUTIME_ID:���̵߳���ǰ����ϵͳCPU���ѵ�ʱ��
*/
	clock_gettime(CLOCK_REALTIME, &ts);
	printf("Function clock_gettime : \n");
	// CLOCK_REALTIME: Real time, According to system time (Start from UTC1970-1-1 00:00:00)
	printf("Clk_id [CLOCK_REALTIMERET] -- RET[%d] Time Sec[%ld] nsec[%ld]\n" , ret, ts.tv_sec, ts.tv_nsec);
	clock_gettime(CLOCK_MONOTONIC, &ts);
	// CLOCK_MONOTONIC: Monotonic time, (Start from system init)
	printf("Clk_id [CLOCK_MONOTONIC]   -- RET[%d] Time Sec[%ld] nsec[%ld]\n" , ret, ts.tv_sec, ts.tv_nsec);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
	// CLOCK_MONOTONIC: Monotonic time, (Start from system init)
	printf("Clk_id [CLOCK_PROCESS_CPUTIME_ID]   -- RET[%d] Time Sec[%ld] nsec[%ld]\n" , ret, ts.tv_sec, ts.tv_nsec);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
	// CLOCK_MONOTONIC: Monotonic time, (Start from system init)
	printf("Clk_id [CLOCK_THREAD_CPUTIME_ID]    -- RET[%d] Time Sec[%ld] nsec[%ld]\n" , ret, ts.tv_sec, ts.tv_nsec);WW

/*
	#include <sys/time.h>
	int gettimeofday(struct timeval*tv, struct timezone *tz);
	struct timezone{
	int tz_minuteswest; //G.M.T.(Greenwich Mean Time) ʱ��� 
	int tz_dsttime;     //����ʱ����
*/
	ret = gettimeofday(&tv, NULL);
	printf("\nFunction gettimeofday: \n");
	printf("RET[%d] Time Sec[%ld] usec[%ld]\n" , ret, tv.tv_sec, tv.tv_usec);
	return 0;
}
