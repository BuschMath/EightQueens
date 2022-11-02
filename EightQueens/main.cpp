#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int problemSize = 10;
string outputFileName = "10QueensSolutions.dat";

void ini(int* board, vector<vector<bool>>& options);
void iniBoard(int* board);
void iniOptions(vector<vector<bool>>& options);
void brute(int* board, vector<vector<bool>>& options);
void update(int i, int j, vector<vector<bool>>& options);

int main()
{
	int board[problemSize];
	vector<vector<bool>> options; 

	for (int i = 0; i < problemSize; i++)
	{
		options.push_back(vector<bool>(problemSize, true));
	}

	ini(board, options);
	brute(board, options);

	return 0;
}

void ini(int* board, vector<vector<bool>>& options)
{
	iniBoard(board);
	iniOptions(options);
}

void iniBoard(int* board)
{
	for (int i = 0; i < problemSize; i++)
	{
		board[i] = -1;
	}
}

void iniOptions(vector<vector<bool>>& options)
{
	for (int i = 0; i < problemSize; i++)
	{
		for (int j = 0; j < problemSize; j++)
		{
			options[i][j] = true;
		}
	}
}

void brute(int* board, vector<vector<bool>>& options)
{
	bool found = false;
	int solutionCount = 0;
	ofstream outfile;
	outfile.open(outputFileName);

	if (!outfile)
		cout << "Can't open file.\n";

	for (int i = 0; i < problemSize; i++)
	{
		for (int j = 0; j < problemSize; j++)
		{
			if (options[i][j] == true)
			{
				board[i] = j;
				update(i, j, options);
				found = true;

				if (i == problemSize - 1)
				{
					outfile << ++solutionCount << ": ";
					for (int k = 0; k < problemSize; k++)
					{
						outfile << board[k];
					}
					outfile << endl;
					found = false;
				}

				break;
			}
		}
		if (found == false && i != 0)
		{
			iniOptions(options);
			for (int k = 0; k < i - 1; k++)
			{
				update(k, board[k], options);
			}

			options[i - 1][board[i - 1]] = false;
			for (int k = 0; k < board[i - 1]; k++)
			{
				options[i - 1][k] = false;
			}
			board[i - 1] = -1;
			i -= 2; // i = i - 2;
			continue;
		}
		else if (found == false && i == 0)
			break;
		found = false;
	}
	outfile.close();
}

void update(int i, int j, vector<vector<bool>>& options)
{
	for (int k = 0; k < problemSize; k++)
	{
		options[k][j] = false;
		options[i][k] = false;
	}

	options[i][j] = true;
	
	int length = 0;

	// Going right
	length = problemSize - i;

	for (int k = 1; k < length; k++)
	{
		if(j + k < problemSize)
			options[i + k][j + k] = false;
		if(j - k > -1)
			options[i + k][j - k] = false;
	}

	// Going left
	length = i;
	for (int k = 1; k < length; k++)
	{
		if (j + k < problemSize)
			options[i - k][j + k] = false;
		if (j - k > -1)
			options[i - k][j - k] = false;
	}
}
