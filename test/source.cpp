#include <iostream>
#include <deque>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
//#define voxelsToReadInMemory 4096;
using namespace std;
template <class T>//要重载==  =(liangge)  !=  < >运算符     必须是一个类       T=-1要重载成标记次单元不存在-
class voxels{//向外可以只提供两个函数 getCode和saveOne   其他都能作为private
private:	
	string address;
	int levelL, levelH;

public://！！！size要小于等于levelL次数下一个文件中的数目    函数中加了一个检查  如果大于 就改小   没有检查会错 我也不知道为什么  可能是测试时候只有一个文件  第二个文件打不开就出错了  多文件测试时候要注意
	deque<T> voxel;
	voxels(string address_, int levelL_, int levelH_, int size = 4096);//构造函数需要知道去哪里读文件(目录)，赋值给address  并且读入前size个值    输入是address和deque的大小,还有两个划分次数   
	voxels(string address_) :address(address_){};
	typename deque<T>::iterator getCode(T mortonCode);//查找deque中有无所需的代码  如果有返回其迭代器  如果没有就去读一个
	typename deque<T>::iterator readOneCode(T needed);//输入为需要的   输出返回一个迭代器 如果没有找到就返回end()
	typename deque<T>::iterator readOneToUpdate(unsigned long long lordCommander);//输入为需要读的  读一个删除一个  删除时候要对文件中的进行修改  返回读入的数据的迭代器
	T readOneFromFile(unsigned long long monica);//读出monica编号的数据
	void saveOne(T oneToSave);//保存这个到队列中  队列中应该有这个 
	~voxels(){}
};
template<class T>
void voxels<T>::saveOne(T oneToSave){
	typename deque<T>::iterator temp = readOneCode(oneToSave);
	*temp = oneTosave;
}
template<class T>
T voxels<T>::readOneFromFile(unsigned long long monica){//使用二分法查找文件中的monica
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
		if (majnun < monica){//middle要变大
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
		cout << "读入的:"<<*asd.getCode(a) << endl;
		cout <<"size:"<< asd.voxel.size();
	}/*
	while (true){
		long long monica;
		cin >> monica;//要读的这个 用二分法查找
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
			if (majnun < monica){//middle要变大
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