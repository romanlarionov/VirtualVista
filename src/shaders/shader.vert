
attribute vec3 position;

varying vec3 vPos;

void main(void)
{
    gl_Position = vec4(position, 1.0);
    vPos = position;
}