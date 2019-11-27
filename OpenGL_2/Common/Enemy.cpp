#include "Enemy.h"
/////////////////////Enemy
Enemy::~Enemy() {
	if (_transform != NULL) delete _transform;
}

void Enemy::SetTRSMatrix(mat4 &mat)
{
	_transform->SetTRSMatrix(mat);
}

void Enemy::SetColor(GLfloat vColor[4], bool hurt) {
	if (hurt)_transform->SetHurtColor(vColor);
	else _transform->SetColor(vColor);
}

GLboolean Enemy::CheckCollider(Collider one, Collider two) {
	bool collisionX = (one.leftButtom.x <= two.rightTop.x && one.leftButtom.x >= two.leftButtom.x) ||
		(one.rightTop.x <= two.rightTop.x && one.rightTop.x >= two.leftButtom.x) ||
		(two.leftButtom.x <= one.rightTop.x && two.leftButtom.x >= one.leftButtom.x) ||
		(two.rightTop.x <= one.rightTop.x && two.rightTop.x >= one.leftButtom.x);
	bool collisionY = (one.leftButtom.y <= two.rightTop.y && one.leftButtom.y >= two.leftButtom.y) ||
		(one.rightTop.y <= two.rightTop.y && one.rightTop.y >= two.leftButtom.y) ||
		(two.leftButtom.y <= one.rightTop.y && two.leftButtom.y >= one.leftButtom.y) ||
		(two.rightTop.y <= one.rightTop.y && two.rightTop.y >= one.leftButtom.y);
	return collisionX&&collisionY;

}

void Enemy::SetHurt(float delta) {
	if (_collider.isHurt) {
		if (hurtColorTime == 0.0f)SetColor(vec4(0.4f, 0.0f, 0.0f, 0.0f), true);

		hurtColorTime += delta;

		if (hurtColorTime >= 0.2f) {
			SetColor(vec4(-0.4f, 0.0f, 0.0f, 0.0f), true);
			hurtColorTime = 0.0f;
			_collider.isHurt = false;
		}
	}
}


/////////////////////Enemy1
Enemy1::Enemy1(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	Num = 1;
	Create();
	_collider.Init(1.5f, 2.25f);
	_transform = new Transform(matModelView, matProjection, 47, _points, _colors);
	SetEnemy();

	_bulletLink = new BulletLink(10, matModelView, matProjection);

	hp = 5;
	_collider.hp = hp;
}

Enemy1::~Enemy1() {
	if (_bulletLink != NULL) delete _bulletLink;
}

