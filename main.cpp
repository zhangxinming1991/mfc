
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
const int N = 1050;
const int inf = 0x3f3f3f3f;
#define Del(a,b) memset(a,b,sizeof(a))
struct Node
{
	int from, to, cap, flow, cost;
};
vector<int> v[N];
vector<Node> e;
void add_Node(int from, int to, int cap, int cost)
{

	e.push_back((Node){ from, to, cap, 0, cost });
	e.push_back((Node){ to, from, 0, 0, -cost });
	int len = e.size() - 1;
	v[to].push_back(len);
	v[from].push_back(len - 1);
}
int vis[N], dis[N];
int father[N], pos[N];
bool BellManford(int s, int t, int& flow, int& cost)
{
	Del(dis, inf);
	Del(vis, 0);
	queue<int> q;
	q.push(s);
	vis[s] = 1;
	father[s] = -1;
	dis[s] = 0;
	pos[s] = inf;
	while (!q.empty())
	{
		int f = q.front();
		q.pop();
		vis[f] = 0;
		for (int i = 0; i<v[f].size(); i++)
		{
			Node& tmp = e[v[f][i]];
			if (tmp.cap>tmp.flow && dis[tmp.to] > dis[f] + tmp.cost)
			{
				dis[tmp.to] = dis[f] + tmp.cost;
				father[tmp.to] = v[f][i];
				pos[tmp.to] = min(pos[f], tmp.cap - tmp.flow);
				if (vis[tmp.to] == 0)
				{
					vis[tmp.to] = 1;
					q.push(tmp.to);
				}
			}
		}
	}
	if (dis[t] == inf)
		return false;
	flow += pos[t];
	cost += dis[t] * pos[t];

	for (int u = t; u != s; u = e[father[u]].from){
        printf("%d->", u);
	}
	printf("0|%d\n",flow);

	for (int u = t; u != s; u = e[father[u]].from)
	{
		e[father[u]].flow += pos[t];
		e[father[u] ^ 1].flow -= pos[t];
	}
	return true;
}
int Mincost(int s, int t)
{
	int flow = 0, cost = 0;
	while (BellManford(s, t, flow, cost)){}
	return cost;
}
void Clear(int x)
{
	for (int i = 0; i <= x; i++)
		v[i].clear();
	e.clear();
}

int main()
{
	/*int n, m;
	while (~scanf("%d%d", &n, &m))
	{
		for (int i = 0; i<m; i++)
		{
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			add_Node(x, y, 1, z);
			add_Node(y, x, 1, z);
		}
		int s = 0, t = n + 1;
		add_Node(s, 1, 2, 0);
		add_Node(n, t, 2, 0);
		int ans = Mincost(s, t);
		printf("%d\n", ans);
		Clear(n + 1);
	}*/

	add_Node(0,1,16,1);
		add_Node(1,0,16,1);

	add_Node(0,2,13,10);
		add_Node(2,0,13,10);

	add_Node(1,2,4,1);
		add_Node(2,1,4,1);

	add_Node(1,3,12,1);
		add_Node(3,1,12,1);

	add_Node(2,3,9,1);
		add_Node(3,2,9,1);

	add_Node(2,4,14,1);
		add_Node(4,2,14,1);

	add_Node(3,4,7,1);
		add_Node(4,3,7,1);

	add_Node(3,5,20,10);
		add_Node(5,3,20,10);

	add_Node(4,5,4,1);
	add_Node(5,4,4,1);

			int s = 0, t = 5;
			int ans = Mincost(s, t);
		printf("%d\n", ans);
		Clear(5);

	return 0;
}
