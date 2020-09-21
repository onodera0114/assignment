import glfw
from OpenGL.GL import *
from math import *

W = 4
Y_MAX = 1
MARGIN_X = 0.2
MARGIN_Y = 0.1
N = 20
H = W/N

def display():
    glClear(GL_COLOR_BUFFER_BIT)

    glLineWidth(1)
    glBegin(GL_LINE_LOOP)
    glVertex2d(-W, -Y_MAX)
    glVertex2d( W, -Y_MAX)
    glVertex2d( W,  Y_MAX)
    glVertex2d(-W,  Y_MAX)
    glEnd()

    glLineWidth(1)
    glBegin(GL_LINES)
    glVertex2d(-W, 0.0)
    glVertex2d( W, 0.0)
    glVertex2d(0.0,  Y_MAX)
    glVertex2d(0.0,  -Y_MAX)
    glEnd()


    glLineWidth(2)
    glBegin(GL_LINE_STRIP)
    for i in range(-N, N+1):
        x = i*H
        glVertex2d(x, sin(x))
    glEnd()

    glfw.swap_buffers(window)

def init():
    gray = 0.95
    glClearColor(gray, gray, gray, 1.0)
    glColor3d(0.0, 0.0, 0.0)
    glOrtho(-W - MARGIN_X, W + MARGIN_X, -Y_MAX - MARGIN_Y, Y_MAX + MARGIN_Y, -1.0, 1.0)
    display()   # necessary only on Windows

def window_refresh(window):
    display()

if not glfw.init():
    raise RuntimeError('Could not initialize GLFW3')

window = glfw.create_window(300, 300, 'Parabola', None, None)
if not window:
    glfw.terminate()
    raise RuntimeError('Could not create an window')

glfw.set_window_refresh_callback(window, window_refresh)
glfw.make_context_current(window)

init()

while not glfw.window_should_close(window):
    glfw.wait_events()

glfw.terminate()