void Enemy1::Create() {
	//Body
	_points[0] = point4(-1.25f, 1.5f, 0.0f, 1.0f);
	_points[1] = point4(1.25f, 1.5f, 0.0f, 1.0f);
	_points[2] = point4(1.25f, -1.5f, 0.0f, 1.0f);
	_points[3] = point4(-1.25f, 1.5f, 0.0f, 1.0f);
	_points[4] = point4(1.25f, -1.5f, 0.0f, 1.0f);
	_points[5] = point4(-1.25f, -1.5f, 0.0f, 1.0f);

	_colors[0] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[1] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[2] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[3] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[4] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[5] = color4(0.25f, 0.25f, 0.25f, 1.0f);

	//Head
	for (int i = 6; i < 26; i++)
	{
		_points[i] = point4(0.1f*cosf(M_PI*2.0*(i - 6) / 20), 0.1f* sinf(M_PI*2.0*(i - 6) / 20), 0.0f, 0.1f);
		_colors[i] = color4(1.0f, 0.5f, 0.25f, 1.0f);
	}

	//Eyes
	_points[26] = point4(0.25f, 0.0f, 0.0f, 1.0f);
	_points[27] = point4(0.75f, 0.25f, 0.0f, 1.0f);
	_points[28] = point4(0.5f, -0.25f, 0.0f, 1.0f);
	_points[29] = point4(-0.25f, 0.0f, 0.0f, 1.0f);
	_points[30] = point4(-0.75f, 0.25f, 0.0f, 1.0f);
	_points[31] = point4(-0.5f, -0.25f, 0.0f, 1.0f);

	_colors[26] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[27] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[28] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[29] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[30] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[31] = color4(0.25f, 0.25f, 0.25f, 1.0f);

	//Buttom
	_points[32] = point4(-1.25f, -1.5f, 0.0f, 1.0f);
	_points[33] = point4(1.25f, -1.5f, 0.0f, 1.0f);
	_points[34] = point4(0.0f, -2.25f, 0.0f, 1.0f);

	_colors[32] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[33] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[34] = color4(0.75f, 0.25f, 0.25f, 1.0f);

	//Top
	_points[35] = point4(-1.75f, 2.25f, 0.0f, 1.0f);
	_points[36] = point4(1.75f, 2.25f, 0.0f, 1.0f);
	_points[37] = point4(1.25f, 1.5f, 0.0f, 1.0f);
	_points[38] = point4(-1.75f, 2.25f, 0.0f, 1.0f);
	_points[39] = point4(1.25f, 1.5f, 0.0f, 1.0f);
	_points[40] = point4(-1.25f, 1.5f, 0.0f, 1.0f);

	_colors[35] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[36] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[37] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[38] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[39] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[40] = color4(0.75f, 0.25f, 0.25f, 1.0f);

	//Triangle
	_points[41] = point4(1.25f, 1.0f, 0.0f, 1.0f);
	_points[42] = point4(1.75f, 1.0f, 0.0f, 1.0f);
	_points[43] = point4(1.25f, -1.0f, 0.0f, 1.0f);
	_points[44] = point4(-1.25f, 1.0f, 0.0f, 1.0f);
	_points[45] = point4(-1.75f, 1.0f, 0.0f, 1.0f);
	_points[46] = point4(-1.25f, -1.0f, 0.0f, 1.0f);

	_colors[41] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[42] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[43] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[44] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[45] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[46] = color4(0.75f, 0.25f, 0.25f, 1.0f);
}

void Enemy1::Draw() {
	_bulletLink->Draw();
	_transform->Draw();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 20);
	glDrawArrays(GL_TRIANGLES, 26, 3);
	glDrawArrays(GL_TRIANGLES, 29, 3);
	glDrawArrays(GL_TRIANGLES, 32, 3);
	glDrawArrays(GL_TRIANGLES, 35, 6);
	glDrawArrays(GL_TRIANGLES, 41, 3);
	glDrawArrays(GL_TRIANGLES, 44, 3);
}

void Enemy1::Update(float delta) {
	shootTime += delta;
	if (shootTime >= 2.0f && (_bulletLink->useCount < _bulletLink->totalCount) && _pos.y<15.0f&&_pos.y>-15.0f&&_pos.x<15.0f&&_pos.x>-15.0f) {
		_bulletLink->Shoot(delta, vec4(_pos.x,_pos.y-2.25f,0.0f,1.0f));
		shootTime = 0;
	}	

	_bulletLink->DetectEnemyBullet();

	hurtTime += delta;
	if (hurtTime>=1.0f) {
		PlayerHurt();
		hurtTime = 0.0f;
	}

	EnemyMove(delta);

	SetHurt(delta);

	if (_collider.isDestroy) {
		gameManager->_enemyCount_1++;
		Print(gameManager->Level);
		SetEnemy();
		_collider.hp = 5;
		_collider.isDestroy = false;
	}
}

void Enemy1::SetPosition(vec4 position) {
	mat4 mT;
	_pos = position;
	mT = Translate(_pos);
	SetTRSMatrix(mT);
	_collider.SetCollider(_pos);
}

void Enemy1::EnemyMove(float delta) {
	mat4 mPLT;
	_pos.y -= 3 * delta;
	
	mPLT = Translate(_pos.x, _pos.y, 0.0f);
	SetPosition(_pos);
	SetTRSMatrix(mPLT);
	if (_pos.y <= -15.0f) {
		SetEnemy();
	}
}

void Enemy1::SetEnemy() {
	int a = rand() % 15;
	int b = rand() % 10;
	while (b == preX) {
		b = rand() % 10;
	}
	preX = b;
	_pos.x = (b - 5)*2.0f;
	_pos.y = a*1.0f +15.0f;
	SetPosition(_pos);
}

