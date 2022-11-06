#include "GameObject.h"

namespace ToyEngine{
	class Component
	{
	public:
		virtual void tick() = 0;
		virtual void init() = 0;
	protected:
		GameObject mGameObject;
	};
}

