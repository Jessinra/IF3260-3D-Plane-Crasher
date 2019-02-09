build:
	g++-7 -pthread main.cpp Master.cpp Line.cpp Plane.cpp Object.cpp Pixel.cpp MoveableObject.cpp MoveablePlane.cpp PlaneFiller.cpp -o main

run:
	sudo ./main