void Enemy1::PlayerHurt() {
	int Count = 0;
	if (CheckCollider(_collider, *playerCollider))
	{
		if (Count <= 0) {
			playerCollider->hp -= 1;
			Count++;
			//Print(playerCollider->hp);
		}		
	}
}

/////////////////////Enemy2
Enemy2::Enemy2(mat4& matModelView, mat4& matProjection, GLuint shaderHandle) {
	Num = 2;
	Create();
	_collider.Init(1.25f, 2.25f);
	_transform = new Transform(matModelView, matProjection, 9, _points, _colors);
	SetEnemy();

	_bulletLink = new BulletLink(10, matModelView, matProjection);

	hp = 5;
	_collider.hp = hp;
}

Enemy2::~Enemy2() {
	if (_bulletLink != NULL) delete _bulletLink;
}

void Enemy2::Create() {
	//Body
	_points[0] = point4(-1.25f, 1.5f, 0.0f, 1.0f);
	_points[1] = point4(1.25f, 1.5f, 0.0f, 1.0f);
	_points[2] = point4(1.25f, -1.5f, 0.0f, 1.0f);
	_points[3] = point4(-1.25f, 1.5f, 0.0f, 1.0f);
	_points[4] = point4(1.25f, -1.5f, 0.0f, 1.0f);
	_points[5] = point4(-1.25f, -1.5f, 0.0f, 1.0f);

	_colors[0] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[1] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[2] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[3] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[4] = color4(0.25f, 0.25f, 0.25f, 1.0f);
	_colors[5] = color4(0.25f, 0.25f, 0.25f, 1.0f);

	//Buttom
	_points[6] = point4(-1.25f, -1.5f, 0.0f, 1.0f);
	_points[7] = point4(1.25f, -1.5f, 0.0f, 1.0f);
	_points[8] = point4(0.0f, -2.25f, 0.0f, 1.0f);

	_colors[6] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[7] = color4(0.75f, 0.25f, 0.25f, 1.0f);
	_colors[8] = color4(0.75f, 0.25f, 0.25f, 1.0f);
}

void Enemy2::Draw() {
	_bulletLink->Draw();
	_transform->Draw();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawArrays(GL_TRIANGLES, 6, 3);
}

void Enemy2::Update(float delta) {


	shootTime += delta;
	if (shootTime >= 2.0f && (_bulletLink->useCount < _bulletLink->totalCount - 1) && _pos.y<15.0f&&_pos.y>-15.0f&&_pos.x<15.0f&&_pos.x>-15.0f) {
		_bulletLink->Shoot(0, delta, _pos);
		_bulletLink->Shoot(1, delta, _pos);
		shootTime = 0;
	}

	_bulletLink->DetectEnemy2Bullet(delta);


	hurtTime += delta;
	if (hurtTime >= 1.0f) {
		PlayerHurt();
		hurtTime = 0.0f;
	}
	
	EnemyMove(delta);

	SetHurt(delta);

	if (_collider.isDestroy) {
		gameManager->_enemyCount_2++;
		SetEnemy();
		_collider.hp = 5;
		_collider.isDestroy = false;
	}
}

void Enemy2::SetPosition(vec4 position) {
	mat4 mT;
	_pos = position;
	mT = Translate(_pos);
	SetTRSMatrix(mT);
	_collider.SetCollider(_pos);
}

void Enemy2::EnemyMove(float delta) {
	mat4 mPLT;
	_pos.y -= 3 * delta;

	mPLT = Translate(_pos.x, _pos.y, 0.0f);
	SetPosition(_pos);
	SetTRSMatrix(mPLT);
	if (_pos.y <= -15.0f) {
		SetEnemy();
	}
}

void Enemy2::SetEnemy() {
	int a = rand() % 15;
	int b = rand() % 10;
	while (b == preX) {
		b = rand() % 10;
	}
	preX = b;
	_pos.x = (b - 5)*2.0f;
	_pos.y = (a + 1) *2.0f + 15.0f;
	SetPosition(_pos);
}

void Enemy2::PlayerHurt() {
	int Count = 0;
	if (CheckCollider(_collider, *playerCollider))
	{
		if (Count <= 0) {
			playerCollider->hp -= 1;
			Count++;
			//Print(playerCollider->hp);
		}
	}
}