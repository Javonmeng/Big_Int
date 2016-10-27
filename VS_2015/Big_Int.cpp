#include<string.h>
#include<stdio.h>
#include<cmath>
#define MAX 200000
#define MAXN 100000
#define MAX1 10000
#define PI 3.14159265359
#define YES 1
#define NO 0
#define OK 1
#define ERROR 0


////////*****加减法代码部分开始*******/////////
int maxlen;

void Trans(char *str1, char *str2, int A[MAX], int B[MAX]) {
	int len1, len2;
	len1 = strlen(str1);
	len2 = strlen(str2);
	maxlen = (len1 > len2 ? len1 : len2) + 1;
	for (int i = 0; i < len1; ++i)
		A[i] = str1[len1 - i - 1] - '0';
	for (int i = 0; i < len2; ++i)
		B[i] = str2[len2 - i - 1] - '0';
	//倒置 
	for (int i = len1; i < maxlen; ++i)
		A[i] = 0;
	for (int i = len2; i < maxlen; ++i)
		B[i] = 0;
}

void Adjust_Add(int *res) {
	for (int i = 0; i < maxlen; ++i) {
		res[i + 1] += res[i] / 10;
		res[i] %= 10;
	}
	//调整加法输出 
	while (res[maxlen - 1] == 0)
		maxlen--;
}

void Adjust_Sub(int *res) {
	int borrow = 0;
	for (int i = 0; i < maxlen; ++i) {
		if (res[i] < 0)
			borrow = 1;
		res[i + 1] -= borrow;
		borrow = 0;
		res[i] = (res[i] + 10) % 10;
	}
	//调整减法输出 
	while (res[maxlen - 1] == 0)
		maxlen--;
}

int isLeftBigger(char *str1, char *str2) {
	if (strlen(str1) > strlen(str2))
		return YES;
	else if (strlen(str1) < strlen(str2))
		return NO;
	else {
		if (strcmp(str1, str2) >= 0)
			return YES;
		else
			return NO;
	}
}

void Add(char *leftVal, char *rightVal, int *resBuf) {//无符号加法 
	int *A = new int[MAX], *B = new int[MAX];
	Trans(leftVal, rightVal, A, B);
	for (int i = 0; i < maxlen; ++i)
		resBuf[i] = A[i] + B[i];
	Adjust_Add(resBuf);
}

void Sub(char *leftVal, char *rightVal, int *resBuf) {//无符号减法 
	int *A = new int[MAX], *B = new int[MAX];
	Trans(leftVal, rightVal, A, B);
	for (int i = 0; i < maxlen; ++i)
		resBuf[i] = A[i] - B[i];
	Adjust_Sub(resBuf);
}

