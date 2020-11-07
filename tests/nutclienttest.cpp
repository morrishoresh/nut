/* nutclienttest - CppUnit nutclient unit test

   Copyright (C) 2016  Emilien Kia <emilien.kia@gmail.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/
#include <cppunit/extensions/HelperMacros.h>

class NutClientTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( NutClientTest );
		CPPUNIT_TEST( test_stringset_to_strarr );
		CPPUNIT_TEST( test_stringvector_to_strarr );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void test_stringset_to_strarr();
	void test_stringvector_to_strarr();
};

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( NutClientTest );

#include "../clients/nutclient.h"
extern "C" {
strarr stringset_to_strarr(const std::set<std::string>& strset);
strarr stringvector_to_strarr(const std::vector<std::string>& strset);
} // extern "C"

void NutClientTest::setUp()
{
}

void NutClientTest::tearDown()
{
}

void NutClientTest::test_stringset_to_strarr()
{
	std::set<std::string> strset;
	strset.insert("test");
	strset.insert("hello");
	strset.insert("world");

	strarr arr = stringset_to_strarr(strset);
	CPPUNIT_ASSERT_MESSAGE("stringset_to_strarr(...) result is null", arr!=NULL);

	std::set<std::string> res;

	char** ptr = arr;
	while(*ptr!=NULL)
	{
		res.insert(std::string(*ptr));
		ptr++;
	}

	CPPUNIT_ASSERT_EQUAL_MESSAGE("stringset_to_strarr(...) result has not 3 items", (size_t)3, res.size());
	CPPUNIT_ASSERT_MESSAGE("stringset_to_strarr(...) result has not item \"test\"", res.find("test")!=res.end());
	CPPUNIT_ASSERT_MESSAGE("stringset_to_strarr(...) result has not item \"hello\"", res.find("hello")!=res.end());
	CPPUNIT_ASSERT_MESSAGE("stringset_to_strarr(...) result has not item \"world\"", res.find("world")!=res.end());

	strarr_free(arr);
}

void NutClientTest::test_stringvector_to_strarr()
{
	std::vector<std::string> strset;
	strset.push_back("test");
	strset.push_back("hello");
	strset.push_back("world");

	strarr arr = stringvector_to_strarr(strset);
	CPPUNIT_ASSERT_MESSAGE("stringvector_to_strarr(...) result is null", arr!=NULL);

	char** ptr = arr;
	CPPUNIT_ASSERT_EQUAL_MESSAGE("stringvector_to_strarr(...) result has not item 0==\"test\"", std::string("test"), std::string(*ptr));
	++ptr;
	CPPUNIT_ASSERT_EQUAL_MESSAGE("stringvector_to_strarr(...) result has not item 1==\"hello\"", std::string("hello"), std::string(*ptr));
	++ptr;
	CPPUNIT_ASSERT_EQUAL_MESSAGE("stringvector_to_strarr(...) result has not item 2==\"world\"", std::string("world"), std::string(*ptr));
	++ptr;
	CPPUNIT_ASSERT_EQUAL_MESSAGE("stringvector_to_strarr(...) result has not only 3 items", (char*)NULL, *ptr);

	strarr_free(arr);
}
