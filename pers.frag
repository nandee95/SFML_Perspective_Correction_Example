in vec4 texCoords;
uniform sampler2D texture;

void main() {
    gl_FragColor = texture2DProj(texture, texCoords);
}
