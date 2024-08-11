#include <iostream>
#include <chrono>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

vector<vector<string>> result;
vector<string> path;
bool isBack(const string& s) {
  int left = 0;
  int right = s.size() - 1;
  while (left <= right) {
    if (s[left] != s[right]) {
      return false;
    }
    left++;
    right--;
  }
  return true;
}

void backtrace(string s, int start) {
  if (path.size() == s.size()) {
    result.push_back(path);
    return;
  }
  int count = 0;
  for (int i = start; i < s.size(); i++) {
    count++;
    string str = s.substr(i, count);
    if (!isBack(str))
      continue;
    path.push_back(str);
    backtrace(s, start + 1);
    path.pop_back();
  }
}

vector<vector<string>> partition(string s) {
  backtrace(s, 0);
  return result;
}


int main() {

  string data = "aab";
  partition(data);

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