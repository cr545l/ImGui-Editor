#ifndef __WIDGET_EDITOR_H__
#define __WIDGET_EDITOR_H__

#include "editor/widget.h"

//
// # TODO
// 
// - font size의 상대값을 가지고 사이즈 처리
// - 별도의 라이브러리에 실시간 c++ 코드 컴파일 및 로드 테스트
// - C++에서 C로 완전히 전환
// - foramt 서식을 공통으로 두고 serialize / deserialize 와 버전관리가 한꺼번에 될 수 있도록 처리
// - 앵커 기반의 이동처리
// - imgui-editor의 멀티 뷰 처리
//
namespace imgui_editor
{
	struct widget;
	struct widget_editor;
	struct history;

	struct widget_tool
	{
		widget_editor* editor = nullptr;
		widget* root = nullptr;
		widget_type type = widget_type::widget_type_none;
	};

	struct widget_hierarchy
	{
		widget_editor* editor = nullptr;
		widget* root = nullptr;
	};

	struct widget_inspector
	{
		widget_editor* editor = nullptr;
		std::string input;
	};

	struct project_context
	{
		bool ready = false;
		std::string absolutePath;
		widget* root = nullptr;
	};

	struct widget_editor
	{
		widget* root;
		project_context project;

		widget_tool tool;
		widget_hierarchy hirarchy;
		widget_inspector inspector;

		std::vector<std::string> last_open_paths;
	};
	std::string normalizeUTF8(const std::string& input);

	void initialize(widget_editor* context, const char* init);
	bool open_project(widget_editor *ctx, const char *path);
	void close_project(widget_editor *ctx);

	void draw_start_page(widget_editor* context);
	void draw_tool(widget_tool* context);
	void draw_hierarchy(widget_hierarchy* context);
	void draw_inspector(widget_inspector* context);
	void draw_histroy(history* ctx);

	void draw(widget_editor* context, history* history);
}

#endif
