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
    int xs,ys,xe,ye,s,e;
}rides[MX];
vector <int> ans[MX];
bool done[MX];

int go( int x , int y , int ti )
{
    int mnx=1e9,mny=1e9 , mn=1e9 , id=-1;
    for ( int i=1 ; i<=n ; i++ )
    {
        if ( done[i] ) { continue; }
        int idle = abs( rides[i].xs-x ) + abs( rides[i].ys - y );
        int real = abs( rides[i].xs-rides[i].xe ) + abs( rides[i].ys - rides[i].ye );
        if ( idle < mn && ( ti + idle + real <= rides[i].e ) && rides[i].e<=t )
        {
            mn = idle;
            id = i;
        }
    }
    return id;
}

int pro( int &x , int &y , int &ti , int id )
{
    int idle = abs( rides[id].xs-x ) + abs( rides[id].ys - y );
    int real = abs( rides[id].xs-rides[id].xe ) + abs( rides[id].ys - rides[id].ye );
    int wait = max( 0 , rides[id].s - ( idle ) );
    ti += ( idle + real + wait );
    x = rides[id].xe;
    y = rides[id].ye;
}

int main()
{
    //freopen("input1.in" , "r" , stdin );
    freopen("no_hurry.txt" , "w" , stdout );
    cin>>r>>c>>f>>n>>b>>t;
    for ( int i=1 ; i<=n ; i++ )
    {
        int xs,ys,xe,ye,s,e;
        scanf ( "%d%d%d%d%d%d" , &xs , &ys , &xe , &ye , &s , &e );
        rides[i] = { xs , ys , xe , ye , s , e };
    }

    int lim = n , nn=n;

    for ( int i=1 ; i<=f ; i++ )
    {
        int curx,cury,curt;
        int l = ( i==f?nn:lim );
        curx = cury = curt = 0;
        for ( int j=1 ; j<=l ; j++ )
        {
            int id = go( curx , cury , curt );
            if ( id==-1 ) { l=j; break; }
            done[id]=1;
            ans[i].push_back( id-1 );
            pro( curx , cury , curt , id );
        }
        nn -= l;
    }

    for ( int i=1 ; i<=f ; i++ )
    {
        int li = ans[i].size();
        printf( "%d " , li );
        for ( int j=0 ; j<li ; j++ )
        {
            printf( "%d " , ans[i][j] );
        }
        printf("\n");
    }

    return 0;
}
