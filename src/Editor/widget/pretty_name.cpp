#include "Precompiled.h"
#include "editor/widget.h"

namespace imgui_editor
{
	const char* get_pretty_name(widget_type type)
	{
		switch (type)
		{
		case widget_type::widget_type_none:						return "None";

		// Windows
		case widget_type::widget_type_begin_end_window:			return "Begin End Window";
		case widget_type::widget_type_begin_end_child: 			return "Begin End Child";

		// Parameters stacks (current window)
		case widget_type::widget_type_push_pop_item_width: 		return "Push Pop Item Width";
		case widget_type::widget_type_push_pop_text_wrap_pos: 	return "Push Pop Text Wrap Pos";

		// Cursor / Layout
		case widget_type::widget_type_separator:				return "Separator";
		case widget_type::widget_type_same_line:				return "Same Line";
		case widget_type::widget_type_spacing:					return "Spacing";
		case widget_type::widget_type_dummy:					return "Dummy";
		case widget_type::widget_type_indent:					return "Indent";
		case widget_type::widget_type_unindent:					return "Unindent";
		case widget_type::widget_type_begin_end_group: 			return "Begin End Group";

		// Widgets: Text
		case widget_type::widget_type_text:						return "Text";
		case widget_type::widget_type_text_colored:				return "Text Colored";
		case widget_type::widget_type_label_text:				return "Label Text";
		case widget_type::widget_type_bullet_text:				return "Bullet Text";

		// Widgets: Main
        case widget_type::widget_type_button:					return "Button";
		case widget_type::widget_type_small_button:				return "Small Button";
		case widget_type::widget_type_checkbox:					return "Checkbox";
		case widget_type::widget_type_checkbox_flags:			return "Checkbox Flags";
		case widget_type::widget_type_radio_button:				return "Radio Button";
		case widget_type::widget_type_bullet:					return "Bullet";

		// Widgets: Combo Box
		case widget_type::widget_type_begin_end_combo: 			return "Begin End Combo";

		// Widgets: Drag Sliders
		case widget_type::widget_type_drag_float:				return "Drag Float";
		case widget_type::widget_type_drag_float2:				return "Drag Float2";
		case widget_type::widget_type_drag_float3:				return "Drag Float3";
		case widget_type::widget_type_drag_float4:				return "Drag Float4";
		case widget_type::widget_type_drag_int:					return "Drag Int";
		case widget_type::widget_type_drag_int2:				return "Drag Int2";
		case widget_type::widget_type_drag_int3:				return "Drag Int3";
		case widget_type::widget_type_drag_int4:				return "Drag Int4";
        
		// Widgets: Regular Sliders
		case widget_type::widget_type_slider_float:				return "Slider Float";
		case widget_type::widget_type_slider_float2:			return "Slider Float2";
		case widget_type::widget_type_slider_float3:			return "Slider Float3";
		case widget_type::widget_type_slider_float4:			return "Slider Float4";
		case widget_type::widget_type_slider_angle:				return "Slider Angle";
		case widget_type::widget_type_slider_int:				return "Slider Int";
		case widget_type::widget_type_slider_int2:				return "Slider Int2";
		case widget_type::widget_type_slider_int3:				return "Slider Int3";
		case widget_type::widget_type_slider_int4:				return "Slider Int4";

		// Widgets: Input with Keyboard
		case widget_type::widget_type_input_text:				return "Input Text";
		case widget_type::widget_type_input_text_multiline:		return "Input Text Multiline";
		case widget_type::widget_type_input_text_with_hint:		return "Input Text With Hint";
		case widget_type::widget_type_input_float:				return "Input Float";
		case widget_type::widget_type_input_float2:				return "Input Float2";
		case widget_type::widget_type_input_float3:				return "Input Float3";
		case widget_type::widget_type_input_float4:				return "Input Float4";
		case widget_type::widget_type_input_int:				return "Input Int";
		case widget_type::widget_type_input_int2:				return "Input Int2";
		case widget_type::widget_type_input_int3:				return "Input Int3";
		case widget_type::widget_type_input_int4:				return "Input Int4";
		case widget_type::widget_type_input_double:				return "Input Double";

		// Widgets: Color Editor/Picker 
		case widget_type::widget_type_color_edit3:				return "Color Edit3";
		case widget_type::widget_type_color_edit4:				return "Color Edit4";
		case widget_type::widget_type_color_picker3:			return "Color Picker3";
		case widget_type::widget_type_color_picker4:			return "Color Picker4";
		case widget_type::widget_type_color_button:				return "Color Button";

		// Widgets: Trees
		case widget_type::widget_type_push_pop_tree_node: 		return "Push Pop Tree Node";
		case widget_type::widget_type_collapsing_header:		return "Collapsing Header";

		// Widgets: Selectables
		case widget_type::widget_type_selectable:				return "Selectable";

		// Widgets: List Boxes
		case widget_type::widget_type_begin_end_list_box: 		return "Begin End List Box";

		// Widgets: Menus
		case widget_type::widget_type_begin_end_menu: 			return "Begin End Menu";

		// Popups, Modals
		case widget_type::widget_type_begin_end_popup: 			return "Begin End Popup";
        
		// Tables
		case widget_type::widget_type_begin_end_table: 			return "Begin End Table";
		}
		return "";
	}
}