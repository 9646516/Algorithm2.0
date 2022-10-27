// 如果字符串S[L..R](闭区间)的同长度的前缀和后缀完全相同，即s[L..L+N-1] = s[R-N+1..R]，则称此前缀为一个Border。
// p是S的周期 等价于 |S| − p 是S的Border
// 此处求出的border是错一位的，即dst[i+1]是S[L..i]的border
// 循环节即为sz-border[sz]

void make_border(const string &src, vector<int> &dst) {
    dst.resize(src.size() + 1);
    int i = 0, j = dst[0] = -1;
    while (i < src.size()) {
        while (j != -1 && src[i] != src[j])
            j = dst[j];
        i++;
        j++;
        dst[i] = j;
    }
}
void make_next(const string &src, vector<int> &dst) {
    dst.resize(src.size() + 1);
    int i = 0, j = dst[0] = -1;
    while (i < src.size()) {
        while (j != -1 && src[i] != src[j])
            j = dst[j];
        i++;
        j++;
        dst[i] = src[i] == src[j] ? dst[j] : j;
    }
}

//模拟识别pattern的自动机,当前pattern匹配到j位置,转移字符为feed,初始状态j=0,即还未匹配的第一个字符,匹配到pattern.size()即为完全匹配
int match_once(const string &pattern, const char feed, vector<int> &next, int j) {
    while (j != -1 && feed != pattern[j])
        j = next[j];
    j++;
    return j;
}

vector<int> match(const string &src, const string &pattern, vector<int> &next) {
    vector<int> ans;
    int j = 0;
    for (int i = 0; i < src.size(); i++) {
        j = match_once(pattern, src[i], next, j);
        if (j >= pattern.size()) {
            ans.push_back(i - pattern.size() + 1);
            j = next[j];
        }
    }
    return ans;
}
