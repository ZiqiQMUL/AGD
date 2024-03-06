#include "../components/ColliderComponent.h"

void BoxColliderComponent::init(const Vector2f& _Position, const Vector2f& _BboxSize)
{
	boundingBox.setTopLeft(_Position);
	boundingBox.setBottomRight(_Position + _BboxSize);
	bboxSize = _BboxSize;
}

bool BoxColliderComponent::interesects(const BoxColliderComponent& boxCollider) const
{
	return boundingBox.interesects(boxCollider.boundingBox);
}

void BoxColliderComponent::setBoxPosition(const Vector2f& position)
{
	boundingBox.setTopLeft(position);
	boundingBox.setBottomRight(position + bboxSize);
}
