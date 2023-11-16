#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

#define MAX_DIGIT 150


void compute_uh(const char* str, int sz, char** uh)
{
	//printf("call to compute_uh with str: %s  sz: %d  ", str,sz);
	int i;
	for (i = 0; i < sz; ++i)
	{
		(*uh)[i] = str[i];
	}
	(*uh)[i]='\0';
	//printf("returning: %s\n", uh);
	//return uh;
}

void compute_lh(const char* str, int sz, char** lh)
{
	//printf("call to compute_lh with str: %s  sz: %d  ", str,sz);
	int len = strlen(str);
	sz = len - sz;
	int i;
	for (i = sz; i < len; ++i)
	{
		(*lh)[i-sz] = str[i];
	}
	(*lh)[i-sz]='\0';
	//printf("returning: %s\n", lh);
	//return lh;
}

char* str_mul(const char* a, const char* b)
{
	//printf("call to str_mul with a: %s  b: %s  ", a,b);
	int x = atoi(a);
	int y = atoi(b);
	int ans = x*y;
	char* res = (char*)malloc(sizeof(char)*5);
	sprintf(res,"%d",ans);
	//printf("returning: %s\n", res);
	return res;
}

int max(int a ,int b)
{
	if(a < b)
		return b;
	return a;
}

int* convert(const char* c)
{
	int len=strlen(c),i;
	int *a=(int*)malloc(len*sizeof(int));
	for(i=0;i<len;i++)
		a[i]=c[i]-48;
	return a;
}

void str_add(const char* a, const char* b,char** res)
{
	//printf("call to str_add with a: %s  b: %s  ", a,b);
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
	while(i < sz && j < sz)
	{
		//res[j] = val[i];
		sprintf(((*res)+j),"%d",val[i]);
		i++;
		j++;
	}
	//printf("returning: %s\n", *res);
}

void str_sub(const char* a, const char* b, char** res)
{
	//printf("call to str_sub with a: %s  b: %s  ", a,b);
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
	while(i < sz && j < sz)
	{
		//res[j] = val[i];
		sprintf(((*res)+j),"%d",val[i]);
		i++;
		j++;
	}
	//printf("returning: %s\n", *res);
}

void concatenate(char p[], char q[]) {
   int c, d;
   
   c = 0;
 
   while (p[c] != '\0') {
      c++;      
   }
 
   d = 0;
 
   while (q[d] != '\0') {
      p[c] = q[d];
      d++;
      c++;    
   }
 
   p[c] = '\0';
}

int split(int a, int b)
{
	if(a>=b)
		return (a - (a/2));
	else
		return (b - (b/2));
}

bool is_zero(const char* str)
{
	char* zero = (char*)malloc(sizeof(char)*(strlen(str)+1));
	memset(zero,'0',strlen(str));
	if(strcmp(str,zero)==0)
		return true;
	return false;
}

