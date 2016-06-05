#include <iostream>
#include <deque>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
//#define voxelsToReadInMemory 4096;
using namespace std;
template <class T>//Ҫ����==  =(liangge)  !=  < >�����     ������һ����       T=-1Ҫ���سɱ�Ǵε�Ԫ������-
class voxels{//�������ֻ�ṩ�������� getCode��saveOne   ����������Ϊprivate
private:	
	string address;
	int levelL, levelH;

public://������sizeҪС�ڵ���levelL������һ���ļ��е���Ŀ    �����м���һ�����  ������� �͸�С   û�м���� ��Ҳ��֪��Ϊʲô  �����ǲ���ʱ��ֻ��һ���ļ�  �ڶ����ļ��򲻿��ͳ�����  ���ļ�����ʱ��Ҫע��
	deque<T> voxel;
	voxels(string address_, int levelL_, int levelH_, int size = 4096);//���캯����Ҫ֪��ȥ������ļ�(Ŀ¼)����ֵ��address  ���Ҷ���ǰsize��ֵ    ������address��deque�Ĵ�С,�����������ִ���   
	voxels(string address_) :address(address_){};
	typename deque<T>::iterator getCode(T mortonCode);//����deque����������Ĵ���  ����з����������  ���û�о�ȥ��һ��
	typename deque<T>::iterator readOneCode(T needed);//����Ϊ��Ҫ��   �������һ�������� ���û���ҵ��ͷ���end()
	typename deque<T>::iterator readOneToUpdate(unsigned long long lordCommander);//����Ϊ��Ҫ����  ��һ��ɾ��һ��  ɾ��ʱ��Ҫ���ļ��еĽ����޸�  ���ض�������ݵĵ�����
	T readOneFromFile(unsigned long long monica);//����monica��ŵ�����
	void saveOne(T oneToSave);//���������������  ������Ӧ������� 
	~voxels(){}
};
template<class T>
void voxels<T>::saveOne(T oneToSave){
	typename deque<T>::iterator temp = readOneCode(oneToSave);
	*temp = oneTosave;
}
template<class T>
T voxels<T>::readOneFromFile(unsigned long long monica){//ʹ�ö��ַ������ļ��е�monica
	string fileAddress;
	unsigned long long fileNum = monica / (1 << (3 * levelL));
	stringstream ss;
	ss << fileNum;
	ss >> fileAddress;
	fileAddress = address + "\\outOfCore" + fileAddress + ".bat";
	ifstream readIn;
	readIn.open(fileAddress, ios::in | ios::binary);
	T majnun;
	readIn.read((char *)&majnun, sizeof(T));
	readIn.seekg(sizeof(T), ios::end);
	long start = 0, end = readIn.tellg() / 8;
	end -= 1;
	long middle = ((end - start) - ((end - start) % 2)) / 2;
	middle *= 8;
	readIn.seekg(middle, ios::beg);
	readIn.read((char *)&majnun, sizeof(T));
	while (majnun != monica){
		middle /= 8;
		if (majnun < monica){//middleҪ���
			start = middle;
			if (end - start == 1){
				middle = end;
				readIn.seekg(middle, ios::beg);
				readIn.read((char *)&majnun, sizeof(T));
				if (majnun != monica){
					majnun = -1;
					return majnun;
				}
			}
			else
				middle = (((end - start) - ((end - start) % 2)) / 2 + start) * 8;
		}
		else{
			end = middle;
			if (end - start == 1){
				middle = start;
				readIn.seekg(middle, ios::beg);
				readIn.read((char *)&majnun, sizeof(T));
				if (majnun != monica){
					majnun = -1;
					return majnun;
				}
			}
			else
				middle = (((end - start) - ((end - start) % 2)) / 2 + start) * 8;
		}
		readIn.seekg(middle, ios::beg);
		readIn.read((char *)&majnun, sizeof(T));
	}
	return majnun;
}
template<class T>
typename deque<T>::iterator voxels<T>::readOneToUpdate(unsigned long long lordCommander){
	T majnun = readOneFromFile(lordCommander);
	//upadte the file
	voxel.pop_front();
	voxel.push_back(majnun);
	return (voxel.end() - 1);
}
template<class T>
typename deque<T>::iterator voxels<T>::getCode(T mortonCode){
	unsigned long long findThisOne = mortonCode;
	deque<T>::iterator temp = readOneCode(mortonCode);
	if (temp != voxel.end())
		return temp;
	else
		return readOneToUpdate(findThisOne);
}
template<class T>
voxels<T>::voxels(string address_, int levelL_, int levelH_, int size = 4096){
	address = address_;
	levelL = levelL_;
	levelH = levelH_;
	size = size < 1 << (3 * levelH) ? size : 1 << (3 * levelH);
	for (int i = 0; i < size; i++){
		voxel.push_back(readOneFromFile(i));
		cout << voxel[i] << endl;
	}
	cout << voxel.size();
}
template<class T>
typename deque<T>::iterator voxels<T>::readOneCode(T needed){
	deque<T>::iterator temp = voxel.begin();
	for (; temp != voxel.end();temp++){
		if (*temp == needed){
			return temp;
		}
	}
	return voxel.end();
}

