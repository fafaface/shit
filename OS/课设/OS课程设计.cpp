#include<iostream>
#include<fstream>
#include<time.h>
#include<iomanip>
#include<sys\stat.h>
#include<stdlib.h>
#include<string.h>
#include<direct.h>
#include<windows.h>
#include<winnls.h>
#include<direct.h>
#include<io.h>
#include<stdio.h>
#include<locale.h>
#include<Tchar.h>
#include<string>
#include<memory>
#include<crtdefs.h>

using namespace std;

#define DISKSIZE 1024*1024	//磁盘大小
#define BLOCKSIZE 1024	//盘块大小
#define FCBSIZE 32	//文件目录块大小
#define DATASIZE 10112	//数据大小
#define FAT1BEG 1	//FAT1表开始位置
#define MAPBEG 126	//位示图开始位置
#define DATABEG 128	//地址存储开始位置

struct diskinfo		//磁盘信息数据结构
{
	unsigned long size;			//磁盘大小，单位字节
	unsigned long blocksize;	//磁盘的盘块大小，单位字节
	unsigned long blocknum;		//磁盘的盘块数
	unsigned long clustersize;	//一簇的大小，单位盘块
	unsigned long usedspace;	//已用空间，单位字节
	unsigned long remainspace;	//剩余空间，单位字节
	unsigned long usedblock;	//已用盘块
	unsigned long remainblock;	//剩余盘块
};

struct directory	//目录项，即FCB
{
	string name;			//文件前缀或目录名
	string type;			//扩展名
	bool isdir;				//目录标示符
	time_t buildtime;		//创建时间
	time_t accesstime;		//访问时间
	time_t modtime;			//修改时间
	unsigned short int beginblock;	//文件起始盘块或目录盘块
	long filesize;			//文件大小或目录所含目录项数目
	string inside;	//文件内部存储内容
};

static string globalpath;	//当前路径
static string diskpath = "SDisk.dat";	//虚拟磁盘路径
static fstream disk;	//虚拟磁盘
static diskinfo dinfo;	//磁盘信息
static unsigned short int fat[DATASIZE];	//FAT表1
static unsigned short int map[DATASIZE / 16];	//位示图
static int curblock;	//当前目录盘块（相对位置）
static directory curdir[7],temp[7];	//当前目录列表和临时目录列表
static char right[] = ".", parent[] = "..";

struct CMD
{
	string cmd;
	string command;	//命令
	string address;	//地址（如果有两个地址也会同时存在这个string内）
}c;	//命令结构体，包含命令和地址，为全局变量

//初始化磁盘信息
void init_diskinfo()	
{
	dinfo.blocksize = BLOCKSIZE;	//盘块大小，静态
	dinfo.clustersize = 1;	//毎簇大小，静态
	dinfo.blocknum = DISKSIZE / BLOCKSIZE;	//磁盘数据区盘块数，静态
	dinfo.size = DISKSIZE;	//磁盘总大小，静态
	dinfo.usedblock = 1;	//已用盘块数，初始化时一盘块做根目录区，动态
	dinfo.remainblock = dinfo.blocknum - 1;	//剩余盘块数，初始化时去掉根目录盘块
	dinfo.usedspace = BLOCKSIZE;	//已用大小，用掉了根目录盘块
	dinfo.remainspace = dinfo.size - dinfo.usedspace;	//未用大小
}

//fat初始化，第一个盘块初始化为已用，置结束标识符ff0f，其余未用盘块置0
void init_fat()
{
	fat[0] = 0xFF0F;
	for(int i = 1; i < DATASIZE; i++)
		fat[i] = 0;
}

//初始化位示图，第一个盘块置1，其余置0
void init_map()
{
	for(int i = 0; i < DATASIZE / 16 - 1; i++)
		map[i] = 0;
	map[0] |= (1 << 15);
}

//建立虚拟磁盘的文件流，并返回是载入或是新建磁盘的bool型变量
bool init_disk()
{
	char * path;
	path = (char *)malloc(diskpath.length() * sizeof(char));
	diskpath.copy(path, diskpath.length(), 0);

	if(access("SDisk.dat", 0) != -1)	//如果磁盘已存在
	{
		cout << "Find existing disk: SDisk" << endl;
enter:	
		cout << "Enter [Y] to Load it or [N] to empty it:";	//提示用户是否载入已存在的磁盘，否则清空原有
		char ch;
		cin >> ch;
		cin.ignore(1000, '\n');	//清空输入流，把回车清掉
		if(ch == 'y' || ch == 'Y')	//用户选择载入磁盘
		{
			cout << "Load the existing disk..." << endl;
			disk.open(diskpath, ios::in | ios::out | ios::binary);//建立文件流
			return true;	//返回
		}
		else if(ch == 'n' || ch == 'N');	//用户选择新建磁盘
		else	//字符不对应，提示重新输入
		{
			cout << "No corresponding order of " << ch << endl;
			goto enter;
		}
	}
	//开始新建盘（当盘不存在或者用户希望新建盘的时候）
	char end = EOF;	//文件结束标识符
	disk.open(diskpath, ios::trunc | ios::in | ios::out | ios::binary);	//建立文件流
	disk.seekp(DISKSIZE, ios::beg);	//写入文件结束标识符
	disk << end;
	cout << "Creating new disk 'SDisk'......" << endl;
	return false;	//返回
}

