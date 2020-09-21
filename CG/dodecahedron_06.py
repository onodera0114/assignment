import glfw
from OpenGL.GL import *
from OpenGL.GLU import *
from math import *

DOUBLE_BUFFERING = True

W_INIT = 320
H_INIT = 240
phi = (1 + sqrt(5)) / 2

VERTEX = [
    [-1.0, -1.0, 1.0],
    [- phi, 0.0, 1 / phi],
    [- phi, 0.0, - 1 / phi],
    [-1.0, -1.0, -1.0],
    [- 1 / phi, - phi, 0.0],
    [-1.0, 1.0, 1.0],
    [0.0, 1 / phi, phi],
    [0.0, - 1 / phi, phi],
    [- 1 / phi, phi, 0.0],
    [-1.0, 1.0, -1.0],
    [1 / phi, phi, 0.0],
    [1.0, 1.0, 1.0],
    [phi, 0.0, 1 / phi],
    [phi, 0.0, - 1 / phi],
    [1.0, 1.0, -1.0],
    [0.0, 1 / phi, - phi],
    [0.0, - 1 / phi, - phi],
    [1.0, -1.0, -1.0],
    [1 / phi, - phi, 0.0],
    [1.0, -1.0, 1.0]
]

EDGE = [
    [0, 1],
    [1, 2],
    [2, 3],
    [3, 4],
    [4, 0],
    [1, 5],
    [5, 6],
    [6, 7],
    [7, 0],
    [6, 11],
    [11, 10],
    [10, 8],
    [8, 5],
    [8, 9],
    [9, 2],
    [11, 12],
    [12, 13],
    [13, 14],
    [14, 10],
    [14, 15],
    [15, 16],
    [16, 17],
    [17, 13],
    [16, 3],
    [17, 18],
    [18, 4],
    [18, 19],
    [19, 12],
    [19, 7],
    [15, 9]
]

def display():
    global r, angle

    glClear(GL_COLOR_BUFFER_BIT)

    glLoadIdentity()
    gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
    glRotated(r, 0.0, 1.0, 0.0)

    glColor3d(0.0, 0.0, 0.0)
    glBegin(GL_LINES)
    for edge1 in EDGE:
        for i in edge1:
            glVertex3dv(VERTEX[i])
    glEnd()

    if DOUBLE_BUFFERING:
        glfw.swap_buffers(window)
    else:
        glFlush()

    r += angle
    if r >= 360:
        r = 0
    elif r < 0:
        r = 359

def set_view(w, h):
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(35.0, w/h, 1.0, 100.0)
    glMatrixMode(GL_MODELVIEW)

def resize(window, w, h):
    # for iconify on Windows
    if h==0:
        return
    glViewport(0, 0, w, h)
    set_view(w, h)

def mouse_button(window, button, action, mods):
    global rotation, angle
    if button == glfw.MOUSE_BUTTON_LEFT:
        rotation = ( action == glfw.PRESS )
        angle = 1
    else:
        angle = 0

def keyboard(window, key, scancode, action, mods):
    global rotation, angle
    if key == glfw.KEY_SPACE:
        rotation = True if(action == glfw.PRESS or action == glfw.REPEAT) else False
        angle = -1
    else:
        angle = 0

def init():
    gray = 0.8
    glClearColor(gray, gray, gray, 1.0)
    set_view(W_INIT, H_INIT)
    display()   # necessary only on Windows

def window_refresh(window): # for resize
    display()


r = 0
angle = 0
rotation = False

if not glfw.init():
    raise RuntimeError('Could not initialize GLFW3')

if not DOUBLE_BUFFERING:
    glfw.window_hint(glfw.DOUBLEBUFFER, glfw.FALSE)

window = glfw.create_window(W_INIT, H_INIT, 'dodecahedron_06', None, None)
if not window:
    glfw.terminate()
    raise RuntimeError('Could not create an window')

glfw.set_key_callback(window, keyboard)
glfw.set_mouse_button_callback(window, mouse_button)
glfw.set_window_size_callback(window, resize)
glfw.set_window_refresh_callback(window, window_refresh)
glfw.make_context_current(window)

init()

while not glfw.window_should_close(window):
    if rotation:
        display()
        glfw.poll_events()
#        glfw.wait_events_timeout(1e-2)
    else:
        glfw.wait_events_timeout(1e-3)

glfw.terminate()
