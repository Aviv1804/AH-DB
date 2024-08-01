#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Token.h"

/**
 * @class Tokenizer
 * @brief Represents a tokenizer for SQL parser.
 *
 * The Tokenizer class contains a static function that generates tokens from query. 
 */
class Tokenizer
{
public:
	/**
	 * @brief Generates SQL tokens from the input query.
	 *
	 * This function processes the input SQL query and generates a vector of tokens
	 * representing keywords, identifiers, operators, punctuation, and literals.
	 * It does not validate SQL syntax, but simply tokenizes the input string.
	 *
	 * @param input The SQL query.
	 * @return A vector of tokens generated from the input query.
	 */
	static std::vector<Token> Tokenize(const std::string& input);


private:
	static const std::unordered_set<std::string> singleWordKeywords;
	static const std::unordered_map<std::string, std::unordered_set<std::string>> twoWordsKeywords;
	static const std::unordered_set<std::string> punctuation;
	static const std::unordered_set<std::string> operators;

	/**
	 * @brief Splits the query into a vector of substrings by punctuation and spaces.
	 *
	 * This function takes an SQL query string and splits it into a vector of substrings
	 * based on punctuation and spaces. Punctuation marks are preserved as separate tokens.
	 *
	 * @param query The query to split.
	 * @return A vector of substrings from the query split by punctuation and spaces.
	 */
	static const std::vector<std::string> split(const std::string& query);


	/**
	* @brief Checks if the string is a single-word SQL keyword.
	* @param word The string to check.
	* @return True if the string is a single-word SQL keyword, false otherwise
	*/
	static bool isSingleWordKeyword(const std::string& word);

	/**
	* @brief Checks if the string is the start of a two-word SQL keyword.
	* @param word The string to check.
	* @return True if the string is the start of a two-word SQL keyword, false otherwise.
	*/
	static bool isStartOfTwoWordKeyword(const std::string& word);

	/**
	* @brief Checks if the strings represent a two-word SQL keyword.
	* @param first, the first string of the keyword.
	* @param second, the second string of the keyword.
	* @return True if the strings represent a two-word SQL keyword, false otherwise.
	*/
	static bool isTwoWordsKeyword(const std::string& first, const std::string& second);
	
	/**
	* @brief Checks if a string is a punctuation mark.
	* @param str The string to check.
	* @return True if the string is a punctuation mark, false otherwise.
	*/
	static bool isPunctuation(const std::string& str);

	/**
	* @brief Checks if a string is an operator.
    * @param str The string to check.
	* @return True if the string is an operator, false otherwise.
    */
	static bool isOperator(const std::string& str);

	/**
	* @brief Checks if a string is a literal.
	* @param str The string to check.
	* @return True if the string is a literal, false otherwise.
	*/
	static bool isLiteral(const std::string& str);

	/**
	* @brief Checks if a string is an identifier.
	* @param str The string to check.
	* @return True if the string is an identifier, false otherwise.
	*/
	static bool isIdentifier(const std::string& str);
};