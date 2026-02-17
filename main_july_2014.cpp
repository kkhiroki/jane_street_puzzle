#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <bitset>

using ll = long long;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;

const ll N = 30;

template <typename T>
std::vector<T> uniquen(std::vector<T> vec){
    sort(vec.begin(), vec.end()); vec.erase(unique(vec.begin(), vec.end()), vec.end()); return vec;
}

vvl divisors(ll n){
    vvl res(n+1);
    for(ll i = 1; i <= n; i++){
        vl divs;
        for(ll k = 1; k*k <= i; k++){
            if(i%k == 0){
                if(k != i)   divs.push_back(k);
                if(i/k != i) divs.push_back(i/k);
            }
        }
        res[i] = uniquen(divs);
    }
    return res;
}




// Custom hash function for std::bitset<N>
template <size_t N>
struct BitsetHash {
    std::size_t operator()(const std::bitset<N>& bs) const noexcept {
        // Convert to unsigned long long for hashing
        // For large N, use bs.to_string() or manual chunk hashing
        return std::hash<unsigned long long>()(bs.to_ullong());
    }
};

// Custom equality comparator (optional, default works fine)
template <size_t N>
struct BitsetEqual {
    bool operator()(const std::bitset<N>& a, const std::bitset<N>& b) const noexcept {
        return a == b;
    }
};


std::vector<std::unordered_map<std::bitset<N+1>, ll, BitsetHash<N+1>, BitsetEqual<N+1>>> bt(N+1);

ll dfs(ll cur, std::bitset<N+1> st, const vvl& divs){
    
    if(st[cur]) return 0;
    st.set(cur);
    
    auto it = bt[cur].find(st);

    ll len = 0;
    for(ll next : divs[cur]){
        if(st[next]) continue;
        ll len_next = dfs(next, st, divs);
        if(len < len_next){
            len = len_next;
            bt[cur][st] = next;
        }
    }

    for(int i = 2; i*cur <= N; i++){
        ll next = i*cur;
        if(st[next]) continue;
        ll len_next = dfs(next, st, divs);
        if(len < len_next){
            len = len_next;
            bt[cur][st] = next;
        }
    }

    return len+1;
}


int main(int argc, const char* argv[]){

    auto divs = divisors(N);
    auto st = std::bitset<N+1>();
    ll start = 1;
    std::cout << dfs(start, st, divs) << std::endl;

    ll cur = start;
    while(true){
        st.set(cur);
        auto it = bt[cur].find(st);
        if(it == bt[cur].end()) break;

        auto next = it->second;
        std::cout << cur << " " << next << std::endl;
        cur = next;
    }
    return 0;
}