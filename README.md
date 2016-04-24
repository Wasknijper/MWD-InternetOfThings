# Making a remote controlled cat toy
My cat occasionally gets bored being home alone all day, with none of his silly humans to entertain him. And when that happens he likes to find tissues and shred them all over the house. Since my mother and I don't like picking up after him, we figured a toy might help entertain him. However after some experiments, and a whole lot of tissues later, we realized he just can't be bothered by toys that don't move on their own. So this is our final shot, in this short manual I'll how I made a cat toy that can be controlled by a website.

##Hardware
- A NodeMCU
- A breadboard
- A 180 degree servo
- A PIR sensor
- A few male-female and male-male cables
- Micro-USB cable
- Hosting
- A piece of string and a cattoy, or some tape and a laser pointer
- A small stick

##The set-up

###Hardware set-up
The most important thing is the servo. First we need to attach the cat toy to the servo. I used a stick to add some range to the movement of my servo. Then I taped the stick to the 'wing'of the servo. Lastly, tried a cat toy to a piece of string and tied it to the stick. 

*pic*

Now on to the board set-up. We will have to connect the PIR-sensor (to see if our cat is actually doing something) and our servo (or else there will be nothing moving). 

Connect the PIR sensor to the *D0* and the servo to the *D1*. 

*PIC*

When actually using this, make sure to fasten the servo somewhere secure, so your lovely furball won't drag it down when playing with the toy, Securing the wing onto your servo with a screw is also a smart move.

###Hosting set-up
Make sure your hosting supports PHP and that your allowed to post data to it.

Make a few files:
- An index.php where we will make the interface and the post methods
- Servo.txt, where we will post the position of the servo too.
- Movement.json, where we will save if kitty is moving or has moved

####Index.php
Feel free to copy the index.php directly from here.

It contains some PHP code that listens if something is send to our site. The first part, line 2-6, will listen if a value named servo is posted. If this is true, it will save the value in servo.txt.

The second PHP part will listen if another server, not your current host, is requesting/sending some data to our hosting. In here we write the PIR value into movement.json. But before we do so, we add a timestamp, so we know when our furry friend was moving.

Next are some CSS styles, to make everything look pretty. These aren't required.

After that we have the body of our page, this is what you will see in our browser. Here we find a form with a slider, to control the servo and a send button, the current position of the toy and whenether or not our home-tiger is sleeping or moving.

Last is some jQuery to read the last value from movement.js. 

####Servo.txt
Nothing! Just keep this file empty.

####Movement.JSON
An empty array, like so: `[]`

###NodeMCU Code
Feel free to copy the arduino sketch directly from here.

First thing we do is include some libraries:

```
#include <ESP8266WiFi.h>
#include <Servo.h>
```

Now, my .ino file has a lot more includes, however these are automatically added when adding the ESP8266WiFi library.

After that your need to set up the wifi connection, ssid is the name of your wifi and password should speak for it self.
```
char ssid[] = "wifi name";
char pass[] = "your password";
```

After that we need to connect to the hosting. Enter your domain, the path to where you keep movement.json and lastly the port. Usually this is 80, unless you changed this yourself, so in 99% of the cases you don't need to change is,

```
char* host = "www.yourdomain.nl";
String path = "/path/to/movement.json";`
const int httpPort = 80;
```

There are a few more lines you need to edit, like line 44.
```
http.begin("http://yourdomain.com/patg/to/servo.txt");
```

And lines XX
```
client.println("POST /path/to/index.php HTTP/1.1");
client.println("Host: www.yourdomain.com:80");
```

After all that, you can upload the code to your NodeMCU.

##Controlling the servo
If everything went right, you can surf to your host and see something like this:

*pic*

Sliding the slider and hitting send should make you servo change position with in a half second, or maybe a little longer if your wifi is a bit slow.

##References
-
-
-
