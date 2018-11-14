struct PS_INPUT
{
	float4 Diffuse		: COLOR0;
	float4 Specular		: COLOR1;
	float2 TexCoord0	: TEXCOORD0;
	float2 TexCoord1	: TEXCOORD1;
} ;

struct PS_OUTPUT
{
	float4 Output		: COLOR0;
} ;

//描画するテクスチャ
sampler tex : register( s0 );

//タイマー
float timer : register( c0 );

PS_OUTPUT main( PS_INPUT psin )
{
	PS_OUTPUT psOut;
	float4 texColor;
	float2 calcPos;
	
	calcPos.x = fmod( 1.0 + psin.TexCoord0.x + 0.2 * sin( psin.TexCoord0.y * 24.0 + timer ) , 1.0);
	calcPos.y = psin.TexCoord0.y;
	
	texColor  = tex2D( tex, calcPos );
	
	psOut.Output = texColor;
	return psOut;
}
