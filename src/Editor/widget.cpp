#include "Precompiled.h"
#include "editor/widget.h"

#include <unordered_map>

#include "editor/imgui_editor.h"
#include "editor/extension.h"

namespace imgui_editor
{
	extern size_t g_widget_id;
	extern std::unordered_map<size_t, widget*>* g_widget_table;

	widget* find(size_t id)
	{
		auto it = (*g_widget_table).find(id);
		assert(it != (*g_widget_table).end());
		return it->second;
	}

	widget* new_widget(widget_type type)
	{
		const size_t id = g_widget_id++;
		return new_widget_by_id(type, id);
	}

	widget* new_widget_by_id(widget_type type, size_t id)
	{
		auto w =  new widget{
			type,
			new_widget_arg(type),
			get_widget_name(type),
			{},
			{},
			{},
			{},
			std::to_string(id),
			id,
			nullptr,
			nullptr,
			nullptr,
		};
		// LOG("NewArgs %s %x", get_widget_name(w->type), w->args);
		return w;
	}

	void regist_widget(widget* w)
	{
		auto ctx = get_context();

		(*g_widget_table)[w->id] = w;
	}

	void delete_widget(widget* target)
	{
		if (!target->children.empty())
		{
			for (size_t i = target->children.size() - 1; 0 <= i; --i)
			{
				delete_widget(target->children[i]);
				target->children[i] = nullptr;
				if (0 == i)break;
			}
			target->children.clear();
		}
		
		delete_widget_args(target->type, target->args);
		target->args = nullptr;

		(*g_widget_table).erase(target->id);

		delete target;
	}

	void unregist_widget(const widget* w)
	{
		(*g_widget_table).erase(w->id);
	}

	std::string widget_serialize(widget * target)
	{
		std::string children;
		for (size_t i = 0, max = target->children.size(); i < max; ++i)
		{
			children += string_format("%s,", widget_serialize(target->children[i]).c_str());
		}

        std::string style_colors;
        for (size_t i = 0, max = target->style_colors.size(); i < max; ++i)
        {
            style_colors += string_format("{%d,%f,%f,%f,%f},", (int)target->style_colors[i].idx, target->style_colors[i].col.Value.x, target->style_colors[i].col.Value.y, target->style_colors[i].col.Value.z, target->style_colors[i].col.Value.w);
        }

        std::string style_var_floats;
        for (size_t i = 0, max = target->style_var_floats.size(); i < max; ++i)
        {
            style_var_floats += string_format("{%d,%f},", (int)target->style_var_floats[i].idx, target->style_var_floats[i].val);
        }

		std::string style_var_vec2s;
		for (size_t i = 0, max = target->style_var_vec2s.size(); i < max; ++i)
		{
            style_var_vec2s += string_format("{%d,%f,%f},", (int)target->style_var_vec2s[i].idx, target->style_var_vec2s[i].val.x, target->style_var_vec2s[i].val.y);
		}

        std::string version;
		std::string args;
		parse_args_data(target->type, target->args, args, version, false);

        return string_format("{%lu,\"%s\",\"%s\",{%s},\"%s\",[%s],[%s],[%s],[%s]}", 
        to_fixed_type(target->type),
		to_safe_string(version).c_str(),
		to_safe_string(target->string_id).c_str(),
        args.c_str(),
		to_safe_string(target->label).c_str(),
        children.c_str(),
        style_colors.c_str(),
        style_var_floats.c_str(),
        style_var_vec2s.c_str());
    }

	static size_t parse(const std::string& source, const size_t begin, std::vector<std::string>& result)
	{
		std::string::size_type end = source.size();
		size_t count = 0;

		// 1 2123 21 23 212121 0
		// [ [][[n]] [[a]][][] ]

		// 121210
		// [[][]]

		// 10
		// []
		for (size_t i = begin; i < source.size(); ++i)
		{
			if ('[' == source[i])
			{
				++count;
			}
			else if (']' == source[i])
			{
				end = i;
				--count;
			}
			if (0 == count)break;
		}

		if (0 != end && begin < end && 0 < end - begin - 1)
		{
			std::string body = source.substr(begin + 1, end - begin - 1); // remove []

			//   1232 32 3210  10  12343 43 4321 210  
			// [ {[{},{},{}]}, {}, {{[{},{},{}]},[]}, {} ]
			//               ^   ^                  ^

			count = 0;
			size_t cursor = 0;
			for (size_t i = 0; i < body.size(); ++i)
			{
				if ('[' == body[i] || '{' == body[i])
				{
					++count;
				}
				else if (']' == body[i] || '}' == body[i])
				{
					--count;
				}
				else if (0 == count && ',' == body[i])
				{
					// empty pass
					if (0 < i - cursor)
					{
						result.push_back(body.substr(cursor, i - cursor)); // include {}
					}
					cursor = i + 1;
				}
			}
		}

		return end + 1; // remove ,
	}
	
