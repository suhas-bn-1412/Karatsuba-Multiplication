#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

char* compute_uh(char* str, int sz)
{
	printf("call to compute_uh with str: %s  sz: %d  ", str,sz);
	char* uh = (char*)malloc(sizeof(char)*(sz));
	int i;
	for (i = 0; i < sz; ++i)
	{
		uh[i] = str[i];
	}
	uh[i]='\0';
	printf("returning: %s\n", uh);
	return uh;
}

char* compute_lh(char* str, int sz)
{
	printf("call to compute_lh with str: %s  sz: %d  ", str,sz);
	int len = strlen(str);
	char* lh = (char*)malloc(sizeof(char)*(sz+1));
	sz = len - sz;
	int i;
	for (i = sz; i < len; ++i)
	{
		lh[i-sz] = str[i];
	}
	lh[i-sz]='\0';
	printf("returning: %s\n", lh);
	return lh;
}

char* str_mul(char* a, char* b)
{
	printf("call to str_mul with a: %s  b: %s  ", a,b);
	int x = atoi(a);
	int y = atoi(b);
	int ans = x*y;
	char* res = (char*)malloc(sizeof(char)*5);
	sprintf(res,"%d",ans);
	printf("returning: %s\n", res);
	return res;
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

char* str_add(char* a, char* b)
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

	else
	{
		val[k] = carry;
	}

	i = 0;
	if(val[0]==0)
		i = 1;
	j = 0;
	char* res = (char*)malloc(sizeof(char)*(sz));
	while(i < sz && j < sz)
	{
		//res[j] = val[i];
		sprintf((res+j),"%d",val[i]);
		i++;
		j++;
	}
	printf("returning: %s\n", res);
	return res;
}

char* str_sub(char* a, char* b)
{
	printf("call to str_sub with a: %s  b: %s  ", a,b);
	int len_a = strlen(a);
	int len_b = strlen(b);
	int sz = max(len_a,len_b);

	int* a1 = convert(a);
	int* b1 = convert(b);
	int* val = (int*)malloc(sizeof(int)*sz);
	memset(val,0,sz);

	int i = len_a-1;
	int j = len_b-1;
	int k = sz-1;
	int s = 0;
	int borrow = 0;
	int diff = 0;

	while(i>=0 && j>=0)
	{
		s = a1[i] - b1[j] - borrow;
		if(s < 0)
		{
			diff = 10+s;
			borrow = 1;
		}
		else
		{
			diff = s;
			borrow = 0;
		}
		val[k] = diff;
		i--;
		j--;
		k--;
	}

	if(j<0 && i>=0)
	{
		while(i>=0)
		{
			s = a1[i] - borrow;
			if(s < 0)
			{
				diff = 10+s;
				borrow = 1;
			}
			else
			{
				diff = s;
				borrow = 0;
			}
			val[k] = diff;
			i--;
			k--;
		}
	}

	i = 0;
	while(val[i]==0)
		i++;
	j = 0;
	char* res = (char*)malloc(sizeof(char)*(sz));
	while(i < sz && j < sz)
	{
		//res[j] = val[i];
		sprintf((res+j),"%d",val[i]);
		i++;
		j++;
	}
	printf("returning: %s\n", res);
	return res;
}

int split(int a, int b)
{
	if(a>=b)
		return (a - (a/2));
	else
		return (b - (b/2));
}

bool is_zero(char* str)
{
	char* zero = (char*)malloc(sizeof(char)*(strlen(str)+1));
	memset(zero,'0',strlen(str));
	if(strcmp(str,zero)==0)
		return true;
	return false;
}

char* karatsuba(char* x, char* y)
{
	int dig_x = strlen(x);
	int dig_y = strlen(y);

	if (dig_x < 4 && dig_y < 4)
	{
		return str_mul(x,y);
	}

	else
	{
		int t = split(dig_x,dig_y);
		char* uh_x = (char*)malloc(sizeof(char)*(dig_x - t + 1));
		char* uh_y = (char*)malloc(sizeof(char)*(dig_x - t + 1));
		char* lh_x = (char*)malloc(sizeof(char)*(t + 1));
		char* lh_y = (char*)malloc(sizeof(char)*(t + 1));

		char* zero = (char*)malloc(sizeof(char));
		memset(zero,'0',1);
		if(dig_x-t != 0)
			uh_x = compute_uh(x,dig_x-t);
		else
			uh_x = zero;

		if(dig_y-t != 0)
			uh_y = compute_uh(y,dig_y-t);
		else
			uh_y = zero;

		lh_x = compute_lh(x,t);
		lh_y = compute_lh(y,t);
		//printf("%s\n", uh_x);
		
		char* base = (char*)malloc(sizeof(char)*(t));
		memset(base,'0',t);

		char* a = (char*)malloc(sizeof(char)*(2*t + 1));
		char* d = (char*)malloc(sizeof(char)*(2*t + 1));

		if(is_zero(uh_x) || is_zero(uh_y))
			a = zero;
		else
			a = karatsuba(uh_x,uh_y);

		if(is_zero(lh_x) || is_zero(lh_y))
			d = zero;
		else
			d = karatsuba(lh_x,lh_y);

		char* m = karatsuba(str_add(uh_x,lh_x),str_add(uh_y,lh_y));
		char* e = str_sub(m, str_add(a,d));

		strcat(a,base);
		strcat(a,base);
		strcat(e,base);

		char* res = str_add(a,str_add(e,d));
		
		//free(a);
		//free(d);
		free(m);
		free(e);
		//free(uh_x);
		//free(uh_y);
		free(lh_x);
		free(lh_y);
		return res;
	}
}


int main()
{
	int dig;
	scanf("%d",&dig);
	char* a = (char*)malloc(sizeof(char)*dig);
	char* b = (char*)malloc(sizeof(char)*dig);

	scanf("%s",a);
	scanf("%s",b);

	//printf("%s\n", a);
	//printf("%s\n", b);

	char* ans1 = karatsuba(a,b);
	printf("%s\n", ans1);
}
