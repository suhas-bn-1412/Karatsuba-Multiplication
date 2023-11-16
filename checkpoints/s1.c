#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

char* karatsuba(char* a, char* b)
{
	return "Well done";
}

bool is_zero(char* str)
{
	char* zero = (char*)malloc(sizeof(char)*(strlen(str)+1));
	memset(zero,'0',strlen(str));
	printf("str: %s   zero: %s\n", str, zero);
	if(strcmp(str,zero)==0)
		return true;
	return false;
}

int max(int a ,int b)
{
	if(a < b)
		return b;
	return a;
}

int* convert(char* c)
{
	int len=strlen(c),i;
	int *a=(int*)malloc(len*sizeof(int));
	for(i=0;i<len;i++)
		a[i]=c[i]-48;
	return a;
}

void str_add(char* a, char* b, char** ans)
{
	printf("call to str_add with a: %s  b: %s  ", a,b);
	int len_a = strlen(a);
	int len_b = strlen(b);
	int sz = max(len_a,len_b)+1;

	int* a1 = convert(a);
	int* b1 = convert(b);
	int* val = (int*)malloc(sizeof(int)*sz);
	memset(val,0,sz);

	int i = len_a-1;
	int j = len_b-1;
	int k = sz-1;
	int s = 0;
	int carry = 0;
	int sum = 0;
	while(i>=0 && j>=0)
	{
		s = a1[i] + b1[j] + carry;
		sum = s%10;
		carry = s/10;
		val[k] = sum;
		i--;
		j--;
		k--;
	}
	if(i<0 && j>=0)
	{
		while(j>=0)
		{
			s = b1[j]+carry;
			sum = s%10;
			carry = s/10;
			val[k] = sum;
			j--;
			k--;
		}
	}

	else if(j<0 && i>=0)
	{
		while(i>=0)
		{
			s = a1[i]+carry;
			sum = s%10;
			carry = s/10;
			val[k] = sum;
			i--;
			k--;
		}
	}

	if(carry!=0)
	{
		val[k] = carry;
	}

	i = 0;
	if(val[0]==0)
		i = 1;
	j = 0;
	char* res = *ans;
	while(i < sz && j < sz)
	{
		//res[j] = val[i];
		sprintf((res+j),"%d",val[i]);
		i++;
		j++;
	}
	printf("returning: %s\n", res);
	//return res;
}

int main()
{

	int dig_a;
	int dig_b;
	scanf("%d",&dig_a);
	scanf("%d",&dig_b);
	char* a = (char*)malloc(sizeof(char)*dig_a);
	char* b = (char*)malloc(sizeof(char)*dig_b);
	scanf("%s",a);
	scanf("%s",b);


	char* ans = (char*)malloc(sizeof(char)*(max(dig_a,dig_b)+1));
	memset(ans,'0',(max(dig_a,dig_b)+1));
	str_add(a,b,&ans);
	//ans = karatsuba(a,b);
	printf("%s\n", ans);
}