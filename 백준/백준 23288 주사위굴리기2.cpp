#include <iostream>

using namespace std;

class Dice
{
	enum eDiceDirection
	{
		Up,
		Down,
		Left,
		Right
	};

	typedef void (Dice::* DiceDirectFunction)();

public:
	Dice();

	int Do();
	void PrintDice() const;
	void Scan();
	void CheckRange(int targetNum, int row, int col);
	void MoveDiceToUp();
	void MoveDiceToDown();
	void MoveDiceToLeft();
	void MoveDiceToRight();

private:

	const DiceDirectFunction mDiceDirectFunction[4];
	const eDiceDirection mDiceDirection[4];

	int mDice[2][4];
	int mRow;
	int mCol;
	int mCurrentDirectionIndex;
	int mTotalScore;

	int mSameNum;
	bool mbIsChecked[20][20];
};

int N, M, K;
int arr[20][20];

//int arr[20][20] = {
//	{4, 1, 2, 3, 3},
//	{6, 1, 1, 3, 3},
//	{5, 6, 1, 3, 2},
//	{5, 5, 6, 5, 5}
//};

#define boundedRow (N - 1)
#define boundedCol (M - 1)

int main()
{
	Dice dice;
	dice.Scan();

	cout << dice.Do();
}

Dice::Dice()
	: mDiceDirectFunction{ &Dice::MoveDiceToRight, &Dice::MoveDiceToDown, &Dice::MoveDiceToLeft, &Dice::MoveDiceToUp }
	, mDiceDirection{ Right, Down, Left, Up }

	, mDice{ { 2, 1, 5, 6 }, { 4, 1, 3, 6 } }
	, mTotalScore(0)
	, mbIsChecked{ false, }
	, mSameNum(0)

	, mRow(0), mCol(0)
	, mCurrentDirectionIndex(0)
{}
int Dice::Do()
{
	//PrintDice();

	int dicedNum = 0;
	while (dicedNum < K)
	{
		(this->*mDiceDirectFunction[mCurrentDirectionIndex])();

		const int bottomNum = mDice[0][3];
		const int targetNum = arr[mRow][mCol];

		if (bottomNum > targetNum)
		{
			mCurrentDirectionIndex = ++mCurrentDirectionIndex % 4;
		}
		else if (bottomNum < targetNum)
		{
			mCurrentDirectionIndex = (--mCurrentDirectionIndex + 4) % 4;
		}
		else
		{

		}

		CheckRange(targetNum, mRow, mCol);
		mTotalScore += mSameNum * targetNum;

		for (int i = 0; i <= boundedRow; ++i)
		{
			for (int j = 0; j <= boundedCol; ++j)
			{
				mbIsChecked[i][j] = 0;
			}
		}
		mSameNum = 0;
		++dicedNum;
	}

	return mTotalScore;
}
void Dice::PrintDice() const
{
	static int n = 0;

	printf("%d, A: ", n);
	for (int i = 0; i < 4; i++)
	{
		cout << mDice[0][i] << ", ";
	}
	printf("\n%d, B: ", n++);
	for (int i = 0; i < 4; i++)
	{
		cout << mDice[1][i] << ", ";
	}
	cout << endl << endl;
}
void Dice::Scan()
{
	cin >> N;
	cin >> M;
	cin >> K;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			cin >> arr[i][j];
		}
	}
}
void Dice::CheckRange(int targetNum, int row, int col)
{
	if (mbIsChecked[row][col] == true)
	{
		return;
	}
	if (row < 0 || row > boundedRow
		|| col < 0 || col > boundedCol)
	{
		return;
	}

	const int curruntNum = arr[row][col];

	if (curruntNum == targetNum)
	{
		++mSameNum;

		mbIsChecked[row][col] = true;

		CheckRange(targetNum, row - 1, col);
		CheckRange(targetNum, row + 1, col);
		CheckRange(targetNum, row, col - 1);
		CheckRange(targetNum, row, col + 1);
	}
	else
	{
		mbIsChecked[row][col] = true;
	}
}
void Dice::MoveDiceToUp()
{
	if (mRow == 0)
	{
		mCurrentDirectionIndex += 2;
		mCurrentDirectionIndex %= 4;

		MoveDiceToDown();

		return;
	}

	int* a = mDice[0];
	int* b = mDice[1];

	int temp = a[0];
	a[0] = a[1];
	a[1] = a[2];
	a[2] = a[3];

	a[3] = temp;

	b[1] = a[1];
	b[3] = a[3];

	--mRow;
}
void Dice::MoveDiceToDown()
{
	if (mRow == boundedRow)
	{
		mCurrentDirectionIndex += 2;
		mCurrentDirectionIndex %= 4;

		MoveDiceToUp();

		return;
	}

	int* a = mDice[0];
	int* b = mDice[1];

	int temp = a[3];
	a[3] = a[2];
	a[2] = a[1];
	a[1] = a[0];

	a[0] = temp;

	b[1] = a[1];
	b[3] = a[3];

	++mRow;
}
void Dice::MoveDiceToLeft()
{
	if (mCol == 0)
	{
		mCurrentDirectionIndex += 2;
		mCurrentDirectionIndex %= 4;

		MoveDiceToRight();

		return;
	}

	int* a = mDice[0];
	int* b = mDice[1];

	int temp = b[0];
	b[0] = b[1];
	b[1] = b[2];
	b[2] = b[3];

	b[3] = temp;

	a[1] = b[1];
	a[3] = b[3];

	--mCol;
}
void Dice::MoveDiceToRight()
{
	if (mCol == boundedCol)
	{
		mCurrentDirectionIndex += 2;
		mCurrentDirectionIndex %= 4;

		MoveDiceToLeft();

		return;
	}

	int* a = mDice[0];
	int* b = mDice[1];

	int temp = b[3];
	b[3] = b[2];
	b[2] = b[1];
	b[1] = b[0];

	b[0] = temp;

	a[1] = b[1];
	a[3] = b[3];

	++mCol;
}