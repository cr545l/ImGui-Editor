#ifndef __CR_WIDGET_H__
#define __CR_WIDGET_H__

#include "CrHistory.h"

class CrWidgetValue
{
public:
	virtual void* GetValue() = 0;

	template<typename T>
	T* GetValue() { return static_cast<T*>(GetValue()); }
};

class CrWidgetValueBool : public CrWidgetValue
{
public:
	bool value;

	void* GetValue() override { return &value; }
};

class CrWidget
{
public:
	enum class Type
	{
		None,
		Window,

		Button,
		Checkbox,
		RadioButton,
	};

	class AttachChild :public CrCommand
	{
	public:
		AttachChild(CrWidget* parent, CrWidget* child)
		{
			_parent = parent;
			_child = child;
		}

		void Redo()	override
		{
			_parent->_children.push_back(_child);
			_index = _parent->_children.size()-1;
		}

		void Undo() override
		{
			_parent->_children.erase(_parent->_children.begin() + _index);
		}

	private:
		CrWidget* _parent;
		CrWidget* _child;
		size_t _index;
	};

	static CrWidget* New(Type type);

	std::string label = "empty";

	CrWidgetValue* value = nullptr;

	CrWidget();
	virtual ~CrWidget();

	ImGuiID GetID() const { return ImGui::GetID(label.c_str()); }

	virtual void OnGUI();
	virtual void OnInspectorGUI();


	const std::vector<CrWidget*>& GetChildren() { return _children; }

protected:
	void drawChildren();

	std::vector<CrWidget*> _children;	
};

namespace Widget
{
	class Window : public CrWidget
	{
	public:
		Window() = default;
		~Window() = default;

		void OnGUI() override;
	};

	class Button : public CrWidget
	{
	public:
		Button() = default;
		~Button() = default;

		void OnGUI() override;
	};

	class Checkbox : public CrWidget
	{
	public:
		Checkbox()
		{
			value = new CrWidgetValueBool();
		}
		~Checkbox()
		{
			delete value;
		}

		void OnGUI() override;
	};

	class RadioButton : public CrWidget
	{
	public:
		RadioButton()
		{
			value = new CrWidgetValueBool();
		}
		~RadioButton()
		{
			delete value;
		}

		void OnGUI() override;
	};	
}

#endif
