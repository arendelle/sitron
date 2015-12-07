/*
 * Arendelle.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: Sina
 */

#include "Arendelle.h"

Arendelle::Arendelle(){
	this->screen = new Screen(30,10);
	this->renderEngine = new RenderEngine(this->screen);
	this->initSources();
}

Arendelle::~Arendelle(){

}

Screen* Arendelle::getScreen(){
	return this->screen;
}

void Arendelle::setScreen(Screen* screen){
	this->screen = screen;
}

void Arendelle::render()
{
	this->renderEngine->render();
}

int isFuncHLine(string str)
{
	if(str.find('<') != string::npos)
		if(str.find('<') != string::npos)
			return 1;
	for(int i=0; i<str.size(); i++)
	{
		if(str[i]!=' ')
			if(str[i] != '\t')
				if(str[i] != '\n')
					return -1;
	}
	return 0;
}


void Arendelle::initFunctions()
{
	vector<boost::filesystem::path> files;
	files = findFunctionFiles(workingDir);
	for(long long i=0 ; i < files.size(); i++)
	{
		string name = files[i].string();
		long long pos = name.find(workingDir) + workingDir.size();
		name = name.substr(pos, name.size()-pos);
		for(long long c = 0; c<name.size(); c++)
		{
			if(name[c] == '/')
				name[c] = '.';
			else if(name[c] == '.')
			{
				name = name.substr(0,c);
				break;
			}
		}
		ifstream myfile (files[i].string());
		string line;
		while(getline(myfile,line))
		{
			int funcHSituation = isFuncHLine(line);
			if(funcHSituation == 1)
			{
				string header = line;
				cout<<"Interpreting Function File: "<<files[i].string()<<endl;
				string codes = "";
				while(getline(myfile,line))
					codes = codes + line;
				Function* func = new Function(name, header, codes);
				functions[name] = func;
			}
			if(funcHSituation == -1)
			{
				break;
			}
		}
	}
}


void Arendelle::addOrUpdateSpace(string name, long long value)
{
	this->spaces[name] = value;
}

bool Arendelle::functionExist(string name)
{
	functionSearch = functions.find(name);
	if(functionSearch != functions.end())
	{
	        return true;
	}
	else
	{
	        return false;
	}
}

Function* Arendelle::getLastFunctionSearch()
{
	return functionSearch->second;
}



bool Arendelle::spaceExist(string name)
{
	spaceSearch = spaces.find(name);
	if(spaceSearch != spaces.end())
	{
	        return true;
	}
	else
	{
	        return false;
	}
}

long long Arendelle::getLastSpaceSearch()
{
	return spaceSearch->second;
}


void Arendelle::addOrUpdateStoredSpace(string name, long long value)
{
	this->storedSpaces[name] = value;
	long long pos = 0;
	string folders="";
	for(long long i = 0; i<name.size(); i++)
	{
		if(name[i] == '.')
		{
			folders = folders + name.substr(pos,i-pos) + "/";
			pos = i+1;
			name[i] = '/';
		}
	}
	cout<<"Space Storage: "<<workingDir+folders<<endl;
	if(folders != "")
	{
		boost::filesystem::create_directories(workingDir+folders);
	}
	string filename = this->workingDir + name + ".space";
	ofstream sFile (filename);
	sFile << value;
	sFile.close();
}


bool Arendelle::storedSpaceExist(string name)
{
	storedSpaceSearch = storedSpaces.find(name);
	if(storedSpaceSearch != storedSpaces.end())
	{
	        return true;
	}
	else
	{
	        return false;
	}
}


long long Arendelle::getLastStoredSpaceSearch()
{
	return storedSpaceSearch->second;
}


void Arendelle::initSources()
{
	sources.insert(std::make_pair("i",&screen->getCursor()->screen_width));
	sources.insert(std::make_pair("width",&screen->getCursor()->screen_width));
	sources.insert(std::make_pair("j",&screen->getCursor()->screen_height));
	sources.insert(std::make_pair("height",&screen->getCursor()->screen_height));
	sources.insert(std::make_pair("n",&screen->getCursor()->current_color));
	sources.insert(std::make_pair("x",&screen->getCursor()->j));
	sources.insert(std::make_pair("y",&screen->getCursor()->i));
	//sources.insert(std::make_pair(,));
}


bool Arendelle::sourceExist(string name)
{
	sourceSearch = sources.find(name);
	if(sourceSearch != sources.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Arendelle::isExtendedSource(string name)
{
	if(name == "rnd")
		return true;
	if(name == "pi")
		return true;
	return false;
}

long long Arendelle::getLastSourceSearch()
{
	return *sourceSearch->second;
}

void Arendelle::setWorkingDir(string mainDir)
{
	long long pos=0;
	for(pos = mainDir.size()-1; pos >= 0; pos--)
	{
		if(mainDir[pos] == '/')
		{
			pos++;
			break;
		}
	}
	this->workingDir = mainDir.substr(0,pos);
	cout<<"Setting Working Directory : "<<this->workingDir<<endl;
}

string Arendelle::getWorkingDir()
{
	return this->workingDir;
}

void Arendelle::initStoredSpaces()
{
	vector<boost::filesystem::path> files;
	files = findStoredSpaceFiles(workingDir);
	for(long long i=0 ; i < files.size(); i++)
	{
		string name = files[i].string();
		long long pos = name.find(workingDir) + workingDir.size();
		name = name.substr(pos, name.size()-pos);
		for(long long c = 0; c<name.size(); c++)
		{
			if(name[c] == '/')
				name[c] = '.';
			else if(name[c] == '.')
			{
				name = name.substr(0,c);
				break;
			}
		}
		ifstream file(files[i].string());
		long long value;
		file >> value;
		cout << "Init St Space : "<<value << " -> "<<name<<endl;
		storedSpaces[name] = value;
		file.close();
	}
}

vector<boost::filesystem::path> Arendelle::findFunctionFiles(string cDir)
{
	vector<boost::filesystem::path> files;
	boost::filesystem::path cPath(cDir);
	boost::filesystem::directory_iterator end_itr;
	for(boost::filesystem::directory_iterator itr(cPath); itr != end_itr; ++itr)
	{
		if(boost::filesystem::is_regular_file(itr->path()))
		{
			if(itr->path().filename().string().find(".arendelle") != string::npos)
			{
				files.push_back(itr->path());
			}
		}
		else if(boost::filesystem::is_directory(itr->path()))
		{
			vector<boost::filesystem::path> newFiles = findStoredSpaceFiles(itr->path().string());
			files.insert(files.end(), newFiles.begin(), newFiles.end() );
		}
	}
	return files;
}


vector<boost::filesystem::path> Arendelle::findStoredSpaceFiles(string cDir)
{
	vector<boost::filesystem::path> files;
	boost::filesystem::path cPath(cDir);
	boost::filesystem::directory_iterator end_itr;
	for(boost::filesystem::directory_iterator itr(cPath); itr != end_itr; ++itr)
	{
		if(boost::filesystem::is_regular_file(itr->path()))
		{
			if(itr->path().filename().string().find(".space") != string::npos)
			{
				files.push_back(itr->path());
			}
		}
		else if(boost::filesystem::is_directory(itr->path()))
		{
			vector<boost::filesystem::path> newFiles = findStoredSpaceFiles(itr->path().string());
			files.insert(files.end(), newFiles.begin(), newFiles.end() );
		}
	}
	return files;
}
