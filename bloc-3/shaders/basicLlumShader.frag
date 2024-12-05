#version 330 core

in vec3 matambFrag;
in vec3 matdiffFrag;
in vec3 matspecFrag;
in float matshinFrag;

in vec4 posSCO;
in vec3 normSCO;
uniform mat4 view;

vec3 llumAmbient = vec3(0.2, 0.2, 0.2);

uniform bool tipusFocus;
uniform vec3 colorFocus;
uniform vec3 posFocus;  // en SCA

out vec4 FragColor;

vec3 Ambient() {
    return llumAmbient * matambFrag;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus) 
{
    // Tant sols retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * matdiffFrag * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus) 
{
    // Tant sols retorna el terme especular!
    // Els vectors rebuts com a paràmetres (NormSCO i L) estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (matshinFrag == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular
    
    // Calculem i retornem la component especular
    float shine = pow(max(0.0, dot(R, V)), matshinFrag);
    return (matspecFrag * colFocus * shine); 
}

void main()
{	
	vec3 posFocusSCO;
	if (!tipusFocus) posFocusSCO = (view * vec4 (posFocus, 1.0)).xyz;
	else posFocusSCO = vec3(0, 0, 0);
	vec3 normalSCOnormalitzada = normalize(normSCO);
	vec3 LSCOnormalitzada = normalize(posFocusSCO - posSCO.xyz);

	FragColor = vec4 (Ambient() + Difus(normalSCOnormalitzada, LSCOnormalitzada, colorFocus) + Especular(normalSCOnormalitzada, LSCOnormalitzada, posSCO, colorFocus), 1.0);	
}
