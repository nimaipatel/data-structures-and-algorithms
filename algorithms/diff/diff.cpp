#include <iostream>
#include <fstream>
#include <vector>

int**
fill_table(std::vector<std::string>v1, std::vector<std::string> v2,
           int m, int n)
{
	int **l = new int*[m + 1];
	for (int i = 0; i < m + 1; ++i) {
		l[i] = new int[n + 1];
	}

	for (int i = 0; i < m + 1; ++i) {
		for (int j = 0; j < n + 1; ++j) {
			if (i == 0 || j == 0) {
				l[i][j] = 0;
			} else if(v1.at(i - 1) == v2.at(j - 1)) {
				l[i][j] = l[i - 1][j - 1] + 1;
			} else {
				l[i][j] = std::max(l[i - 1][j], l[i][j - 1]);
			}
		}
	}

	/* LCS length is stored at l[m][n] */
	return l;
}

void
print_diff(int **l, std::vector<std::string> v1, std::vector<std::string> v2,
     int m, int n)
{
	if (m > 0 && n > 0 && v1.at(m - 1) == v2.at(n - 1)) {
		print_diff(l, v1, v2, m - 1, n - 1);
		std::cout << " " << v1.at(m - 1) << "\n";
	} else if (n > 0 && (m == 0 || l[m][n - 1] >= l[m - 1][n])) {
		print_diff(l, v1, v2, m, n - 1);
		std::cout << "+" << v2.at(n - 1) << "\n";
	} else if (m > 0 && (n == 0 || l[m][n - 1] < l[m - 1][n])) {
		print_diff(l, v1, v2, m - 1, n);
		std::cout << "-" << v1.at(m - 1) << "\n";
	}
}

int
main(int argc, char **argv)
{
	if (argc != 3) {
		std::cerr << "Error: expecting path to TWO files\n";
	}

	std::vector<std::string> f1_lines, f2_lines;
	std::string tmp;
	std::fstream fs;
	fs.open(argv[1], std::ios::in);
	if(!fs.is_open()) {
		std::cerr << "couln't open file " + (std::string)argv[1] + "\n";
	}
	while(getline(fs, tmp)) {
		f1_lines.push_back(tmp);
	}
	fs.close();
	fs.open(argv[2], std::ios::in);
	if(!fs.is_open()) {
		std::cerr << "couln't open file " + (std::string)argv[2] + "\n";
	}
	while(getline(fs, tmp)) {
		f2_lines.push_back(tmp);
	}
	fs.close();

	int  m = f1_lines.size();
	int  n = f2_lines.size();
	int **l = fill_table(f1_lines, f2_lines, m, n);
	print_diff(l, f1_lines, f2_lines, m, n);

	for (int i = 0; i < m + 1; ++i) {
		delete l[i];
	}
	delete l;

	return 0;
}
