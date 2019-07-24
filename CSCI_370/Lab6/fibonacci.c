#include <stdio.h>

int
fib (int n);

int
zeros (int n);

int
main(int argc, char* argv[])
{
	printf("n ==> ");
	int x;
	scanf("%d", &x);

	int f = fib(x);
	int z = zeros(x);
	printf("fib(|%d|) - zeros(%d) = %d - %d = %d\n",
			x , x , f , z , (f - z) );
}

int
fib (int n)
{
	if ( n < 0 )
	{
		n *= -1;
	}
	if (n == 1 || n == 0)
	{
		return 1;
	}
	else 
	{
		return fib(n - 1) + fib(n - 2);
	}
}

int
zeros (int n)
{
	int z = 0;

	if ( n < 0 )
	{
		n *= -1;
	}
	else
	{
		z++;
	}

	for(int i = 0; i < 32; i++)
	{
		if ( ( n & (1 << i) ) == 0 )
		{
			z++;
		}
	}
}
