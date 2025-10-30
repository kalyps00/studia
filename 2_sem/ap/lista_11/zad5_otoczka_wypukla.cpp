#include <bits/stdc++.h>
using namespace std;
struct Point
{
    long long coord_x, coord_y;
    bool operator<(const Point &p) const
    {
        return tie(coord_x, coord_y) < tie(p.coord_x, p.coord_y);
    }
};
long long cross_product(const Point &p1, const Point &p2, const Point &p3)
{
    long long dx1 = p2.coord_x - p1.coord_x;
    long long dy1 = p2.coord_y - p1.coord_y;
    long long dx2 = p3.coord_x - p1.coord_x;
    long long dy2 = p3.coord_y - p1.coord_y;
    return dx1 * dy2 - dy1 * dx2;
}

vector<Point> calculate_convex_hull(vector<Point> vertices)
{
    int num_points = vertices.size();
    if (num_points <= 1)
        return vertices;
    sort(vertices.begin(), vertices.end(), [](const Point &a, const Point &b)
         { return tie(a.coord_y, a.coord_x) < tie(b.coord_y, b.coord_x); });

    vector<Point> bottom_hull;
    vector<Point> top_hull;
    for (int i = 0; i < num_points; i++)
    {
        while (top_hull.size() >= 2 && cross_product(top_hull[top_hull.size() - 2], top_hull.back(), vertices[i]) < 0)
        {
            top_hull.pop_back();
        }
        top_hull.push_back(vertices[i]);
    }
    for (int i = num_points - 1; i >= 0; i--)
    {
        while (bottom_hull.size() >= 2 && cross_product(bottom_hull[bottom_hull.size() - 2], bottom_hull.back(), vertices[i]) < 0)
        {
            bottom_hull.pop_back();
        }
        bottom_hull.push_back(vertices[i]);
    }

    bottom_hull.pop_back();
    top_hull.pop_back();
    bottom_hull.insert(bottom_hull.end(), top_hull.begin(), top_hull.end());
    return bottom_hull;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int num_vertices;
    cin >> num_vertices;
    vector<Point> vertices(num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
        cin >> vertices[i].coord_x >> vertices[i].coord_y;
    }
    vector<Point> hull = calculate_convex_hull(vertices);
    sort(hull.begin(), hull.end());

    cout << hull.size() << "\n";
    for (const auto &p : hull)
    {
        cout << p.coord_x << " " << p.coord_y << "\n";
    }
    return 0;
}