#include "Token.h"
#include <stdexcept>

Token::Token():
	_tokenType(TokenType::Unknown), _value("") {}

Token::Token(const TokenType type, const std::string& value):
	_tokenType(type), _value(value) 
{
	tokenTypeValidation(type);  // Validate type in constructor
}

Token::TokenType Token::getTokenType() const
{
	return this->_tokenType;
}

std::string Token::getValue() const
{
	return this->_value;
}

void Token::setTokenType(const TokenType type)
{
	tokenTypeValidation(type);  // Validate type
	this->_tokenType = type;
}

void Token::setValue(const std::string& value)
{
	this->_value = value;
}

void Token::tokenTypeValidation(const TokenType type) const
{
	if (type < TokenType::Keyword || type >  TokenType::Unknown) {
		throw std::invalid_argument("Invalid token type");
	}
}
