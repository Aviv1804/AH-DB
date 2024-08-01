#include "Tokenizer.h"
#include <regex>

const std::unordered_set<std::string> Tokenizer::singleWordKeywords =  {
"SELECT", "FROM", "WHERE", "INSERT", "UPDATE", "DELETE", "CREATE", "ALTER", "DROP", "TABLE", "JOIN", "INNER", "LEFT", "RIGHT", "FULL", "GROUP BY", "HAVING", "ORDER BY", "DISTINCT", "UNION", "ALL", "AS", "AND", "OR", "NOT", "NULL", "IS", "LIKE", "IN", "INTO", "BETWEEN", "EXISTS", "CASE", "WHEN", "THEN", "ELSE", "END", "LIMIT", "OFFSET", "SET", "VALUES", "RETURNING", "WITH", "CTE", "ROW_NUMBER", "PARTITION BY", "OVER", "INDEX", "VIEW", "TRIGGER", "PROCEDURE", "FUNCTION", "USER", "GRANT", "REVOKE", "COMMIT", "ROLLBACK", "TRANSACTION"
};

const std::unordered_map<std::string, std::unordered_set<std::string>> Tokenizer::twoWordsKeywords = {
    {"GROUP", { "BY" }},
    { "ORDER", {"BY"} },
    { "PARTITION", {"BY"} },
    { "INNER", {"JOIN"} },
    { "LEFT", {"JOIN"} },
    { "RIGHT", {"JOIN"} },
    { "FULL", {"JOIN"} },
    { "NATURAL", {"JOIN"} }
};

const std::unordered_set<std::string> Tokenizer::punctuation = {
    ",", ";", ".", "(", ")", "'", "\"", "`", "[", "]", "/*", "*/" 
};

const std::unordered_set<std::string> Tokenizer::operators = { 
    "+", "-", "*", "/", "%", "+=", "-=",  "*=", "/=" , "=", "!=", "<", ">", "<=", ">="
};

std::vector<Token> Tokenizer::Tokenize(const std::string& input)
{
    std::vector<Token> tokens;
    std::vector<std::string> splittedQuery = Tokenizer::split(input);
    for (auto it = splittedQuery.begin(); it != splittedQuery.end(); ++it) {
        if (Tokenizer::isSingleWordKeyword(*it))
        {
            tokens.push_back(Token(Token::TokenType::Keyword, *it));

        }
        else if ((it + 1) != splittedQuery.end() && Tokenizer::isStartOfTwoWordKeyword(*it) && Tokenizer::isTwoWordsKeyword(*it, *(it+1)))
        {
            tokens.push_back(Token(Token::TokenType::Keyword, *it + " " + *(it+1)));
            it++;
        }
        else if (Tokenizer::isPunctuation(*it))
        {
            tokens.push_back(Token(Token::TokenType::Punctuation, *it));
        }
        else if (Tokenizer::isOperator(*it))
        {
            tokens.push_back(Token(Token::TokenType::Operator, *it));
        }
        else if (Tokenizer::isLiteral(*it))
        {
            tokens.push_back(Token(Token::TokenType::Literal, *it));
        }
        else if (Tokenizer::isIdentifier(*it))
        {
            tokens.push_back(Token(Token::TokenType::Identifier, *it));
        }
        else
        {
            tokens.push_back(Token(Token::TokenType::Unknown, *it));
        }
    }
    return tokens;
}

const std::vector<std::string> Tokenizer::split(const std::string& query)
{
    std::vector<std::string> possibleTokens;
    std::string regex_str = R"((\"(?:\\.|[^"\\])*\"|'(?:\\.|[^'\\])*'|[A-Za-z_][A-Za-z_0-9]*|[0-9]+(?:\.[0-9]*)?|\*|=|,|;|\(|\)|\s+|.))";
    std::regex re(regex_str);
    std::sregex_token_iterator it(query.begin(), query.end(), re);
    std::sregex_token_iterator end;

    for (; it != end; it++) 
    {
        std::string str = it->str();
        if (!str.empty() && str.find_first_not_of(" \t\n") != std::string::npos) // check if str is not empty
        {
            if (str == "\"" || str == "'") 
            {
                it++;
                for (; it != end; it++)
                {
                    if (!it->str().empty() && it->str().find_first_not_of(" \t\n") != std::string::npos)
                    {
                        str += it->str() + " " ;
                    }
                }
                str.pop_back();
                possibleTokens.push_back(str);
                return possibleTokens;
            }

            possibleTokens.push_back(str);
        }
    }
    return possibleTokens;
}

bool Tokenizer::isSingleWordKeyword(const std::string& word)
{
    // Check if the word exists in the set of single-word SQL keywords
    return singleWordKeywords.count(word) > 0;
}

bool Tokenizer::isStartOfTwoWordKeyword(const std::string& word)
{
    // Check if the word exists in the keys of two-words SQL keywords
    return twoWordsKeywords.count(word) > 0;
}

bool Tokenizer::isTwoWordsKeyword(const std::string& first, const std::string& second)
{
    // Check if the word exists in the map of two-word SQL keywords
    return twoWordsKeywords.count(first) > 0 && twoWordsKeywords.at(first).count(second) > 0;
}

bool Tokenizer::isPunctuation(const std::string& str)
{
    // Check if the word exists in the set of punctuations
    return punctuation.count(str) > 0;
}

bool Tokenizer::isOperator(const std::string& str)
{
    // Check if the word exists in the set of operators
    return operators.count(str) > 0;
}

bool Tokenizer::isLiteral(const std::string& str)
{
    std::regex pattern(R"(^[+-]?(\d+(\.\d*)?|\.\d+)$)"); // number regex check

    // check if literal string
    if (str.length() > 1 && ((str[0] == '"' && str[str.length()-1] == '"') || (str[0] == '\'' && str[str.length() - 1] == '\'')))
    {
        return true;
    }
    else if (std::regex_match(str, pattern))
    {
        return true;
    }
    return false;
}

bool Tokenizer::isIdentifier(const std::string& str)
{
    std::regex pattern(R"(^[A-Z a-z_]+\b$)");
    if (std::regex_match(str, pattern))
    {
        return true;
    }
    return false;
}