void Big_Add(char *leftVal, char *rightVal, char *res) {//减法看做加法 
	int len0;
	len0 = strlen(leftVal) > strlen(rightVal) ? strlen(leftVal) : strlen(rightVal);
	int *resBuf = new int[len0];
	if ((leftVal[0] >= '0' && leftVal[0] <= '9') && (rightVal[0] >= '0' && rightVal[0] <= '9')) {
		//左右两边均为直接正数
		Add(leftVal, rightVal, resBuf);
		for (int i = maxlen - 1; i >= 0; --i)
			res[maxlen - i - 1] = resBuf[i] + '0';
	}
	else if ((leftVal[0] >= '0' && leftVal[0] <= '9') && (rightVal[0] == '+' || rightVal[0] == '-')) {
		if (rightVal[0] == '+') {
			//左边为直接正数，右边为带‘+’正数
			Add(leftVal, rightVal + 1, resBuf);
			for (int i = maxlen - 1; i >= 0; --i)
				res[maxlen - i - 1] = resBuf[i] + '0';
		}
		else {				 
			//左边为直接正数，右边为带'-'负数
			if (isLeftBigger(leftVal, rightVal + 1)) {
				Sub(leftVal, rightVal + 1, resBuf);
				for (int i = maxlen - 1; i >= 0; --i)
					res[maxlen - i - 1] = resBuf[i] + '0';
			}
			else {
				Sub(rightVal + 1, leftVal, resBuf);
				res[0] = '-';
				for (int i = maxlen; i >= 1; --i)
					res[maxlen - i + 1] = resBuf[i - 1] + '0';
				maxlen++;

			}
		}
	}
	else if ((rightVal[0] >= '0' && rightVal[0] <= '9') && (leftVal[0] == '+' || leftVal[0] == '-')) {

		if (leftVal[0] == '+') {
			//左边为带‘+’的正数，右边为直接正数
			Add(leftVal + 1, rightVal, resBuf);
			for (int i = maxlen - 1; i >= 0; --i)
				res[maxlen - i - 1] = resBuf[i] + '0';
		}
		else {	 
			//左边为带‘-’的正数，右边为直接正数
			if (isLeftBigger(leftVal + 1, rightVal)) {
				Sub(leftVal + 1, rightVal, resBuf);
				res[0] = '-';
				for (int i = maxlen; i >= 1; --i)
					res[maxlen - i + 1] = resBuf[i - 1] + '0';
				maxlen++;
			}
			else {
				Sub(rightVal, leftVal + 1, resBuf);
				for (int i = maxlen - 1; i >= 0; --i)
					res[maxlen - i - 1] = resBuf[i] + '0';
			}
		}
	}
	else if ((leftVal[0] == '+' && rightVal[0] == '+') || (leftVal[0] == '-' && rightVal[0] == '-')) {
		//左右两边同为带‘+’的正数，或两边同为带'-'的负数
		Add(leftVal + 1, rightVal + 1, resBuf);
		if (leftVal[0] == '+')
			for (int i = 0; i <= maxlen - 1; ++i)
				res[maxlen - i - 1] = resBuf[i] + '0';
		else {
			for (int i = maxlen; i >= 1; --i)
				res[maxlen - i + 1] = resBuf[i - 1] + '0';
			res[0] = '-';
			maxlen++;
		}
	}
	else if ((leftVal[0] == '+' && rightVal[0] == '-') || (leftVal[0] == '-' && rightVal[0] == '+')) {
		//左边为带‘+’的正数，右边为带‘-’的负数
		if (leftVal[0] == '+') {
			if (isLeftBigger(leftVal + 1, rightVal + 1)) {
				Sub(leftVal + 1, rightVal + 1, resBuf);
				for (int i = maxlen - 1; i >= 0; --i)
					res[maxlen - i - 1] = resBuf[i] + '0';
			}
			else {
				Sub(rightVal + 1, leftVal + 1, resBuf);
				res[0] = '-';
				for (int i = maxlen; i >= 1; --i)
					res[maxlen - i + 1] = resBuf[i - 1] + '0';
				maxlen++;
			}
		}
		else {	             
			if (isLeftBigger(leftVal + 1, rightVal + 1)) {
				Sub(leftVal + 1, rightVal + 1, resBuf);
				res[0] = '-';
				for (int i = maxlen; i >= 1; --i)
					res[maxlen - i + 1] = resBuf[i - 1] + '0';
				maxlen++;
			}
			else {
				Sub(rightVal + 1, leftVal + 1, resBuf);
				for (int i = maxlen - 1; i >= 0; --i)
					res[maxlen - i - 1] = resBuf[i] + '0';
			}
		}
	}
	if (maxlen == 0) {
		res[maxlen] = '0';
		res[maxlen + 1] = '\0';
	}
	else
		res[maxlen] = '\0';
}
/////////*******加减法结束********///////////////////////

////////********乘法代码开始******///////////////////////
int len;

class Complex
{
public:
	double real, imag;
	Complex(double real = 0.0, double imag = 0.0)
	{
		this->real = real, this->imag = imag;
	}
	Complex operator - (const Complex &elem) const
	{
		return Complex(this->real - elem.real, this->imag - elem.imag);
	}
	Complex operator + (const Complex &elem) const
	{
		return Complex(this->real + elem.real, this->imag + elem.imag);
	}
	Complex operator * (const Complex &elem) const
	{
		return Complex(this->real * elem.real - this->imag * elem.imag, this->real * elem.imag + this->imag * elem.real);
	}
	void setValue(double real = 0.0, double imag = 0.0)
	{
		this->real = real, this->imag = imag;
	}
};

