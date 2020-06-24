// 求max{最大子列和，0}的几种方法，比较几种算法
#include <stdio.h>
#define LEN 8 // 子列的长度
int MaxSubseqSum1(int A[], int N);
int MaxSubseqSum2(int A[], int left, int right);
int maxThree(int a, int b, int c);
int MaxSubseqSum3(int A[], int N);
int main() {
  int A[LEN] = {4, -1, 5, -2, -1, 2, 6, -2};
  int sum1, sum2, sum3;
  sum1 = MaxSubseqSum1(A, LEN);
  sum2 = MaxSubseqSum2(A, 0, LEN-1);
  sum3 = MaxSubseqSum1(A, LEN);
  printf("暴力求解法得到最大子序列和为：%d\n", sum1);
  printf("分值法得到最大子序列和为：%d\n", sum2);
  printf("分值法得到最大子序列和为：%d\n", sum3);
  system("pause");
  return 0;
}
// 暴力求解，时间复杂度n^2
int MaxSubseqSum1(int A[], int N) {
  int ThisSum, MaxSum = 0;      
  int i, j;
  for(i = 0; i < N; i++) {      // 进行N轮的比较,即子列左端
    ThisSum = 0;                // 每轮开始当前结果置0
    for(j = i; j < N; j++) {    // j是子列右端位置
       ThisSum  += A[j];        
       if(ThisSum > MaxSum) {  //更新结果
         MaxSum = ThisSum;
       }
    }
  }                             
  return MaxSum;
}

//分治法,递归实现。时间复杂度为nlogn 
int MaxSubseqSum2(int A[], int left, int right) { 
  int iThisSum = 0, iLeftMaxSum, iRightMaxSum;
  int mid, lSum, rSum, mSum;
  int i;
  if(left >= right) { return A[left]; } 
  mid = (left + right) / 2;
  lSum = MaxSubseqSum2(A, left, mid);   // 解决左半边最大值
  rSum = MaxSubseqSum2(A, mid+1, right);// 解决右半边最大值
  // 解决跨越边界的最大和
  iLeftMaxSum = A[mid];
  for(i = mid; i >= left; i--) {         // 左边扫描
    iThisSum += A[i];
    if(iThisSum > iLeftMaxSum) {
      iLeftMaxSum = iThisSum;
    }
  }
  iThisSum = 0;
  iRightMaxSum = A[mid+1];
  for(i = mid + 1; i <= right; i++) {    // 右边扫描
    iThisSum += A[i];
    if(iThisSum > iRightMaxSum) {
      iRightMaxSum = iThisSum;
    }
  }
  mSum = iLeftMaxSum + iRightMaxSum;
  return maxThree(lSum, rSum, mSum); // 返回左、右、中的最大值
}
// 三个数中最大值。若全小于0，返回0
int maxThree(int a, int b, int c) {
  int max = a;
  if(a < 0 && b < 0 && c < 0) { return 0; }
  if(b > max) { max = b; }
  if(c > max) { max = c; }
  return max;
}

//在线求解法，O(n)
int MaxSubseqSum3(int A[], int N) {
  int i, sum = 0;
  for(i = 0; i < N; i++) {
    sum += A[i];
    if(sum < 0) {  // 如果前面的数之和小于0，再加上后面的数只会更小
      sum = 0;
      continue; 
    }
  }
  return sum;
}