//初始化目录项的时间信息
void init_dirtime(directory *dir)
{
	time(&(*dir).buildtime);
	time(&(*dir).accesstime);
	time(&(*dir).modtime);
}

//初始化新建目录的共同目录项字段
void init_dir(directory *dir)
{
	(*dir).filesize = 0;	//∵新建，且目录在父目录下的目录项不显示本目录的目录项数目
	(*dir).isdir = true;	//是目录
	(*dir).type = '\0';	//目录项无扩展名
	init_dirtime(dir);	//初始化目录项的时间信息
}

//初始化根目录并同步到磁盘上
void init_root()
{
	curblock = 0;	//初始化当前目录在根目录;
	for(int i = 2; i < 7; i++)	//初始化其他目录项为空
		curdir[i].name = (char) 0xE5;
	curdir[0].beginblock = 0;	//根目录
	init_dir(&curdir[0]);	//初始化根目录的本目录项（'.'），因为是目录，所以用initdir
	curdir[0].name = ".";
	memcpy(&curdir[1], &curdir[0], sizeof(directory));	//初始化父目录的本目录项，其实这一步可以不需要，因为根节点不会有子目录
	curdir[1].name = parent;
	disk.seekp(DATABEG * BLOCKSIZE, ios::beg);
	disk.write((char*)&curdir, sizeof(curdir));	//同步根目录到磁盘上
	globalpath = "/";	//初始化当前路径为根目录'/'
}

//同步磁盘内容到内存中，包括磁盘信息，fat表，位示图和根目录
void disktomem()
{
	disk.seekg(0, ios::beg);
	disk.read((char*)&dinfo, sizeof(diskinfo));
	disk.seekg(FAT1BEG*BLOCKSIZE, ios::beg);
	disk.read((char*)&fat, sizeof(fat));
	disk.seekg(MAPBEG*BLOCKSIZE, ios::beg);
	disk.read((char*)&map, sizeof(map));
	disk.seekg(DATABEG*BLOCKSIZE, ios::beg);
	disk.read((char*)&curdir, sizeof(curdir));
}

//同步内存中的磁盘信息、fat、map、根目录到磁盘上
void memtodisk()
{
	disk.seekp(0, ios::beg);
	disk.write((char*)&dinfo, sizeof(diskinfo));
	disk.seekp(FAT1BEG*BLOCKSIZE, ios::beg);
	disk.write((char*)&fat, sizeof(fat));
	disk.seekp(MAPBEG*BLOCKSIZE, ios::beg);
	disk.write((char*)&map, sizeof(map));
}

//初始化SDisk.dat及其文件系统
void init_fs()
{
	if(init_disk())		//磁盘为载入
	{
		disktomem();	//从磁盘上同步信息到内存
		curblock = 0;		//初始化当前目录及路径
		globalpath = "/";
	}
	else				//否则初始化磁盘信息、fat、map、根目录
	{
		init_diskinfo();
		init_fat();
		init_map();
		init_root();
		memtodisk();	//并同步到磁盘上
	}
}

//将字符串文件名分解成文件名和扩展名
bool analysisname(string filename, string &name, string &type)
{
	unsigned int i;
	name = "";
	for(i = 0;  (i < filename.length()) && (filename[i] != '.'); i++);	//定位到文件名和扩展名分隔符
	if(i == filename.length())		//无扩展名
	{
		name = filename;
		type = "";
	}
	else	//有扩展名
	{
		name = "";
		type = "";
		for(int j = 0; j < i; j++)
			name.push_back(filename[j]);
		for(int j = i + 1; j < filename.length(); j++)
			type.push_back(filename[j]);
	}
	return true;
}

//文件名和目录名中是否有非法字符
bool isName(bool isdir, string filename)	
{
	unsigned i,j;
	for(i = 0; (i < filename.length()) && (filename[i] != '.'); i++)	//找到文件名和扩展名分隔符'.'
		if(filename[i] == '/')	//文件名或者目录名中有目录项分隔符/
			return false;
	if(isdir && i != filename.length())	//目录名中有'.'
		return false;
	for(j = i + 1; j < filename.length(); j++)
		if(filename[j] == '/' || filename[j] == '.')	//文件扩展名中有非法字符
			return false;
	return true;
}

