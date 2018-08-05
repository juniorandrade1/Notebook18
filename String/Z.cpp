vector< int > Zalgorithm(vector<int> s) {
  vector< int > z(1,s.size());
  int l=0,r=0;
  for(int a = 1;a< (int) s.size(); ++a) {
    if(r < a) {
      l = r = a;
      while(r<(int)s.size() && s[r] == s[r-l]) ++r;
      z.push_back(r-l);
      r--;
    }
    else if(z[a-l] < r-a+1) z.push_back(min<int>(z[a-l],s.size()-a));
    else {
      l = a;
      while(r<(int)s.size() && s[r] == s[r-l]) ++r;
      z.push_back(r-l);
      r--;
    }
  }
  return z;
}