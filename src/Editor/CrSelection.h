#ifndef __CR_SELECTION_H__
#define __CR_SELECTION_H__

#include "Editor/CrHistory.h"

class CrWidget;

class CrSelection
{
public:
	class Select: public CrCommand
	{
	public:
		Select(CrWidget* select)
		{
			_select = select;
			_selects.push_back(select);
			_original = select;
			_originals = _targets;
		}

		Select(std::initializer_list<CrWidget*> selects)
		{
			assert(0 < selects.size());
			for(auto target : selects)
			{
				if (nullptr == _select) _select = target;
				_selects.push_back(target);
			}
			_original = _target;
			_originals = selects;
		}

		void Redo() override
		{
			_target = _select;
			_targets = _selects;
		}

		void Undo() override
		{
			_target = _original;
			_targets = _originals;
		}

	private:
		CrWidget* _select = nullptr;
		std::vector<CrWidget*> _selects;

		CrWidget* _original = nullptr;
		std::vector<CrWidget*> _originals;
	};

	static CrWidget* GetTarget() { return _target; }
	static const std::vector<CrWidget*>& GetTargets() { return _targets; }

private:
	static CrWidget* _target;
	static std::vector<CrWidget*> _targets;
};

#endif