void karatsuba(const char* x, const char* y, char** res)
{
	int dig_x = strlen(x);
	int dig_y = strlen(y);
	if(dig_y < dig_x)
	{
		concat(&y, dig_x-dig_y);
	}
	if(dig_x < dig_y)
	{
		concat(&x, dig_y-dig_x);
	}
	printf("x: %s  y: %s\n", x, y);

	dig_x = strlen(x);
	dig_y = strlen(y);
	if (dig_x < 4 && dig_y < 4)
	{
		*res = str_mul(x,y);
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
			compute_uh(x,dig_x-t, &uh_x);
		else
			uh_x = zero;

		if(dig_y-t != 0)
			compute_uh(y,dig_y-t, &uh_y);
		else
			uh_y = zero;

		compute_lh(x,t,&lh_x);
		compute_lh(y,t,&lh_y);
		//printf("%s\n", uh_x);
		
		char* base = (char*)malloc(sizeof(char)*(t));
		memset(base,'0',t);

		char* a = (char*)malloc(sizeof(char)*(2*t + 1));
		char* d = (char*)malloc(sizeof(char)*(2*t + 1));

		if(is_zero(uh_x) || is_zero(uh_y))
			a = zero;
		else
			karatsuba(uh_x,uh_y,&a);

		if(is_zero(lh_x) || is_zero(lh_y))
		{
			//printf("lh_x: %s   lh_y: %s\n", lh_x, lh_y);
			d = zero;
		}
		else
		{
			karatsuba(lh_x,lh_y,&d);
			//printf("lh_x: %s   lh_y: %s\n", lh_x, lh_y);
			//printf("d: %s\n", d);
			if (is_zero(d))
			{
				//printf("YES\n");
				karatsuba(lh_x,lh_y,&d);
			}
		}
		const char* val_d = d;

		char* s1 = (char*)malloc(sizeof(char)*(strlen(lh_x) + 1));
		str_add(uh_x,lh_x,&s1);
		char* s2 = (char*)malloc(sizeof(char)*(strlen(lh_y) + 1));
		str_add(uh_y,lh_y,&s2);
		char* s3 = (char*)malloc(sizeof(char)*(max(strlen(a),strlen(d)) + 1));
		str_add(a,d,&s3);

		char* m = (char*)malloc(sizeof(char)*(max(strlen(s1),strlen(s2)) + 1));
		karatsuba(s1,s2,&m);

		char* e = (char*)malloc(sizeof(char*)*(strlen(m)));
		str_sub(m, s3, &e);

		//printf("x: %s   y: %s\n", x, y);
		//printf("a: %s   e: %s   d: %s\n", a, e, d);
		

		concatenate(e,base);
		char* s4 = (char*)malloc(sizeof(char)*(strlen(e)));
		str_add(e,val_d,&s4);

		concatenate(a,base);
		concatenate(a,base);
		str_add(s4,a,res);
		//printf("a: %s   \n", a);
		//printf("lh_x: %s   lh_y: %s\n", lh_x, lh_y);
		//printf("res: %s\n", *res);
		/*
		if(!is_zero(a))
			free(a);
		if(!is_zero(d))
			free(d);
		
		free(m);
		free(e);
		free(s1);
		free(s2);
		free(s3);
		free(s4);
		if(!is_zero(uh_x))
			free(uh_x);
		if(!is_zero(uh_y))
			free(uh_y);
		free(lh_x);
		free(lh_y);*/
	}
}

void concat(char** str, int n)
{
	int len = strlen(*str);
	int sz = len + n;
	char* p = (char*)malloc(sizeof(char)*sz);
	memset(p,'0',n);
	int i = n;
	int j = 0;
	while(i<sz)
	{
		p[i] = *(*str+j);
		i++;
		j++;
	}
	p[i] = '\0';
	*str = p;
}

void strip(char* str1, char** str2)
{
	int i=0;
	if(str1[0]=='+' || str1[0]=='-')
		i = 1;
	int k=0;
	while(i<strlen(str1))
	{
		(*str2)


		[k] = str1[i];
		i++;
		k++;
	}
}

int main()
{
	int dig_a;
	int dig_b;
	//scanf("%d",&dig);
	char* x = (char*)malloc(sizeof(char)*MAX_DIGIT);
	char* y = (char*)malloc(sizeof(char)*MAX_DIGIT);
	char* a = (char*)malloc(sizeof(char)*MAX_DIGIT);
	char* b = (char*)malloc(sizeof(char)*MAX_DIGIT);
	scanf("%s",x);
	scanf("%s",y);

	int flag=0;
	if(x[0]=='-')
		flag++;
	if(y[0]=='-')
		flag++;

	strip(x, &a);
	strip(y, &b);

	//printf("a: %s   b: %s\n", a, b);

	//printf("a: %s   b: %s\n", a, b);

	char* ans1 = (char*)malloc(sizeof(char)*(dig_a + dig_b + 1));

	karatsuba(a,b,&ans1);
	int i=0;
	while(ans1[i]=='0')
		i++;
	ans1 = (ans1+i);

	//printf("i:%d\n", i);

	if(flag==1)
		printf("-");
	printf("%s\n", ans1);
}
