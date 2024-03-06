#pragma once

#include "../utils/Rectangle.h"
#include "../entities/Entity.h"
#include "../graphics/Window.h"


class BoxColliderComponent :public Component
{
public:
    BoxColliderComponent() {}
    ~BoxColliderComponent() {}
    void init(const Vector2f& position, const Vector2f& bboxSize);  //Assigns the size of the box.
    bool interesects(const BoxColliderComponent& boxCollider) const;  //Checks the intersection between "this" and cc box collider components.
    auto& getDrawableRect()
    {
        return boundingBox.getDrawableRect();
    }
    void setBoxPosition(const Vector2f& _Position); //sets the bounding box position to the current position of the entity.

    ComponentID getID()const override { return ComponentID::COLLIDER; }

private:
    Rectangle boundingBox;
    Vector2f bboxSize;
};