//分配size个盘块，修改fat、map、磁盘信息并返回size个盘块中的开始盘块号
unsigned short int allocate(unsigned int size)
{
	unsigned short int beginblock,lastblock;
	if(size <= 0)	//所申请要分配的空间必须大于0
	{
		cout << "The space apply for must be positive!" << endl;
		return 0;
	}
	if(dinfo.remainblock < size)	//没有足够的空间
	{
		cout << "No enough space!" << endl;
		return 0;
	}
	for(unsigned int i = 0, j = 0; i < DATASIZE && j < size; i++)	//遍历位示图
	{
		if(map[i / 16] & (1 << (15 - i % 16)))	//盘块已用
			continue;
		else	//找到空闲盘块
		{
			map[i / 16] |= (1 << (15 - i % 16));	//重置map相应位置
			if((j++) == 0)	//当前分配的是第一个盘块
				beginblock = i;	//置开始盘块为i
			else
				fat[lastblock] = i;	//否则置上次分配的盘块对应的fat项为i
			lastblock = i;	//记录当前盘块以备分配下个盘块用
		}
//		cout << "begin_block:" << beginblock << "  last_block:" << lastblock << endl;
	}
	fat[lastblock] = 0xFF0F;	//最后一个盘块置文件结束符
	dinfo.usedblock += size;	//更新磁盘信息
	dinfo.remainblock -= size;
	dinfo.usedspace += size * BLOCKSIZE;
	dinfo.remainspace -= size * BLOCKSIZE;
	memtodisk();	//同步到磁盘
	return beginblock;	//返回分配盘块的开始盘块
}

//根据文件名在block所指目录盘块下找到文件目录项
int find(string filename, int block)
{
	disk.seekg((block + DATABEG) * BLOCKSIZE, ios::beg);
	disk.read((char*)temp, sizeof(temp));
	if(filename == "..")	//为父目录
		return 1;
	if(filename == ".")	//为本目录
		return 0;
	for(int i = 0; i < temp[0].filesize + 2; i++)
	{
		if(temp[i].isdir && (filename == temp[i].name))	//目录直接比较目录名
			return i;
		else	//若为文件则将文件名扩展名合并比较
		{
			string tempname = temp[i].name + "." + temp[i].type;
			if(tempname == filename)	//比较文件名
				return i;
		}			
	}
	return -1;
}

//创建目录
void createdir(string name)
{
	if(curdir[0].filesize == 5)	//目录中目录项已满
	{
		cout << "Creating directory or file FAILED!" << endl;
		return;
	}
	if(!isName(true, name))	//目录名中是否含有非法字符
	{
		cout << "Illagel character exists." << endl;
		return;
	}
	if(find(name, curblock) != -1)	//在当前目录下有重名的文件或目录
	{	
		cout << "The directory:" << name << " is existing." << endl;
		return;
	}
	int beginblock = allocate(1);	//分配文件空间
	if(!beginblock)	//分配失败，退出
	{
		cout << "Creating Failed!" << endl;
		return;
	}
	int pos = (curdir[0].filesize) + 2;
	curdir[0].filesize += 1;
	curdir[pos].beginblock = beginblock;
	curdir[pos].name = name;
	init_dir(&curdir[pos]);	//初始化目录项                                                                                           
	disk.seekp((curblock + DATABEG) * BLOCKSIZE);
	disk.write((char*)curdir, sizeof(curdir));	//同步目录到磁盘
	memcpy(&temp[0], &curdir[curdir[0].filesize + 1], sizeof(directory));	//新建目录第一项(.)初始化( = currdir[新建项])
	memcpy(&temp[1], &curdir[0], sizeof(directory));	//将新建目录第二项(..)初始化( = currdir[.])
	temp[1].filesize = 0;	//子目录无法得知父t目录下的目录项个数
	temp[0].name = ".";
	temp[1].name = parent;
	disk.seekp((curdir[pos].beginblock + DATABEG) * BLOCKSIZE, ios::beg);
	disk.write((char*)temp, sizeof(temp));	//同步新建目录到磁盘
	disk.seekg((curdir[pos].beginblock + DATABEG) * BLOCKSIZE, ios::beg);
	disk.read((char*)temp, sizeof(temp));	//同步新建目录到磁盘
	disk.seekg((curdir[1].beginblock + DATABEG) * BLOCKSIZE, ios::beg);
	disk.read((char*)temp, sizeof(temp));
	for(int i = 0; i < 7; i++)
		if(temp[i].beginblock == curdir[0].beginblock)
		{
			temp[i].filesize = curdir[0].filesize;
			disk.seekp((temp[0].beginblock + DATABEG) * BLOCKSIZE, ios::beg);
			disk.write((char*)temp, sizeof(temp));
			break;
		}	//////////////////////////////////////////报告重点！
	disk.seekg((curdir[pos].beginblock + DATABEG) * BLOCKSIZE, ios::beg);
	disk.read((char*)temp, sizeof(temp));	//同步新建目录到磁盘
	return;
}

