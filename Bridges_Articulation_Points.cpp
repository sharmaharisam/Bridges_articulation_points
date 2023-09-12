//****************************Template Begins****************************//

// Header Files
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<utility>
#include<set>
#include<unordered_set>
#include<list>
#include<iterator>
#include<deque>
#include<queue>
#include<stack>
#include<set>
#include<bitset>
#include<random>
#include<map>
#include<unordered_map>
#include<stdio.h>
#include<complex>
#include<math.h>
#include<cstring>
#include<chrono>
#include<string>
// #include "ext/pb_ds/assoc_container.hpp"
// #include "ext/pb_ds/tree_policy.hpp"
// Header Files End

using namespace std;
// using namespace __gnu_pbds;
// template<class T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update> ;

// template<class key, class value, class cmp = std::less<key>>
// using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order(k)  returns iterator to kth element starting from 0;
// order_of_key(k) returns count of elements strictly smaller than k;

#define DIVYA ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define ll long long
#define umap unordered_map
#define uset unordered_set
#define lb lower_bound
#define ub upper_bound
#define fo(i,a,b) for(i=a;i<=b;i++)
#define all(v) (v).begin(),(v).end()
#define all1(v) (v).begin()+1,(v).end()
#define allr(v) (v).rbegin(),(v).rend()
#define allr1(v) (v).rbegin()+1,(v).rend()
#define sort0(v) sort(all(v))
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;
#define sz(x) (ll)x.size()
#define pb push_back
#define ppb pop_back
#define mkp make_pair
#define inf 1000000000000000005
const ll mod = 1e9 + 7;

ll inv(ll i) {if (i == 1) return 1; return (mod - ((mod / i) * inv(mod % i)) % mod) % mod;}

ll mod_mul(ll a, ll b) {a = a % mod; b = b % mod; return (((a * b) % mod) + mod) % mod;}

ll mod_add(ll a, ll b) {a = a % mod; b = b % mod; return (((a + b) % mod) + mod) % mod;}

ll gcd(ll a, ll b) { if (b == 0) return a; return gcd(b, a % b);}

ll ceil_div(ll a, ll b) {return a % b == 0 ? a / b : a / b + 1;}

ll pwr(ll a, ll b) {a %= mod; ll res = 1; while (b > 0) {if (b & 1) res = res * a % mod; a = a * a % mod; b >>= 1;} return res;}
//****************************Template Ends*******************************//

vector<vll>adj;
vector<ll>depth,low;
vector<bool>visited;
void dfs(ll u, ll par)
{
	visited[u] = true;
	for(auto v : adj[u])
	{
		if(v == par)continue;
		if(visited[v])
		{
			//back edge:
			low[u] = min(low[u], depth[v]);
		}
		else
		{
			//forward edge:
			depth[v] = 1 + depth[u];
			dfs(v,u);
			low[u] = min(low[u], low[v]);
		}
	}
}

void print_bridges(ll u, ll par)
{
	visited[u] = true;
	for(auto v : adj[u])
	{
		if(v == par)continue;
		if(visited[v])
		{
			//back edge, can never be a bridge
		}
		else
		{
			//forward edge:
			if(low[v] > depth[u])
			{
				//this is a bridge edge, so we can print both the endpoints:
				cout<<u<<" "<<v<<"\n";
			}
			print_bridges(v,u);
		}
	}
}

void print_articulation_points(ll u, ll par)
{
	visited[u] = true;
	bool root = false;
	ll num_children = 0;
	bool found_bad_child = false;
	if(par == -1)root = true;
	for(auto v : adj[u])
	{
		if(v == par)continue;
		if(visited[v])
		{
			//back edge
		}
		else
		{
			//forward edge:
			num_children++;
			if(low[v] >= depth[u])found_bad_child = true;
			print_articulation_points(v,u);
		}
	}
	if((root and num_children > 1) or (!root and found_bad_child))
	{
		//We found an articulation point:
		cout<<u<<"\n";
	}
}

int main() {
    DIVYA;
#ifndef ONLINE_JUDGE
    freopen("input.txt" , "r" , stdin);
    freopen("output.txt", "w", stdout);
#endif
    ll t, n, i, j, ans, temp, sum,m;
    string sans;
    t = 1;
    cin >> t;
    while (t--)
    {
        sans = "NO";
        ans = temp = sum = 0;
        cin >> n>>m; // # of nodes and edges in the graph
        adj.assign(n+1,{});
        depth.assign(n+1,0);
        low.assign(n+1,inf);
        visited.assign(n+1,false);
        //taking the graph as input:
        for(ll i = 1;i<=m;i++)
        {
        	ll u,v;
        	cin>>u>>v;
        	adj[u].push_back(v);
        	adj[v].push_back(u);
        }
        //computing the depth and low arrays:
        dfs(1,-1);

        //printing all bridges:
        cout<<"Bridges:\n";
        visited.assign(n+1,false);
        print_bridges(1,-1);

        //printing all Articulation Points:
        cout<<"Articulation Points:\n";
        visited.assign(n+1,false);
        print_articulation_points(1,-1);

    }
    return 0;
}