void Swap(Complex &a, Complex &b) {
	Complex tmp = a;
	a = b;
	b = tmp;
}//交换

int max(int a, int b) {
	return a > b ? a : b;
}

void Prepare(char *str1, char *str2, Complex A[MAX], Complex B[MAX]) {
	int len1, len2, mlen;
	len1 = strlen(str1);
	len2 = strlen(str2);
	mlen = max(len1, len2);
	len = 1;
	//要用FFT，将len扩充为2的整数次幂
	while (len < (mlen << 1))
		len <<= 1;
	//初始化多项式的系数
	for (int i = 0; i < len1; ++i)
		A[i].setValue(str1[len1 - i - 1] - '0', 0.0);
	for (int i = 0; i < len2; ++i)
		B[i].setValue(str2[len2 - i - 1] - '0', 0.0);
	//补0
	for (int i = len1; i < len; ++i)
		A[i].setValue();
	for (int i = len2; i < len; ++i)
		B[i].setValue();
}

void Rader(Complex y[]) {
	for (int i = 1, j = len >> 1, k; i < len - 1; ++i) {
		if (i < j)
			Swap(y[i], y[j]);
		k = len >> 1;
		while (j >= k) {
			j -= k;
			k >>= 1;
		}
		if (j < k)
			j += k;
	}
}//雷德算法，位逆序置换

void FFT(Complex y[], int op) {
	//先位逆序置换
	Rader(y);
	//h为每次要处理的长度,h=1时不需要处理
	for (int h = 2; h <= len; h <<= 1) {
		//Wn = e^(2 * PI / n)
		Complex Wn(cos(op * 2 * PI / h), sin(op * 2 * PI / h));
		for (int i = 0; i < len; i += h) {
			//旋转因子，初始化为e^0
			Complex W(1, 0);
			for (int j = i; j < i + h / 2; ++j) {
				Complex u = y[j];
				Complex t = W * y[j + h / 2];
				//蝴蝶操作
				y[j] = u + t;
				y[j + h / 2] = u - t;
				//更新旋转因子
				W = W * Wn;
			}
		}
	}
	//插值的时候要除以len
	if (op == -1) {
		for (int i = 0; i < len; ++i)
			y[i].real /= len;
	}
}//op为1:DFT,op为-1:IDFT

void Convolution(Complex *A, Complex *B, int *res) {
	//evaluation
	FFT(A, 1), FFT(B, 1);
	for (int i = 0; i < len; ++i)
		A[i] = A[i] * B[i];
	//interpolation
	FFT(A, -1);
	for (int i = 0; i < len; ++i)
		res[i] = (int)(A[i].real + 0.5);
}//卷积求A*B,结果放置在res中

void Adjust(int *res) {
	for (int i = 0; i < len; ++i) {
		res[i + 1] += res[i] / 10;
		res[i] %= 10;
	}
	//去除多余的0
	while (res[len] == 0 && len != -1)
		len--;
	len++;
}

void Mul(char *leftVal, char *rightVal, int *resBuf) {
	Complex *A = new Complex[MAX1], *B = new Complex[MAX1];
	Prepare(leftVal, rightVal, A, B);
	Convolution(A, B, resBuf);
	Adjust(resBuf);
}

