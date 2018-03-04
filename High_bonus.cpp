#include <bits/stdc++.h>
const int MX = 1e4+69;
using namespace std;
typedef long long ll;
typedef long double ld;
const ll mod = 1e9+7;
const double eps=1e-9;
#define F first
#define S second

int r,c,f,n,b,t;

struct state
{
    int xs,ys,xe,ye,s,e,id;
}rides[MX];

struct vehicle
{
    int x,y,t;
}cars[MX];


vector <int> ans[MX],sol[MX];
bool done[MX];

bool cmp ( state a , state b )
{
    if ( a.e==b.e ) { return ( a.s<b.s ); } else { return (a.e<b.e); }
}

int fun( state c )
{
    int mn=1e9 , id=-1;
    for ( int i=1 ; i<=f ; i++ )
    {
        int dis = abs( cars[i].x-c.xs ) + abs( cars[i].y-c.ys );
        int real = abs( c.xe-c.xs ) + abs( c.ye-c.ys );
        if ( mn>(c.s - dis + cars[i].t) && dis + cars[i].t <= c.s && c.e<=t ) { mn = c.s - (dis + cars[i].t); id=i; }
    }
    if ( id==-1 )
    {
            for ( int i=1 ; i<=f ; i++ )
            {
                int dis = abs( cars[i].x-c.xs ) + abs( cars[i].y-c.ys );
                int real = abs( c.xe-c.xs ) + abs( c.ye-c.ys );
                if ( dis<mn && id==-1 && dis + cars[i].t + real <= c.e && c.e<=t ) { mn=dis; id=i; }
            }
    }
    return id;
}

int calc( int id , state c , int &ti )
{
    int dis = abs( cars[id].x-c.xs ) + abs( cars[id].y-c.ys );
    int real = abs( c.xe-c.xs ) + abs( c.ye-c.ys );
    int wait = max( 0 , c.s - ( cars[id].t + dis ) );
    cars[id] = { c.xe , c.ye , cars[id].t + dis + real + wait };
    ti += ( dis + real + wait );
}

int main()
{
    //freopen("input1.in" , "r" , stdin );
    freopen("High_bonus.txt" , "w" , stdout );
    cin>>r>>c>>f>>n>>b>>t;
    for ( int i=1 ; i<=n ; i++ )
    {
        int xs,ys,xe,ye,s,e;
        scanf ( "%d%d%d%d%d%d" , &xs , &ys , &xe , &ye , &s , &e );
        rides[i] = { xs , ys , xe , ye , s , e , i-1 };
    }
    sort ( rides+1 , rides+1+n , cmp );

    int cnt=1;
    int curt=0 , mn=1e9+7;
    while ( cnt-- )
    {
        curt=0;
        //random_shuffle( rides+1 , rides+1+n );
        for ( int i=1 ; i<=f ; i++ ) { cars[i] = { 0 , 0 , 0 }; }
        for ( int i=1 ; i<=f ; i++ ) { ans[i].clear(); }
        for ( int i=1 ; i<=n ; i++ )
        {
            state cur = rides[i];
            int id = fun( cur );
            if ( id==-1 ) continue;
            ans[id].push_back( cur.id );
            calc( id , cur , curt );
        }
        if ( curt<mn )
        {
            mn = curt;
            for ( int i=1 ; i<=f ; i++ ) sol[i]=ans[i];
        }
    }

    for ( int i=1 ; i<=f ; i++ )
    {
        int li = sol[i].size();
        printf( "%d " , li );
        for ( int j=0 ; j<li ; j++ )
        {
            printf( "%d " , sol[i][j] );
        }
        printf("\n");
    }

    return 0;
}
