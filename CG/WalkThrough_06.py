# glutSolidCube(1.0) -> glCallList(cube)

import glfw
from OpenGL.GL import *
from OpenGL.GLU import *
from math import *

W_INIT = 300
H_INIT = 300

LIGHTPOS = (3.0, 4.0, 5.0, 1.0)
BLUE = (0.2, 0.2, 0.8, 1.0)
DIFFUSE_GROUND = ((0.6, 0.6, 0.6, 1.0), (0.3, 0.3, 0.3, 1.0))
RANGE_GROUND = range(-5, 5)
GROUND_LEVEL = -2.0

class Face:
    def __init__(self, i_vertex, normal):
        self.i_vertex = i_vertex
        self.normal = normal


VERTEX = (
    (-0.1, -0.5, -0.1),   # A
    ( 0.1, -0.5, -0.1),   # B
    ( 0.1,  1.0, -0.1),   # C
    (-0.1,  1.0, -0.1),   # D
    (-0.1, -0.5,  0.1),   # E
    ( 0.1, -0.5,  0.1),   # F
    ( 0.1,  1.0,  0.1),   # G
    (-0.1,  1.0,  0.1))   # H

FACE = (
    Face((3, 2, 1, 0), ( 0.0,  0.0, -1.0)),
    Face((2, 6, 5, 1), ( 1.0,  0.0,  0.0)),
    Face((6, 7, 4, 5), ( 0.0,  0.0,  1.0)),
    Face((7, 3, 0, 4), (-1.0,  0.0,  0.0)),
    Face((0, 1, 5, 4), ( 0.0, -1.0,  0.0)),
    Face((7, 6, 2, 3), ( 0.0,  1.0,  0.0)))

ex = 0.0
ez = -3.0
r = 0.0
t = 0.6
theta = 0.0
V = 0.0

def display():
    global theta, r, t, V, ex, ez
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT )
    glLoadIdentity()

    glRotated(r, 0.0, 1.0, 0.0)
    glTranslated(ex, 0.0, ez)

    r += theta * t

    if r < 0:
        Vx = V * sin(abs(radians(r)))
        Vz = V * cos(abs(radians(r)))
    if r >= 0:
        Vx = -V * sin(abs(radians(r)))
        Vz = V * cos(abs(radians(r)))

    ex += Vx * t
    ez += Vz * t

    glLightfv(GL_LIGHT0, GL_POSITION, LIGHTPOS)
    glCallList(objects)
    glFlush()


def set_view(w, h):
    global cx, cy
    glViewport(0, 0, w, h)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(30.0, w/h, 1.0, 100.0)
    glMatrixMode(GL_MODELVIEW)

    cx = w / 2
    cy = h / 2

def resize(window, w, h):
    # for iconify on Windows

    if h==0:
        return
    glViewport(0, 0, w, h)
    set_view(w, h)

def gen_cube():
    global cube
    cube = glGenLists(1)
    glNewList(cube, GL_COMPILE)
    glBegin(GL_QUADS)
    for face1 in FACE:
        glNormal3dv(face1.normal)
        for i in face1.i_vertex:
            glVertex3dv(VERTEX[i])
    glEnd()
    glEndList()


def scene():
    global box, objects
    objects = glGenLists(1)
    glNewList(objects, GL_COMPILE)

    # blue box
    glPushMatrix()
    glTranslated(0.8, 0.0, -0.5)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BLUE)
    glCallList(cube)
    glPopMatrix()

    glPushMatrix()
    glTranslated(-0.8, 0.0, -0.5)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BLUE)
    glCallList(cube)
    glPopMatrix()

    glPushMatrix()
    glRotated(90, 0.0, 0.0, 1.0)
    glTranslated(0.9, -0.2, -0.5)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BLUE)
    glCallList(cube)
    glPopMatrix()

    # ground
    glBegin(GL_QUADS)
    glNormal3d(0.0, 1.0, 0.0)
    for j in RANGE_GROUND:
        for i in RANGE_GROUND:
            glMaterialfv(GL_FRONT, GL_DIFFUSE, \
                DIFFUSE_GROUND[(i+j)&1])
            glVertex3d(i, -0.5, j)
            glVertex3d(i, -0.5, j+1)
            glVertex3d(i+1, -0.5, j+1)
            glVertex3d(i+1, -0.5, j)
    glEnd()

    glEndList()

def init():
    gray = 1.0
    glClearColor(gray, gray, gray, 1.0)
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_CULL_FACE)
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    set_view(W_INIT, H_INIT)
    display()   # necessary only on Windows

def window_refresh(window):
    display()

def cursor_pos(window, xp, yp):
    global xps, yps, theta, V
    if dragging:
        dxp = xp-xps
        dyp = yp-yps

        xps = xp
        yps = yp
        if dxp > 0:
            theta = (atan2(abs(dxp), abs(dyp)))
        if dxp <= 0:
            theta = -(atan2(abs(dxp), abs(dyp)))

        if dyp > 0:
            if degrees(abs(theta)) >  60:
                V = 0
            elif degrees(abs(theta)) < 30:
                V = -0.1
                theta = 0
            else:
                V = -0.1
        if dyp <= 0:
            if degrees(abs(theta)) >  60:
                V = 0
            elif degrees(abs(theta)) < 30:
                V = 0.1
                theta = 0
            else:
                V = 0.1

    else:
          theta = 0
          V = 0

    display()

def mouse_button(window, button, action, mods):
    global dragging, xps, yps
    if button == glfw.MOUSE_BUTTON_LEFT:
        if action == glfw.PRESS:
            dragging = True
            xps, yps = glfw.get_cursor_pos(window)    # s: start
        else:
            dragging = False

dragging = False

if not glfw.init():
    raise RuntimeError('Could not initialize GLFW3')

glfw.window_hint(glfw.DOUBLEBUFFER, glfw.FALSE)

window = glfw.create_window(W_INIT, H_INIT, 'WalkThrough_06', None, None)
if not window:
    glfw.terminate()
    raise RuntimeError('Could not create an window')

glfw.set_window_size_callback(window, resize)
glfw.set_window_refresh_callback(window, window_refresh)
glfw.set_cursor_pos_callback(window, cursor_pos)
glfw.set_mouse_button_callback(window, mouse_button)
glfw.make_context_current(window)

gen_cube()
scene()
init()

while not glfw.window_should_close(window):
    glfw.wait_events()

glfw.terminate()