//创建文件
void create_file(string filename, int size, string inside)
{
	if(curdir[0].filesize == 5)	//目录中目录项已满
	{
		cout << "The current directory already has 30 directories!Cannot create directory or file anymore!!" << endl;
		return;
	}
	int beginblock = allocate(size);	//分配文件空间
	if(!beginblock)	//分配失败，退出
	{
		cout << "Failed to create new file!" << endl;
		return;
	}
	string name, type;
	analysisname(filename, name, type);
	int pos = (curdir[0].filesize++) + 2;
	curdir[pos].beginblock = beginblock;	//初始化文件的目录项
	curdir[pos].name = name;
	curdir[pos].type = type;
	curdir[pos].isdir = false;
	curdir[pos].filesize = size;	
	curdir[pos].inside = inside;
	init_dirtime(&curdir[pos]);
	disk.seekp((curblock + DATABEG) * BLOCKSIZE, ios::beg);
	disk.write((char*)curdir, sizeof(curdir));	//同步目录到磁盘
	disk.seekg((curdir[1].beginblock + DATABEG) * BLOCKSIZE, ios::beg);
	disk.read((char*)temp, sizeof(temp));
	for(int i = 0; i < 7; i++)
		if(temp[i].beginblock == curdir[0].beginblock)
		{
			temp[i].filesize = curdir[0].filesize;
			disk.seekp((temp[0].beginblock + DATABEG) * BLOCKSIZE, ios::beg);
			disk.write((char*)temp, sizeof(temp));
			break;
		}	//////////////////////////////////////////报告重点！
	disk.seekg((curdir[pos].beginblock + DATABEG) * BLOCKSIZE, ios::beg);
	disk.read((char*)temp, sizeof(temp));	//同步新建目录到磁盘
}

//根据文件名在block所指目录盘块下找到文件目录项
int show_more(string filename, int block)
{
	disk.seekg((block + DATABEG) * BLOCKSIZE, ios::beg);
	disk.read((char*)temp, sizeof(temp));
	for(int i = 0; i < temp[0].filesize + 2; i++)
	{
		if(temp[i].isdir && (filename == temp[i].name))//目录直接比较目录名
		{	
	        cout.setf(ios::left);
			cout << "Build time: ";
		    cout << ctime(&temp[i].buildtime);
			cout << "Contianing file's number: ";
			cout << temp[i].filesize << endl;;
			return i;
		}
		else	//若为文件则将文件名扩展名合并比较
		{
			string tempname;
			tempname = temp[i].name + "." + temp[i].type;
			if(tempname == filename)//比较文件名
				{
	             cout.setf(ios::left);
				 cout << "Build time: ";
				 cout << ctime(&temp[i].buildtime);
				 cout << filename << endl;
				 cout << setw(6)<<setfill(' ') << temp[i].inside << endl;
				 return i;
			    }
		}
	}
	return -1;
}

//回收指定的空间，递归
void recycle(int dirblock, int pos)
{
	int size = 0;	//记录回收的盘块数
	disk.seekg((dirblock + DATABEG) * BLOCKSIZE, ios::beg);
	disk.read((char*)temp, sizeof(temp));
	directory tempdir;
	memcpy(&tempdir, &temp[pos], sizeof(directory));	//暂存所要删除的目录项
	temp[pos].name = (char)0xE5;	//清除目录项
	temp[0].filesize --;	//本目录更新数据
	if(pos != temp[0].filesize + 2)	//保持目录项的连贯
		memcpy(&temp[pos], &temp[pos + 1], (temp[0].filesize + 2 - pos) * sizeof(directory));
	disk.seekp((dirblock + DATABEG) * BLOCKSIZE, ios::beg);	//更新到磁盘中
	disk.write((char*)temp, sizeof(temp));
	if(tempdir.isdir)	//删除子目录下的内容
	{
		size += 1;	//回收目录盘块+1
		map[tempdir.beginblock / 16] &= (~(1 << (15 - tempdir.beginblock % 16)));	//置位示图相应位置
		fat[tempdir.beginblock] = 0;	//置fat相应位置
		disk.seekg((tempdir.beginblock + DATABEG) * BLOCKSIZE, ios::beg);
		disk.read((char*)temp, sizeof(temp));	//获取子目录的目录项		
		for(int i = temp[0].filesize + 1; i > 1; i--)
			recycle(tempdir.beginblock, i);	//递归回收目录下的内容
	}
	else	//回收文件
	{
		size += temp[pos].filesize;	//回收文件，回收大小加文件大小
		int thisblock = tempdir.beginblock, nextblock;
		for(int i = 0; i < tempdir.filesize; i++)	//沿fat指示回收盘块
		{
			nextblock = fat[thisblock];	//记录下一个要回收的盘块
			map[thisblock / 16] &= (~(1 << (15 - thisblock % 16)));	//置map位
			fat[thisblock] = 0;	//置fat位
			thisblock = nextblock;
		}
	}
	dinfo.usedblock -= size;	//更新磁盘信息
	dinfo.remainblock += size;
	dinfo.usedspace -= size * BLOCKSIZE;
	dinfo.remainspace += size * BLOCKSIZE;
	memtodisk();	//同步到磁盘上
}

