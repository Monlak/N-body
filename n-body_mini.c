#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define G 6.67428E-11

GLuint plotPoint;

/* Create display list with Torus and initialize state*/
void plot(float *px, float *py,int numdot){
	int i =0;
	glPointSize(10.0f);
  glColor3f(1.0f,0.0f,0.0f); // blue
	glBegin( GL_POINTS );
		for(i=0;i<numdot;i++)
		{
			printf("%.2f %.2f \n",px[i],py[i]);
			glVertex2f(px[i], py[i]);
		}
	glEnd();
}

// display keep list
void init(float *px, float *py,int numdot){
	plotPoint = glGenLists(1);
	glNewList(plotPoint, GL_COMPILE);
		plot(px,py,numdot); // gl plot
	glEndList();
}

//setting display
void display(void) {
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
	 glMatrixMode ( GL_PROJECTION );
	 glLoadIdentity();
	 gluOrtho2D( 0.0, 500.0, 0.0, 500.0 );	//set world window (left,right,bottom,top ); 
	 glViewport( 40, 60, 300, 200 );		//set viewport (x,y,width,height ); 
   glCallList(plotPoint);	// Call function display list    
   glFlush(); //render
}

void openGL(float *px, float *py,int numdot){

	 glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
   glutInitWindowSize(1000, 1000);   // Set the window's initial width & height
   glutInitWindowPosition(200,100); // Position the window's initial top-left corner
   init(px,py,numdot);
   glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutMainLoop();           // Enter the infinitely event-processing loop
}

void readFile(FILE *fp,int numdot,float *px, float *py,int *mass) {
	int i=0;
	
	for(i=0;i<numdot;i++)
	{
		fscanf(fp,"%f",&px[i]);
		fscanf(fp,"%f",&py[i]);
		fscanf(fp,"%d",&mass[i]);
	}
}
 
/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
   
   int numdot = 0;
   float *px;
   float *py;
   int *mass;
   
   FILE *fp = NULL;
   fp = fopen("test_input.txt","r");

   if(fp != NULL)
   {
   fscanf(fp,"%d",&numdot);
     //-----------------colloc-------------------
     px = (float*)calloc(numdot,sizeof(float));
     py = (float*)calloc(numdot,sizeof(float));
     mass = (int*)calloc(numdot,sizeof(int));
     //-------------------------------------------
     
     readFile(fp,numdot,px,py,mass);
   		
		for(int i=0;i<numdot;i++)
	{
		printf("%.2f %.2f \n",px[i],py[i]);
	}

     glutInit(&argc, argv);                 // Initialize GLUT
     openGL(px,py,numdot);
     
     //------------------Free-------------------
     free(px);
     free(py);
     free(mass);
     //-------------------------------------------
   }
 
 return 0;
}
