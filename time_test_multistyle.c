// 浙大数据结构第一讲1.1，求多项式的值。利用clock()计算函数运行时间，观察算法对解决问题的效率。
#include <stdio.h>
#include <time.h>
#include <math.h>
clock_t start, stop;  // clock()返回的变量类型
double duration;      // 被检测数据运行时间
#define MAXN 10       // 多项式最大项数
#define MAXK 1e7      // 重复调用次数
double f1(int n, double a[], double x);
double f2(int n, double a[], double x);

int main() {
	int i;
	double a[MAXN];
	for(i = 0; i < MAXN; i++) {
		a[i] = (double)i;
	}

	start = clock();
	for(i = 0; i < MAXK; i++) {
		f1(MAXN - 1, a, 1.1);
	}
	stop = clock();
	duration = (double)(stop - start) / CLK_TCK;
	printf("ticks1 = %f\n", (double)(stop - start));
	printf("duration = %6.2e\n", duration);

	start = clock();
	for(i = 0; i < MAXK; i++) {
		f2(MAXN - 1, a, 1.1);
	}
	stop = clock();
	duration = (double)(stop - start) / CLK_TCK;
	printf("ticks2 = %f\n", (double)(stop - start));
	printf("duration = %6.2e\n", duration);
	system("pause");
	return 0;
}

// 直接相加
double f1(int n, double a[], double x) {  
	int i;
	double sum = a[0];
	for(i = 1; i <= n; i++) {
		sum += a[i] * pow(x, i);
	}
	return sum;
}

// 提取法
double f2(int n, double a[], double x) {
	int i;
	double sum = a[n];
	for(i = n; i >= 1; i--) {
		sum = a[i-1] + x * sum;
	}
	return sum;
}
