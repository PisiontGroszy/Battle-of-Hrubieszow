uniform sampler2D tex;
uniform float mass[10];
uniform vec2 massPosTexCoord[10];
uniform float massDist[10];
uniform float massRadiaus[10];
uniform vec2 windowsSize;
uniform float pixelSize;
uniform float LARGE_DISTANCE;

void main(void){
vec2 texCoordFinal = gl_TexCoord[0].st;
vec2 normal = (massPosTexCoord[0] - texCoordFinal);
vec2 normalizedNormal = normalize(normal);

float p = windowSize.y * length(normal);
float r = max(massRadiaus[0], 2.0 * massDist[0] * p * pixelSize);
float alpha = 5.91 * mass[0] / r;
float thetaE2 = 5.91 * mass[0] / massDist[0];
float magnification = 1.0 / (1.0 - thetaE2 * thetaE2 / pow(r / massDist[0], 4.0));
float amountEye = alpha * LARGE_DISTANCE;
vec4 deflectEye = vec4(normalizedNormal * amountEye, -5.0, 1.0);
vec4 deflectNDC = gl_ProjectionMatrix *deflectEye;
deflect NDC /= deflectNDC.w;

texCoordFinal += deflectNDC.xy;
gl_FragColor = magnification * texture2D(tex, texCoordFinal);
}
