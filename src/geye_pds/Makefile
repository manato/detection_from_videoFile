# Builds all the projects in the solution...
.PHONY: all_projects
all_projects: CAR_TRACKING 

# Builds project 'CAR_TRACKING'...
.PHONY: CAR_TRACKING
CAR_TRACKING: 
	make --directory="CAR_TRACKING/" --file=CAR_TRACKING.makefile

# Cleans all projects...
.PHONY: clean
clean:
	make --directory="CAR_TRACKING/" --file=CAR_TRACKING.makefile clean

# Install executable file to /usr/local/geye_with_cam/bin
install:
	cp ./CAR_TRACKING/2010_2_3.txt ../../bin/pedestrian_detecter/2010_2_3.txt
	cp ./CAR_TRACKING/person_comp.csv ../../bin/pedestrian_detecter/person_comp.csv
	cp ./CAR_TRACKING/person_root.csv ../../bin/pedestrian_detecter/person_root.csv
	cp ./CAR_TRACKING/person_part.csv ../../bin/pedestrian_detecter/person_part.csv
	cp ./gccRelease/GPU_function.cubin ../../bin/pedestrian_detecter/GPU_function.cubin
	cp ./gccRelease/CAR_TRACKING.exe ../../bin/pedestrian_detecter/pedestrian_detecter
