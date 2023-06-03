#pragma once
#include<iostream>
#include<vector>
#include<unordered_map>

#define MAXN 50//���֧�ֵĽ�����
#define MAXM 50//���֧�ֵ���Դ������

using namespace std;

//vector<int> array //�޴�С����
//vector<vector<int>>array  //�޴�С����

int n;//������
int m;//��Դ������
int available[MAXM];//ÿ����Դʣ����
int max_need[MAXN][MAXM];//������Ҫÿ����Դ�����������
int allocation[MAXN][MAXM];//�����ѵõ�����Դ��
int need[MAXN][MAXM]; //���̻���Ҫ����Դ��
int request[MAXN][MAXM];//�����������Դ��


void DataSet();//��������
void Display();//չʾ����
void BankersAlgorithm();//���м��㷨
bool SafeCheck();//��ȫ����㷨

void DataSet() {
	cout << "�����������" << endl;;
	cin >> n;
	cout << "��������Դ������"<<endl;
	cin >> m;
	cout << "����������ÿ����Դ�ĳ�ʼ������" << endl;
	for (int i = 0; i < m; i++) {
		cout << "��Դ R" << i + 1 << ": ";
		cin >> available[i];
	}

	cout << "����������ÿ�����̵ķ�������������Դ����" << endl;
	for (int i = 0; i < n; i++) {
		cout << "���� P" << i + 1 << ":" << endl;
		for (int j = 0; j < m; j++) {
			cout << "��Դ R" << j + 1 << "�ķ������������������";
			cin >> allocation[i][j] >> max_need[i][j];
			need[i][j] = max_need[i][j] - allocation[i][j];
			available[j] -= allocation[i][j]; // ����ÿ����Դ��ʣ����
		}
	}
}


void Display() {
	system("cls");
	cout << "��ǰ��Դ���������" << endl;
	cout << "������Դ��" << endl;
	for (int i = 0; i < m; i++) {
		cout << "R" << i + 1 << ": " << available[i] << endl;
	}
	cout << "���̵���Դ���������" << endl;
	for (int i = 0; i < n; i++) {
		cout << "���� P" << i + 1 << ":" << endl;
		cout << "�ѷ�����Դ��" << endl;
		for (int j = 0; j < m; j++) {
			cout << "R" << j + 1 << ": " << allocation[i][j] << endl;
		}
		cout << "������Դ��" << endl;
		for (int j = 0; j < m; j++) {
			cout << "R" << j + 1 << ": " << need[i][j] << endl;
		}
		cout << endl;
	}
}


void BankersAlgorithm() {
	int temp;
	cout << "������������Դ�Ľ��̵����" << endl;
	cin >> temp;
	temp--;
	cout << "�������������P" << temp+1 << "����" << m << "����Դ��������" << endl;
	for (int i = 0; i < m; i++) {
		cin >> request[temp][i];
	}
	for (int i = 0; i < m; i++) {
		if (request[temp][i] > need[temp - 1][i]) {
			cout << "���󣬽�������������������!" << endl;
			system("pause");
			system("cls");
			break;
		}
		if (request[temp][i] > available[i]) {
			cout << "����ʧ�ܣ�ϵͳ����ԴR" << i << "���㣡" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	//ģ����Դ����
	for (int i = 0; i < m; i++) {
		available[i] -= request[temp][i];
		allocation[temp][i] += request[temp][i];
		need[temp][i] -= request[temp][i];
	}
	// ִ�а�ȫ�Լ��
	if (SafeCheck()) {
		cout << "��Դ����ɹ���" << endl;
	}
	else {
		// ����ʧ�ܣ��ع��������
		for (int i = 0; i < m; i++) {
			available[i] += request[temp][i];
			allocation[temp][i] -= request[temp][i];
			need[temp][i] += request[temp][i];
		}
	}
}


bool SafeCheck() {
	int work[MAXM]; // ���ڼ�¼ϵͳ�ṩ�����̼��������������Դ��
	bool finish[MAXN]; // ���ڼ�¼ÿ�������Ƿ��ѻ���㹻��Դ����ִ�����
	vector<int> safe_sequence; // �洢��ȫ����

	// ��ʼ��work�����finish����
	for (int i = 0; i < m; i++) {
		work[i] = available[i];
	}
	for (int i = 0; i < n; i++) {
		finish[i] = false;
	}

	// �ҵ�һ����ִ�еĽ���
	int count = 0; // ��¼��ִ����ϵĽ�����

	while (count < n) {
		bool found = false; // Ĭ��δ�ҵ���ִ�еĽ���

		for (int i = 0; i < n; i++) {
			if (!finish[i]) { // ������δִ����ϵĽ���
				bool canExecute = true; // ��Ǹý����Ƿ����ִ��

				// ���ý��̵���Դ�����Ƿ�С�ڵ��ڿ�����Դ
				for (int j = 0; j < m; j++) {
					if (need[i][j] > work[j]) {
						canExecute = false;
						break;
					}
				}

				if (canExecute) {
					// ���ý��̱��Ϊ��ִ�����
					finish[i] = true;
					found = true;
					count++;

					// �ͷŸý���ռ�õ���Դ����ӵ�������Դ��
					for (int j = 0; j < m; j++) {
						work[j] += allocation[i][j];
					}

					// ��ִ����ϵĽ�����ӵ���ȫ������
					safe_sequence.push_back(i);
				}
			}
		}

		// ���û���ҵ���ִ�еĽ��̣���ϵͳ�����ڰ�ȫ״̬
		if (!found) {
			break;
		}
	}

	// �ж�ϵͳ�Ƿ��ڰ�ȫ״̬
	if (count == n) {
		cout << "ϵͳ���ڰ�ȫ״̬����ȫ����Ϊ: ";
		for (int i = 0; i < safe_sequence.size(); i++) {
			cout << "P" << safe_sequence[i] + 1 << " ";
		}
		cout << endl;
		return true;
	}
	else {
		cout << "ϵͳ���ڲ���ȫ״̬���޷��ҵ���ȫ���У�" << endl;
		return false;
	}
}
