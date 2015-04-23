#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "png_reader.h"

#include "geo_sphere.h"


GLuint textureID;
bool drawTeapot;
GLint programObj;

GLint location_testTexture;
GLint location_time;
GLint location_center;

void gl_init();
void gl_draw();

char* readShaderFile(const char *filename) {
  FILE *file;
  struct stat st;
  
  file = fopen(filename, "r");
  
  if(file == NULL){
    fprintf( stderr, "ERROR: Cannot open shader file!");
    return 0;
  }
  
  stat(filename,&st);
  
  int bytesinfile = st.st_size;
  char *buffer = (char*)malloc(bytesinfile+sizeof(char));
  int bytesread = fread( buffer, 1, bytesinfile, file);
  buffer[bytesread] = 0; // Terminate the string with 0
  fclose(file);
  
  return buffer;
}

void createShaders() {
  
  GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  
  const char *vertexAssembly = readShaderFile("vertex_shader.vert");
  glShaderSource( vertexShader, 1, &vertexAssembly, NULL );
  glCompileShader( vertexShader);
  free((void *)vertexAssembly);
  
  GLint isCompiled;
  glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &isCompiled );
  
  if(isCompiled == GL_FALSE){
    char str[256];
    glGetShaderInfoLog(vertexShader, 256, NULL, str);
    fprintf( stderr, "Vertex shader compile error: %s\n", str);
  }
  
  
  GLint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
  
  const char *fragmentAssembly = readShaderFile( "fragment_shader.frag" );
  glShaderSource( fragmentShader, 1, &fragmentAssembly, NULL );
  glCompileShader( fragmentShader );
  free((void *)fragmentAssembly);
  
  
  glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &isCompiled );
  
  if(isCompiled == GL_FALSE){
    char str[256];
    glGetShaderInfoLog( fragmentShader, 256, NULL, str );
    fprintf( stderr, "Fragment shader compile error: %s\n", str );
  }
  
  programObj = glCreateProgram();
  glAttachShader( programObj, vertexShader );
  glAttachShader( programObj, fragmentShader );
  
  glLinkProgram( programObj );
  GLint isLinked;
  glGetProgramiv( programObj, GL_LINK_STATUS, &isLinked );
  
  if( isLinked == GL_FALSE ){
    char str[256];
    glGetProgramInfoLog( programObj, 256, NULL, str );
    fprintf( stderr, "Program object linking error: %s\n", str );
  }
	
  location_testTexture = glGetUniformLocation( programObj, "testTexture" );
	if(location_testTexture == -1)
    fprintf( stderr, "Binding warning: Failed to locate uniform variable 'testTexture'.\n");
  
 	location_time = glGetUniformLocation( programObj, "time" );
	if(location_time == -1)
    fprintf( stderr, "Binding warning: Failed to locate uniform variable 'time'.\n");
  
 	location_center = glGetUniformLocation( programObj, "center" );
}



void gl_anim(){
  glutPostRedisplay();
}

void reshape(int w, int h){
  glViewport( 0, 0, w, h );
  
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 45, ( float ) w / ( float ) h,
		  0.01, 10.0 );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}

int mouseState = 0;
int xOld, yOld;
GLfloat xRot = 0, yRot = 0;
GLfloat zoom = -5;
void mouse(int button, int state, int x, int y){
  if( state == GLUT_DOWN ){
    if( button == GLUT_LEFT_BUTTON ){
      mouseState = 1;
      xOld = x;
      yOld = y;
    }
    if( button == GLUT_MIDDLE_BUTTON ){
      mouseState = 2;
      yOld = y;
    }
  }
  else if( state == GLUT_UP ){
    mouseState = 0; }
}

void motion( int x, int y ){
  switch(mouseState){
  case 1:
    xRot += (float)(x - xOld) / 2.0;
    yRot += (float)(y - yOld) / 2.0;
    xOld = x;
    yOld = y;
  case 2:
    zoom += (float)(y - yOld) / 5.0;
    if( zoom < -5 ){
      zoom = -5; }
    if( zoom > 0 ){ zoom = 0; }
    yOld = y;
  }
}

void keyboard(unsigned char key, int x, int y){
  
  switch(key){
  case 't':
    drawTeapot = !drawTeapot;
    break;
  case 'q':
    exit(1);
  default:
    fprintf( stderr, "%d %c\n", key, key );
  }
}

clock_t clock_0;
int main(int argc, char *argv[]){
  
  clock_0 = clock();
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);
  
  glutCreateWindow("Demo");
  glutInitWindowPosition(20, 20);
  glutInitWindowSize(800, 600);
  
  glewInit();
  gl_init();
  
  glutIdleFunc(gl_anim);
  glutDisplayFunc(gl_draw);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);
  
  createShaders();
  
  glutMainLoop();
}

void gl_init(){
  glClearColor( .5, .5, .5, 0 );
  
  glEnable(GL_TEXTURE_2D); // Enable texturing
  glGenTextures(1, &textureID); // Generate a unique texture ID
  glBindTexture(GL_TEXTURE_2D, textureID); // Activate the texture
  
  png_data_t *image = read_png("texture.png");
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 
               0, 
               image->has_alpha ? GL_RGBA : GL_RGB,
               image->width,
               image->height, 
               0, 
               image->has_alpha ? GL_RGBA : GL_RGB,
               GL_UNSIGNED_BYTE,
               image->pixelData);

  
}

void gl_draw(){
  glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
  
  glLoadIdentity();
  glTranslatef(0,0,zoom);
  glRotatef(yRot, 1, 0, 0);
  glRotatef(xRot, 0, 1, 0);
  glScalef( .25, .25, .25 );
  
  float time = (clock()-clock_0)/(float)(CLOCKS_PER_SEC);
  
  glPushMatrix();
  glRotatef(30.0f*time, 0.0f, 0.0f, 1.0f);
  glTranslatef(5.0f, 0.0f, 0.0f);
  float lightpos0[4]={0.0f, 0.0f, 0.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos0);
  glPopMatrix();
  
  glPushMatrix();
  glRotatef(45.0f*time, 0.0f, 0.0f, 1.0f);
  glColor3f(1.0f, 1.0f, 1.0f);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glBindTexture(GL_TEXTURE_2D, textureID);
  
  glUseProgram( programObj );
  
  if(drawTeapot){
    glutSolidTeapot(1.0); }
  else{
    drawTexturedSphere(1.0, 20); }
  
  glUseProgram(0);
  
  glPopMatrix();
  
  // Disable lighting again, to prepare for next frame.
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  
  
  glutSwapBuffers();
}

