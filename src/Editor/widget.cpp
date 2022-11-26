#include "Precompiled.h"

#include "Editor/widget.h"
#include "Editor/widget_data.h"
#include "Editor/selection.h"
#include "Editor/history.h"

namespace imgui_editor
{
	widget* new_widget(widget_type type)
	{
		auto w = new widget();
		w->type = type;
		w->args = new_widget_arg(type);
		return w;
	}

	void* new_widget_arg(widget_type type)
	{
		switch (type)
		{
		case widget_type::widget_type_none:					return new widget_none();
		case widget_type::widget_type_button:				return new widget_button();
		case widget_type::widget_type_checkbox:				return new widget_checkbox();
		case widget_type::widget_type_radio_button:			return new widget_radio_button();
		case widget_type::widget_type_small_button:			return new widget_small_button();
		case widget_type::widget_type_checkbox_flags:		return new widget_checkbox_flags();
		case widget_type::widget_type_text:					return new widget_text();
		case widget_type::widget_type_text_colored:			return new widget_text_colored();
		case widget_type::widget_type_bullet_text:			return new widget_bullet_text();
		case widget_type::widget_type_bullet:				return new widget_bullet();
		case widget_type::widget_type_selectable:			return new widget_selectable();
		case widget_type::widget_type_label_text:			return new widget_label_text();
		case widget_type::widget_type_input_text:			return new widget_input_text();
		case widget_type::widget_type_input_text_multiline:	return new widget_input_text_multiline();
		case widget_type::widget_type_input_text_with_hint:	return new widget_input_text_with_hint();
		case widget_type::widget_type_input_int:			return new widget_input_int();
		case widget_type::widget_type_input_int2:			return new widget_input_int2();
		case widget_type::widget_type_input_int3:			return new widget_input_int3();
		case widget_type::widget_type_input_int4:			return new widget_input_int4();
		case widget_type::widget_type_input_float:			return new widget_input_float();
		case widget_type::widget_type_input_float2:			return new widget_input_float2();
		case widget_type::widget_type_input_float3:			return new widget_input_float3();
		case widget_type::widget_type_input_float4:			return new widget_input_float4();
		case widget_type::widget_type_input_double:			return new widget_input_double();
		case widget_type::widget_type_drag_int:				return new widget_drag_int();
		case widget_type::widget_type_drag_int2:			return new widget_drag_int2();
		case widget_type::widget_type_drag_int3:			return new widget_drag_int3();
		case widget_type::widget_type_drag_int4:			return new widget_drag_int4();
		case widget_type::widget_type_drag_float:			return new widget_drag_float();
		case widget_type::widget_type_drag_float2:			return new widget_drag_float2();
		case widget_type::widget_type_drag_float3:			return new widget_drag_float3();
		case widget_type::widget_type_drag_float4:			return new widget_drag_float4();
		case widget_type::widget_type_slider_int:			return new widget_slider_int();
		case widget_type::widget_type_slider_int2:			return new widget_slider_int2();
		case widget_type::widget_type_slider_int3:			return new widget_slider_int3();
		case widget_type::widget_type_slider_int4:			return new widget_slider_int4();
		case widget_type::widget_type_slider_float:			return new widget_slider_float();
		case widget_type::widget_type_slider_float2:		return new widget_slider_float2();
		case widget_type::widget_type_slider_float3:		return new widget_slider_float3();
		case widget_type::widget_type_slider_float4:		return new widget_slider_float4();
		case widget_type::widget_type_slider_angle:			return new widget_slider_angle();
		case widget_type::widget_type_color_edit3:			return new widget_color_edit3();
		case widget_type::widget_type_color_edit4:			return new widget_color_edit4();
		case widget_type::widget_type_color_picker3:		return new widget_color_picker3();
		case widget_type::widget_type_color_picker4:		return new widget_color_picker4();
		case widget_type::widget_type_color_button:			return new widget_color_button();
		case widget_type::widget_type_list_box:				return new widget_list_box();
		case widget_type::widget_type_collapsing_header:	return new widget_collapsing_header();
		case widget_type::widget_type_separator:			return new widget_separator();
		case widget_type::widget_type_same_line:			return new widget_same_line();
		case widget_type::widget_type_spacing:				return new widget_spacing();
		case widget_type::widget_type_dummy:				return new widget_dummy();
		case widget_type::widget_type_indent:				return new widget_indent();
		case widget_type::widget_type_unindent:				return new widget_unindent();
		case widget_type::widget_type_begin_end_window:		return new widget_begin_end_window();
		case widget_type::widget_type_begin_end_child:		return new widget_begin_end_child();
		case widget_type::widget_type_begin_end_popup:		return new widget_begin_end_popup();
		case widget_type::widget_type_begin_end_list_box:	return new widget_begin_end_list_box();
		case widget_type::widget_type_begin_end_table:		return new widget_begin_end_table();
		case widget_type::widget_type_push_pop_tree_node:	return new widget_push_pop_tree_node();
		case widget_type::widget_type_begin_end_group:		return new widget_begin_end_group();
		case widget_type::widget_type_begin_end_combo:		return new widget_begin_end_combo();
		case widget_type::widget_type_begin_end_menu:		return new widget_begin_end_menu();
		}
		return nullptr;
	}