//删除文件
void delfile(int pos)
{
	if(curdir[pos].isdir)	//删除的目录项不能为目录
		cout << curdir[pos].name << "is not a file." << endl;
	else	//删除的目录项是文件
	{
		recycle(curblock, pos);	//回收文件所占空间
		disk.seekg((curblock + DATABEG) * BLOCKSIZE, ios::beg);
		disk.read((char*)curdir,sizeof(curdir));	//磁盘与内存同步
	}
}

//删除目录
void rmdir(int pos)
{
	if(curdir[pos].isdir)	//删除目录项为目录
	{
		recycle(curblock, pos);	//回收目录
		disk.seekg((curblock + DATABEG) * BLOCKSIZE, ios::beg);
		disk.read((char*)curdir, sizeof(curdir));	//磁盘内存同步
	}
	else	//目录项不为目录，报错
		cout << curdir[pos].name << "is not a directory." << endl;
}

//获取参数
bool getpara(int num)
{
	int pos = c.cmd.find(' ');
	return true;
}

//分析字符串形式路径，返回路径指向的目录项的盘块和位置
bool analysispath(string path,int *block,int *pos)
{
	string filename;
	int i;
	int len = path.length();
	*pos = 0;		//所指路径指向文件时才置pos为非0值
	if(path[0] == '/')	//绝对路径
	{
		*block = 0;	//根目录（0号盘块）
		for(i = 1; i < path.length(); i++)
			filename.push_back(path[i]);	//“/”后面的东西给filename
		if(path.length() == 1)//是根目录
			return true;
		else	//绝对路径
			if(path[1] != '/' && analysispath(&path[1], block, pos))	//第一个&&为了防止cd //
				return true;
		return false;
	}
	else	//相对路径
	{
		filename = "";
		i = path.find('/');
//		for(i=0;i<len&&path[i]!='/';i++);	//获取所要寻找的本级目录的目录项名及其长度
		if(i == -1 || path == ".." || path == ".")
			filename = path;
		else
			for(int j = 0; j < i; j++)
				filename.push_back(path[j]);
//		for(i; i < path.length(); i++)
//			filename.push_back(path[i]);
//		strncpy(filename,path,i);
		*pos = find(filename, *block);	//在目录盘块中找到目录项
		if(*pos == -1)//找不到文件
			return false;
	}
	if(i == -1 || path == ".." || path == ".")	//路径分析完毕
		return true;
	else	//路径未分析完
	{
		if(!temp[*pos].isdir)	//此时找到的目录项是文件，报错
		{
			cout << "File:" << filename << " is not a directory!" << endl;
			return false;
		}
		if(path[i + 1] == '/')	//路径中重复了目录项分隔符'/'
		{
			cout << "The path is illegal." << endl;
			return false;
		}
		filename = "";
		*block = temp[*pos].beginblock;	//从下级目录开始分析路径
		for(i = i + 1; i < path.length(); i++)
			filename.push_back(path[i]);
		if(analysispath(filename, block, pos))	//递归分析后续路径
			return true;
		else
			return false;
	}
}

//获取当前路径
void getcurpath()
{
	globalpath = "/";
//	strcpy(curpath, "/");	//根目录
//	curpath[1] = '\0';
	if(curblock == 0)	//当前为根目录
		return;
//	char path[30][10];
	string path[10];
	int i, j, block;
	memcpy(temp, curdir, sizeof(temp));
	for(i = 0; temp[0].beginblock != 0; i++)	//获取当前路径中各目录项的目录名
	{
		block = temp[0].beginblock;
		disk.seekg((temp[1].beginblock + DATABEG) * BLOCKSIZE, ios::beg);
		disk.read((char*)temp, sizeof(temp));
		for(j = 2; j < temp[0].filesize + 2; j++)
			if(block == temp[j].beginblock)		//找到目录名复制到暂存的路径数组中
				path[i] = temp[j].name;
	}
	for(j = i; j > 0; j--)	//将路径数组中的目录名组织成当前路径
	{
		globalpath += path[j - 1];
		globalpath += "/";
	}
}

