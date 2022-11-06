#ifndef __CR_WIDGET_EDITOR_H__
#define __CR_WIDGET_EDITOR_H__

#include "Editor/CrWidget.h"

class CrWidgetEditor;

class CrWidgetTool
{
public:
	CrWidgetTool(CrWidgetEditor* editor) :_editor(editor) {}

	void OnGUI();

	void SetRoot(CrWidget* target) { _root = target; }

private:
	CrWidgetEditor* _editor = nullptr;
	CrWidget* _root = nullptr;

	CrWidget::Type _type = CrWidget::Type::None;
};

class CrWidgetHirarchy
{
public:
	CrWidgetHirarchy(CrWidgetEditor* editor) :_editor(editor) {}

	void OnGUI();

	void SetTarget(CrWidget* target) { _target = target; }

private:
	CrWidgetEditor* _editor = nullptr;
	CrWidget* _target = nullptr;
};

class CrWidgetInspector
{
public:
	CrWidgetInspector(CrWidgetEditor* editor) :_editor(editor) {}

	void OnGUI();	

private:
	CrWidgetEditor* _editor = nullptr;
};

class CrWidgetEditor
{
public:
	CrWidgetEditor() :_tool(this), _hirarchy(this), _inspector(this) {}

	void Initialize();
	void Finalize();

	void OnGUI();

private:
	CrWidget _root;

	CrWidgetTool _tool;
	CrWidgetHirarchy _hirarchy;
	CrWidgetInspector _inspector;
};

#endif
