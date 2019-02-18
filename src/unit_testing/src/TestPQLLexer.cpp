
#include "PQLLexer.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("Testing basic declaration variable")
{
	const string input = "variable a; Select a;";
	queue<pair<TokenType, string>> res;
	PQLLexer p(input);
	
	res = p.getTokenQueue();

	SECTION("Selectqueue's first pair is KEYWORD: variable") {
        
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "variable");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "select");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
	}
}

TEST_CASE("Testing read a")
{
	const string input = "read a; Select a;";
	queue<pair<TokenType, string>> res;
	PQLLexer p(input);

	res = p.getTokenQueue();

	SECTION("Selectqueue's first pair is KEYWORD: variable") {

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "read");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "select");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
	}
}

TEST_CASE("Testing print a")
{
	const string input = "print a; Select a;";
	queue<pair<TokenType, string>> res;
	PQLLexer p(input);

	res = p.getTokenQueue();

	SECTION("Selectqueue's first pair is KEYWORD: variable") {

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "print");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "select");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
	}
}

TEST_CASE("Testing while a")
{
	const string input = "while a; Select a;";
	queue<pair<TokenType, string>> res;
	PQLLexer p(input);

	res = p.getTokenQueue();

	SECTION("1") {

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "while");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "select");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
	}
}

TEST_CASE("Testing if a")
{
	const string input = "if a; Select a;";
	queue<pair<TokenType, string>> res;
	PQLLexer p(input);

	res = p.getTokenQueue();

	SECTION("1") {

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "if");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "select");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
	}
}

TEST_CASE("Testing assign a")
{
	const string input = "assign a; Select a;";
	queue<pair<TokenType, string>> res;
	PQLLexer p(input);

	res = p.getTokenQueue();

	SECTION("1") {

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "assign");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "select");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
	}
}

TEST_CASE("Testing follows")
{
	const string input = "assign a; while w; Select a such that Follows (w, a);";
	queue<pair<TokenType, string>> res;
	PQLLexer p(input);

	res = p.getTokenQueue();

	SECTION("1") {

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "assign");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "while");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "w");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "select");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "such that");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "follows");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == "(");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "w");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ",");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ")");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
	}
}

TEST_CASE("Testing follows(1, s)")
{
	const string input = "assign a; statement s; variable v; Select s such that Follows (1, s);";
	queue<pair<TokenType, string>> res;
	PQLLexer p(input);

	res = p.getTokenQueue();

	SECTION("1") {

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "assign");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().second == "statement");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "s");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "variable");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "v");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "select");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "s");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "such that");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "follows");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == "(");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "1");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ",");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "s");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ")");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
	}
}

TEST_CASE("Testing follows*(1, s)")
{
	const string input = "assign a; statement s; variable v; Select s such that Follows* (1, s);";
	queue<pair<TokenType, string>> res;
	PQLLexer p(input);

	res = p.getTokenQueue();

	SECTION("1") {

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "assign");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().second == "statement");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "s");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "variable");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "v");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "select");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "s");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "such that");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "follows*");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == "(");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "1");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ",");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "s");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ")");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
	}
}

TEST_CASE("Testing + pattern")
{
	const string input = "assign a; Select a pattern a ( _ , \"v + x * y + z * t\");";
	queue<pair<TokenType, string>> res;
	PQLLexer p(input);

	res = p.getTokenQueue();

	SECTION("1") {

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "assign");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "select");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "pattern");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == "(");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "_");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ",");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == "\"");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "v+x*y+z*t");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == "\"");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ")");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
	}
}

TEST_CASE("Testing parents(3, s)")
{
	const string input = "assign a; statement s; variable v; Select s such that Parent (3, s);";
	queue<pair<TokenType, string>> res;
	PQLLexer p(input);

	res = p.getTokenQueue();

	SECTION("1") {

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "assign");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().second == "statement");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "s");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "variable");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "v");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "select");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "s");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "such that");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "parent");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == "(");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "3");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ",");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "s");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ")");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
	}
}

