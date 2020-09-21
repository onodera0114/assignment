import glfw
from OpenGL.GL import *
from OpenGL.GLU import *
from math import *

DOUBLE_BUFFERING = True

W_INIT = 320
H_INIT = 240

VERTEX = [
    [0.0, 3.0, 0.0],
    [2 * sqrt(2), -1.0, 0.0],
    [- sqrt(2), -1.0, - sqrt(6)],
    [- sqrt(2), -1.0, sqrt(6)]
]

FACE = [
    [0, 1, 2],
    [0, 2, 3],
    [0, 1, 3],
    [1, 2, 3]
]

AB = [VERTEX[1][0] - VERTEX[0][0], VERTEX[1][1] - VERTEX[0][1], VERTEX[1][2] - VERTEX[0][2]]
AC = [VERTEX[2][0] - VERTEX[0][0], VERTEX[2][1] - VERTEX[0][1], VERTEX[2][2] - VERTEX[0][2]]
AD = [VERTEX[3][0] - VERTEX[0][0], VERTEX[3][1] - VERTEX[0][1], VERTEX[3][2] - VERTEX[0][2]]
BC = [VERTEX[2][0] - VERTEX[1][0], VERTEX[2][1] - VERTEX[1][1], VERTEX[2][2] - VERTEX[1][2]]
BD = [VERTEX[3][0] - VERTEX[1][0], VERTEX[3][1] - VERTEX[1][1], VERTEX[3][2] - VERTEX[1][2]]

NORMAL = [
      [AB[1] * AC[2] - AB[2] * AC[1], AB[2] * AC[0] - AB[0] * AC[2], AB[0] * AC[1] - AB[1] * AC[0]],
      [AC[1] * AD[2] - AC[2] * AD[1], AC[2] * AD[0] - AC[0] * AD[2], AC[0] * AD[1] - AC[1] * AD[0]],
      [AB[1] * AD[2] - AB[2] * AD[1], AB[2] * AD[0] - AB[0] * AD[2], AB[0] * AD[1] - AB[1] * AD[0]],
      [BC[1] * BD[2] - BC[2] * BD[1], BC[2] * BD[0] - BC[0] * BD[2], BC[0] * BD[1] - BC[1] * BD[0]]
]

light0pos = [0.0, 3.0, 5.0, 1.0]
light1pos = [5.0, 3.0, 0.0, 1.0]
green = [0.0, 1.0, 0.0, 1.0]

def display():
    global r

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

    glLoadIdentity()
    gluLookAt(3.0, 4.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)

    glLightfv(GL_LIGHT0, GL_POSITION, light0pos)
    glLightfv(GL_LIGHT1, GL_POSITION, light1pos)

    glRotated(r, 0.0, 1.0, 0.0)

    glColor3d(0.0, 0.0, 0.0)

    glBegin(GL_POLYGON)
    for j in range(4):
        glNormal3dv(NORMAL[j])
        for i in range(3):
            glVertex3dv(VERTEX[FACE[j][i]])
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
    elif button == glfw.MOUSE_BUTTON_RIGHT:
        rotation = ( action == glfw.PRESS )
        angle = -1
    else:
        angle = 0

def init():
    gray = 0.8
    glClearColor(gray, gray, gray, 1.0)
    set_view(W_INIT, H_INIT)
    glEnable(GL_DEPTH_TEST)

    glEnable(GL_CULL_FACE)
    glCullFace(GL_BACK)

    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glEnable(GL_LIGHT1)
    glLightfv(GL_LIGHT1, GL_DIFFUSE, green)
    glLightfv(GL_LIGHT1, GL_SPECULAR, green)
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

window = glfw.create_window(W_INIT, H_INIT, 'tetrahedron_06', None, None)
if not window:
    glfw.terminate()
    raise RuntimeError('Could not create an window')

glfw.set_mouse_button_callback(window, mouse_button)
glfw.set_window_size_callback(window, resize)
glfw.set_window_refresh_callback(window, window_refresh)
glfw.make_context_current(window)

init()

while not glfw.window_should_close(window):
    if rotation:
        display()
        glfw.poll_events()
        #glfw.wait_events_timeout(1e-2)
    else:
        glfw.wait_events_timeout(1e-3)

glfw.terminate()
