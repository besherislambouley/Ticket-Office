/*
 * first we sort the array then fill Num [i] which means what is the maximum number of interval of value 2 we can put befor A [i] 
 * now we process the solution from the last to the first interval , intervals with equel Num [i] means that we must choose one of them ( we cant choose both )
 * since we dont want to lose chairs we choose from those intervals the one with the smallest ( Last - R [i] ) % L 
 * ( R[i] = A [i] + L - 1 , Last = A[i] of the last interval with value 2 we choose ) 
 * before that make sure you throw away the intervals which overlap with our last interval 
 * now greedly add the 1 value intervals 
*/ 
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 547
//#define mp make_pair
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll inf=1e18;
const ll mod=1e9+7;
const ld pai=acos(-1);
int Sz , W , N , Sum ;
pi A [100009] ; 
vi groups [100009] ;
int Num [100009] , done [100009] ; 
int main () {
	cin >> Sz >> W >> N ;
	for ( int i = 0 ; i < N ; i ++ ) cin >> A [i] .fi , A [i] .se = i ; 
	sort ( A , A + N ) ;
	int it = 0 , Mx = 0 ; 
	for ( int i = 0 ; i < N ; i ++ ) {
		while ( it < N && A [it].fi + W - 1 < A [i] .fi ) {
			Mx = max ( Mx , Num [it] + 1 ) ;
			it ++ ;
		}
		Num [i] = Mx ; 
	}
	vpi Ans ; 
	vi More ; 
	int Last = Sz + 1 ; 
	for ( int i = N - 1 ; i >= 0 ; i -- ) {
		int j = i ;
		while ( j >= 0 && A [j] .fi + W - 1 >= Last ) j -- ; 
		vi Ret ;
		pi Best = { 1e9 , 1e9 } ;
		while ( j >= 0 && Num [j] == Num [i] ) { 
			pi Crnt = { ( Last - ( A [j] .fi + W - 1 ) - 1 ) % W , j } ;
			Best = min ( Best , Crnt ) ;
			Ret .pb ( j ) ;
			j -- ; 
		}
		Last = A [ Best.se ] .fi ;
		Ans .pb ( { A [ Best .se ] .fi , A [ Best .se ] .se + 1 } ) ;
		Sum += 2 ; 
		for ( auto u : Ret ) {
			if ( u == Best .se ) C ;
			More .pb ( u ) ; 	
		}
		i = j + 1 ;
	}
	for ( auto u : Ans ) {
		done [ u.fi ] ++ ;
		done [ u.fi + W ] -- ; 		
	}
	for ( int i = 1 ; i <= Sz ; i ++ ) done [i] += done [i-1] ;
	int Crnt = 0 ;
	for ( int i = 1 ; i <= Sz ; i ++ ) {
		Crnt += ( ! done [i] ) ;
		if ( done [i] ) Crnt = 0 ;
		if ( More .size() == 0 ) break ; 
		if ( Crnt == W ) {
			Crnt = 0 ;
			Sum ++ ;
			Ans .pb ( { i - W + 1 , A [ More.back() ] .se + 1 } ) ;
			More .ppb () ;
		}
	}
	sort ( all ( Ans ) ) ; 
	cout << Sum << endl ; 
	cout << Ans .size() << endl ;	
	for ( auto u : Ans ) cout << u.se << " " << u.fi << endl ; 
}
