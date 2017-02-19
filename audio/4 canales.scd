// Get the local server's options

o = Server.local.options;

// Post the number of output channels

o.numOutputBusChannels.postln;

// Set them to a new number

o.numOutputBusChannels = 6; // The next time it boots, this will take effect

// specify a device

o.device ="FCA610 USB ASIO"; // use a specific soundcard
o.device = nil;	// use the system default soundcard

// Create a new instance of ServerOptions

o = ServerOptions.new;

// Set the memory size to twice the default

o.memSize = 4096;

p=ProxySpace.push(s.boot)

s.scope(4);
s.meter

~a={Out.ar(0,Pulse.kr(2)*SinOsc.ar([120, 120],0,0.25)!2)}
~b={Out.ar(2,Pulse.kr(4)*SinOsc.ar([120, 120]*2,0,0.15)!2)}
~c={Out.ar(4,Pulse.kr(2)*SinOsc.ar([120, 120]*3,0,0.15)!2)}

~a.play
~b.play
~c.play

(
SynthDef(\kick0, {|gate = 1, frec = 110, frecP = 18|
	Out.ar(0, EnvGen.ar(Env.perc(0.1,0.1,1), gate, 1, doneAction:2)*SinOsc.ar(frec,0,0.5)+Pulse.ar(frecP,0.5,0.2))
	}
).add;
SynthDef(\kick1, {
	Out.ar(1, EnvGen.ar(Env.perc(0.1,0.1,1), 1, 1, doneAction:2)*SinOsc.ar(110,0,0.5))
	}
).add;
SynthDef(\kick2, {
	Out.ar(2, EnvGen.ar(Env.perc(0.1,0.1,1), 1, 1, doneAction:2)*SinOsc.ar(110,0,0.5)*Saw.kr(8))
	}
).add;
SynthDef(\kick3, {
	Out.ar(3, EnvGen.ar(Env.perc(0.1,0.1,1), 1, 1, doneAction:2)*SinOsc.ar(110,0,0.5))
	}
).add;
)
Pattern

Synth(\kick0);
Synth(\kick1);
Synth(\kick2);
Synth(\kick3);

(
Tdef(\k4, {50.do {
	Synth(\kick0, [\frecP, [12,18,24].choose]);
	0.25.wait;
	Synth(\kick1);
	0.25.wait;
	Synth(\kick2);
	0.25.wait;
	Synth(\kick3);
	0.25.wait;
	}}
)
)

Tdef(\k4).play;
Tdef(\k4).stop;
