#include "accountObject.h"
#include "../system_static_library/namespaceUtility.h"

Account::Account() : m_username("guest"), m_password("guest")
{
	m_isAdmin = false;
}

Account::Account(const std::string& username, const std::string& password) : m_username(username), m_password(password)
{
}

const std::string& Account::getUsername() const
{
	return m_username;
}

const std::string& Account::getPassword() const
{
	return m_password;
}

const bool& Account::getIsAdmin() const
{
	return m_isAdmin;
}

void Account::setAdmin(bool adminStatus)
{
	this->m_isAdmin = adminStatus;
}

bool Account::saveToFile(std::ostream& os) const
{
	if (!utility::writeString(os, getUsername())) return false;
	if (!utility::writeString(os, getPassword())) return false;
	bool admin = m_isAdmin;
	os.write(reinterpret_cast<const char*>(&admin), sizeof(admin));
	return os.good();
}

std::optional<Account> Account::loadFromFile(std::istream& is)
{
	std::string username, password;
	bool isAdmin;

	if (!utility::readString(is, username)) return std::nullopt;
	if (!utility::readString(is, password)) return std::nullopt;
	is.read(reinterpret_cast<char*>(&isAdmin), sizeof(isAdmin));
	if (!is) return std::nullopt;

	Account account(username, password);
	account.m_isAdmin = isAdmin;
	return account;
}
