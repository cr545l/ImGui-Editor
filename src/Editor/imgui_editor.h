#ifndef __IMGUI_EDITOR_H__
#define __IMGUI_EDITOR_H__

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
	struct imgui_editor_context;
	struct history;
	
	struct project_context
	{
		bool ready = false;
		bool dirty = false;
		std::string absolutePath;
		widget* root = nullptr;
	};

	struct imgui_editor_context
	{
		widget* root;
		project_context project;
		
		std::vector<std::string> last_open_paths;

		widget_type create_widget_type = widget_type::widget_type_none;
		std::string import_text;
	};

	imgui_editor_context* get_context();

	void initialize_editor(imgui_editor_context* ctx, const char* init);
	bool open_project(imgui_editor_context *ctx, const char *path);
	void close_project(imgui_editor_context *ctx);

	void draw_start_page(imgui_editor_context* context);
	void draw_tool(imgui_editor_context* context);
	void draw_hierarchy(const imgui_editor_context* editor_context);
	void draw_inspector(imgui_editor_context* context);
	void draw_history(history* ctx);

	void draw_editor_context(imgui_editor_context* ctx, history* history);
}

#endif