//重命名文件
void rename(string oldname, string newname)
{
	int pos = find(newname, curblock);
	if(pos != -1)
	{
		cout << "Having same name in the dir." << endl;
		return;
	}
	pos = find(oldname, curblock);//找到文件
	if(pos == -1)
		return;
	if(analysisname(newname, curdir[pos].name, curdir[pos].type))	//同步到磁盘并重新读取
	{
		disk.seekp((curblock + DATABEG) * BLOCKSIZE, ios::beg);
		disk.write((char*)curdir, sizeof(curdir));
		disk.seekg((curblock + DATABEG) * BLOCKSIZE, ios::beg);
		disk.read((char*)curdir, sizeof(curdir));
	}
	else
		cout << "Failed to rename the file:" << oldname << endl;
}

//变换路径
void changedir(string path)	//改变当前目录，更新当前路径
{
	int block, pos = 0;
	block = curblock;
	if(analysispath(path, &block, &pos))	//路径存在
	{
		disk.seekg((block + DATABEG) * BLOCKSIZE, ios::beg);
		disk.read((char*)temp, sizeof(temp));
		if(temp[pos].isdir)	//路径所指为目录,不能为文件
		{	
			curblock = temp[pos].beginblock;	//重置当前目录相关的全局变量
			disk.seekg((curblock + DATABEG) * BLOCKSIZE, ios::beg);
			disk.read((char*)curdir, sizeof(curdir));
//			memcpy(curdir, temp, sizeof(temp));
			getcurpath();	//获取当前路径
			return;
		}
	}
	cout<<"Path:"<<path<<" is not exist or not a directory!"<<endl;
}

//复制文件
void copyfile(string src,string den)
{
	int srcblock, srcpos = 0;
	int denblock, denpos = 0;
	srcblock = curblock;
	denblock = curblock;
	directory srcdir;
	if(analysispath(src, &srcblock, &srcpos))	//源文件存在
	{
		disk.seekg((srcblock + DATABEG) * BLOCKSIZE, ios::beg);
		disk.read((char*)temp, sizeof(temp));
		if(temp[srcpos].isdir)	//只能复制文件
		{
			cout << "Cannot copy directory." << endl;
			return;
		}
		disk.seekg((srcblock + DATABEG) * BLOCKSIZE, ios::beg);
		disk.read((char*)temp, sizeof(temp));
		memcpy(&srcdir, &temp[srcpos], sizeof(directory));	//暂存找到的文件目录项
		if(analysispath(den, &denblock, &denpos))	//目的路径存在
		{
			disk.seekg((denblock + DATABEG) * BLOCKSIZE, ios::beg);
			disk.read((char*)temp, sizeof(temp));
			if(!temp[denpos].isdir)	//目的路径必须指向目录
			{
				cout << "The destinate path shouldnot be a file." << endl;
				return;
			}
			srcblock = curblock;
			disk.seekg((temp[denpos].beginblock + DATABEG) * BLOCKSIZE, ios::beg);
			curblock = temp[denpos].beginblock;
			memcpy(temp, curdir, sizeof(curdir));	//保存当前目录以备还原
			disk.read((char*)curdir, sizeof(curdir));
			for(int i = 2; i < curdir[0].filesize + 2; i++)	//目的路径下有重名文件
			{
				if((srcdir.name == curdir[i].name) && (srcdir.type == curdir[i].type))
				{
					cout << "The file is existing in the destinate directory." << endl;
					return;
				}
			}
			create_file(srcdir.name + "." + srcdir.type, srcdir.filesize, srcdir.inside);	//创建文件
			curblock = srcblock;	//还原当前目录
//			cout << "copy succeed!!!" << endl;
			memcpy(curdir, temp, sizeof(curdir));
			return;
		}
		else	//目的路径不存在
		{
			cout << "Destination path:" << den << " is not exist!" << endl;
			return;
		}
	}
	else	//源文件不存在
		cout << "Source path:" << src << " is not exist!" << endl;
}

//-----------------前置内容-----------------------
//-----------------开始命令-----------------------

//显示指定目录下内容
void dir()
{
	disk.seekg((curblock + DATABEG) * BLOCKSIZE, ios::beg);
	disk.read(( char*)temp, sizeof(temp));//获取指定盘块下的目录
	for(int i=0; i < (temp[0].filesize+2); i++)
	{
		struct tm * time;
		time = localtime(&temp[i].buildtime);
		cout << time ->tm_year + 1900 << "-" << time ->tm_mon << "-" << time ->tm_mday << "  ";
		cout << time ->tm_hour << ":" << time ->tm_min;
		cout << "\t    ";
		if(temp[i].isdir == 1)
			cout << "<DIR>       ";
		else
		{
			cout.setf(ios::right);
			cout << setw(12) << setfill(' ') << temp[i].filesize;
		}
		cout << "\t" << temp[i].name;
		if(temp[i].isdir == false)
			cout << "." << temp[i].type;
		cout << endl;	
	}
	cout.unsetf(ios::left);
}

