#pragma once
#include<iostream>
#include<string>
#include"BankersAlgorithm.h"

using namespace std;

void menu() {
	string input;//�û���������
	int op;//����ѡ�������
	while (true) {
		cout << "*****����������ʾ����V1.0*****" << endl;
		cout << "*       1.��������           *" << endl;
		cout << "*       2.״̬չʾ           *" << endl;
		cout << "*       3.�������           *" << endl;
		cout << "*       4.�˳�����           *" << endl;
		cout << "******************************" << endl;
		cin >> input;
		if (input != "1" && input != "2" && input != "3"&&input!="4") {
			system("cls");
			cout << "���벻�Ϸ���������ѡ��" << endl;
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
			cout << "��лʹ�ã�" << endl;
			exit(0);
			break;
		}
	}
}