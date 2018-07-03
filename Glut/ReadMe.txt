PLG Models Real time Renderer with Gouraud shaded environment mapping.
Coded by Thanassis Tsiodras (Hawk/Enigma).

Requirements:

  386DX-33MHz and above
  VGA video card, preferably a Local Bus or PCI.
  4 MB RAM (may work with 2MB - not tested, though)

This software is in the public domain.
The code in this software is Copyright (c) 1995 by Thanassis Tsiodras.

Contents.
=========

0. Disclaimer
1. What is this program? How is it used?
2. What does PLG stand for?
3. Can I create my own objects?
4. How did you do this, this fast?
5. What is Enigma?

0. Disclaimer
=============

I will not be held responsible for any kind of damage this software causes
to your machine. You are using it at your own risk. Having said that, I must
admit that as a computer engineer I believe there is no way this software
can harm your system. I have tested it in more than 6 computers, and even
in crash situations, it doesn't cause lost clusters (all the disk activity
is done at the beginning - and it is reading, not writing).


1. What is this program? How is it used?
========================================

This program is a real time renderer. What this means, is that it
takes a mathematical specification of a scene, and creates a computer
generated world in which you can move at FAST speed. The mathematical
specification is actually a set of polygons, defined by the
coordinates of their bounding points (in x,y,z - Cartesian coords).
The specification is included in a .plg file, which is given as
a parameter with the program.
  You can type 3DENVMAP without any parameters at the DOS prompt, and you
will be shown the following line:

Syntax:  3denvmap file.plg [dth] [dphi] [dmi] [scale]");

From dth and on, the parameters are optional.
dth is the number of degrees the object will spin when you press left-right.
dphi is the number of degrees the object will spin when you press up-down.
dmi is the number of units SPACEBAR/V move you towards/from the object.
scale is only needed when the vertex coordinates are small numbers:
  The renderer is truncating the coordinates, taking the integer part. If
they are numbers like 0.00012 0.0021 etc. you have to provide a scaling
factor: all coordinates will be multiplied with it.
  You can move inside the world using these keys:

  Cursor keys : Rotate around the center of the world
  SPACE, V    : Zoom in and out
  W           : (Press and release key) Toggle wireframe display

  If you zoom very close to an object, the polygons that intersect with
the view plane, are not displayed. In order to show them, the algorithm
would have to do 3D polygon clipping, which would significantly slow
things down.

2. What does PLG stand for?
===========================

I wish I knew. Three years ago, I stumbled over this format on the
Internet, and found out that it's quite simply the easiest method
of polygon-based world representation. Say for example that you have
just one triangle forming the "scene", with these coordinates:

  Point 1:   10, 10, 10
  Point 2:   -10,10, 60
  Point 3:  110, 0, -10

Then the .plg file representing this "object" would be this:

Line 1:
object_name 3 1
            | |
            | +--- This is the number of polygons in the scene
            +----- This is the number of vertexes (points) in the scene.

Lines 2-4:   The coordinates of all the points in the scene
10 10 10
-10 10 60
110 0 -10

Line 5:            The polygons. The first number is 1 (I don't know what
                   this is used for, but I keet it for compatibility).
                   The next number is the number of points this specific
                   polygon has (in our example, 3, since it's a triangle).
                   This version only allows 3 and 4 point polygons.
                   The following numbers are the indexes in the vertexes
                   already given (i.e. this polygon is formed by vertexes
                   x,y,z,...) The numbers following should be as many
                   as specified (in our example, 3). Note that the first
                   vertex (point) is vertex 0, not vertex 1.
1 3 0 1 2

After defining an object, you can define another one, in the same way:

obj1 3 1
10 10 10
-10 10 60
110 0 -10
1 3 0 1 2
object2 2100 310
...
..
object3 10 20
...

etc.
Don't let any blank lines between data. You can examine the plg's
contained in this archive, if you want.


3. Can I create my own objects?
===============================

Why do you think I described the format? Start now! Make simple objects
at first, to get the idea, then let your imagination guide you!
It would be nice if someone could code a 3D world editor, capable of saving
in .plg format! I simply don't have the time to do that anymore. I wish
I knew this algorithm two years ago, when I was still a student. By enabling
.plg as a save format, you have the benefit of being able to spawn my viewer
for tests! (Although if you do that and earn fame/money, I'd really
appreciate some cash, thank you).


4. How did you do this, this fast?
==================================

Testing with chopper.plg (about 2000 polygons), the renderer produces
about 18-19 frames/sec (at distances where no clipping is needed:clipping
really puzzles the CPU). This means rendering at about 36000 polygons/sec
on a 486DX-100MHz with Local Bus VGA. It's a nice machine, I admit it,
but the results are also incredible (considering the current status in
graphics programming - even commercial games are slower than this!)
The main ideas behind this clever algorithm come from a friend of mine:
tmL. tmL is the organiser/coder of a demo group called Enigma. I am
currently a member of this group.
Note that this routine is faster than many graphics demos (even some that
competed in Assembly '95), although most of them were written entirely in
assembly.


5. What is Enigma?
==================

Enigma is a Greek demo group. So far we have only released music disks,
but tmL is working on the IllusionRender Engine, containing this algorithm,
amongst others. This is going to be a spectacular engine. We will
probably release it as an independent library. If enough interest appears
on the net, maybe I will port it to the 32 bit Windows environments
(Win32S, Windows 95, NT) since I already have the necessary equipment
and know-how.

If you want to contact us, email at:

gmosx@softlab.ece.ntua.gr        tmL
ttsiod@softlab.ece.ntua.gr       Hawk