	bool widget_deserialize(widget* target_widget, const char* data)
	{
		bool success = true;
		std::string read;
		std::istringstream widget_stream(data);
		char* pos = nullptr;

		const auto original_type = target_widget->type;

		std::getline(widget_stream, read, '{');
        std::getline(widget_stream, read, ',');
		const size_t fixed_type = strtoul(read.c_str(), &pos, 0);
        target_widget->type = to_widget_type(fixed_type);

		std::string version = read_string(widget_stream);
		std::getline(widget_stream, read, ',');

		target_widget->string_id = read_string(widget_stream);

		try 
		{
			target_widget->id = std::stoul(target_widget->string_id);
		}
		catch (const std::invalid_argument& e) 
		{
			LOG("Invalid id: %s", e.what());
			success = false;
		}

		std::getline(widget_stream, read, ',');

        std::getline(widget_stream, read, '{');
        std::getline(widget_stream, read, '}');

        if (nullptr != target_widget->args && original_type != target_widget->type)
        {
	        delete_widget_args(original_type, target_widget->args);
			target_widget->args = nullptr;
        }

		if (nullptr == target_widget->args)
		{
			target_widget->args = new_widget_arg(target_widget->type);
			// LOG("NewArgs %s %x", get_widget_name(target_widget->type), target_widget->args);
		}

		parse_args_data(target_widget->type, target_widget->args, read, version, true);

        std::getline(widget_stream, read, ',');

		target_widget->label = read_string(widget_stream);
        std::getline(widget_stream, read, ',');
		
        std::getline(widget_stream, read);

		if (!target_widget->children.empty())
		{
			for (size_t i = target_widget->children.size() - 1;; --i)
			{
				delete_widget(target_widget->children[i]);
				target_widget->children[i] = nullptr;
				if (0 == i) break;
			}
			target_widget->children.clear();
		}

		std::vector<std::string> children;
		size_t next = parse(read, 0, children);
		for (size_t i = 0; i < children.size(); ++i)
		{
			widget* child_widget = new_widget_by_id(widget_type::widget_type_none, 0);
			if (widget_deserialize(child_widget, children[i].c_str()))
			{
				target_widget->children.push_back(child_widget);
				child_widget->parent = target_widget;
				regist_widget(child_widget);
			}
			else
			{
				delete_widget(child_widget);
				LOG("Failed deserialze child index %zu", i);
			}
		}

		char dummy;

		std::vector<std::string> style_colors;
		next = parse(read, next+1, style_colors);
		target_widget->style_colors.resize(style_colors.size());

		for (size_t i = 0; i < style_colors.size(); ++i)
		{
			std::istringstream stream(style_colors[i]);
			stream >> dummy; // {
			stream >> target_widget->style_colors[i].idx;
			stream >> dummy; // ,
			stream >> target_widget->style_colors[i].col.Value.x;
			stream >> dummy; // ,
			stream >> target_widget->style_colors[i].col.Value.y;
			stream >> dummy; // ,
			stream >> target_widget->style_colors[i].col.Value.z;
			stream >> dummy; // ,
			stream >> target_widget->style_colors[i].col.Value.w;
		}

		std::vector<std::string> style_var_floats;
		next = parse(read, next+1, style_var_floats);
		target_widget->style_var_floats.resize(style_var_floats.size());

		for (size_t i = 0; i < style_var_floats.size(); ++i)
		{
			std::istringstream stream(style_var_floats[i]);
			stream >> dummy; // {
			stream >> target_widget->style_var_floats[i].idx;
			stream >> dummy; // ,
			stream >> target_widget->style_var_floats[i].val;
		}

		std::vector<std::string> style_var_vec2s;
		next = parse(read, next+1, style_var_vec2s);
		target_widget->style_var_vec2s.resize(style_var_vec2s.size());

		for (size_t i = 0; i < style_var_vec2s.size(); ++i)
		{
			std::istringstream stream(style_var_vec2s[i]);
			stream >> dummy; // {
			stream >> target_widget->style_var_vec2s[i].idx;
			stream >> dummy; // ,
			stream >> target_widget->style_var_vec2s[i].val.x;
			stream >> dummy; // ,
			stream >> target_widget->style_var_vec2s[i].val.y;
		}

		return success;
    }
}