	void delete_widget(widget* target)
	{
		delete_widget_args(target->type, target->args);
		target->args = nullptr;

		for(size_t i = 0, max = target->children.size(); i < max; ++i)
		{
			delete_widget(target->children[i]);
		}
		target->children.clear();
	}

	void delete_widget_args(widget_type type, void* target)
	{
		switch (type)
		{
		case widget_type::widget_type_none:					delete (widget_none*)target;					break;
		case widget_type::widget_type_button:				delete (widget_button*)target;					break;
		case widget_type::widget_type_small_button:			delete (widget_small_button*)target;			break;
		case widget_type::widget_type_checkbox:				delete (widget_checkbox*)target;				break;
		case widget_type::widget_type_checkbox_flags:		delete (widget_checkbox_flags*)target;			break;
		case widget_type::widget_type_radio_button:			delete (widget_radio_button*)target;			break;
		case widget_type::widget_type_text:					delete (widget_text*)target;					break;
		case widget_type::widget_type_text_colored:			delete (widget_text_colored*)target;			break;
		case widget_type::widget_type_bullet_text:			delete (widget_bullet_text*)target;				break;
		case widget_type::widget_type_bullet:				delete (widget_bullet*)target;					break;
		case widget_type::widget_type_selectable:			delete (widget_selectable*)target;				break;
		case widget_type::widget_type_label_text:			delete (widget_label_text*)target;				break;
		case widget_type::widget_type_input_text:			delete (widget_input_text*)target;				break;
		case widget_type::widget_type_input_text_multiline:	delete (widget_input_text_multiline*)target;	break;
		case widget_type::widget_type_input_text_with_hint:	delete (widget_input_text_with_hint*)target;	break;
		case widget_type::widget_type_input_int:			delete (widget_input_int*)target;				break;
		case widget_type::widget_type_input_int2:			delete (widget_input_int2*)target;				break;
		case widget_type::widget_type_input_int3:			delete (widget_input_int3*)target;				break;
		case widget_type::widget_type_input_int4:			delete (widget_input_int4*)target;				break;
		case widget_type::widget_type_input_float:			delete (widget_input_float*)target;				break;
		case widget_type::widget_type_input_float2:			delete (widget_input_float2*)target;			break;
		case widget_type::widget_type_input_float3:			delete (widget_input_float3*)target;			break;
		case widget_type::widget_type_input_float4:			delete (widget_input_float4*)target;			break;
		case widget_type::widget_type_input_double:			delete (widget_input_double*)target;			break;
		case widget_type::widget_type_drag_int:				delete (widget_drag_int*)target;				break;
		case widget_type::widget_type_drag_int2:			delete (widget_drag_int2*)target;				break;
		case widget_type::widget_type_drag_int3:			delete (widget_drag_int3*)target;				break;
		case widget_type::widget_type_drag_int4:			delete (widget_drag_int4*)target;				break;
		case widget_type::widget_type_drag_float:			delete (widget_drag_float*)target;				break;
		case widget_type::widget_type_drag_float2:			delete (widget_drag_float2*)target;				break;
		case widget_type::widget_type_drag_float3:			delete (widget_drag_float3*)target;				break;
		case widget_type::widget_type_drag_float4:			delete (widget_drag_float4*)target;				break;
		case widget_type::widget_type_slider_int:			delete (widget_slider_int*)target;				break;
		case widget_type::widget_type_slider_int2:			delete (widget_slider_int2*)target;				break;
		case widget_type::widget_type_slider_int3:			delete (widget_slider_int3*)target;				break;
		case widget_type::widget_type_slider_int4:			delete (widget_slider_int4*)target;				break;
		case widget_type::widget_type_slider_float:			delete (widget_slider_float*)target;			break;
		case widget_type::widget_type_slider_float2:		delete (widget_slider_float2*)target;			break;
		case widget_type::widget_type_slider_float3:		delete (widget_slider_float3*)target;			break;
		case widget_type::widget_type_slider_float4:		delete (widget_slider_float4*)target;			break;
		case widget_type::widget_type_slider_angle:			delete (widget_slider_angle*)target;			break;
		case widget_type::widget_type_color_edit3:			delete (widget_color_edit3*)target;				break;
		case widget_type::widget_type_color_edit4:			delete (widget_color_edit4*)target;				break;
		case widget_type::widget_type_color_picker3:		delete (widget_color_picker3*)target;			break;
		case widget_type::widget_type_color_picker4:		delete (widget_color_picker4*)target;			break;
		case widget_type::widget_type_color_button:			delete (widget_color_button*)target;			break;
		case widget_type::widget_type_list_box:				delete (widget_list_box*)target;				break;
		case widget_type::widget_type_collapsing_header:	delete (widget_collapsing_header*)target;		break;
		case widget_type::widget_type_separator:			delete (widget_separator*)target;				break;
		case widget_type::widget_type_same_line:			delete (widget_same_line*)target;				break;
		case widget_type::widget_type_spacing:				delete (widget_spacing*)target;					break;
		case widget_type::widget_type_dummy:				delete (widget_dummy*)target;					break;
		case widget_type::widget_type_indent:				delete (widget_indent*)target;					break;
		case widget_type::widget_type_unindent:				delete (widget_unindent*)target;				break;
		case widget_type::widget_type_begin_end_window:		delete (widget_begin_end_window*)target;		break;
		case widget_type::widget_type_begin_end_child:		delete (widget_begin_end_child*)target;			break;
		case widget_type::widget_type_begin_end_popup:		delete (widget_begin_end_popup*)target;			break;
		case widget_type::widget_type_begin_end_list_box:	delete (widget_begin_end_list_box*)target;		break;
		case widget_type::widget_type_begin_end_table:		delete (widget_begin_end_table*)target;			break;
		case widget_type::widget_type_begin_end_group:		delete (widget_begin_end_group*)target;			break;
		case widget_type::widget_type_begin_end_combo:		delete (widget_begin_end_combo*)target;			break;
		case widget_type::widget_type_begin_end_menu:		delete (widget_begin_end_menu*)target;			break;
		case widget_type::widget_type_push_pop_tree_node:	delete (widget_push_pop_tree_node*)target;		break;
		}
	}

	struct command_attach_child
	{
		widget* parent;
		widget* child;
		size_t index;
	};

	void command_attach_child_undo(void* _context)
	{
		command_attach_child* ctx = (command_attach_child*)_context;
		ctx->parent->children.erase(ctx->parent->children.begin() + ctx->index);
	}

	void command_attach_child_redo(void* _context)
	{
		command_attach_child* ctx = (command_attach_child*)_context;
		ctx->parent->children.push_back(ctx->child);
		ctx->index = ctx->parent->children.size() - 1;
	}

	void command_attach_child_destructor(void* ctx)
	{
		command_attach_child* cmd = (command_attach_child*)ctx;
		delete cmd;
	}

	void attach_child(widget* parent, widget* child)
	{
		imgui_editor::command* cmd = new imgui_editor::command();
		cmd->label = "attach child";

		command_attach_child* ctx = new command_attach_child();

		ctx->parent = parent;
		ctx->child = child;

		cmd->argument_data = ctx;
		cmd->undo = command_attach_child_undo;
		cmd->redo = command_attach_child_redo;
		cmd->destructor = command_attach_child_destructor;

		commit(cmd);

		// parent->children.push_back(child);
	}
}
