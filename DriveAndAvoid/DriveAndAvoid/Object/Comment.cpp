#include "Comment.h"
#include "DxLib.h"
#include "math.h"

Comment::Comment(int type, int font_size, int font_color, std::string string) : type(type), font_size(font_size), font_color(font_color), comment(string), speed(0.0f), location(0.0f), box_size(0.0f)
{
	
}

Comment::~Comment()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Comment::Initialize()
{
	int margin_top  = 25; // y 軸方向の上マージン
	int margin_left = 25; // x 軸方向の左マージン

	int canvas_x_size = 860;
	int canvas_y_size = 484;

	int max_y_grid = round(canvas_y_size/ font_size) - 1; // y 軸方向の最大割り当て数

	if (type >= 0)
	{
		// 速さの設定
		speed = (float)(this->type * 2);

		// 生成位置の設定
		location = Vector2D((margin_left + canvas_x_size), ((float)(GetRand(max_y_grid) * font_size + margin_top)));
	}
	else
	{
		// 生成位置の設定
		location = Vector2D((margin_left + (canvas_x_size / 2)) - (GetDrawFormatStringWidth(comment.c_str()) / 2), ((float)(GetRand(max_y_grid) * font_size + margin_top)));
	}

	// 当たり判定の大きさ設定
	box_size = Vector2D(GetDrawFormatStringWidth(comment.c_str()), font_size);
}

void Comment::Update(float speed)
{
	if (type >= 0) location -= Vector2D(this->speed + speed, 0.0f); // 位置情報に移動量を加算
}

void Comment::Draw() const
{
	SetFontSize(font_size);
	DrawFormatString(location.x, location.y, font_color, comment.c_str());

	//DrawBox(location.x, location.y, location.x + GetDrawFormatStringWidth(comment), location.y + font_size, 0xffffff, false);
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