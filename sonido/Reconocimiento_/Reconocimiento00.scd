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



///// RECONOCIMIENTO 00

//// checar que los percs salgan por 4 canales!!
(
SynthDef(\perc_c, {|senal, paneo, out, env, gate = 1, salida|
	senal = SinOsc.ar(130.81);
	env = EnvGen.ar(Env.perc(0.01, 4, 1, -4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(0, salida);
}).add;
);

~perc_c = Synth(\perc_c)



(
SynthDef(\perc_d, {|senal, paneo, out, env, gate = 1, salida|
	senal = SinOsc.ar(146.83);
	env = EnvGen.ar(Env.perc(0.01, 4, 0.5, -4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(1, salida);
}).add;
);

~perc_d = Synth(\perc_d)

(
SynthDef(\perc_f, {|senal, paneo, out, env, gate = 1, salida|
	senal = SinOsc.ar(174.61);
	env = EnvGen.ar(Env.perc(0.01, 4, 1, -4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(2, salida);
}).add;
);

~perc_f = Synth(\perc_f)



(
SynthDef(\perc_g, {|senal, paneo, out, env, gate = 1, salida|
	senal = SinOsc.ar(196.00);
	env = EnvGen.ar(Env.perc(0.01, 4, 0.5, -4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(3, salida);
}).add;
);

~perc_g = Synth(\perc_g)

(
SynthDef(\perc_a, {|senal, paneo, out, env, gate = 1, salida|
	senal = SinOsc.ar(220.00);
	env = EnvGen.ar(Env.perc(0.01, 4, 0.4, -4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(0, salida);
}).add;
);

~perc_a = Synth(\perc_a)


(
SynthDef(\perc_c1, {|senal, paneo, out, env, gate = 1, salida|
	senal = SinOsc.ar(261.63);
	env = EnvGen.ar(Env.perc(0.01, 4, 0.7, -4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(1, salida);
}).add;
);

~perc_c1 = Synth(\perc_c1)



(
SynthDef(\perc_d1, {|senal, paneo, out, env, gate = 1, salida|
	senal = SinOsc.ar(293.66);
	env = EnvGen.ar(Env.perc(0.01, 4, 1, -4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(2, salida);
}).add;
);

~perc_d1 = Synth(\perc_d1)

(
SynthDef(\perc_c2, {|senal, paneo, out, env, gate = 1, salida|
	senal = SinOsc.ar(69.30);
	env = EnvGen.ar(Env.perc(0.01, 4, 1, -4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(3, salida);
}).add;
);

~perc_c2 = Synth(\perc_c2)

(
SynthDef(\perc_g2, {|senal, paneo, out, env, gate = 1, salida|
	senal = SinOsc.ar(392.00);
	env = EnvGen.ar(Env.perc(0.01, 4, 1, -4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(0, salida);
}).add;
);

~perc_g2 = Synth(\perc_g2)

(
SynthDef(\bass1, {|senal, paneo, out, env, gate = 1, salida, frec1 = 73.42, frec2 = 73.42, pan1 = 1|
	senal = SinOsc.ar(frec1);
	env = EnvGen.ar(Env.adsr(10, 10, 0.5, -4), gate, doneAction:2);
	paneo = SinOsc.kr(pan1,0,2,0);
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida, paneo));
}).add;
);

~bass1 = Synth(\bass1)

(
SynthDef(\bass2, {|senal, paneo, out, env, gate = 1, salida, frec1 = 110, frec2 = 73.42, pan1 = 1|
	senal = SinOsc.ar(frec1);
	env = EnvGen.ar(Env.adsr(10, 10, 0.5, -4), gate, doneAction:2);
	paneo = SinOsc.kr(pan1,0,2,0);
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida, paneo));
}).add;
);

~bass2 = Synth(\bass2)
~bass1.set(\frec1, 80)




Tdef(\Reconocimiento00).play;

(
Tdef(\Reconocimiento00, {
	0.25.wait;
	~bass1 = Synth(\bass1);
	0.25.wait;
	~bass2 = Synth(\bass2);
	(
		x=OSCdef(\museOscx, {|msg|
			var freq;
			msg[1].postln;
			if(msg[1]==1,
				{"blink".post;
					~choose = Synth([\perc_c, \perc_d, \perc_f, \perc_g, \perc_a, \perc_c1, \perc_d1, \perc_g2, \perc_c2].choose);
				},{
					"NOT".postln;
				}
			)
		},
		'/muse/elements/blink'
		);
	);
	90.wait;
	/*
	(
		c=OSCdef(\museOscc, {|msg|
			var alpha1, alpha2, alpha3;
			msg.postln;
			alpha1 = msg[1].linlin(0.1,0.9, 73.42, 110);
			//alpha2 = msg[1].linlin(0.1,0.9, 73, 110);
			alpha3 = msg[1].linlin(0.1,0.9, 1, 5);
			~bass1.set(\frec1, alpha1);
			~bass1.set(\pan1, alpha3);
		},'/muse/elements/alpha_relative')
	);
	*/
	x.free;
	~bass1.set(\gate, 0);
	~bass2.set(\gate, 0);
});
);

