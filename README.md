# SoundTriggerVolume-UnrealEngine
Simple C++ Actor Volume That Triggers A Sound Cue.

Implementation:

First you'll need to create a public c++ actor class name it "SoundTriggerVolume" and place it in preferably a "Volumes" Folder.
When it compiles copy and paste the .h and .cpp code in their respected scripts in your IDE.
Compile and re-launch Unreal Engine.
And the class will be ready for you to drag into your level and configure the default properties.
If you edit other parameters that are not exposed (e.x. Pitch Level) right click the c++ class and create a blueprint class based on it

WARNING:
In the SoundTriggerVolume.cpp I used PostEditChangeProperty which is used to modify the actor in the level editor without creating child Blueprints of it
This will cause an error when you build the game for Shipping so make sure to comment the params used in the function out before building the game.

Info:

If you have some experience with c++ you'll have no problem understanding how it works and how to expand uppon this system,
but if you have no experience I've tried my best commenting things appropriately so that you can work your way around it if you wanna understand how it works.