void Big_Mul(char *leftVal, char *rightVal, char *res) {
	int *resBuf = new int[MAX];
	for (int i = 0; i < MAX; i++)
		resBuf[i] = 0;
	if ((leftVal[0] >= '0' && leftVal[0] <= '9') && (rightVal[0] >= '0' && rightVal[0] <= '9')) {
		Mul(leftVal, rightVal, resBuf);
		for (int i = len - 1; i >= 0; --i)
			res[len - i - 1] = resBuf[i] + '0';
	}//正常无符号输入
	else if ((leftVal[0] >= '0' && leftVal[0] <= '9') && (rightVal[0] == '+' || rightVal[0] == '-')) {
		Mul(leftVal, rightVal + 1, resBuf);
		if (rightVal[0] == '+')//右式带正号
			for (int i = len - 1; i >= 0; --i)
				res[len - i - 1] = resBuf[i] + '0';
		else {				  //右式带负号
			for (int i = len; i >= 1; --i)
				res[len - i + 1] = resBuf[i - 1] + '0';
			res[0] = '-';
			len++;
		}
	}
	else if ((rightVal[0] >= '0' && rightVal[0] <= '9') && (leftVal[0] == '+' || leftVal[0] == '-')) {
		Mul(leftVal + 1, rightVal, resBuf);
		if (leftVal[0] == '+')//左式带正号
			for (int i = len - 1; i >= 0; --i)
				res[len - i - 1] = resBuf[i] + '0';
		else {	             //左式带负号
			res[0] = '-';
			for (int i = len; i >= 1; --i)
				res[len - i + 1] = resBuf[i - 1] + '0';
			len++;
		}
	}
	else if ((leftVal[0] == '+' && rightVal[0] == '+') || (leftVal[0] == '-' && rightVal[0] == '-')) {
		Mul(leftVal + 1, rightVal + 1, resBuf);
		for (int i = len - 1; i >= 0; --i)
			res[len - i - 1] = resBuf[i] + '0';
	}//两式都带正号或者负号
	else if ((leftVal[0] == '+' && rightVal[0] == '-') || (leftVal[0] == '-' && rightVal[0] == '+')) {
		Mul(leftVal + 1, rightVal + 1, resBuf);
		res[0] = '-';
		for (int i = len; i >= 1; --i)
			res[len - i + 1] = resBuf[i - 1] + '0';
		len++;
	}//两式一正一负
	if (len == 0) {
		res[len] = '0';
		res[len + 1] = '\0';
	}
	else
		res[len] = '\0';
}
////////////******乘法结束********///////////////////////////////

///////////*******除法代码开始****///////////////////////////////
void mul(char *Val, char *res, int x) {//x为一位整数，运算过程中获取商 
	int len0 = strlen(Val) + 1;
	int *tmp = new int[len0];
	tmp[len0 - 1] = 0;
	int i;
	for (i = 0; i < len0 - 1; i++) {
		tmp[len0 - i - 2] = (Val[i] - '0') * x;
	}
	for (i = 0; i < len0 - 1; i++) {
		tmp[i + 1] += tmp[i] / 10;
		tmp[i] %= 10;
	}
	if (tmp[len0 - 1] == 0)
		len0--;
	for (i = 0; i < len0; i++)
		res[i] = tmp[len0 - i - 1] + '0';
	res[i] = '\0';
}

void Div(char *leftVal, char *rightVal, int &res, char *extra) {//被除数只比除数多一位或者相等 ，商只有一位 
	int len1;
	len1 = strlen(leftVal);
	char *tmp = new char[len1];
	int *array = new int[len1];
	res = 1;
	if (!isLeftBigger(leftVal, rightVal)) {
		res = 0;
		int i = 0;
		while (leftVal[i] != '\0')
		{
			extra[i] = leftVal[i];
			i++;
		}
	}
	else if (strcmp(leftVal, rightVal) == 0) {
		res = 1;
		extra[0] = '0', extra[1] = '\0';
	}
	else {
		while (res <= 9) {
			mul(rightVal, tmp, res);
			if (isLeftBigger(leftVal, tmp)) {
				res++;
			}
			else {
				res--;
				break;
			}
		}
		if (res == 10)
			res--;
		mul(rightVal, tmp, res);
		Sub(leftVal, tmp, array);
		for (int i = maxlen - 1; i >= 0; --i)
			extra[maxlen - i - 1] = array[i] + '0';
		extra[maxlen] = '\0';
	}
}

