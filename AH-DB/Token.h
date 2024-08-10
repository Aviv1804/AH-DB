#pragma once
#include <string>

/**
 * @class Token
 * @brief Represents a token in the SQL parser.
 *
 * The Token class encapsulates the type and value of a token recognized by the SQL parser.
 * It provides methods to get and set the token's type and value.
 */
class Token
{
public:
    /**
     * @enum TokenType
     * @brief Enum representing the types of tokens in the SQL parser.
     *
     * This enumeration defines various types of tokens that can be recognized by the SQL parser, including keywords, operators, symbols, literals, and special tokens.
     */
    enum class TokenType {
        Keyword, Identifier, Literal, Operator, Punctuation, Comment, Whitespace, Unknown
    };

    /**
     * @brief Default constructor.
     *
     * Initializes the token with default values.
     * The default type is set to INVALID and value is an empty string.
     */
    Token();

    /**
     * @brief Parameterized constructor.
     * @param type The type of the token.
     * @param value The value of the token.
     *
     * Initializes the token with the specified type and value.
     */
    Token(const TokenType type, const std::string& value);

    /**
     * @brief Destructor.
     *
     * Cleans up resources used by the Token instance.
     */
    ~Token() = default;  // Default destructor

    /**
     * @brief Gets the type of the token.
     * @return The token type.
     *
     * Retrieves the type of the token.
     */
    TokenType getTokenType() const;

    /**
     * @brief Gets the value of the token.
     * @return The token value.
     *
     * Retrieves the value associated with the token.
     */
    std::string getValue() const;

    /**
     * @brief Sets the type of the token.
     * @param type The new type of the token.
     *
     * Updates the type of the token.
     */
    void setTokenType(const TokenType type);

    /**
     * @brief Sets the value of the token.
     * @param value The new value of the token.
     *
     * Updates the value of the token.
     */
    void setValue(const std::string& value);

    /**
    * @brief Check if two tokens are the same.
    * @param other The other token to compare with.
    * @return True if the tokens are identical, false otherwise.
    */
    bool operator==(const Token& other) const;

private:
    TokenType _tokenType; ///< The type of the token.
    std::string _value;   ///< The value of the token.

    /**
    * @brief Check the validation of token type.
    * @param type The new token type of the token.
    */
    void tokenTypeValidation(const TokenType type) const;

};
