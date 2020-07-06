// 多项式的乘法与加法运算，输入按照指数递增的顺序，输出的加法和乘法也按照递增顺序。
#include <iostream>
using namespace std;

typedef struct PolyNode {
	int coef;  // 系数
	int expon; // 指数
	PolyNode *next; // 下一项
}*Polynominal;

void CrePoly(Polynominal p) {
	Polynominal pn, q = p;
	p->coef = 0; // 带头节点的链表
	p->expon = -1;
	p->next = NULL;
	for (;;) {
		pn = (PolyNode*)malloc(sizeof(PolyNode));
		cout << "coef: ";
		cin >> pn->coef;
		cout << "expon: ";
		cin >> pn->expon;
		if (pn->expon < 0) { //当系数为负数时认为终止
			break;
		}
		pn->next = NULL;
		q->next = pn;
		q = q->next;
	}
}
void PrintPoly(Polynominal p) {
	Polynominal q = p->next;
	while (q != NULL) {
		if (q->next != NULL) {
			cout << q->coef << "x^" << q->expon << " + ";
		}
		else {
			cout << q->coef << "x^" << q->expon << endl;
		}
		q = q->next;
	}
	return;
}

Polynominal PolyAdd(Polynominal p1, Polynominal p2) {
	Polynominal res, font; // 结果多项式
	res = (PolyNode*)malloc(sizeof(PolyNode));
	res->coef = 0;
	res->expon = -1;
	res->next = NULL;
	font = res; // 指向结构多项式的头节点
	Polynominal rn; // 空数据块
	// q1,q2分别指向两个多项式的第一项
	Polynominal q1 = p1->next, q2 = p2->next;                              
	
	while (q1 != NULL && q2 !=NULL) {
		rn = (PolyNode*)malloc(sizeof(PolyNode));
		if (q1->expon == q2->expon) { // 指数相同
			int sum_coef = q1->coef + q2->coef;
			if (sum_coef != 0) { // 系数之和不为0
				rn->coef = sum_coef;
				rn->expon = q1->expon;
			}
			q1 = q1->next;
			q2 = q2->next;
			if(sum_coef == 0) {
				continue; // 没有生成项，所以不能让res->next指向rn
			}
		} else {
			if (q1->expon < q2->expon) {
				rn->coef = q1->coef;
				rn->expon = q1->expon;
				q1 = q1->next;
			} else {
				rn->coef = q2->coef;
				rn->expon = q2->expon;
				q2 = q2->next;
			}
		}
		res->next = rn;
		rn->next = NULL;
		res = res->next;
	}
	if (q1 != NULL) {
		res->next = q1;
	} else {
		res->next = q2;
	}
	return font;  // 返回结果多项式的头
}

Polynominal PolyMul(Polynominal p1, Polynominal p2) {
	// q1,q2分别指向两个多项式的第一项
	Polynominal q1 = p1->next, q2 = p2->next;
	Polynominal pn; // 一个数据块
	Polynominal p; 
	p = (PolyNode*)malloc(sizeof(PolyNode)); //空链表头
	Polynominal rear = p;
	while (q2) { // 先用p1第一项乘以p2，得到p
		pn = (PolyNode*)malloc(sizeof(PolyNode));
		pn->coef = q1->coef * q2->coef;
		pn->expon = q1->expon + q2->expon;
		if (pn->coef == 0) {
			q2 = q2->next;
			continue;
		}
		rear->next = pn;
		pn->next = NULL;
		q2 = q2->next;
		rear = rear->next;
	}
	q1 = q1->next;
	while (q1) { // p1第二项开始每一项分别与p2进行相乘
		q2 = p2->next;
		rear = p;
		while (q2) { // 乘出来的每一项需要找到插入p中的位置
			int c = q1->coef * q2->coef;
			int e = q1->expon + q2->expon;
			pn = (PolyNode*)malloc(sizeof(PolyNode));
			while (rear->next && rear->next->expon < e) { // 前面系数都比e小且后面还有项的时候遍历
				rear = rear->next;
			}
			if (rear->next && rear->next->expon == e) {
				rear->next->coef += c;
				if (!rear->next->coef) {
					Polynominal temp;
					temp = rear->next;
					rear->next = rear->next->next;
					free(temp);
				}
			} else {  // 系数大于rear所指的项
				pn->coef = c;
				pn->expon = e;
				if (rear->next && rear->next->expon > e) {
					pn->next = rear->next;
				}
				else if (!rear->next) {
					pn->next = NULL;
				}
				rear->next = pn;
			}
			q2 = q2->next;
		}
		q1 = q1->next;
	}
	return p;
}

int main() {
	Polynominal p1, p2, res;
	p1 = (PolyNode*)malloc(sizeof(PolyNode));
	p2 = (PolyNode*)malloc(sizeof(PolyNode));
  CrePoly(p1);
	PrintPoly(p1);
	CrePoly(p2);
	PrintPoly(p2);
	cout << "两个多项式之和为：" << endl;
	res = PolyAdd(p1, p2);
	PrintPoly(res);
	cout << "两个多项式相乘为：" << endl;
	res = PolyMul(p1, p2);
	PrintPoly(res);
	cin.get();
	return 0;
}
