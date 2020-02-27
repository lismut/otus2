#include <iostream>
#include <fstream>
#include <iomanip>  
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>

using namespace std;
using CIp = tuple<int, int, int, int>;
using TAddresses = vector<CIp>;

CIp parse(const string& input)
{
	size_t idx = 0;
	size_t shift = 0;
	int ip1 = stoul(input.substr(idx), &shift);
	idx += shift + 1;
	int ip2 = stoul(input.substr(idx), &shift);
	idx += shift + 1;
	int ip3 = stoul(input.substr(idx), &shift);
	idx += shift + 1;
	int ip4 = stoul(input.substr(idx), &shift);
	return make_tuple(ip1, ip2, ip3, ip4);
}

void PrintIP(const CIp& ip)
{
	cout << (get<0>(ip)) << "." << get<1>(ip) << "." << get<2>(ip) << "." << get<3>(ip) << endl;
}

void conditionalOutput(const TAddresses& addrs, bool(*func)(const CIp&))
{
	for_each(addrs.begin(), addrs.end(), [&](const CIp& ip) {
		if (func(ip)) {
			PrintIP(ip);
		}
	});
}

int main()
{
	TAddresses addresses;
	string text1;
	while (getline(cin, text1)) {
		CIp ip = parse(text1);
		addresses.push_back(ip);
	}
	sort(addresses.begin(), addresses.end(), [](const auto& a, const auto& b) {
		return a > b;
    	});
	for_each(addresses.begin(), addresses.end(), [](const CIp& ip) {
		PrintIP(ip);
	});
	conditionalOutput(addresses, [](const CIp& ip) {
		if (get<0>(ip) == 1) return true;
		else return false;
	});
	conditionalOutput(addresses, [](const CIp& ip) {
		if (get<0>(ip) == 46 && get<1>(ip) == 70) return true;
		else return false;
	});
	conditionalOutput(addresses, [](const CIp& ip) {
		if (get<0>(ip) == 46 || get<1>(ip) == 46 || get<2>(ip) == 46 || get<3>(ip) == 46) return true;
		else return false;
	});
	return 0;
}
