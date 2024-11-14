#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "WinINet.lib")
#include <Windows.h>
#include <filesystem>
#include <stdio.h>
#include <urlmon.h>
#include <WinINet.h>
#include "sha256.h"

void RunBeforeAutorun(const std::string& buff);
void ClearBeforeAutorunScript();

bool dirExists(const char* dire)
{
	std::experimental::filesystem::path dir(dire);

	if (!(std::experimental::filesystem::exists(dire))) {
		return false;
	}
	else
	{
		return true;
	}
}

bool createDir(const char* dire)
{
	std::experimental::filesystem::path dir(dire);

	if (!(std::experimental::filesystem::exists(dire))) {

		if (std::experimental::filesystem::create_directory(dire))
			return true;
		else
			return false;
	}
	else
	{
		return true;
	}
}
bool createDirs(const char* dire)
{
	std::experimental::filesystem::path dir(dire);

	if (!(std::experimental::filesystem::exists(dire))) {

		if (std::experimental::filesystem::create_directories(dire))
		{
			return true;
		}
			//return true;
	}
	else
	{
		return true;
	}
}
bool fileExists(const char* dire)
{
	std::ifstream t(dire);
	if (t.good())
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::string openFile(const char* dire)
{
	std::ifstream t(dire);
	if (t.good())
	{
		std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
		return str;
	}
	else
	{
		return "NO_FILE";
	}
}
bool createFile(const char* fil, std::string& content, bool stolen = false, std::string ip = std::string("NULL"), std::string name = std::string("NULL"))
{
	if (!stolen)
	{
		std::ofstream file;
		file.open(fil);
		file << content;
		file.close();
	}
	else
	{
		std::ofstream file;
		file.open(fil);
		file << "--[[ \n";
		//file << "Server Name: \t " + name + "\n";
		file << "Server IP: \t " + std::string(engine()->GetNetChannelInfo()->GetAddress()) + "\n";
		file << "File: \t " + std::string(fil) + "\n";
		file << "\nStolen using Appel \n \n";
		file << "]]-- \n";
		file << content;
		file.close();
		if (HackVars::Script::Steal_Lua_Log)
			printInfo(std::string("Stolen " + std::string(fil) + " \n").c_str());
	}
	return true;
}
bool deleteFile(const char* fil)
{
	if (remove(fil) != 0)
		return false;
	else
		return true;
}
bool createDirsFile(const char* fil, std::string& content)
{
	char drive[MAX_PATH];
	char dir[MAX_PATH];
	char fname[MAX_PATH];
	char ext[MAX_PATH];
	_splitpath(fil, drive, dir, fname, ext);
	std::string path = std::string(drive) + std::string(dir);
	std::string fila = path + std::string(fname) + std::string(ext);
	if (createDirs(path.c_str()))
	{
		if (createFile(fila.c_str(), content))
		{
			return true;
		}
	}
	else
		return false;
}
bool stealLua(const char* fil, std::string content)
{
	char drive[MAX_PATH];
	char dir[MAX_PATH];
	char fname[MAX_PATH];
	char ext[MAX_PATH];

	_splitpath(fil, drive, dir, fname, ext);
	std::string dira = dir;
	dira.erase(std::remove(dira.begin(), dira.end(), '@'), dira.end());
	std::replace(dira.begin(), dira.end(), '.', '-');
	boost::replace_all(dira, "/nul/", "/nula/");
	std::string exten;
	std::string finame;

	if (std::string(ext) == "")
		exten = ".lua";
	else
		exten = std::string(ext);

	if (std::string(fname) == "")
		finame = "Other";
	else
		finame = std::string(fname);

	std::string path = std::string(drive) + dira;
	std::string fila = path + finame + exten;
	if (createDirs(path.c_str()))
	{
		if (createFile(fila.c_str(), content, true))
			return true;
	}
	else
		return false;
}

void SaveSettings()
{
	std::ofstream file;
	file.open("C:/Appel/settings.ini");
	file << "[PlayerESP]\n";
	file << "box_r = "+ std::to_string(HackVars::Visuals::ESP::fPBoxColor[0]) +"\n";
	file << "box_g = " + std::to_string(HackVars::Visuals::ESP::fPBoxColor[1]) + "\n";
	file << "box_b = " + std::to_string(HackVars::Visuals::ESP::fPBoxColor[2]) + "\n";
	file << "box_a = " + std::to_string(HackVars::Visuals::ESP::fPBoxColor[3]) + "\n";
	file << "hbox_r = " + std::to_string(HackVars::Visuals::ESP::fPHBoxColor[0]) + "\n";
	file << "hbox_g = " + std::to_string(HackVars::Visuals::ESP::fPHBoxColor[1]) + "\n";
	file << "hbox_b = " + std::to_string(HackVars::Visuals::ESP::fPHBoxColor[2]) + "\n";
	file << "hbox_a = " + std::to_string(HackVars::Visuals::ESP::fPHBoxColor[3]) + "\n";
	file << "chams_r = " + std::to_string(HackVars::Visuals::ESP::fVPlayerChamsColor[0]) + "\n";
	file << "chams_g = " + std::to_string(HackVars::Visuals::ESP::fVPlayerChamsColor[1]) + "\n";
	file << "chams_b = " + std::to_string(HackVars::Visuals::ESP::fVPlayerChamsColor[2]) + "\n";
	file << "\n";
	file << "[LuaESP]\n";
	file << "box_r = " + std::to_string(HackVars::Visuals::ESP::fLBoxColor[0]) + "\n";
	file << "box_g = " + std::to_string(HackVars::Visuals::ESP::fLBoxColor[1]) + "\n";
	file << "box_b = " + std::to_string(HackVars::Visuals::ESP::fLBoxColor[2]) + "\n";
	file << "box_a = " + std::to_string(HackVars::Visuals::ESP::fLBoxColor[3]) + "\n";
	file << "chams_r = " + std::to_string(HackVars::Visuals::ESP::fVLuaChamsColor[0]) + "\n";
	file << "chams_g = " + std::to_string(HackVars::Visuals::ESP::fVLuaChamsColor[1]) + "\n";
	file << "chams_b = " + std::to_string(HackVars::Visuals::ESP::fVLuaChamsColor[2]) + "\n";
	file << "\n";
	file << "[WeaponESP]\n";
	file << "chams_r = " + std::to_string(HackVars::Visuals::ESP::fVWeapChamsColor[0]) + "\n";
	file << "chams_g = " + std::to_string(HackVars::Visuals::ESP::fVWeapChamsColor[1]) + "\n";
	file << "chams_b = " + std::to_string(HackVars::Visuals::ESP::fVWeapChamsColor[2]) + "\n";
	file << "\n";
	file << "[HotKeys]\n";
	if (HackVars::Visuals::HEFreeCam && HackVars::Visuals::HFreeCam != NULL)
		file << "freecam = " + std::to_string(HackVars::Visuals::HFreeCam) + "\n";
	else
		file << "freecam = 0\n";
	if (HackVars::Aimbot::HEAimbot && HackVars::Aimbot::HAimbot != NULL)
		file << "aimbot = " + std::to_string(HackVars::Aimbot::HAimbot) + "\n";
	else
		file << "aimbot = 0\n";
	if (HackVars::Script::HPropBoost != NULL)
		file << "propboost = " + std::to_string(HackVars::Script::HPropBoost) + "\n";
	else
		file << "propboost = 0\n";
	file << "\n";
	file << "[Toggles]\n";
	if (HackVars::Script::PropBoost)
		file << "phystricks = true\n";
	else
		file << "phystricks = false\n";
	file << "phystricksmode = " + std::to_string(HackVars::Script::MPropBoost) + "\n";
	file << "\n";
	file.close();
}
void LoadSettings()
{
	//std::ofstream file;
	//file.open("garrysmod/cl");
	//file << "000";
	//file.close();
	if (!fileExists("C:/Appel/settings.ini"))
		return;

	INIReader reader("C:/Appel/settings.ini");

	if (reader.ParseError() != 0) {
		printError("Error loading settings file!");
		return;
	}
	
	//PlayerESP
	HackVars::Visuals::ESP::fPBoxColor[0] = reader.GetReal("PlayerESP", "box_r", 0);
	HackVars::Visuals::ESP::fPBoxColor[1] = reader.GetReal("PlayerESP", "box_g", 0);
	HackVars::Visuals::ESP::fPBoxColor[2] = reader.GetReal("PlayerESP", "box_b", 0);
	HackVars::Visuals::ESP::fPBoxColor[3] = reader.GetReal("PlayerESP", "box_a", 0);

	HackVars::Visuals::ESP::fPHBoxColor[0] = reader.GetReal("PlayerESP", "hbox_r", 0);
	HackVars::Visuals::ESP::fPHBoxColor[1] = reader.GetReal("PlayerESP", "hbox_g", 0);
	HackVars::Visuals::ESP::fPHBoxColor[2] = reader.GetReal("PlayerESP", "hbox_b", 0);
	HackVars::Visuals::ESP::fPHBoxColor[3] = reader.GetReal("PlayerESP", "hbox_a", 0);

	HackVars::Visuals::ESP::fVPlayerChamsColor[0] = reader.GetReal("PlayerESP", "chams_r", 0);
	HackVars::Visuals::ESP::fVPlayerChamsColor[1] = reader.GetReal("PlayerESP", "chams_g", 0);
	HackVars::Visuals::ESP::fVPlayerChamsColor[2] = reader.GetReal("PlayerESP", "chams_b", 0);

	//LuaESP
	HackVars::Visuals::ESP::fLBoxColor[0] = reader.GetReal("LuaESP", "box_r", 0);
	HackVars::Visuals::ESP::fLBoxColor[1] = reader.GetReal("LuaESP", "box_g", 0);
	HackVars::Visuals::ESP::fLBoxColor[2] = reader.GetReal("LuaESP", "box_b", 0);
	HackVars::Visuals::ESP::fLBoxColor[3] = reader.GetReal("LuaESP", "box_a", 0);

	HackVars::Visuals::ESP::fVLuaChamsColor[0] = reader.GetReal("LuaESP", "chams_r", 0);
	HackVars::Visuals::ESP::fVLuaChamsColor[1] = reader.GetReal("LuaESP", "chams_g", 0);
	HackVars::Visuals::ESP::fVLuaChamsColor[2] = reader.GetReal("LuaESP", "chams_b", 0);

	//WeaponESP
	HackVars::Visuals::ESP::fVWeapChamsColor[0] = reader.GetReal("WeaponESP", "chams_r", 0);
	HackVars::Visuals::ESP::fVWeapChamsColor[1] = reader.GetReal("WeaponESP", "chams_g", 0);
	HackVars::Visuals::ESP::fVWeapChamsColor[2] = reader.GetReal("WeaponESP", "chams_b", 0);

	//HotKeys
	int freecam = reader.GetReal("HotKeys", "freecam", 0);
	if (freecam != 0)
	{
		HackVars::Visuals::HEFreeCam = true;
		HackVars::Visuals::HFreeCam = freecam;
	}
	int aimbot = reader.GetReal("HotKeys", "aimbot", 0);
	if (freecam != 0)
	{
		HackVars::Aimbot::HEAimbot = true;
		HackVars::Aimbot::HAimbot = aimbot;
	}
	int propboost = reader.GetReal("HotKeys", "phystricks", 0);
	if (propboost != 0)
	{
		HackVars::Script::HPropBoost = propboost;
	}
	HackVars::Script::PropBoost = reader.GetBoolean("Toggles", "phystricks", false);
	HackVars::Script::MPropBoost = reader.GetReal("Toggles", "phystricksmode", 0);
}
void ResetSettings()
{
	if (fileExists("C:/Appel/settings.ini"))
	{
		deleteFile("C:/Appel/settings.ini");
	}
}