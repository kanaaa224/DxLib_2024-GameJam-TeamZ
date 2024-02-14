#include"Collider.h"

Collider::Collider(Vector2D location, Vector2D size) : location(location) , size(size)
{
}

bool Collider::Hit(Collider* collider)const
{
	float sx1 = this->location.x;
	float sx2 = this->location.x + this->size.x;
	float sy1 = this->location.y;
	float sy2 = this->location.y + this->size.x;

	float dx1 = collider->location.x;
	float dx2 = collider->location.x + collider->size.x;
	float dy1 = collider->location.y;
	float dy2 = collider->location.y + collider->size.y;

	//‹éŒ`‚ªd‚È‚Á‚Ä‚¢‚ê‚Î“–‚½‚è
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2)return true;
	return false;
}

Vector2D Collider::GetLocation()const
{
	return location;
}

Vector2D Collider::GetSize()const
{
	return size;
}