TEST_CASE("Testing parent*(3, s)")
{
	const string input = "assign a; statement s; variable v; Select s such that Parent* (3, s);";
	queue<pair<TokenType, string>> res;
	PQLLexer p(input);

	res = p.getTokenQueue();

	SECTION("1") {

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "assign");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().second == "statement");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "s");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "variable");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "v");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "select");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "s");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "such that");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "parent*");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == "(");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "3");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ",");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "s");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ")");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
	}
}

TEST_CASE("Testing modifies(3, s)")
{
	const string input = "assign a; statement s; variable v; Select s such that Modifies (3, s);";
	queue<pair<TokenType, string>> res;
	PQLLexer p(input);

	res = p.getTokenQueue();

	SECTION("test modifes") {

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "assign");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().second == "statement");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "s");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "variable");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "v");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "select");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "s");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "such that");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "modifies");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == "(");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "3");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ",");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "s");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ")");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
	}
}

TEST_CASE("Testing modifies(a, 'x')")
{
	const string input = "assign a; statement s; variable v; Select a such that Modifies (a, \"x\");";
	queue<pair<TokenType, string>> res;
	PQLLexer p(input);

	res = p.getTokenQueue();

	SECTION("2") {

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "assign");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().second == "statement");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "s");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "variable");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "v");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "select");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "such that");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "modifies");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == "(");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ",");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == "\"");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "x");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == "\"");
		res.pop();
	        REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ")");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
	}
}

TEST_CASE("Testing uses(a, 'x')")
{
	const string input = "assign a; statement s; variable v; Select a such that Uses (a, \"x\");";
	queue<pair<TokenType, string>> res;
	PQLLexer p(input);

	res = p.getTokenQueue();

	SECTION("2") {

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "assign");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().second == "statement");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "s");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "variable");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "v");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "select");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "such that");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "uses");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == "(");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ",");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == "\"");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "x");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == "\"");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ")");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
	}
}

TEST_CASE("Testing + pattern1")
{
	const string input = "assign a; Select a pattern a ( _ , \"v\");";
	queue<pair<TokenType, string>> res;
	PQLLexer p(input);

	res = p.getTokenQueue();

	SECTION("1") {

		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "assign");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "select");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Keyword);
		REQUIRE(res.front().second == "pattern");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "a");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == "(");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "_");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ",");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == "\"");
		res.pop();
		REQUIRE(res.front().first == TokenType::Identifier);
		REQUIRE(res.front().second == "v");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == "\"");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ")");
		res.pop();
		REQUIRE(res.front().first == TokenType::Separator);
		REQUIRE(res.front().second == ";");
		res.pop();
	}
}


