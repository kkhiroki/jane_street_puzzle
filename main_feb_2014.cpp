#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

using ll     = long long;
using vl     = std::vector<ll>;
using vvl    = std::vector<vl>;
using vvvl   = std::vector<vvl>;
using vvvvl  = std::vector<vvvl>;

const long long N = 9;

const vl row_sum = {26, 42, 11, 22, 42, 36, 29, 32, 45};
const vl col_sum = {31, 19, 45, 16, 5,  47, 28, 49, 45};

bool bit(ll st, ll b){return ((st>>b)&1) == 1;}

ll global_counter = 0;

vl matchCases(int nb){

    vl res;
    for(long long st = 0; st < (1ll<<N); st++){
        ll sum = 0;
        for(int b = 0; b < N; b++){
            if(!bit(st, b)) continue;
            if(b < nb) sum += nb;
            else sum += b+1;
        }

        // special rules to reduce search range
        if(nb == 9 && !bit(st, 8)) continue;
        if(nb == 8 && !bit(st, 7)) continue;
        if(nb == 7 &&  bit(st, 6)) continue;
        if(nb == 1 && !bit(st, 0)) continue;

        if(col_sum[nb-1] == sum) res.push_back(st);     
    }

    return res;
}


void checkRowSum(const vl& sts){
    vvl grid(N, vl(N, 0));

    for(int col = 0; col < N; col++){
        for(int b = 0; b < N; b++){
            if(!bit(sts[col], b)) continue;
            if(b <= col) grid[b][col] = col+1;
            else grid[b][col] = b+1;
        }
    }

    for(int row = 0; row < N; row++){
        int sum = 0;
        for(int col = 0; col < N; col++) sum += grid[row][col];
        if(sum != row_sum[row]) return;
    }

    std::cout << "found" << std::endl;
    ll ans = 0;
    for(int row = 0; row < N; row++){
        for(int col = 0; col < N; col++){
            std::cout << grid[row][col] << " ";
            if((row + col)%2 == 0) ans += grid[row][col];
        }
        std::cout << std::endl;
    }
    std::cout << "The answer is " << ans << std::endl;
}


void dfs(const vvl& cases, vl sts, ll nb){

    if(nb == N){
        global_counter++;
        checkRowSum(sts);
        if(global_counter % 10000000 == 0) std::cout << "Now processing ... " << global_counter << std::endl;
        return;
    }

    for(auto st : cases[nb]){
        auto cur_st = sts;
        cur_st.push_back(st);
        dfs(cases, std::move(cur_st), nb+1);
    }
}


int main(int argc, const char* argv[]){

    vvl tot;
    for(int col_nb = 1; col_nb <= N; col_nb++){
        tot.push_back(matchCases(col_nb));
    }

    vl idx;
    dfs(tot, idx, 0);
    return 0;
}