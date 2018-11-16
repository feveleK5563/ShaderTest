struct PS_INPUT
{
	float4 Diffuse		: COLOR0;
	float4 Specular		: COLOR1;
	float2 TexCoord0	: TEXCOORD0;
	float2 TexCoord1	: TEXCOORD1;
};

struct PS_OUTPUT
{
	float4 Output		: COLOR0;
};


//画面サイズ
float sizex : register( c0 );
float sizey : register( c1 );

//円の半径
float r : register( c2 );

//クリックされたか否か
bool onclick : register( c3 );

//座標
float posx : register( c4 );
float posy : register( c5 );

//--------------------------------------------------------------------------------------------------

bool CirclePixel( float px, float py )
{
	return ((px - posx) * (px - posx) +
			(py - posy) * (py - posy) -
			(r * r) < 0.000001f);
}


PS_OUTPUT main( PS_INPUT psin )
{
	PS_OUTPUT psout;
	
	psout.Output.r = 0.f;
	psout.Output.g = 0.f;
	psout.Output.b = 0.f;
	psout.Output.a = 1.f;
	
	float px = sizex * psin.TexCoord0.x;
	float py = sizey * psin.TexCoord0.y;
	
	if(onclick)
	{
		if(CirclePixel(px, py))
		{
			psout.Output.r = 1.f;
		}
		else
		{
			psout.Output.r = 0.f;
		}
	}
	else
	{
		if(CirclePixel(px, py))
		{
			psout.Output.r = 0.f;
		}
		else
		{
			psout.Output.r = 1.f;
		}
	}
	
	return psout;
}