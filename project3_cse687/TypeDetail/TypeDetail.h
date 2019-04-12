#pragma once




#include<iostream>
#include<string>
#include<unordered_map>
namespace TypeDetail {
	struct Typedata
	{
		std::string type_name;
		std::string type_;
		int startline_;
		int endline_;
	};
	class TypeInfo
	{
	public:
		TypeInfo();
		~TypeInfo();
		void AddInfo(const std::string& filename,Typedata * const);
		std::vector<Typedata*> GetInfo(const std::string& filename);
		TypeInfo* GetInfo();
		
	private:
		std::unordered_map<std::string, std::vector<Typedata*>> Info_;
	};
	class Dependencies
	{
	public:
		Dependencies();
		~Dependencies();
		std::vector<std::string>getdependencies(const std::string& filename);
		void adddependency(const std::string& filename,const std::string& dependency);
		bool haskey(const std::string& filename);
	private:
		std::unordered_map<std::string, std::vector<std::string>> depend_;
	};

	
}