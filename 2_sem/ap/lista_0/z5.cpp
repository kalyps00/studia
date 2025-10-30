#include <iostream>
#include <vector>
using namespace std;
bool is_free(vector<int> &board, int row, int column)
{
    for (int i = 0; i < column; i++)
    {
        if (board[i] == row || abs(board[i] - row) == abs(i - column))
            return false;
    }
    return true;
}
int hetmany(int n, vector<int> &board, int column)
{
    if (column == n)
        return 1;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (is_free(board, i, column))
        {
            board[column] = i;
            ans += hetmany(n, board, column + 1);
        }
    }
    return ans;
}
int main()
{
    int n;
    cin >> n;
    vector<int> board(n, -1);
    cout << hetmany(n, board, 0);
}