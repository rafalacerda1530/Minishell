#include <stdio.h>
#include <unistd.h>

int main (int argc, char **argv)
{
	char pwd[4096];
	printf("%s\n", getcwd(pwd, 4096));

	return 0;
}