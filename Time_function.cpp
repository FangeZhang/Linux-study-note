/* 
 * Time function learning note  
 * Introduction: 
	========================================================================
	struct timespec {
	time_t tv_sec; // seconds 
	long tv_nsec; // and nanoseconds 纳秒
	};
	========================================================================
	struct timeval {
	time_t tv_sec; // seconds 
	long tv_usec; // microseconds 微秒
	};
	========================================================================
 	#include <sys/time.h>
	int gettimeofday(struct timeval*tv, struct timezone *tz);
	struct timezone{
	int tz_minuteswest; //G.M.T.(Greenwich Mean Time) 与零时区的时间差 
	int tz_dsttime;     //夏令时修正, 夏令时为1
	========================================================================
	#include<time.h>
	int clock_gettime(clockid_t clk_id,struct timespec *tp);
	clk_id : 检索和设置的clk_id指定的时钟时间。
	CLOCK_REALTIME:系统实时时间,随系统实时时间改变而改变, UTC1970-1-1 0:0:0 开始 
	CLOCK_MONOTONIC:从系统启动这一刻起开始计时,不受系统时间被用户改变的影响
	CLOCK_PROCESS_CPUTIME_ID:本进程到当前代码系统CPU花费的时间
	CLOCK_THREAD_CPUTIME_ID:本线程到当前代码系统CPU花费的时间
 	========================================================================
 */
#include <stdio.h> 
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

int main()
{	
	int ret;
	struct timeval tv;
	struct timespec ts;

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

	ret = gettimeofday(&tv, NULL);
	printf("\nFunction gettimeofday: \n");
	printf("RET[%d] Time Sec[%ld] usec[%ld]\n" , ret, tv.tv_sec, tv.tv_usec);
	return 0;
}
