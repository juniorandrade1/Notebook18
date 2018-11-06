
struct state
{
	int len, link;
	map<char,int>next;
	state(){};
	state( int a, int b, map<char,int> s )
	{
		len = a;
		link = b;
		next = s;
	}
};

state st[4*N];
int sz, last;

void init_sa()
{
	sz = 1; last = 0;
	st[0] = state(0,-1,map<char,int>());
}

ll ret;

void add_char( char c )
{
	int cur = sz++;
	st[cur].len = st[last].len+1;
	st[cur].next.clear();
	int p = last;
	for( p = last; p != -1 && !st[p].next.count(c); p = st[p].link ) st[p].next[c] = cur;
	if( p == -1 ) st[cur].link = 0;
	else
	{
		int q = st[p].next[c];
		if( st[p].len+1 == st[q].len ) st[cur].link = q;
		else
		{
			int clone = sz++;
			st[clone].len = st[p].len+1;
			st[clone].next = st[q].next;
			st[clone].link = st[q].link;
			for(;p!=-1 && st[p].next[c]==q;p = st[p].link) st[p].next[c] = clone;
			st[q].link = st[cur].link = clone;
		}
	}
	ret+=(st[cur].len-st[st[cur].link].len);
	last = cur;
}

//Numero de substrings distintas online

char s[N];

int main()
{
	//ios::sync_with_stdio(0);
	while( scanf(" %s",s) != EOF )
	{
		ret = 0;
		int len = strlen(s);
		init_sa();
		for(int i=0;i<len;++i)
		{
			if( s[i] == '?' ) printf("%lld\n",ret);
			else add_char(s[i]);
		}
	}
	return 0;
}	