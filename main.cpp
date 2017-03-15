
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

struct Edge
{
	int from, to, cap, flow, cost,rev;//rev反向边的vector下标
};
vector<Edge> graph[N];

void print_allflow(int node_nums){
    for(int i = 0;i<node_nums;i++){
            for(int j = 0;j<graph[i].size();j++){
                if(graph[i][j].cost >= 0 && graph[i][j].flow > 0)
                    printf("{%d->%d,flow:%d}",graph[i][j].from,graph[i][j].to,graph[i][j].flow);
            }
            printf("\n");
    }
}


struct point{
    int node_id;
    int side_id;//边在vector中的下标
};

void add_Edge(int from, int to, int cap, int cost)
{

	/*e.push_back((Node){ from, to, cap, 0, cost });
	e.push_back((Node){ to, from, 0, 0, -cost });
	int len = e.size() - 1;
	v[to].push_back(len);
	v[from].push_back(len - 1);*/

	graph[from].push_back((Edge){ from, to, cap, 0, cost, graph[to].size()});
	graph[to].push_back((Edge){to, from, 0, 0, -cost, graph[from].size()-1});

    graph[to].push_back((Edge){ to, from, cap, 0, cost, graph[from].size()});
	graph[from].push_back((Edge){from, to, 0, 0, -cost, graph[to].size()-1});

}

int vis[N], dis[N];
point father[N];//路径信息
int pos[N];

int push_couter = 0;

bool BellManford(int s, int t, int& flow, int& cost)
{
	Del(dis, inf);
	Del(vis, 0);
	queue<int> q;
	q.push(s);
	vis[s] = 1;
	father[s] = ((point) {-1,-1});
	dis[s] = 0;

    pos[s] = inf;//路径中所有边的流量中，最小值

	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for (int i = 0; i<graph[u].size(); i++)
		{
			Edge tmp = graph[u][i];
			int v = tmp.to;
			if (tmp.cap>tmp.flow && dis[tmp.to] > dis[u] + tmp.cost)
			{
				dis[v] = dis[u] + tmp.cost;
				father[v].node_id = u;
				father[v].side_id = i;

				pos[v] = min(pos[u], tmp.cap - tmp.flow);
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

	for (int u = t; u != s; u = father[u].node_id){
        printf("%d->", u);
	}
	printf("%d|%d\n",s,pos[t]);

	for (int u = t; u != s; u = father[u].node_id)
	{
	    int nd_id = father[u].node_id;//父亲节点id
	    int sd_id = father[u].side_id;//具体边的vector下标

	    int rev_id = graph[nd_id][sd_id].rev;//反向边在vector中的下标

		graph[nd_id][sd_id].flow += pos[t];
		graph[u][rev_id].flow -= pos[t];
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
		graph[i].clear();
}


int* Initial_OneSD_Graph(){

    int *super_s_t = (int *)malloc(2*sizeof(int));

    	add_Edge(0,1,16,1);
   // add_Edge(1,0,16,1);

	add_Edge(0,2,13,10);
  //  add_Edge(2,0,13,10);

	add_Edge(1,2,4,1);
 //   add_Edge(2,1,4,1);

	add_Edge(1,3,12,1);
 //   add_Edge(3,1,12,1);

	add_Edge(2,3,9,1);
 //   add_Edge(3,2,9,1);

	add_Edge(2,4,14,1);
  //  add_Edge(4,2,14,1);

	add_Edge(3,4,7,1);
  //  add_Edge(4,3,7,1);

	add_Edge(3,5,20,10);
  //  add_Edge(5,3,20,10);

	add_Edge(4,5,4,1);
//	add_Edge(5,4,4,1);

    super_s_t[0] = 0;
    super_s_t[1] = 5;

    return super_s_t;
}

int* Initial_Graph(int min_max_id[],int supply[],int demand[],int supply_nums,int demand_nums){

    int *super_s_t = (int *)malloc(2*sizeof(int));
    super_s_t[0] = min_max_id[0];
    super_s_t[1] = min_max_id[1];

    for(int i = 0;i<supply_nums;i++){
        add_Edge(super_s_t[0],supply[i],inf,0);
    }

    for(int i = 0;i<demand_nums;i++){
        add_Edge(super_s_t[1],demand[i],inf,0);
    }

    add_Edge(0,2,12,2);
    add_Edge(1,0,4,5);
    add_Edge(1,3,14,1);
    add_Edge(2,1,9,1);
    add_Edge(2,4,20,0);
    add_Edge(3,5,4,0);
    add_Edge(3,2,7,3);

    return super_s_t;
}

int main()
{

    int demand_flow = 24;
    int demand_nums = 2;
    int node_nums = 6;
    int min_max_id[] = {node_nums,node_nums+1};
    int supply[] = {0,1};
    int demand[] = {4,5};

    int *super_s_t = Initial_Graph(min_max_id,supply,demand,2,demand_nums);
    //int *super_s_t = Initial_OneSD_Graph();

    int s = super_s_t[0], t = super_s_t[1];
    printf("%d->%d\n",s,t);
    int ans = Mincost(s, t);
    printf("%d\n", ans);

    print_allflow(node_nums+2);

    Clear(5);

	return 0;
}
