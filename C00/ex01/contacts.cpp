#include "contacts.hpp"


contacts::contacts() {

}
contacts::~contacts() {
	
}

void contacts::setterFname(std::string FirstName) {
	Finame = FirstName;
}
void contacts::setterSname(std::string SecondName) {
	Sename = SecondName;
}
void contacts::setterNname(std::string NickName) {
	Niname = NickName;
}
void contacts::setterPnumber(std::string NumberPhone) {
	Phnumber = NumberPhone;
}
void contacts::setterDsecret(std::string DarkSecret) {
	Dasecret = DarkSecret;
}
std::string contacts::getterFname() {
	return (Finame);
}
std::string contacts::getterSname() {
	return (Sename);
}
std::string contacts::getterNname() {
	return (Niname);
}
std::string contacts::getterPnumber() {
	return (Phnumber);
}
std::string contacts::getterDsecret() {
	return (Dasecret);
}