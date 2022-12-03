#include "Precompiled.h"

#include <algorithm>

#include "editor/selection.h"
#include "editor/widget_editor.h"
#include "editor/widget.h"

namespace imgui_editor
{
	void draw_widget_hierarchy(widget_hierarchy *context)
	{
		auto selected = selection::get_targets();
		std::function<void(widget *)> drawNode = [&](widget *_widget)
		{
			ImGui::PushID(_widget->label.c_str());
			ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_OpenOnDoubleClick;

			if (std::any_of(selected.begin(), selected.end(), [&](widget *w)
							{ return w == _widget; }))
			{
				flag |= ImGuiTreeNodeFlags_Selected;
			}

			if (_widget )
            { 
                bool showChildren = ImGui::TreeNodeEx(_widget->label.c_str(), flag,"%s (%s)", _widget->label.c_str(), get_pretty_name(_widget->type));
                if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                {
                    selection::select(_widget);
                }
                if (ImGui::BeginPopupContextItem())
                {
                    ImGui::Text(_widget->label.c_str());
                    ImGui::Separator();
                    if(ImGui::MenuItem("Delete"))
                    {
                        remove_widget(_widget);
                    }
                    ImGui::EndPopup();
                }

                if(showChildren)
                {
                    const auto &children = _widget->children;
                    for (size_t i = 0, max = children.size(); i < max; ++i)
                    {
                        ImGui::PushID(i);
                        drawNode(children[i]);
                        ImGui::PopID();
                    }
                    ImGui::TreePop();
                }
            }
			ImGui::PopID();
		};

		drawNode(context->root);

        
	}
}