//创建文件
void mkfile()
{
	if(find(c.address, curblock) != -1)
	{
		cout << "File exist!" << endl;
		return;
	}
	int size;
	string inside;
	cout << "Input size: ";
	cin >> size;
	cout << "Input content:";
	cin.ignore(1000,'\n');
	getline(cin, inside);
	create_file(c.address, size, inside); 
}

//转换目录位置
void cd()
{
	changedir(c.address);
}

//删除文件 del[filename]
void del()
{
	if(find(c.address, curblock))
		delfile(find(c.address, curblock));
}

//新建文件夹
void md()
{
	createdir(c.address);
}

//显示文件/文件夹信息
void more()
{
	show_more(c.address, curblock);
}

//删除文件夹
void rd()
{
	if(find(c.address, curblock))
		rmdir(find(c.address, curblock));
}

//帮助
void help()
{
	cout << "cd[PATH/DIRECTORY]             turn to the directory" << endl;
	cout << "dir                            show the files and diretory" << endl;
	cout << "time                           show the system time" << endl;
	cout << "ver                            show the files and version" << endl;
	cout << "md[DIRECTORY]                  make a new direcroty under current direcroty" << endl;
	cout << "mkfile[FILENAME]               make a new file under current direcroty" << endl;
	cout << "more[FILENAME/DIRECTORY]       show the detail of file or directory" << endl;
	cout << "rd[DIRECTORY]                  delete the directory under current diretory" << endl;
	cout << "del[FILENAME]                  show the files and diretory" << endl;
	cout << "rename[FILENAME][FILENAMEB]    rename the file with FILNAMEB" << endl;
	cout << "copy[FILENAME][PATH]           copy the file from current directory to another" << endl;
	cout << "move[FILENAME][PATH]           move the file from current directory to another" << endl;
	cout << "import[FILENAME][PATH]         copy the file from current directory to virtual disk" << endl;
	cout << "export[FILENAME][PATH]         copy the file from virtual disk to current directory" << endl;
	cout << "xcopy[DIRECTORY][PATH]         copy the directory to target path" << endl;
}

//调出系统时间
void time()
{
	time_t t;
    struct tm * tm_now;
    time(&t);
    tm_now = localtime(&t);
    cout << "current time: " << tm_now->tm_hour << ":" << tm_now->tm_min << ":" << tm_now->tm_sec << endl;
}

//显示版本信息
void ver()
{
	cout << "Microsoft Windows [版本 10.0.17134.81]" << endl;
}

//重命名
void rename()
{
	int pos = c.address.find(' ');
	string a, b;
	for(int i = 0; i < pos; i++)
		a.push_back(c.address[i]);
	for(int i = pos + 1; i < c.address.length(); i++)
		b.push_back(c.address[i]);
	rename(a, b);
}

//复制文件
void copy()
{
	int pos = c.address.find(' ');
	string a, b;
	for(int i = 0; i < pos; i++)
		a.push_back(c.address[i]);
	for(int i = pos + 1; i < c.address.length(); i++)
		b.push_back(c.address[i]);
	copyfile(a, b);
}

//移动文件
void move()
{
	copy();
	int pos = c.address.find(' ');
	string a;
	for(int i = 0; i < pos; i++)
		a.push_back(c.address[i]);
	if(find(a, curblock))
		delfile(find(a, curblock));
}

//import	从c盘复制到虚拟盘
void import()
{
	int pos = c.address.find(' ');
	string a, b;
	for(int i = 0; i < pos; i++)
		a.push_back(c.address[i]);
	for(int i = pos + 1; i < c.address.length(); i++)
		b.push_back(c.address[i]);
	string str = "";
	string t;
	ifstream syst(a);
	while(!syst.eof())
	{
		getline(syst, t);
		str += t;
		str += '\n';
	}
	string str1;
	for(int i = 0; i < str.length() - 1; i++)
		str1.push_back(str[i]);
	int block = curblock;
	changedir(b);
	create_file(a, 1, str1);
	curblock = block;
	getcurpath();
}

