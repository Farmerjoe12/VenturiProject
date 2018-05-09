# VenturiProject

The 'Venturi Project', named because of the sheer power over wind and nature given to the user by the software in this project, is an open source alternative to the all the proprietary applications in the world. With the simple modification in a script, or the turn of a potentiometer, you will have immediate control over the airflow from your case fans and the water flowing from the pump at the heart of your custom water-cooling loop. Although 'Poseidon' was a runner up, this project started with humble beginnings as a simple fan controller, and over time will evolve to include whatever is deemed neccessary by myself and any community that arises to support Venturi.

Wall of text incoming.

# Repository Details

This repo will house the sketches that allow a user to control various components in their enthusiast PC mods. Included are things like LED strips, fan controllers, pump controllers, and more. These sketches are for the most part designed to be generic, and will (probably not) work with your (name brand) equipment. Note: the PWM controllers are platform-independent, and *should* control anything that is PWM, however YMMV.

# Project Details

The Venturi Project is a compilation of Arduino Sketches, and as such, requires an arduino to access the raw power enclosed in these files. As of the initial commit, the project has functionality for fans, a water pump, and an LED strip. The water pump control is identical to the fan control, so the same file can be used for both - with a little modification. I also will include some files that implement a water flow sensor as well as a temperature sensor. These additional sensors are not currently tied into the main file because they are not being implemented in my system as of right now. 

# Project Structure

There is no traditional 'main' executable file in the arduino-verse, and as such all files can be (and have code written to do this) run on their own as stand-alone sketches. However, the main structure that you will find is that within "Computer_Controller", all files that I am currently using are combined in a conglomeration of sorts in order to mix and match the functionality of all the desired components. On that note, the sketches themselves can be considered components, and the Computer_Controller sketch is the piece of equipment that arises when you put the components together. Note, in this case, the grand sum is no less or greater than the sum of its' parts, because it is literally just the sum of the parts. Also note that since this project is not the typical software project with source files and mains, the repo structure will be different as well; organized by what the sketches do in their respective folders.

# Project Goals

I created this project to act as a hub for any and all sketches that can be used on the arduino platform to integrate into your PC mods. The code here can be used without my permission, as some of the code found here is not written by me. I am acting as nothing more than the gatherer and compiler for all of this code across the internet so you and I can benefit from the work of the community. 

# Future Plans / Dreams

I would like this project to evolve into something that rivals the proprietary software of the giants in industry. I know that's a stretch considering this repo is open source and *probably* will not be the subject of any paid labor, but there's no reason that it can't have that same level of usability. I'd like to see a decent GUI to control things like fan speed and LED color/programs so that we don't have to manually edit sketches every time we want to change something. Right now I'm using (analog) switches and potentiometers to modulate fan speeds and turn led's on and off, and would love to see everything software controlled. Alas, I don't really understand the underlying nature of Arduino, and I'm not sure entirely that a real-time GUI can be created. This is left as an exercise for the student ;)

I also welcome anyone who is interested to create some neat LED functions like a 'breathing' or a 'carnival' effect. Any and all contributions are welcome, open an issue or write me if you want, see contact info.

# Additional Notes

Be aware that some code does not work with other code. For example; if you are using PWM on your water pump and you include code that uses the 'delay()' call, your sketch will be pausing for an amount of time which **will** cause your pump to stop and bad things will happen (ask me how I know this). As a result, be sure to read the comments in **ALL** the sketches you are using (very carefully) and be aware and cognizant that this is not a system that is "Plug and Play", or "Set and Forget". Be careful in what you're doing, and make sure you know what you're doing when you hit upload. Also, it doesn't hurt to test components independently prior to installation in a 'live' system, this process *will* help you iron out any issues and detect possible problems prior to their occurance. See disclaimer below.

Also be aware that some libraries are reqiured to use this code, theses libraries themselves are no large challenge to include in your own projects. The libraries you need are pre-included in the files, and if you want to use the file, simply use the 'manage libraries' tool in your Arduino IDE to download them yourself. As of right now, there are no libraries that are not available in the arduino IDE for download.

# DISCLAIMER

I am not responsible for any damage that may occur to your system as a result of using this software. I am only a sole provider and this repo provides a collection of software that you may use in your projects to speed up your development time, and overall advance the field of enthusiast PC modding. I am making no claims from here on out that I own any of this code and as such, it is not my responsibility to fix any broken or damaged equipment. However, I'd love to help you troubleshoot any issues you're having, and do not hesitate to contact me if you want to talk, have an idea for the project, or have an issue.

Please do not try and sue me because your pump stopped as a result of your negligence (not this code) and your system melted, your processor overheated, or the sun stopped emmitting light. At the end of the day, *YOU* are in charge of what is implemented on *YOUR* system, so any damage is a result of your negligence.

# Contact Info

You can write me on GitHub if you want, be aware that I may or may not see it. Discord is the most reliable contact method of choice, so shoot me a dm.

Discord: Farmerjoe#6151