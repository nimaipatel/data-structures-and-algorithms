#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
max(int a, int b)
{
	return a > b ? a : b;
}

int
lcs(char *str1, char *str2)
{
	int m = strlen(str1);
	int n = strlen(str2);
	int l[m + 1][n + 1];

	for (int i = 0; i < m + 1; ++i) {
		for (int j = 0; j < n + 1; ++j) {
			if (i == 0 || j == 0)
				l[i][j] = 0;
			else if(str1[i - 1] == str2 [j - 1])
				l[i][j] = l[i - 1][j - 1] + 1;
			else
				l[i][j] = max(l[i - 1][j], l[i][j - 1]);
		}
	}
	 
	return l[m][n];
}

int
main(int argc, char **argv)
{
	printf("Length of LCS: %d\n", lcs(argv[1], argv[2]));
}
