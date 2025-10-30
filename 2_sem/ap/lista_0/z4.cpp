#include <iostream>
#include <vector>

using namespace std;

void qsort(vector<int> &v, int first, int last)
{
    if (first < last)
    {
        int pivot = v[(last + first) / 2];
        int i = first, j = last;
        while (i <= j)
        {
            while (v[i] < pivot)
                i++;
            while (v[j] > pivot)
                j--;
            if (i <= j)
            {
                swap(v[i], v[j]);
                i++;
                j--;
            }
        }
        qsort(v, first, j);
        qsort(v, i, last);
    }
}

int main()
{
    int n;
    vector<int> v;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        v.push_back(a);
    }
    qsort(v, 0, n - 1);

    for (auto x : v)
    {
        cout << x << " ";
    }

    return 0;
}
