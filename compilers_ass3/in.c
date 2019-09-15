int foo(int a, int b[10])
{
	a = foo(a, b);
	return a;
}

int main(int a)
{
	int b[10][340];
	b[0] = foo(a, b);
	return a;
}
