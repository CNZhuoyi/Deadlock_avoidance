#pragma once
#include<iostream>
#include<vector>
#include<unordered_map>

#define MAXN 50//最大支持的进程数
#define MAXM 50//最大支持的资源类型数

using namespace std;

//vector<int> array //无大小限制
//vector<vector<int>>array  //无大小限制

int n;//进程数
int m;//资源类型数
int available[MAXM];//每类资源剩余量
int max_need[MAXN][MAXM];//进程需要每类资源的最大需求量
int allocation[MAXN][MAXM];//进程已得到的资源量
int need[MAXN][MAXM]; //进程还需要的资源量
int request[MAXN][MAXM];//进程申请的资源量


void DataSet();//数据设置
void Display();//展示数据
void BankersAlgorithm();//银行家算法
bool SafeCheck();//安全检查算法

void DataSet() {
	cout << "请输入进程数" << endl;;
	cin >> n;
	cout << "请输入资源类型数"<<endl;
	cin >> m;
	cout << "请依次输入每种资源的初始总量：" << endl;
	for (int i = 0; i < m; i++) {
		cout << "资源 R" << i + 1 << ": ";
		cin >> available[i];
	}

	cout << "请依次输入每个进程的分配和最大需求资源量：" << endl;
	for (int i = 0; i < n; i++) {
		cout << "进程 P" << i + 1 << ":" << endl;
		for (int j = 0; j < m; j++) {
			cout << "资源 R" << j + 1 << "的分配量和最大需求量：";
			cin >> allocation[i][j] >> max_need[i][j];
			need[i][j] = max_need[i][j] - allocation[i][j];
			available[j] -= allocation[i][j]; // 更新每种资源的剩余量
		}
	}
}


void Display() {
	system("cls");
	cout << "当前资源分配情况：" << endl;
	cout << "可用资源：" << endl;
	for (int i = 0; i < m; i++) {
		cout << "R" << i + 1 << ": " << available[i] << endl;
	}
	cout << "进程的资源分配情况：" << endl;
	for (int i = 0; i < n; i++) {
		cout << "进程 P" << i + 1 << ":" << endl;
		cout << "已分配资源：" << endl;
		for (int j = 0; j < m; j++) {
			cout << "R" << j + 1 << ": " << allocation[i][j] << endl;
		}
		cout << "还需资源：" << endl;
		for (int j = 0; j < m; j++) {
			cout << "R" << j + 1 << ": " << need[i][j] << endl;
		}
		cout << endl;
	}
}


void BankersAlgorithm() {
	int temp;
	cout << "请输入请求资源的进程的序号" << endl;
	cin >> temp;
	temp--;
	cout << "请依次输入进程P" << temp+1 << "对于" << m << "种资源的请求量" << endl;
	for (int i = 0; i < m; i++) {
		cin >> request[temp][i];
	}
	for (int i = 0; i < m; i++) {
		if (request[temp][i] > need[temp - 1][i]) {
			cout << "错误，进程请求量大于需求量!" << endl;
			system("pause");
			system("cls");
			break;
		}
		if (request[temp][i] > available[i]) {
			cout << "分配失败，系统中资源R" << i << "不足！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	//模拟资源分配
	for (int i = 0; i < m; i++) {
		available[i] -= request[temp][i];
		allocation[temp][i] += request[temp][i];
		need[temp][i] -= request[temp][i];
	}
	// 执行安全性检查
	if (SafeCheck()) {
		cout << "资源分配成功！" << endl;
	}
	else {
		// 分配失败，回滚分配操作
		for (int i = 0; i < m; i++) {
			available[i] += request[temp][i];
			allocation[temp][i] -= request[temp][i];
			need[temp][i] += request[temp][i];
		}
	}
}


bool SafeCheck() {
	int work[MAXM]; // 用于记录系统提供给进程继续运行所需的资源数
	bool finish[MAXN]; // 用于记录每个进程是否已获得足够资源可以执行完毕
	vector<int> safe_sequence; // 存储安全序列

	// 初始化work数组和finish数组
	for (int i = 0; i < m; i++) {
		work[i] = available[i];
	}
	for (int i = 0; i < n; i++) {
		finish[i] = false;
	}

	// 找到一个可执行的进程
	int count = 0; // 记录已执行完毕的进程数

	while (count < n) {
		bool found = false; // 默认未找到可执行的进程

		for (int i = 0; i < n; i++) {
			if (!finish[i]) { // 对于尚未执行完毕的进程
				bool canExecute = true; // 标记该进程是否可以执行

				// 检查该进程的资源需求是否小于等于可用资源
				for (int j = 0; j < m; j++) {
					if (need[i][j] > work[j]) {
						canExecute = false;
						break;
					}
				}

				if (canExecute) {
					// 将该进程标记为已执行完毕
					finish[i] = true;
					found = true;
					count++;

					// 释放该进程占用的资源，添加到可用资源中
					for (int j = 0; j < m; j++) {
						work[j] += allocation[i][j];
					}

					// 将执行完毕的进程添加到安全序列中
					safe_sequence.push_back(i);
				}
			}
		}

		// 如果没有找到可执行的进程，则系统不处于安全状态
		if (!found) {
			break;
		}
	}

	// 判断系统是否处于安全状态
	if (count == n) {
		cout << "系统处于安全状态，安全序列为: ";
		for (int i = 0; i < safe_sequence.size(); i++) {
			cout << "P" << safe_sequence[i] + 1 << " ";
		}
		cout << endl;
		return true;
	}
	else {
		cout << "系统处于不安全状态，无法找到安全序列！" << endl;
		return false;
	}
}
