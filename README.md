# Chinese Chess
## EC535-Lab5 Project 

One Qt-based Chinese Chess game, using touchscreen or mouse as the basic user interactive tool. 
Support 2 player to play in a round-based strategy.
Implemented basic rules for Chinese Chess game, supporting additional functions like "flip", "pause" and timer to record the game time. 
Dedicatedly designed a "zoom in" feature to fit the small touchscreen operation, mitigate mis-touching.


### Team member
Zhangchi Lu zhchlu@bu.edu
Tianyi Xu tyx@bu.edu


## How to run this project
Note, we do not offer pre-compiled executable files in this repo. Please follow the instructions below to play this game on your device. 

### To run on Beagle Bone Black with 4.3` touchscreen
Note: we assume that the BBB is ssh enabled

#### On eng-grid, run the following code 
```
source /ad/eng/courses/ec/ec535/bashrc_ec535
pwd # make sure you are under ./your/path/to/Chinese_Chess directory
cd ./chess2
qmake
make
file chess2 # check if you get the executable file
```

#### On your local machine
Use `rsync` or `scp` to copy the executable file named "chess2" from your grid directory to your local machine, and then send the file through another `rsync` or `scp` to copy the "chess2" to BBB.
Or you can directly `scp` from BBB. 

#### On BBB
Note: we assume you put the executable file "chess2" under `/root`
```
./chess2
```

Use your fingers to press any button appears on the screen and enjoy the game!


### To run on Mac or Windows platform:
Please load this project into Qt Creator and run it.
