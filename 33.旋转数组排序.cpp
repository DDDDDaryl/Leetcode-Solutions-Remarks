#include <iostream>
#include <sstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <deque>
#include <list>
#include <forward_list>
#include <array>
#include <stack>
#include <map>
#include <random>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cctype>
using namespace std;
using namespace std::chrono;

/*假设按照升序排序的数组在预先未知的某个点上进行了旋转。
( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。
搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。
你可以假设数组中不存在重复的元素。
你的算法时间复杂度必须是 O(log n) 级别。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/search-in-rotated-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

/*分析：数组旋转后仍是两个有序的数组
 *      根据时间复杂度，算法的实现需要使用分治
 *      旋转的结果就是原升序数组出现断层，断层之前的元素索引+bias，之后的元素-bias，bias为断层之后第一个元素的索引
 *      问题在于我们不能遍历搜索断层出现的位置，如何二分搜索断层？
 *      Note: 不能用find，find的实现是遍历搜索。。。
 *
 *      当然可以快排排好序然后再二分查找，但快排是nlog n,且找断点更快
 *
 *      看了大佬的答案决定把自己写的垃圾删掉重新写
 *      实际上开始的思路就是对的，一部分有序一部分无序，而找到idx根本不需要两次二分查找*/

class Solution {
public:
    static int search(vector<int>& nums, int target) {
        if(nums.empty()) return -1;
        auto lo = nums.begin();
        auto hi = nums.end()-1;
        auto mid = lo+(hi-lo)/2;
        while(lo < hi){
            //
            if(*lo > *hi){//无序
                if(target >= *lo) {
                    if(target < *mid) hi = mid;
                    else if(target > *mid) lo = mid+1;
                    else return mid-nums.begin();
                }
                else if(target < *hi) {
                    if(target < *mid) hi = mid;
                    else if(target > *mid) lo = mid+1;
                    else return mid-nums.begin();
                }
                else return -1;
            }
            else if(*lo < *hi){//有序
                if(target < *mid) hi = mid;
                else if(target > *mid) lo = mid+1;
                else return mid-nums.begin();
            }
            mid = lo+(hi-lo)/2;
        }
        return *lo==target?lo-nums.begin():-1;
    }

};

int main(){
    /*===========================Test case============================*/
    vector<vector<int>> test{{1,2,3,4,5,6,7},
                             {3,4,5,6,1,2},
                             {1,6},
                             {2}};

    /*========================End test case===========================*/
    auto start = system_clock::now();
    /*============================API call============================*/
    for(auto& t:test){
        cout<<Solution::search(t, 6)<<endl;
    }
    /*========================End of API call=========================*/
    auto end = system_clock::now();
    auto duration =
            duration_cast<microseconds>(end-start);
    cout<<"Program spent "
        <<duration.count()
        <<" us"
        <<endl;
    return 0;
}