//export	从虚拟盘复制到c盘
void file_export()
{
	int pos = c.address.find(' ');
	string a, b, temp_filename, temp_path;
	for(int i = 0; i < pos; i++)
		a.push_back(c.address[i]);
	for(int i = pos + 1; i < c.address.length(); i++)
		b.push_back(c.address[i]);
	int t = -1;
	for(int i = 0; i < a.size(); i++)
		if(a[i] == '/')
			t = i;
	if(t == -1)	//当前目录底下的文件
	{
		temp_filename = a;
		int temp_pos = find(temp_filename, curblock);
		disk.seekg((curblock + DATABEG) * BLOCKSIZE,ios::beg);
		disk.read((char*)temp, sizeof(temp));
		b += temp_filename;
		ofstream syst(b);
		cout << temp[temp_pos].inside << endl;
		syst << temp[temp_pos].inside;
	}
	else
	{
		for(int i = 0; i < t; i++)
			temp_path.push_back(a[i]);
		for(int i = t + 1; i < a.size(); i++)
			temp_filename.push_back(a[i]);
		int temp_block = curblock;
		changedir(temp_path);
		int temp_pos = find(temp_filename, curblock);
		disk.seekg((curblock + DATABEG) * BLOCKSIZE,ios::beg);
		disk.read((char*)temp, sizeof(temp));
		b += temp_filename;
		ofstream syst(b);
		syst << temp[temp_pos].inside;
		curblock = temp_block;
		getcurpath();
	}
}

//复制文件夹
void xcopy()
{
	int pos;
	pos = c.address.find(' ');
	string a, b;
	for(int i = 0; i < pos; i++)
		a.push_back(c.address[i]);
	for(int i = pos + 1; i < c.address.length(); i++)
		b.push_back(c.address[i]);
	int temp_pos;
	if(a[0] == '/')	//绝对路径
	{
		int t;
		string source_path, source_dir;
		for(int i = 0; i < a.size(); i++)
			if(a[i] == '/')
				t = i;
		if(t == 0)
			source_path.push_back(a[0]);
		else
			for(int i = 0; i < t; i++)
				source_path.push_back(a[i]);
		int temp_block = curblock;
		changedir(source_path);
		for(int i = t + 1; i < a.length(); i++)
			source_dir.push_back(a[i]);
		directory source_temp;
		source_temp = curdir[find(source_dir, curblock)];
		source_temp.name = source_dir;
		curblock = temp_block;
		getcurpath();
		temp_block = curblock;
		changedir(b);
		curdir[curdir[0].filesize++ +  2] = source_temp;
		disk.seekp((curblock + DATABEG) * BLOCKSIZE,ios::beg);
		disk.write((char*)curdir, sizeof(curdir));
		curblock = temp_block;
		getcurpath();
	}
	else
	{
		directory source_temp;
		source_temp = curdir[find(a, curblock)];
		source_temp.name = a;
		int temp_block = curblock;
		changedir(b);
		curdir[curdir[0].filesize++ +  2] = source_temp;
		disk.seekp((curblock + DATABEG) * BLOCKSIZE,ios::beg);
		disk.write((char*)curdir, sizeof(curdir));
		curblock = temp_block;
		getcurpath();
	}
}

//退出系统
void exit()
{
	exit(0);
}

int main()
{
	int i;
	init_fs();	//初始化硬盘信息
	while(1)
	{
		i = 0;
		c.command.clear();
		c.address.clear();
		cout << "SDisk:" << globalpath << ">";
		getline(cin, c.cmd);
		if(c.cmd.length() == 0)
			continue;	//没输入指令，继续输入
		int pos = c.cmd.find(' ');	//通过空格分隔命令和地址
		if(pos != -1)
		{
			for(i = 0; i < pos; i++)
				c.command.push_back(c.cmd[i]);
			for(pos = pos + 1; pos < c.cmd.size(); pos++)
				c.address.push_back(c.cmd[pos]);
		}
		else
			for(i = 0; i < c.cmd.size(); i++)
				c.command.push_back(c.cmd[i]);
//		cout << c.command << " " << c.address << endl;
		if(c.command == "exit")
			exit();
		else if(c.command == "cd")
			cd();
		else if(c.command == "help")
			help();
		else if(c.command == "dir")
			dir();
		else if(c.command == "time")
			time();
		else if(c.command == "ver")
			ver();
		else if(c.command == "md")
			md();
		else if(c.command == "mkfile")
			mkfile();
		else if(c.command == "more")
			more();
		else if(c.command == "rd")
			rd();
		else if(c.command == "del")
			del();
		else if(c.command == "rename")
			rename();
		else if(c.command == "copy")
			copy();
		else if(c.command == "move")
			move();
		else if(c.command == "import")
			import();
		else if(c.command == "export")
			file_export();
		else if(c.command == "xcopy")
			xcopy();
		else
			cout << "Wrong Instruction!" << endl;
	}
	return 0;
}

//簇是多个连续的块组成的，这里定义一个盘块为一簇