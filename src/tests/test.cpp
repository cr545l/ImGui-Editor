#include "Precompiled.h"

#include <algorithm>
#include <gtest/gtest.h>
#include <magic_enum/magic_enum.hpp>

#include "editor/widget/args_data.h"
#include "editor/widget.h"
#include "editor/extension.h"

using namespace imgui_editor;

TEST(widget, args_nullptr_check)
{
	magic_enum::enum_for_each<widget_type>([&](widget_type t) {
		auto w = new_widget(t);
		std::string name = std::string(magic_enum::enum_name(t));

		EXPECT_TRUE(nullptr == w->args);// , "%s IS NULLPTR", name.c_str());
		delete_widget(w);
		EXPECT_TRUE(nullptr != w->args);// , "%s IS NOT NULLPTR", name.c_str());
		delete w;
		});
}

TEST(parse, string_parse)
{
	{
		std::istringstream stream("\"data\",");
		
		std::string result = read_string(stream);

		EXPECT_TRUE("data" == result);
	}

	{
		const std::string data1 = "ab\"c";

		const std::string sdata1 = to_safe_string(data1);

		EXPECT_TRUE("ab\\\"c" == sdata1);
	}

	{
		const std::string data1 = "ab\"casda\"sa \"sd";

		const std::string sdata1 = to_safe_string(data1);

		EXPECT_TRUE("ab\\\"casda\\\"sa \\\"sd" == sdata1);
	}	
	
	{
		const std::string data1 = "ab\"ckjsa\"asjasdhkj\"";

		const std::string sdata1 = to_safe_string(data1);

		const std::string serialized = string_format("\"%s\",", sdata1.c_str());
		
		std::istringstream stream(serialized);
		
		std::string result = read_string(stream);

		EXPECT_TRUE(data1 == result);
	}

	{
		const std::string data1 = "ab\"ckjsa\"asjasdhkj\"";

		const std::string sdata1 = to_safe_string(data1);

		const std::string data2 = "1\"\"sadjasd'';|\'\"234";

		const std::string sdata2 = to_safe_string(data2);

		const std::string serialized = string_format("\"%s\",1234,\"%s\"", sdata1.c_str(),sdata2.c_str());

		std::istringstream stream(serialized);

		std::string result = read_string(stream);

		EXPECT_TRUE(data1 == result);

		std::getline(stream, result, ',');
		
		std::getline(stream, result, ',');

		EXPECT_TRUE("1234" == result);

		result = read_string(stream);

		EXPECT_TRUE(data2 == result);
	}
}

TEST(parse, string_parse2)
{

#pragma pack(push, 1)
	struct test_struct
	{
		int a;
		std::string b;
		float c;
	};
#pragma pack(pop) 

	test_struct test;
	test.a = 123;
	test.b = "123";
	test.c = 123.123f;

	const char* format = "%d,%s,%f";

	std::string serialized = safe_string_format(format, test.a, test.b.c_str(), test.c);	
	
	std::istringstream stream(serialized);

	test_struct result;	
	sscanf2(format, serialized.c_str(), &result);

	EXPECT_TRUE(test.a == result.a);
	EXPECT_TRUE(test.b == result.b);
	EXPECT_TRUE(test.c == result.c);
}