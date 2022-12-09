#include "Precompiled.h"
#include "editor/widget.h"
#include "editor/widget/args_data.h"

namespace imgui_editor
{
	void delete_widget_args(widget_type type, void* target)
	{
		switch (type)
		{
		case widget_type::widget_type_none:						delete (widget_none*)target;					break;

		// Windows
		case widget_type::widget_type_begin_end_window:			delete (widget_begin_end_window*)target;		break;
		case widget_type::widget_type_begin_end_child:			delete (widget_begin_end_child*)target;			break;

		// Parameters stacks (current window)
		case widget_type::widget_type_push_pop_item_width:		delete (widget_push_pop_item_width*)target;		break;
		case widget_type::widget_type_push_pop_text_wrap_pos:	delete (widget_push_pop_text_wrap_pos*)target;	break;

		// Cursor / Layout
		case widget_type::widget_type_separator:				delete (widget_separator*)target;				break;
		case widget_type::widget_type_same_line:				delete (widget_same_line*)target;				break;
		case widget_type::widget_type_spacing:					delete (widget_spacing*)target;					break;
		case widget_type::widget_type_dummy:					delete (widget_dummy*)target;					break;
		case widget_type::widget_type_indent:					delete (widget_indent*)target;					break;
		case widget_type::widget_type_unindent:					delete (widget_unindent*)target;				break;
		case widget_type::widget_type_begin_end_group:			delete (widget_begin_end_group*)target;			break;

		// Widgets: Text
		case widget_type::widget_type_text:						delete (widget_text*)target;					break;
		case widget_type::widget_type_text_colored:				delete (widget_text_colored*)target;			break;
		case widget_type::widget_type_label_text:				delete (widget_label_text*)target;				break;
		case widget_type::widget_type_bullet_text:				delete (widget_bullet_text*)target;				break;

		// Widgets: Main
		case widget_type::widget_type_button:					delete (widget_button*)target;					break;
		case widget_type::widget_type_small_button:				delete (widget_small_button*)target;			break;
		case widget_type::widget_type_checkbox:					delete (widget_checkbox*)target;				break;
		case widget_type::widget_type_checkbox_flags:			delete (widget_checkbox_flags*)target;			break;
		case widget_type::widget_type_radio_button:				delete (widget_radio_button*)target;			break;
		case widget_type::widget_type_bullet:					delete (widget_bullet*)target;					break;

		 // Widgets: Combo Box
		case widget_type::widget_type_begin_end_combo:			delete (widget_begin_end_combo*)target;			break;

		// Widgets: Drag Sliders
		case widget_type::widget_type_drag_float:				delete (widget_drag_float*)target;				break;
		case widget_type::widget_type_drag_float2:				delete (widget_drag_float2*)target;				break;
		case widget_type::widget_type_drag_float3:				delete (widget_drag_float3*)target;				break;
		case widget_type::widget_type_drag_float4:				delete (widget_drag_float4*)target;				break;
		case widget_type::widget_type_drag_int:					delete (widget_drag_int*)target;				break;
		case widget_type::widget_type_drag_int2:				delete (widget_drag_int2*)target;				break;
		case widget_type::widget_type_drag_int3:				delete (widget_drag_int3*)target;				break;
		case widget_type::widget_type_drag_int4:				delete (widget_drag_int4*)target;				break;

		// Widgets: Regular Sliders
		case widget_type::widget_type_slider_float:				delete (widget_slider_float*)target;			break;
		case widget_type::widget_type_slider_float2:			delete (widget_slider_float2*)target;			break;
		case widget_type::widget_type_slider_float3:			delete (widget_slider_float3*)target;			break;
		case widget_type::widget_type_slider_float4:			delete (widget_slider_float4*)target;			break;
		case widget_type::widget_type_slider_angle:				delete (widget_slider_angle*)target;			break;
		case widget_type::widget_type_slider_int:				delete (widget_slider_int*)target;				break;
		case widget_type::widget_type_slider_int2:				delete (widget_slider_int2*)target;				break;
		case widget_type::widget_type_slider_int3:				delete (widget_slider_int3*)target;				break;
		case widget_type::widget_type_slider_int4:				delete (widget_slider_int4*)target;				break;

   		// Widgets: Input with Keyboard
		case widget_type::widget_type_input_text:				delete (widget_input_text*)target;				break;
		case widget_type::widget_type_input_text_multiline:		delete (widget_input_text_multiline*)target;	break;
		case widget_type::widget_type_input_text_with_hint:		delete (widget_input_text_with_hint*)target;	break;
		case widget_type::widget_type_input_float:				delete (widget_input_float*)target;				break;
		case widget_type::widget_type_input_float2:				delete (widget_input_float2*)target;			break;
		case widget_type::widget_type_input_float3:				delete (widget_input_float3*)target;			break;
		case widget_type::widget_type_input_float4:				delete (widget_input_float4*)target;			break;
		case widget_type::widget_type_input_int:				delete (widget_input_int*)target;				break;
		case widget_type::widget_type_input_int2:				delete (widget_input_int2*)target;				break;
		case widget_type::widget_type_input_int3:				delete (widget_input_int3*)target;				break;
		case widget_type::widget_type_input_int4:				delete (widget_input_int4*)target;				break;
		case widget_type::widget_type_input_double:				delete (widget_input_double*)target;			break;

		// Widgets: Color Editor/Picker 
		case widget_type::widget_type_color_edit3:				delete (widget_color_edit3*)target;				break;
		case widget_type::widget_type_color_edit4:				delete (widget_color_edit4*)target;				break;
		case widget_type::widget_type_color_picker3:			delete (widget_color_picker3*)target;			break;
		case widget_type::widget_type_color_picker4:			delete (widget_color_picker4*)target;			break;
		case widget_type::widget_type_color_button:				delete (widget_color_button*)target;			break;

    	// Widgets: Trees
		case widget_type::widget_type_push_pop_tree_node:		delete (widget_push_pop_tree_node*)target;		break;
		case widget_type::widget_type_collapsing_header:		delete (widget_collapsing_header*)target;		break;

		// Widgets: Selectables
		case widget_type::widget_type_selectable:				delete (widget_selectable*)target;				break;

		// Widgets: List Boxes
		case widget_type::widget_type_begin_end_list_box:		delete (widget_begin_end_list_box*)target;		break;

		// Widgets: Menus
		case widget_type::widget_type_begin_end_menu:			delete (widget_begin_end_menu*)target;			break;

    	// Popups, Modals
		case widget_type::widget_type_begin_end_popup:			delete (widget_begin_end_popup*)target;			break;

		// Tables
		case widget_type::widget_type_begin_end_table:			delete (widget_begin_end_table*)target;			break;
		}
	}
}