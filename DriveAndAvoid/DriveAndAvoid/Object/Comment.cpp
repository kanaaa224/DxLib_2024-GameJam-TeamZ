#include "Comment.h"
#include "DxLib.h"

Comment::Comment(int type, int font_size, int font_color, const char* string) : type(type), font_size(font_size), font_color(font_color), comment(string), speed(0.0f), location(0.0f), box_size(0.0f)
{
	
}

Comment::~Comment()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Comment::Initialize()
{
	// 速さの設定
	speed = (float)(this->type * 2);

	// 生成位置の設定
	int max_y_grid   = 28; // y 軸方向の最大割り当て数
	int y_margin_top = 30; // y 軸方向の上マージン
	location = Vector2D(1280.0f, ((float)(GetRand(max_y_grid) * font_size + y_margin_top)));

	// 当たり判定の大きさ設定
	box_size = Vector2D(GetDrawFormatStringWidth(comment), font_size);
}

void Comment::Update(float speed)
{
	location -= Vector2D(this->speed + speed, 0.0f); // 位置情報に移動量を加算
}

void Comment::Draw() const
{
	SetFontSize(font_size);
	DrawFormatString(location.x, location.y, font_color, comment);

	DrawBox(location.x, location.y, location.x + GetDrawFormatStringWidth(comment), location.y + font_size, 0xffffff, false);
}

void Comment::Fialize()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////

int Comment::GetType() const
{
	return type;
}

Vector2D Comment::GetLocation() const
{
	return location;
}

Vector2D Comment::GetBoxSize() const
{
	return box_size;
}