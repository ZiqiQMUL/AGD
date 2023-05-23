#pragma once
#include "../utils/Rectangle.h"
#include "Components.h"

class ColliderComponent :public Component
{
public:
	ColliderComponent() = default;
	void init(const Vector2f& _Position,const Vector2f& _BboxSize)
	{
		boundingBox.setTopLeft(_Position);
		boundingBox.setBottomRight(_Position + _BboxSize);
		bboxSize = _BboxSize;
	}
	bool interesects(const ColliderComponent& _Rhs)const
	{
		return boundingBox.intersects(_Rhs.boundingBox);
	}

	auto& getDrawableRect()
	{
		return boundingBox.getDrawableRect();
	}

	void setBox(const Vector2f& _Position)
	{
		boundingBox.setTopLeft(_Position);
		boundingBox.setBottomRight(_Position + bboxSize);
	}
	ComponentID getID()override { return ComponentID::COLLIDER; }

private:
	Rectangle boundingBox;
	Vector2f bboxSize;
};