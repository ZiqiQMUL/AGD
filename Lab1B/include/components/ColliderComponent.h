#pragma once
#include "../utils/Rectangle.h"

class ColliderComponent
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

	void update(Game* _Game, Entity* _Ent, float _Elapsed)
	{
		auto position = _Ent->getPosition();
		boundingBox.setTopLeft(position);
		boundingBox.setBottomRight(position + bboxSize);
	}

private:
	Rectangle boundingBox;
	Vector2f bboxSize;
};