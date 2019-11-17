#include "../Header/Angel.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Protect.h"
#define UpCircle_NUM 20
#define Eyes_NUM 40
#define Head_NUM 20
#define UpQuad_NUM 6
#define ButtomQuad_NUM 6
#define ButtomCircle_NUM 60
#define Total_NUM UpQuad_NUM+Head_NUM+Eyes_NUM+ButtomQuad_NUM+ButtomCircle_NUM+UpCircle_NUM

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class Player :public GameObject {
private:
	point4 _points[Total_NUM];
	color4 _colors[Total_NUM];

	bool isShoot=false;
	bool isProtect = false;
public:
	Protect *_protect;
	BulletLink *_bulletLink;

	float shootTime = 0.0f;

	Player(mat4& matModelView, mat4& matProjection, GLuint shaderHandle = MAX_UNSIGNED_INT);
	~Player();

	void Create(mat4& matModelView, mat4& matProjection, GLuint shaderHandle);
	void Update(float delta);
	void Draw();

	void SetPosition(vec4 position);

	void SetShoot(bool shoot) { isShoot = shoot; }
	void SetProtect(bool protect) { isProtect = protect; }
};