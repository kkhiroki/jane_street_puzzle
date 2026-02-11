#include <iostream>
#include <vector>
#include <algorithm>

const long long N = 23;

bool checkImpl(const std::vector<std::vector<long long>>& val){

    for(long long r = 0; r < 5; r++){
        for(long long c = 0; c < 5; c++){
            if(val[r][c] < 0){
                return false;
            }
        }
    }
    
    for(long long r = 0; r < 5; r++){
        long long sum = 0;
        for(long long c = 0; c < 5; c++){
            sum = (sum*10) + val[r][c];
        }
        if(sum % (r+1) != 0) return false;
    }

    for(long long c = 0; c < 5; c++){
        long long sum = 0;
        for(long long r = 0; r < 5; r++){
            sum = (sum*10) + val[r][c];
        }
        if(sum % (c+6) != 0) return false;
    }

    return true;
}


bool check(std::string&& base_str){

    do{
        auto val = std::vector<std::vector<long long>>(5, std::vector<long long>(5, 9));
        val[4][4] = 0; // the bottom right cell must be equal to 0

        long long idx = 0, dec = 0;
        for(char c : base_str){
            if(c == '|'){
                val[idx/5][idx%5] -= dec;
                idx++;
                dec = 0;
            }
            else{
                dec++;
            }
        }

        if(dec > 0){
            val[idx/5][idx%5] -= dec;
        }

        if(checkImpl(val)){
            for(auto& r : val){
                for(auto v : r){
                    std::cout << v << " ";
                }
                std::cout << std::endl;
            }
            return true;
        }
    }while(std::next_permutation(base_str.begin(), base_str.end()));
    return false;
}


int main(int argc, const char* argv[]){

    const auto split_str = std::string(N, '|');
    for(long long r = 0; r <= 13; r++){
        std::cout << "INFO:: now processing ... " << r << std::endl;
        auto decrease = std::string(r, 'd');
        if(check(decrease + split_str)){
            std::cout << 9*24 - r << std::endl;
            return 0;
        }
    }

    
    return 0;
}
