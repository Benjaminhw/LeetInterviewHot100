/*
给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

示例 1：

输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。
示例 2：

输入：s = "a", t = "a"
输出："a"
解释：整个字符串 s 是最小覆盖子串。
示例 3:

输入: s = "a", t = "aa"
输出: ""
解释: t 中两个字符 'a' 均应包含在 s 的子串中，
因此没有符合条件的子字符串，返回空字符串

*/

#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


//265/268 继续剪枝
class Solution {
public:
	void addChar(char x, unordered_map<char, int>& m) {
		if (m.find(x) == m.end())
		{
			m[x] = 1;
		}
		else
		{
			++m[x];
		}
	}
	void deleteChar(char x, unordered_map<char, int>& m) {
		if (m[x] == 1)
		{
			m.erase(x);
		}
		else
		{
			--m[x];
		}
	}

	bool ifContains(unordered_map<char, int> S, unordered_map<char, int> sin)
	{
		for (auto& x : sin)
		{
			if (S.find(x.first) != S.end())
			{
				if (S[x.first] < x.second)
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		return true;
	}

	string minWindow(string s, string t) {
		string ans = "";
		if (s.size() < t.size())
		{
			return "";
		}
		else if (s.size() == t.size())
		{
			if (s == t)
			{
				return s;
			}
		}
		unordered_map<char, int> tempMap; //for 遍历tempMap即可
		unordered_map<char, int> theMap;

		int i = 0, j = 0;

		while (i < t.size())
		{
			addChar(s[i], tempMap);
			addChar(t[i], theMap);
			++i;
		}

		while (i <= s.size())
		{
			if (ifContains(tempMap, theMap))
			{
				while ( j < i && j < s.size())
				{
					if ((ans == "") || ans.size() > i - j)
					{
						ans = s.substr(j, i - j);
					}
					deleteChar(s[j], tempMap);
					if (theMap.find(s[j]) != theMap.end())
					{
						if (tempMap.find(s[j]) == tempMap.end())
						{
							break;
						}
						else
						{
							if (tempMap[s[j]] < theMap[s[j]])
							{
								break;
							}
						}
					}
					++j;
				}
			}
			if (i < s.size())
			{
				addChar(s[i], tempMap);
			}
			++i;
		}
		return ans;
	}
};