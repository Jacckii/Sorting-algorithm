#include "stdafx.h"

#include <vector>
#include <mutex>

#include "gui.h"

extern std::mutex mutex;
extern std::vector<int32_t> array_to_sort;

GUI::GUI()
{
	/* Initialize the library */
	if (!glfwInit())
		throw "Error while initializing lib";

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 600, "By Jaccko", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw "Error while creating window!";
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

}

GUI::~GUI()
{
	glfwTerminate();
}

void GUI::Draw()
{
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);
		/* Render here */
		//Clear information from last draw
		glClear(GL_COLOR_BUFFER_BIT);
		glOrtho(0, width, height, 0, 0, 1);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //clear background screen to black		

		glMatrixMode(GL_PROJECTION); //Switch to the drawing perspective
		glLoadIdentity(); //Reset the drawing perspective;

		glLineWidth(5);

		//pos
		int x = 8, y = 500;
		//size of 1 int
		static int size_1 = 3;

		int max_size = -1;
		for (int size : array_to_sort) //getting max value from vector
		{
			if (size > max_size)
				max_size = size;
		}

		for (int size : array_to_sort)
		{
			float percentage = (float)size / (float)max_size; // calculate color
			glColor3f(1.0f - percentage, percentage, 0.0f);

			glBegin(GL_LINES); //draw Line
			glVertex2i(x, y);
			glVertex2i(x, y - size_1 * size);
			glEnd();
			x += 6;
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
}
