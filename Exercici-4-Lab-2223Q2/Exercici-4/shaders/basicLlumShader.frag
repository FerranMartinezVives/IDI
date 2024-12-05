#version 330 core

in vec3  fmatamb;
in vec3  fmatdiff;
in vec3  fmatspec;
in float fmatshin;
in vec3  fvertex;
in vec3  fnormal;

const vec3 llumAmbient = vec3(0.1, 0.1, 0.1);

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;

uniform vec3 colorFocusEscena;
uniform vec3 posicioFocusEscena;

uniform vec3 arrayColorsFocus[4];
uniform vec3 arrayPosicionsFocus[4];

out vec4 FragColor;


vec3 Ambient() {
  return llumAmbient*fmatamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme de Lambert!
  // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
  vec3 colRes = vec3(0);
  if (dot (L, NormSCO) > 0)
    colRes = colFocus * fmatdiff * dot (L, NormSCO);
  return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec3 vertSCO, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme especular!
  // Assumim que els vectors estan normalitzats
  vec3 colRes = vec3 (0);
  // Si la llum ve de darrera o el material és mate no fem res
  if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
    return colRes;  // no hi ha component especular

  vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
  vec3 V = normalize(-vertSCO); // perquè la càmera està a (0,0,0) en SCO

  if (dot(R, V) < 0)
    return colRes;  // no hi ha component especular

  float shine = pow(max(0.0, dot(R, V)), fmatshin);
  return (colRes + fmatspec * colFocus * shine);
}

void main()
{
    vec3 posicioFocusEscenaSCO = (View * vec4(posicioFocusEscena, 1)).xyz;

    vec3 arrayPosicionsFocusSCO[4];
    for (int i = 0; i < 4; ++i) arrayPosicionsFocusSCO[i] = (View * vec4(arrayPosicionsFocus[i], 1.0)).xyz;

    vec3 normalSCOnormalitzada = normalize(fnormal);

    vec3 LSCOnormalitzadaEscena = normalize(posicioFocusEscenaSCO - fvertex);

    vec3 arrayLSCOnormalitzades[4];
    for (int i = 0; i < 4; ++i) arrayLSCOnormalitzades[i] = normalize(arrayPosicionsFocusSCO[i] - fvertex);

    vec3 sumaDifus = Difus(normalSCOnormalitzada, LSCOnormalitzadaEscena, colorFocusEscena);
    for (int i = 0; i < 4; ++i) sumaDifus = sumaDifus + Difus(normalSCOnormalitzada, arrayLSCOnormalitzades[i], arrayColorsFocus[i]);

    vec3 sumaEspecular = Especular(normalSCOnormalitzada, LSCOnormalitzadaEscena, fvertex, colorFocusEscena);
    for (int i = 0; i < 4; ++i) sumaEspecular = sumaEspecular + Especular(normalSCOnormalitzada, arrayLSCOnormalitzades[i], fvertex, arrayColorsFocus[i]);

    FragColor = vec4(Ambient() + sumaDifus + sumaEspecular, 1);
}

