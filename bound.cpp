#include <iostream>
#include <vector>
#include <algorithm>

//  lower_bound, upper_bound
//  이진탐색 기반의 탐색 방법.(그러므로 사용하려면 정렬이 되어있어야함)

//  lower_bound(first, last, value);
//  lower_bound :   [first, last) 안의 원소들 중, value 보다 작지 않은(크거나 같은) 첫 번째 원소를 리턴.
//                   만약, 그런게 없다면 last를 리턴. 어떤 값의 하한선을 의미.

//  upper_bound(first, last, value);
//  upper_bound :   [first, last) 안의 원소들 중, value 보다 큰 첫 번째 원소를 리턴.
//                  만약, 그런게 없다면 last를 리턴. 어떤 값의 상한선을 의미.

int main(){
    std::vector<int> v{0, 1, 2, 2, 5, 8, 10, 10};

    auto lower = std::lower_bound(v.begin(), v.end(), 2);   // 2
    auto upper = std::upper_bound(v.begin(), v.end(), 2);   // 4

    std::cout<<lower - v.begin()<<"\n";
    std::cout<<upper - v.begin()<<"\n";

    return 0;
}