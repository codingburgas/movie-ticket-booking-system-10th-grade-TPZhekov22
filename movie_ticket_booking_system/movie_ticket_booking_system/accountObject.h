#pragma once
#include <string>
#include <optional>

class Account
{
	std::string m_username;
	std::string m_password;
	bool m_isAdmin = true; //CHANGE LATER TO FALSE

public:
	Account(const std::string& accountUsername, const std::string& accountPassword);

	const std::string& getUsername() const;
	const std::string& getPassword() const;
	const bool& getIsAdmin() const;

	// Serialization methods for saving and loading movie objects
	bool saveToFile(std::ostream& os) const;
	static std::optional<Account> loadFromFile(std::istream& is);
};