build:
	g++-7 -pthread main.cpp Master.cpp Line.cpp Plane.cpp MoveablePlane.cpp Object.cpp Pixel.cpp \
	MoveableObject.cpp PlaneFiller.cpp Point.cpp -o main

run:
	sudo ./main
