#include <bits/stdc++.h>
using namespace std;

struct QueryData
{
    int index;
    int start;
    int end;
    int minimum;
};

vector<QueryData> processQueries(int *arr, vector<QueryData> queries, int leftBound, int rightBound)
{
    if (queries.empty() || leftBound > rightBound)
        return queries;

    int mid = (leftBound + rightBound) / 2;
    vector<QueryData> groupLeft, groupRight, groupMid;
    int low = INT_MAX, high = 0;

    for (QueryData q : queries)
    {
        if (q.start < mid && q.end < mid)
            groupLeft.push_back(q);
        else if (q.start > mid && q.end > mid)
            groupRight.push_back(q);
        else
        {
            low = min(low, q.start);
            high = max(high, q.end);
            groupMid.push_back(q);
        }
    }

    if (!groupMid.empty())
    {
        int helper[high + 1];
        helper[mid] = arr[mid];
        helper[mid - 1] = arr[mid - 1];

        for (int i = mid + 1; i <= high; i++)
            helper[i] = min(helper[i - 1], arr[i]);

        for (int i = mid - 2; i >= low; i--)
            helper[i] = min(helper[i + 1], arr[i]);

        for (QueryData &q : groupMid)
            q.minimum = min(helper[q.start], helper[q.end]);
    }

    groupLeft = processQueries(arr, groupLeft, leftBound, mid);
    groupRight = processQueries(arr, groupRight, mid + 1, rightBound);

    for (QueryData q : groupLeft)
        groupMid.push_back(q);
    for (QueryData q : groupRight)
        groupMid.push_back(q);

    return groupMid;
}

bool compareByIndex(QueryData a, QueryData b)
{
    return (a.index < b.index);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, numQueries;
    cin >> n >> numQueries;

    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    vector<QueryData> queries(numQueries);
    for (int i = 0; i < numQueries; i++)
    {
        int l, r;
        queries[i].index = i + 1;
        cin >> l >> r;
        queries[i].start = l - 1;
        queries[i].end = r - 1;
    }

    queries = processQueries(arr, queries, 0, n - 1);
    sort(queries.begin(), queries.end(), compareByIndex);

    for (QueryData q : queries)
        cout << q.minimum << "\n";

    return 0;
}