/*
SCENARIO("Only declare one variable a") {
  queue<Token> tokens;
  tokens.push(Token(TokenType::Identifier, "variable"));
  tokens.push(Token(TokenType::Identifier, "a"));
  tokens.push(Token(TokenType::Identifier, ";"));
  PQLParser p = PQLParser();
  Query q = p.buildQuery(tokens);
  std::vector<QueryEntity> selectors = q.selectors;
>>>>>>> develop:src/unit_testing/src/TestPQLParser.cpp

  WHEN("Parsed") {
    REQUIRE(selectors.size() == 1);
    QueryEntity qe = selectors.front();
    REQUIRE(qe.name == "a");
    REQUIRE(qe.type == QueryEntityType::Variable);
  }
}

SCENARIO("Declare 2 variables a and b") {
  queue<Token> tokens;
  tokens.push(Token(TokenType::Identifier, "variable"));
  tokens.push(Token(TokenType::Identifier, "a"));
  tokens.push(Token(TokenType::Identifier, ","));
  tokens.push(Token(TokenType::Identifier, "b"));
  tokens.push(Token(TokenType::Identifier, ";"));
  PQLParser p = PQLParser();
  Query q = p.buildQuery(tokens);
  std::vector<QueryEntity> selectors = q.selectors;

<<<<<<< HEAD:src/unit_testing/src/TestPQLLexer.cpp
TEST_CASE("Testing basic select")
{
	const string input = "select a";
	//queue<tuple<RelationType, string, string>> res;
	string t;
	PQLLexer p(input);
	//res = p.getSelectQueue();
	t = p.getTarget();
	SECTION("discover the targer is a") {

		REQUIRE(t == "a");
	}

}

TEST_CASE("Testing basic declaration variable and select this variable")
{
	const string input = "variable a; select a";
	queue<pair<DeclarationType, string>> resd;
	queue<tuple<RelationType, string, string>> ress;
	string t;

	PQLLexer p(input);
	resd = p.getDeclarationQueue();
	ress = p.getSelectQueue();
	t = p.getTarget();
		SECTION("Selectqueue's first pair is KEYWORD: variable") {

		REQUIRE(resd.front().first == DeclarationType::Variable);
		REQUIRE(resd.front().second == "a");
	}

	SECTION("Target is a") {

		REQUIRE(t == "a");
	}
=======
  WHEN("Parsed") {
    REQUIRE(selectors.size() == 2);
    QueryEntity qe1 = selectors.front();
    QueryEntity qe2 = selectors[1];
    REQUIRE(qe1.name == "a");
    REQUIRE(qe1.type == QueryEntityType::Variable);
    REQUIRE(qe2.name == "b");
    REQUIRE(qe2.type == QueryEntityType::Variable);
  }
}

SCENARIO("Declare several different type of query entities, one for each") {
  queue<Token> tokens;
  tokens.push(Token(TokenType::Identifier, "variable"));
  tokens.push(Token(TokenType::Identifier, "a"));
  tokens.push(Token(TokenType::Identifier, ";"));
  tokens.push(Token(TokenType::Identifier, "procedure"));
  tokens.push(Token(TokenType::Identifier, "p"));
  tokens.push(Token(TokenType::Identifier, ";"));
  tokens.push(Token(TokenType::Identifier, "stmt"));
  tokens.push(Token(TokenType::Identifier, "s"));
  tokens.push(Token(TokenType::Identifier, ";"));
  PQLParser p = PQLParser();
  Query q = p.buildQuery(tokens);
  std::vector<QueryEntity> selectors = q.selectors;
>>>>>>> develop:src/unit_testing/src/TestPQLParser.cpp

  WHEN("Parsed") {
    REQUIRE(selectors.size() == 3);
    QueryEntity qe1 = selectors.front();
    QueryEntity qe2 = selectors[1];
    QueryEntity qe3 = selectors[2];
    REQUIRE(qe1.name == "a");
    REQUIRE(qe1.type == QueryEntityType::Variable);
    REQUIRE(qe2.name == "p");
    REQUIRE(qe2.type == QueryEntityType::Procedure);
    REQUIRE(qe3.name == "s");
    REQUIRE(qe3.type == QueryEntityType::Stmt);
  }
}

<<<<<<< HEAD:src/unit_testing/src/TestPQLLexer.cpp
TEST_CASE("Testing basic declaration procedure")
{
	const string input = "procedure a;";
	const string input1 = "select a";
	queue<pair<DeclarationType, string>> res;
	queue<tuple<RelationType, string, string>> res1;
	string t;
	PQLLexer p(input);

	res = p.getDeclarationQueue();
	res1 = p.getSelectQueue();
	t = p.getTarget();
	SECTION("Selectqueue's first pair is Procedure: a") {

		REQUIRE(res.front().first == DeclarationType::Procedure);
		REQUIRE(res.front().second == "a");
	}
=======
SCENARIO("Declare several different type of query entities, several for each") {
  queue<Token> tokens;
  tokens.push(Token(TokenType::Identifier, "read"));
  tokens.push(Token(TokenType::Identifier, "r1"));
  tokens.push(Token(TokenType::Identifier, ","));
  tokens.push(Token(TokenType::Identifier, "r2"));
  tokens.push(Token(TokenType::Identifier, ";"));
  tokens.push(Token(TokenType::Identifier, "if"));
  tokens.push(Token(TokenType::Identifier, "ifs1"));
  tokens.push(Token(TokenType::Identifier, ","));
  tokens.push(Token(TokenType::Identifier, "ifs2"));
  tokens.push(Token(TokenType::Identifier, ";"));
  tokens.push(Token(TokenType::Identifier, "constant"));
  tokens.push(Token(TokenType::Identifier, "c1"));
  tokens.push(Token(TokenType::Identifier, ","));
  tokens.push(Token(TokenType::Identifier, "c2"));
  tokens.push(Token(TokenType::Identifier, ";"));
  PQLParser p = PQLParser();
  Query q = p.buildQuery(tokens);
  std::vector<QueryEntity> selectors = q.selectors;
>>>>>>> develop:src/unit_testing/src/TestPQLParser.cpp

  WHEN("Parsed") {
    REQUIRE(selectors.size() == 6);
    QueryEntity qe1 = selectors.front();
    QueryEntity qe2 = selectors[1];
    QueryEntity qe3 = selectors[2];
    QueryEntity qe4 = selectors[3];
    QueryEntity qe5 = selectors[4];
    QueryEntity qe6 = selectors[5];
    REQUIRE(qe1.name == "r1");
    REQUIRE(qe1.type == QueryEntityType::Read);
    REQUIRE(qe2.name == "r2");
    REQUIRE(qe2.type == QueryEntityType::Read);
    REQUIRE(qe3.name == "ifs1");
    REQUIRE(qe3.type == QueryEntityType::If);
    REQUIRE(qe4.name == "ifs2");
    REQUIRE(qe4.type == QueryEntityType::If);
    REQUIRE(qe5.name == "c1");
    REQUIRE(qe5.type == QueryEntityType::Constant);
    REQUIRE(qe6.name == "c2");
    REQUIRE(qe6.type == QueryEntityType::Constant);
  }
}

SCENARIO("Select all variables") {
  queue<Token> tokens;
  tokens.push(Token(TokenType::Identifier, "variable"));
  tokens.push(Token(TokenType::Identifier, "a"));
  tokens.push(Token(TokenType::Identifier, ";"));
  tokens.push(Token(TokenType::Identifier, "Select"));
  tokens.push(Token(TokenType::Identifier, "a"));
  PQLParser p = PQLParser();
  Query q = p.buildQuery(tokens);
  std::vector<QueryEntity> selectors = q.selectors;
  QueryEntity tar = q.target;

<<<<<<< HEAD:src/unit_testing/src/TestPQLLexer.cpp
TEST_CASE("Testing basic declaration procedure and select this procedure")
{
	const string input = "procedure a; select a";
	queue<pair<DeclarationType, string>> resd;
	queue<tuple<RelationType, string, string>> ress;
	string t;
	PQLLexer p(input);
	resd = p.getDeclarationQueue();
	ress = p.getSelectQueue();
	t = p.getTarget();
	SECTION("Selectqueue's first pair is KEYWORD: procedure") {

		REQUIRE(resd.front().first == DeclarationType::Procedure);
		REQUIRE(resd.front().second == "a");
	}


	SECTION("Target is a") {

		REQUIRE(t == "a");
	}

}


  WHEN("Parsed") {
    REQUIRE(selectors.size() == 1);
    QueryEntity qe = selectors.front();
    REQUIRE(qe.name == "a");
    REQUIRE(qe.type == QueryEntityType::Variable);
    REQUIRE(tar.name == "a");
    REQUIRE(tar.type == QueryEntityType::Variable);
  }
}

SCENARIO("Including one such that clause") {
  queue<Token> tokens;
  tokens.push(Token(TokenType::Identifier, "assign"));
  tokens.push(Token(TokenType::Identifier, "a"));
  tokens.push(Token(TokenType::Identifier, ";"));
  tokens.push(Token(TokenType::Identifier, "Select"));
  tokens.push(Token(TokenType::Identifier, "a"));
  tokens.push(Token(TokenType::Identifier, "such that"));
  tokens.push(Token(TokenType::Identifier, "Follows"));
  tokens.push(Token(TokenType::Identifier, "("));
  tokens.push(Token(TokenType::Identifier, "a"));
  tokens.push(Token(TokenType::Identifier, ","));
  tokens.push(Token(TokenType::Identifier, "5"));
  tokens.push(Token(TokenType::Identifier, ")"));
  PQLParser p = PQLParser();
  Query q = p.buildQuery(tokens);
  std::vector<QueryEntity> selectors = q.selectors;
  std::vector<Clause> clauses = q.clauses;
  QueryEntity tar = q.target;

  WHEN("Parsed") {
    REQUIRE(selectors.size() == 1);
    QueryEntity qe = selectors.front();
    REQUIRE(qe.name == "a");
    REQUIRE(qe.type == QueryEntityType::Assign);
    REQUIRE(tar.name == "a");
    REQUIRE(tar.type == QueryEntityType::Assign);
    REQUIRE(clauses.size() == 1);
    Clause c = clauses.front();
    std::vector<QueryEntity> parameters = c.parameters;
    REQUIRE(c.clauseType == ClauseType::Follows);
    REQUIRE(parameters[0].name == "a");
    REQUIRE(parameters[0].type == QueryEntityType::Assign);
    REQUIRE(parameters[1].name == "5");
    REQUIRE(parameters[1].type == QueryEntityType::Line);
  }
}
>>>>>>> develop:src/unit_testing/src/TestPQLParser.cpp

// TEST_CASE("Testing basic declaration variable") {
//  const string input = "variable a;";
//  queue<pair<DeclarationType, string>> res;
//  PQLParser p(input);
//
//  res = p.getDeclarationQueue();
//  SECTION("Selectqueue's first pair is KEYWORD: variable") {
//
//    REQUIRE(res.front().first == DeclarationType::Variable);
//  }
//
//  SECTION("Selectqueue's second pair is Identifier: a") {
//    REQUIRE(res.front().second == "a");
//    res.pop();
//  }
//}
//
// TEST_CASE("Testing basic select") {
//  const string input = "select a";
//  // queue<tuple<RelationType, string, string>> res;
//  string t;
//  PQLParser p(input);
//  // res = p.getSelectQueue();
//  t = p.getTarget();
//  SECTION("discover the targer is a") { REQUIRE(t == "a"); }
//}
//
// TEST_CASE("Testing basic declaration variable and select this variable") {
//  const string input = "variable a; select a";
//  queue<pair<DeclarationType, string>> resd;
//  queue<tuple<RelationType, string, string>> ress;
//  string t;
//
//  PQLParser p(input);
//  resd = p.getDeclarationQueue();
//  ress = p.getSelectQueue();
//  t = p.getTarget();
//  SECTION("Selectqueue's first pair is KEYWORD: variable") {
//
//    REQUIRE(resd.front().first == DeclarationType::Variable);
//    REQUIRE(resd.front().second == "a");
//  }
//
//  SECTION("Target is a") { REQUIRE(t == "a"); }
//}
//
// TEST_CASE("Testing basic declaration procedure") {
//  const string input = "procedure a;";
//  const string input1 = "select a";
//  queue<pair<DeclarationType, string>> res;
//  queue<tuple<RelationType, string, string>> res1;
//  string t;
//  PQLParser p(input);
//
//  res = p.getDeclarationQueue();
//  res1 = p.getSelectQueue();
//  t = p.getTarget();
//  SECTION("Selectqueue's first pair is Procedure: a") {
//
//    REQUIRE(res.front().first == DeclarationType::Procedure);
//    REQUIRE(res.front().second == "a");
//  }
//}
//
// TEST_CASE("Testing basic declaration procedure and select this procedure") {
//  const string input = "procedure a; select a";
//  queue<pair<DeclarationType, string>> resd;
//  queue<tuple<RelationType, string, string>> ress;
//  string t;
//  PQLParser p(input);
//  resd = p.getDeclarationQueue();
//  ress = p.getSelectQueue();
//  t = p.getTarget();
//  SECTION("Selectqueue's first pair is KEYWORD: procedure") {
//
//    REQUIRE(resd.front().first == DeclarationType::Procedure);
//    REQUIRE(resd.front().second == "a");
//  }
//
//  SECTION("Target is a") { REQUIRE(t == "a"); }
//}
*/