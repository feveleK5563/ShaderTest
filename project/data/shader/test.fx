struct PS_INPUT
{
	float4 Diffuse         : COLOR0 ;
	float4 Specular        : COLOR1 ;
	float2 TexCoords0      : TEXCOORD0 ;
	float2 TexCoords1      : TEXCOORD1 ;
} ;

struct PS_OUTPUT
{
	float4 Output          : COLOR0 ;
} ;

sampler sampler0 : register( s0 ) ;

PS_OUTPUT main( PS_INPUT psin )
{
	PS_OUTPUT psout;
	float4 texc;
	texc  = tex2D( sampler0, psin.TexCoords0 );
	
	if (0.3 < psin.TexCoords0.y && psin.TexCoords0.y < 0.7)
	{
		texc.rgb = 1.0 - texc.rgb;
	}
	
	psout.Output = texc;
	return psout;
}
