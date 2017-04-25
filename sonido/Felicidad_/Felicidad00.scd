s.options.device_("ASIO : ASIO4ALL v2");
s.boot;
s.meter;
Server.default.makeGui;
s.recChannels_(4); // or whatever number of channels
s.record;
stop.record;

c = 4;
s.options.numOutputBusChannels = c;
s.options.sampleRate = 48000;
s.boot;
s.recChannels = c;
s.recHeaderFormat = "WAV";


~cardew_buf = Buffer.read(s, "C:/Users/atheriot/Desktop/OUTPUT/Sounds/Abismo/Felicidad/Cardew_4ch.wav");


(
SynthDef(\Cardew, {| senal, paneo, out, env, gate = 1, salida, dir = 0.9|
	senal = PlayBuf.ar(~cardew_buf.numChannels, ~cardew_buf.bufnum, dir, loop:0, doneaction:0);
	env = EnvGen.ar(Env.adsr(50, 3, 0.4, 20, 0.4, -4, 0), gate, doneAction:2);
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida,paneo,1));
}).add;
)

~cardew = Synth(\Cardew);


(
SynthDef(\solsus00, {|senal, paneo, out, env, gate = 1, salida, freq = 118, arm00 = 1, arm01 = 1, arm02 = 1, arm03 = 1|
	senal = Blip.ar(freq, [arm00, arm01, arm02, arm03]);
	env = EnvGen.ar(Env.adsr(1000, 0.1, 0.1, 10, 0.1, -4, 0), gate, doneAction:2)!4;
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida, paneo, 0.1));
}).add;
);

~solsus00 = Synth(\solsus00);
~solsus.set(\freq, 199);
~solsus.set(\arm00, 1);
~solsus.set(\arm01, 6);
~solsus00.set(\amp, 0);


(
SynthDef(\solsus01, {|senal, paneo, out, env, gate = 1, salida, freq = 156, arm00 = 1, arm01 = 1, arm02 = 1, arm03 = 1|
	senal = Blip.ar(freq, [arm00, arm01, arm02, arm03]);
	env = EnvGen.ar(Env.adsr(1000, 0.1, 0.1, 10, 0.1, -4, 0), gate, doneAction:2)!4;
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida, paneo, 0.1));
}).add;
);

~solsus01 = Synth(\solsus01);

(
Tdef(\felicidad00, {
	1.wait;
	(
		k=OSCdef(\museOsck, {|msg|
			var acc00, acc01, acc02, acc03;
			msg.postln;
			acc00 = msg[1].linlin(-2000.0, 1996.1, 1, 7);
			acc01 = msg[1].linlin(-2000.0, 1996.1, 1, 10);
			acc02 = msg[1].linlin(-2000.0, 1996.1, 1, 13);
			acc03 = msg[1].linlin(-2000.0, 1996.1, 1, 4);
			~solsus00.set(\arm00, acc00);
			~solsus00.set(\arm01, acc01);
			~solsus00.set(\arm02, acc02);
			~solsus00.set(\arm03, acc03);
			~solsus01.set(\arm00, acc00);
			~solsus01.set(\arm01, acc01);
			~solsus01.set(\arm02, acc02);
			~solsus01.set(\arm03, acc03);
		},'/muse/acc')
	);
	1.wait;
	(
		x=OSCdef(\museOscx, {|msg|
			var freq;
			msg[1].postln;
			if(msg[1]==1,
				{"blink".post;
					~solsus00.set(\freq, 237);
					~solsus01.set(\freq, 312);
					(
						Pbind(
							\degree, Pseq([1,2,4,5], 1),
							\dur, 1,
							\octave, 4,
							\root, 1
						).play
					)
				},{
					"false".postln;
					~solsus00.set(\freq, 118);
					~solsus01.set(\freq, 156);

				}
			)
		},
		'/muse/elements/blink'
		);
	);
	3.wait;
	~solsus00 = Synth(\solsus00);
	0.5.wait;
	~solsus01 = Synth(\solsus01);
	20.wait;
	~cardew = Synth(\Cardew);
	40.wait;
	~solsus00.set(\gate, 0);
	1.wait;
	~solsus01.set(\gate, 0);
	k.free;
	20.wait;
	x.free;
}));

x.free;


(
Pbind(
	\degree, Pseq([1,3,5,7], 3),
	\dur, 0.125,
	\octave, 4,
	\root, 3
).play
)



/////// frecuencias

c = 130
dsus = 156
f = 175
g = 199
asus = 118