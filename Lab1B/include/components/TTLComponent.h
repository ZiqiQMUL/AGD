#pragma once

class TTLComponent
{
public:
	TTLComponent() = delete;
	TTLComponent(int _TTL) :ttl(_TTL) {}
	void update(class Game* _Game, class Entity* _Ent, float _Elapsed) { if (ttl > 0) --ttl; else ttl = 0; }
	int getTTL()const { return ttl; }
private:
	int ttl;
};