#include <iostream>
#include <chrono>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>

//
//using namespace std;
//
//class MinStack{
// private:
//  stack<pair<int,int>> minStack_;
// public:
//  MinStack(){
//
//  }
//  void push(int val){
//    pair<int,int> result;
//    if (minStack_.empty()){
//      result = pair<int,int>(val,min(val,val));
//    }else{
//      result = pair<int,int>(val,min(val,minStack_.top().second));
//    }
//    minStack_.push(result);
//  }
//  void pop(){
//    minStack_.pop();
//  }
//  int top(){
//    return minStack_.top().first;
//  }
//  int getMin(){
//    return minStack_.top().second;
//  }
//};
//
//#include <queue>
//class MyStack{
// private:
//  queue<int> stack_;
// public:
//  MyStack()= default;
//  void push(int x){
//
//  }
//  int pop(){
//    int re = stack_.back();
//
//  }
//  int top(){
//    return stack_.back();
//  }
//  bool empty(){
//    return stack_.empty();
//  }
//};
//
//
//bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
//  stack<int> data;
//  int len = pushed.size();
//  int pushLine = 0;
//  int popLine = 0;
//
//  for(pushLine; pushLine < len; pushLine++){
//    if(pushed[pushLine] == popped[popLine]){
//      popLine++;
//    }else{
//      if(!data.empty() && (popped[popLine] == data.top())){
//        data.pop();
//        popLine++;
//      }else{
//        data.push(pushed[pushLine]);
//      }
//    }
//  }
//
//  for(popLine; popLine < len; popLine++){
//    if(popped[popLine] != data.top()){
//      return false;
//    }
//    data.pop();
//  }
//
//  return true;
//}
//
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>


struct { int a; } anonStruct;
auto myStruct = anonStruct;


int main() {




  return 0;
}


/*
 * 2004 年 12 月 31 日 23 时 59 分 59 秒
 */

//struct ListNode {
//  int val;
//  ListNode *next;
//  ListNode() : val(0), next(nullptr) {}
//  ListNode(int x) : val(x), next(nullptr) {}
//  ListNode(int x, ListNode *next) : val(x), next(next) {}
//};


