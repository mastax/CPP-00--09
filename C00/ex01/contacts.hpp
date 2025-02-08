#ifndef CONTACTS_HPP
#define CONTACTS_HPP

#include <iostream>
#include <string>

class contacts {
	private :
		std::string Finame;
		std::string Sename;
		std::string Niname;
		std::string Phnumber;
		std::string Dasecret;
	public :
		contacts();
		std::string getterFname();
		std::string getterSname();
		std::string getterNname();
		std::string getterPnumber();
		std::string getterDsecret();

		void setterFname(std::string Fame);
		void setterSname(std::string Same);
		void setterNname(std::string Name);
		void setterPnumber(std::string phone);
		void setterDsecret(std::string secret);
	~contacts();
};

#endif