int Big_Div(char *leftVal, char *rightVal, char *res, char *extra) {//模拟竖式除法运算 
	int len1, len2, c, i;
	len1 = strlen(leftVal), len2 = strlen(rightVal);
	if (len2 == 1 && rightVal[0] == '0') {
		printf("INPUT ERROR\n");
		return 0;
	}
	else if (len1 == 1 && leftVal[0] == '0') {
		res[0] = '0';
		res[1] = '\0';
		extra[0] = '0';
		extra[1] = '\0';
	}
	else if (len1 < len2) {
		res[0] = '0';
		res[1] = '\0';
		int i=0; 
		while (leftVal[i]!='\0')
		{
			extra[i] = leftVal[i];
			i++;
		}
	}
	else if (len1 == len2) {
		Div(leftVal, rightVal, c, extra);
		res[0] = c + '0';
	}
	else {
		int now = 0;
		int j = 1;
		for (; now < len2; now++)
			extra[now] = leftVal[now];
		extra[now] = '\0';
		Div(extra, rightVal, c, extra);
		res[0] = '0' + c;
		while (leftVal[now] != '\0') {
			int len3 = strlen(extra);
			extra[len3] = leftVal[now];
			extra[len3 + 1] = '\0';
			Div(extra, rightVal, c, extra);
			res[j] = '0' + c;
			j++;
			now++;
		}
		res[j] = '\0';
		//strcpy_s(extra, sizeof(tmp), tmp);//	extra = tmp;
		now = 0, j = 0;
		while (res[now] != '\0' && res[now] == '0')
			now++;
		for (j = now, i = 0; res[j] != '\0'; j++, i++)
			res[i] = res[j];
		res[i] = '\0';
	}
	if (extra[0] == '\0') 
	{
		extra[0] = '0';
		extra[1] = '\0';
	}
	return OK;

}
//////////********除法结束******///////////////////////////////

using namespace std;
char str1[MAXN], str2[MAXN], res[MAX],extra[MAXN];;//提前开辟内存 

int Inspect(char *s) {//检查操作数 
	int i = 0;
	if (s[i] == '\0') {
		printf("INPUT ERROR\n");
		return ERROR;
	}//非空字符串
	if (!((s[i] >= '0' && s[i] <= '9') || s[i] == '+' || s[i] == '-')) {
		printf("INPUT ERROR\n");
		return ERROR;
	}//第一个字符可为0~9或者'+'、'-'
	i++;//之后必须为0~9
	while (s[i] != '\0') {
		if (!(s[i] >= '0' && s[i] <= '9')) {
			printf("INPUT ERROR\n");
			return ERROR;
		}
		i++;
	}
	return OK;
}

int InspectOp(char *op) {//检查运算符 
	if ((op[0] == '+' || op[0]== '-' || op[0] == '*' || op[0] == '/') && op[1] == '\0') {

		return OK;
	}
	else {
		printf_s("INPUT ERROR\n");
		return ERROR;
	}
}

int main() {
	char op[100];
	char tmp[MAX];
	while (gets_s(str1)!= NULL
	&&gets_s(str2)!= NULL
	&&gets_s(op)!= NULL
	)
	{
		res[0] = '\0';
		extra[0] = '\0';
		if (Inspect(str1) && Inspect(str2) && InspectOp(op)) {
			switch (op[0]) {//根据操作数运算 
			case '+':
				Big_Add(str1, str2, res);
				printf("%s\n", res);
				break;

			case '-':
				if (str2[0] == '+') {
					str2[0] = '-';
					Big_Add(str1, str2, res);
				}
				else if (str2[0] == '-') {
					str2[0] = '+';
					Big_Add(str1, str2, res);
				}
				else {
					strcpy_s(tmp + 1, sizeof(str2), str2);
					tmp[0] = '-';
					Big_Add(str1, tmp, res);
				}
				printf("%s\n", res);
				break;

			case '*':
				Big_Mul(str1, str2, res);
				printf("%s\n", res);
				break;

			case '/':
				if (Big_Div(str1, str2, res, extra))
				{
					printf("%s ", res);
					printf("%s\n", extra);
				}
				break;

			}

		}
		else
			continue;
	}
}
