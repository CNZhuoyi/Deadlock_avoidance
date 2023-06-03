#pragma once
#include<iostream>
#include<string>
#include"BankersAlgorithm.h"

using namespace std;

void menu() {
	string input;//用户输入内容
	int op;//操作选择控制数
	while (true) {
		cout << "*****死锁避免演示程序V1.0*****" << endl;
		cout << "*       1.输入数据           *" << endl;
		cout << "*       2.状态展示           *" << endl;
		cout << "*       3.请求分配           *" << endl;
		cout << "*       4.退出程序           *" << endl;
		cout << "******************************" << endl;
		cin >> input;
		if (input != "1" && input != "2" && input != "3"&&input!="4") {
			system("cls");
			cout << "输入不合法，请重新选择" << endl;
			continue;
		}
		op = stoi(input);
		switch (op) {
		case 1:
			DataSet();
			break;
		case 2:
			Display();
			break;
		case 3:
			BankersAlgorithm();
			break;
		case 4:
			cout << "感谢使用！" << endl;
			exit(0);
			break;
		}
	}
}