int main(){
	voxels<long long> asd("d:", 2, 2, 32);
	while (true){
		cout << endl;
		cout << endl;
		unsigned long long a;
		cin >> a;
		cout << "�����:"<<*asd.getCode(a) << endl;
		cout <<"size:"<< asd.voxel.size();
	}/*
	while (true){
		long long monica;
		cin >> monica;//Ҫ������� �ö��ַ�����
		ifstream readIn;
		readIn.open("d:\\outOfCore0.bat", ios::in | ios::binary);
		long long majnun;
		readIn.read((char *)&majnun, sizeof(long long));
		cout << majnun << ' ';
		readIn.seekg(sizeof(long long), ios::end);
		cout << readIn.tellg();
		long start = 0, end = readIn.tellg() / 8;
		end -= 1;
		long middle = ((end - start) - ((end - start) % 2)) / 2;
		middle *= 8;

		readIn.seekg(middle, ios::beg);
		readIn.read((char *)&majnun, sizeof(long long));
		cout << majnun << ' ' << endl;
		while (majnun != monica){
			middle /= 8;
			if (majnun < monica){//middleҪ���
				start = middle;
				if (end - start == 1){
					middle = end;
					readIn.seekg(middle, ios::beg);
					readIn.read((char *)&majnun, sizeof(long long));
					if (majnun != monica){
						cout << "wrong";
						break;
					}
				}
				else
					middle = (((end - start) - ((end - start) % 2)) / 2 + start) * 8;
			}
			else{
				end = middle;
				if (end - start == 1){
					middle = start;
					readIn.seekg(middle, ios::beg);
					readIn.read((char *)&majnun, sizeof(long long));
					if (majnun != monica){
						cout << "wrong";
						break;
					}
				}
				else
					middle = (((end - start) - ((end - start) % 2)) / 2 + start) * 8;
			}
			readIn.seekg(middle, ios::beg);
			readIn.read((char *)&majnun, sizeof(long long));

			cout << start << ' ' << middle / 8 << ' ' << end << ' ' << majnun << endl;
		}
		cout << majnun;
	}*/
	/*vector<long long> monica;
	ifstream readIn;
	readIn.open("d:\\outOfCore0.bat", ios::in | ios::binary);
	
	int temp;
	long majnun = 0;
	cout << readIn.tellg();
	while (readIn.read((char *)& temp, sizeof(long long))){		
		cout << temp << ' ' << readIn.tellg() << ' ' << '|';
		monica.push_back(temp);
		if (readIn.tellg() >= 38416)
			break;
	}
	
	readIn.close();*////////////////////////////////////////////////////////////////////////
	/*CStudent s;
	cout << sizeof(s);
	ofstream OutFile("D:\\outOfCore\\7\\outOfCore0.bat", ios::out | ios::binary);
	while (cin >> s.szName >> s.nScore){
		if (_stricmp(s.szName, "exit") == 0)
			break;
		OutFile.write((char*)&s, sizeof(s));
	}
	OutFile.close();
	ifstream InFile("student.dat", ios::in | ios::binary);
	long location = InFile.tellg();
	InFile.seekg(sizeof(s));
	InFile.read((char*)&s, sizeof(s));
	cout << s.szName << s.nScore;*/
	/*while (InFile.read((char *)&s, sizeof(s))){
		int nReadedBytes = InFile.gcount();
		cout << nReadedBytes << ' ' << s.szName << s.nScore << endl;
	}*/
	//InFile.close();
	return 0;
}