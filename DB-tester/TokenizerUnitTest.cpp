#include "pch.h"
#include "CppUnitTest.h"
#include "../AH-DB/Tokenizer.h"
#include "../AH-DB/Token.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DBtester
{
    // Struct for Is* functions
    typedef struct TokenizerTestCase
    {
        std::string str;
        bool expected;
    } TokenizerTestCase;

    // Struct for IsTwoWordsKeyword tests
    typedef struct TwoWordsKeywordTestCase
    {
        std::string first;
        std::string second;
        bool expected;
    } TwoWordsKeywordTestCase;

    // Struct for Tokenize tests
    typedef struct TokenizeTestCase
    {
        std::string str;
        std::vector<Token> expectedTokens;
    } TokenizeTestCase;

    TEST_CLASS(TokenizerTests)
    {
    private:

        void runTestCases(const std::vector<TokenizerTestCase>& testCases, bool (*method)(const std::string&), const wchar_t* errorMessage)
        {
            for (const auto& testCase : testCases)
            {
                bool result = (*method)(testCase.str);
                Assert::AreEqual(testCase.expected, result, errorMessage);
            }
        }

        void runTestCases(const std::vector<TwoWordsKeywordTestCase>& testCases, bool (*method)(const std::string&, const std::string&), const wchar_t* errorMessage)
        {
            for (const auto& testCase : testCases)
            {
                bool result = (*method)(testCase.first, testCase.second);
                Assert::AreEqual(testCase.expected, result, errorMessage);
            }
        }

        void runTestCases(const std::vector<TokenizeTestCase>& testCases, std::vector<Token>(*method)(const std::string&), const wchar_t* errorMessage)
        {
            for (const auto& testCase : testCases)
            {
                std::vector<Token> result = (*method)(testCase.str);
                for (size_t i = 0; i < testCase.expectedTokens.size(); ++i) {
                    if (!(testCase.expectedTokens[i] == result[i])) { 
                        Assert::Fail(errorMessage);
                    }
                }
            }
        }

    public:

        TEST_METHOD(AddMethodTest)
        {
            Tokenizer obj;
            int result = 5;
            Assert::AreEqual(5, result);
        }

        TEST_METHOD(IsIdentifierMethodTest)
        {
            std::vector<TokenizerTestCase> testCases = {
                {"validIdentifier", true},
                {"123invalid", false},
                {"another_valid_id", true},
                {"invalid-id", false},
                {"_valid123", true}
            };

            this->runTestCases(testCases, &Tokenizer::isIdentifier, L"IsIdentifier test failed");
        }

        TEST_METHOD(IsLiteralMethodTest)
        {
            std::vector<TokenizerTestCase> testCases = {
                {"\"validString\"", true},
                {"\"unterminatedString", false},
                {"12345", true},
                {"invalidLiteral", false},
                {"'validLiteral'", true}
            };

            this->runTestCases(testCases, &Tokenizer::isLiteral, L"IsLiteral test failed");
        }

        TEST_METHOD(IsOperatorMethodTest)
        {
            std::vector<TokenizerTestCase> testCases = {
                {"+", true},
                {"-", true},
                {"*", true},
                {"/", true},
                {"=", true},
                {"invalidOp", false}
            };

            this->runTestCases(testCases, &Tokenizer::isOperator, L"IsOperator test failed");
        }

        TEST_METHOD(IsPunctuationMethodTest)
        {
            std::vector<TokenizerTestCase> testCases = {
                {";", true},
                {",", true},
                {".", true},
                {"(", true},
                {")", true},
                {"invalidPunc", false}
            };

            this->runTestCases(testCases, &Tokenizer::isPunctuation, L"IsPunctuation test failed");
        }

        TEST_METHOD(IsTwoWordsKeywordMethodTest)
        {
            std::vector<TwoWordsKeywordTestCase> testCases = {
                {"INNER", "JOIN", true},
                {"LEFT", "JOIN", true},
                {"RIGHT", "JOIN", true},
                {"FULL", "JOIN", true},
                {"invalid", "keyword", false}
            };

            this->runTestCases(testCases, &Tokenizer::isTwoWordsKeyword, L"IsTwoWordsKeyword test failed");
        }

        TEST_METHOD(IsSingleWordKeywordMethodTest)
        {
            std::vector<TokenizerTestCase> testCases = {
                {"SELECT", true},
                {"FROM", true},
                {"WHERE", true},
                {"INSERT", true},
                {"invalidKeyword", false}
            };

            this->runTestCases(testCases, &Tokenizer::isSingleWordKeyword, L"IsSingleWordKeyword test failed");
        }

        TEST_METHOD(tokenizeMethodTest)
        {
            std::vector<TokenizeTestCase> testCases = {
            {"SELECT * FROM table;",
                {Token(Token::TokenType::Keyword, "SELECT"),
                 Token(Token::TokenType::Operator, "*"),
                 Token(Token::TokenType::Keyword, "FROM"),
                 Token(Token::TokenType::Identifier, "table"),
                 Token(Token::TokenType::Punctuation, ";")}},
            {"INSERT INTO table (column1) VALUES (value1);",
                {Token(Token::TokenType::Keyword, "INSERT"),
                 Token(Token::TokenType::Keyword, "INTO"),
                 Token(Token::TokenType::Identifier, "table"),
                 Token(Token::TokenType::Punctuation, "("),
                 Token(Token::TokenType::Identifier, "column1"),
                 Token(Token::TokenType::Punctuation, ")"),
                 Token(Token::TokenType::Keyword, "VALUES"),
                 Token(Token::TokenType::Punctuation, "("),
                 Token(Token::TokenType::Identifier, "value1"),
                 Token(Token::TokenType::Punctuation, ")"),
                 Token(Token::TokenType::Punctuation, ";")}},
            {"DELETE FROM table WHERE column1 = 'value1';",
                {Token(Token::TokenType::Keyword, "DELETE"),
                 Token(Token::TokenType::Keyword, "FROM"),
                 Token(Token::TokenType::Identifier, "table"),
                 Token(Token::TokenType::Keyword, "WHERE"),
                 Token(Token::TokenType::Identifier, "column1"),
                 Token(Token::TokenType::Operator, "="),
                 Token(Token::TokenType::Literal, "'value1'"),
                 Token(Token::TokenType::Punctuation, ";")}}
            };


             this->runTestCases(testCases, &Tokenizer::tokenize, L"Tokenize test failed");
        }
    };
}