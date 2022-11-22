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
		switch (type)
		{
		case widget_type::widget_type_none:
		{
			w->args = new widget_none();
		}
		break;
		case widget_type::widget_type_button:
		{
			w->args = new widget_button();
		}
		break;
		case widget_type::widget_type_checkbox:
		{
			w->args = new widget_checkbox();
		}
		break;
		case widget_type::widget_type_radio_button:
		{
			w->args = new widget_radio_button();
		}
		break;
		case widget_type::widget_type_small_button:
		{
			w->args = new widget_small_button();
		}
		break;
		case widget_type::widget_type_checkbox_flags:
		{
			w->args = new widget_checkbox_flags();
		}
		break;
		case widget_type::widget_type_text:
		{
			w->args = new widget_text();
		}
		break;
		case widget_type::widget_type_text_colored:
		{
			w->args = new widget_text_colored();
		}
		break;
		case widget_type::widget_type_bullet_text:
		{
			w->args = new widget_bullet_text();
		}
		break;
		case widget_type::widget_type_bullet:
		{
			w->args = new widget_bullet();
		}
		break;
		case widget_type::widget_type_selectable:
		{
			w->args = new widget_selectable();
		}
		break;
		case widget_type::widget_type_label_text:
		{
			w->args = new widget_label_text();
		}
		break;
		case widget_type::widget_type_input_text:
		{
			w->args = new widget_input_text();
		}
		break;
		case widget_type::widget_type_input_text_multiline:
		{
			w->args = new widget_input_text_multiline();
		}
		case widget_type::widget_type_input_text_with_hint:
		{
			w->args = new widget_input_text_with_hint();
		}
		break;
		case widget_type::widget_type_input_int:
		{
			w->args = new widget_input_int();
		}
		break;
		case widget_type::widget_type_input_int2:
		{
			w->args = new widget_input_int2();
		}
		break;
		case widget_type::widget_type_input_int3:
		{
			w->args = new widget_input_int3();
		}
		break;
		case widget_type::widget_type_input_int4:
		{
			w->args = new widget_input_int4();
		}
		break;
		case widget_type::widget_type_input_float:
		{
			w->args = new widget_input_float();
		}
		break;
		case widget_type::widget_type_input_float2:
		{
			w->args = new widget_input_float2();
		}
		break;
		case widget_type::widget_type_input_float3:
		{
			w->args = new widget_input_float3();
		}
		break;
		case widget_type::widget_type_input_float4:
		{
			w->args = new widget_input_float4();
		}
		break;
		case widget_type::widget_type_input_double:
		{
			w->args = new widget_input_double();
		}
		break;
		case widget_type::widget_type_drag_int:
		{
			w->args = new widget_drag_int();
		}
		break;
		case widget_type::widget_type_drag_int2:
		{
			w->args = new widget_drag_int2();
		}
		break;
		case widget_type::widget_type_drag_int3:
		{
			w->args = new widget_drag_int3();
		}
		break;
		case widget_type::widget_type_drag_int4:
		{
			w->args = new widget_drag_int4();
		}
		break;
		case widget_type::widget_type_drag_float:
		{
			w->args = new widget_drag_float();
		}
		break;
		case widget_type::widget_type_drag_float2:
		{
			w->args = new widget_drag_float2();
		}
		break;
		case widget_type::widget_type_drag_float3:
		{
			w->args = new widget_drag_float3();
		}
		break;
		case widget_type::widget_type_drag_float4:
		{
			w->args = new widget_drag_float4();
		}
		break;
		case widget_type::widget_type_slider_int:
		{
			w->args = new widget_slider_int();
		}
		break;
		case widget_type::widget_type_slider_int2:
		{
			w->args = new widget_slider_int2();
		}
		break;
		case widget_type::widget_type_slider_int3:
		{
			w->args = new widget_slider_int3();
		}
		break;
		case widget_type::widget_type_slider_int4:
		{
			w->args = new widget_slider_int4();
		}
		break;
		case widget_type::widget_type_slider_float:
		{
			w->args = new widget_slider_float();
		}
		break;
		case widget_type::widget_type_slider_float2:
		{
			w->args = new widget_slider_float2();
		}
		break;
		case widget_type::widget_type_slider_float3:
		{
			w->args = new widget_slider_float3();
		}
		break;
		case widget_type::widget_type_slider_float4:
		{
			w->args = new widget_slider_float4();
		}
		break;
		case widget_type::widget_type_slider_angle:
		{
			w->args = new widget_slider_angle();
		}
		break;
		case widget_type::widget_type_color_edit3:
		{
			w->args = new widget_color_edit3();
		}
		break;
		case widget_type::widget_type_color_edit4:
		{
			w->args = new widget_color_edit4();
		}
		break;
		case widget_type::widget_type_color_picker3:
		{
			w->args = new widget_color_picker3();
		}
		break;
		case widget_type::widget_type_color_picker4:
		{
			w->args = new widget_color_picker4();
		}
		break;
		case widget_type::widget_type_color_button:
		{
			w->args = new widget_color_button();
		}
		break;
		case widget_type::widget_type_list_box:
		{
			w->args = new widget_list_box();
		}
		break;
		case widget_type::widget_type_collapsing_header:
		{
			w->args = new widget_collapsing_header();
		}
		break;
		case widget_type::widget_type_separator:
		{
			w->args = new widget_separator();
		}
		break;
		case widget_type::widget_type_same_line:
		{
			w->args = new widget_same_line();
		}
		break;
		case widget_type::widget_type_spacing:
		{
			w->args = new widget_spacing();
		}
		break;
		case widget_type::widget_type_dummy:
		{
			w->args = new widget_dummy();
		}
		break;
		case widget_type::widget_type_indent:
		{
			w->args = new widget_indent();
		}
		break;
		case widget_type::widget_type_unindent:
		{
			w->args = new widget_unindent();
		}
		break;
		case widget_type::widget_type_begin_end_window:
		{
			w->args = new widget_begin_end_window();
		}
		break;
		case widget_type::widget_type_begin_end_child:
		{
			w->args = new widget_begin_end_child();
		}
		break;
		case widget_type::widget_type_begin_end_popup:
		{
			w->args = new widget_begin_end_popup();
		}
		case widget_type::widget_type_begin_end_list_box:
		{
			w->args = new widget_begin_end_list_box();
		}
		break;
		case widget_type::widget_type_begin_end_table:
		{
			w->args = new widget_begin_end_table();
		}
		break;
		case widget_type::widget_type_push_pop_tree_node:
		{
			w->args = new widget_push_pop_tree_node();
		}
		break;
		case widget_type::widget_type_begin_end_group:
		{
			w->args = new widget_begin_end_group();
		}
		break;
		case widget_type::widget_type_begin_end_combo:
		{
			w->args = new widget_begin_end_combo();
		}
		break;
		case widget_type::widget_type_begin_end_menu:
		{
			w->args = new widget_begin_end_menu();
		}
		}
		return w;
	}

	void delete_widget(widget* target)
	{
		switch (target->type)
		{
			case widget_type::widget_type_none:
			{
				delete (widget_none*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_button:
			{
				delete (widget_button*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_small_button:
			{
				delete (widget_small_button*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_checkbox:
			{
				delete (widget_checkbox*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_checkbox_flags:
			{
				delete (widget_checkbox_flags*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_radio_button:
			{
				delete (widget_radio_button*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_text:
			{
				delete (widget_text*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_text_colored:
			{
				delete (widget_text_colored*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_bullet_text:
			{
				delete (widget_bullet_text*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_bullet:
			{
				delete (widget_bullet*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_selectable:
			{
				delete (widget_selectable*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_label_text:
			{
				delete (widget_label_text*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_input_text:
			{
				delete (widget_input_text*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_input_text_multiline:
			{
				delete (widget_input_text_multiline*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_input_text_with_hint:
			{
				delete (widget_input_text_with_hint*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_input_int:
			{
				delete (widget_input_int*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_input_int2:
			{
				delete (widget_input_int2*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_input_int3:
			{
				delete (widget_input_int3*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_input_int4:
			{
				delete (widget_input_int4*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_input_float:
			{
				delete (widget_input_float*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_input_float2:
			{
				delete (widget_input_float2*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_input_float3:
			{
				delete (widget_input_float3*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_input_float4:
			{
				delete (widget_input_float4*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_input_double:
			{
				delete (widget_input_double*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_drag_int:
			{
				delete (widget_drag_int*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_drag_int2:
			{
				delete (widget_drag_int2*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_drag_int3:
			{
				delete (widget_drag_int3*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_drag_int4:
			{
				delete (widget_drag_int4*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_drag_float:
			{
				delete (widget_drag_float*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_drag_float2:
			{
				delete (widget_drag_float2*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_drag_float3:
			{
				delete (widget_drag_float3*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_drag_float4:
			{
				delete (widget_drag_float4*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_slider_int:
			{
				delete (widget_slider_int*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_slider_int2:
			{
				delete (widget_slider_int2*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_slider_int3:
			{
				delete (widget_slider_int3*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_slider_int4:
			{
				delete (widget_slider_int4*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_slider_float:
			{
				delete (widget_slider_float*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_slider_float2:
			{
				delete (widget_slider_float2*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_slider_float3:
			{
				delete (widget_slider_float3*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_slider_float4:
			{
				delete (widget_slider_float4*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_slider_angle:
			{
				delete (widget_slider_angle*)target->args;
				target->args = nullptr;
			}
			case widget_type::widget_type_color_edit3:
			{
				delete (widget_color_edit3*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_color_edit4:
			{
				delete (widget_color_edit4*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_color_picker3:
			{
				delete (widget_color_picker3*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_color_picker4:
			{
				delete (widget_color_picker4*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_color_button:
			{
				delete (widget_color_button*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_list_box:
			{
				delete (widget_list_box*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_collapsing_header:
			{
				delete (widget_collapsing_header*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_separator:
			{
				delete (widget_separator*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_same_line:
			{
				delete (widget_same_line*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_spacing:
			{
				delete (widget_spacing*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_dummy:
			{
				delete (widget_dummy*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_indent:
			{
				delete (widget_indent*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_unindent:
			{
				delete (widget_unindent*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_begin_end_window:
			{
				delete (widget_begin_end_window*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_begin_end_child:
			{
				delete (widget_begin_end_child*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_begin_end_popup:
			{
				delete (widget_begin_end_popup*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_begin_end_list_box:
			{
				delete (widget_begin_end_list_box*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_begin_end_table:
			{
				delete (widget_begin_end_table*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_begin_end_group:
			{
				delete (widget_begin_end_group*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_begin_end_combo:
			{
				delete (widget_begin_end_combo*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_begin_end_menu:
			{
				delete (widget_begin_end_menu*)target->args;
				target->args = nullptr;
			}
			break;
			case widget_type::widget_type_push_pop_tree_node:
			{
				delete (widget_push_pop_tree_node*)target->args;
				target->args = nullptr;
			}
			break;
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
