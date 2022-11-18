#include <iostream>
#include <fstream>
#include <list>
#include <vector>

int main() {

	std::ifstream fin("201 RAW.txt");

	if (fin.is_open()) 
	{
		int count = 0;
		const int SIZEBUF = 1024;
		char buffer[SIZEBUF] = {};

		std::string str, ip, mac;

		while (!fin.eof())
		{
			fin.getline(buffer, SIZEBUF, ' ');
			ip = buffer;
			fin.getline(buffer, SIZEBUF, '\n');
			mac = buffer;
			mac.erase(std::remove(mac.begin(), mac.end(), ' '), mac.end());
			str += mac + "\t" + ip + "\n";
		}
		fin.close();

		std::ofstream fout("201.dhcpd", std::ios::app);
		fout << str;
		fout.close();
	}

}