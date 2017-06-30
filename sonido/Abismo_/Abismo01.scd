s.boot;
s.meter;
s.options.device = "ASIO : UMC ASIO Driver"
Server.default.makeGui;
s.recChannels_(4);
s.record;
stop.record;
s.options.numOutputBusChannels = 4;
s.options.sampleRate = 48000;
s.recHeaderFormat = "WAV";



//// ABISMO01 //////////

//seguir trabajando este movimiento con blinks que saturen



(
SynthDef(\klang00, {| senal, paneo, out, env, gate = 1, salida, num01 = 440, num02 = 880|
	senal = Klang.ar(`[ {exprand(num01, num02)}.dup(5), nil, nil ], 1, 0) * 0.04;
	env = EnvGen.ar(Env.perc(1, 2, 1, 4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida,paneo,level:0.8));
}).add;
)


~klang00 = Synth(\klang00);
~klang.set(\gate, 0);

(
SynthDef(\klang01, {| senal, paneo, out, env, gate = 1, salida, num01 = 110, num02 = 1200|
	senal = Klang.ar(`[ {exprand(num01, num02)}.dup(5), nil, nil ], 1, 0) * 0.04;
	env = EnvGen.ar(Env.perc(1, 2, 1, 4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida,paneo,level:0.8));
}).add;
)

~klang01 = Synth(\klang01);

(
SynthDef(\klang02, {| senal, paneo, out, env, gate = 1, salida, num01 = 110, num02 = 900|
	senal = Klang.ar(`[ {exprand(num01, num02)}.dup(5), nil, nil ], 1, 0) * 0.04;
	env = EnvGen.ar(Env.perc(1, 2, 1, 4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida,paneo,level:0.8));
}).add;
)


~klang02 = Synth(\klang02);
~klang.set(\gate, 0);

(
SynthDef(\klang03, {| senal, paneo, out, env, gate = 1, salida, num01 = 70, num02 = 1300|
	senal = Klang.ar(`[ {exprand(num01, num02)}.dup(5), nil, nil ], 1, 0) * 0.04;
	env = EnvGen.ar(Env.perc(1, 2, 1, 4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida,paneo,level:0.8));
}).add;
)

~klang03 = Synth(\klang03);

(
SynthDef(\klang04, {| senal, paneo, out, env, gate = 1, salida, num01 = 300, num02 = 2000|
	senal = Klang.ar(`[ {exprand(num01, num02)}.dup(5), nil, nil ], 1, 0) * 0.04;
	env = EnvGen.ar(Env.perc(1, 2, 1, 4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida,paneo,level:0.8));
}).add;
)


~klang04 = Synth(\klang04);
~klang04.set(\gate, 0);

(
SynthDef(\klang05, {| senal, paneo, out, env, gate = 1, salida, num01 = 50, num02 = 1600|
	senal = Klang.ar(`[ {exprand(num01, num02)}.dup(5), nil, nil ], 1, 0) * 0.04;
	env = EnvGen.ar(Env.perc(1, 2, 1, 4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida,paneo,level:0.8));
}).add;
)

~klang05 = Synth(\klang05);




(
Tdef(\Abismo01, {
	s.record;
	1.wait;
	~resonz00 = Synth(\resonz00);
	5.wait;
	~resonz01 = Synth(\resonz01);
	10.wait;
	(
		x=OSCdef(\museOscx, {|msg|
			var freq;
			msg[1].postln;
			if(msg[1]==1,
				{"blink".post;
					~choose = Synth([\klang00, \klang01, \klang02, \klang03, \klang04, \klang05].choose);
				},{
					"NOT".postln;
				}
			)
		},
		'/muse/elements/blink'////////////////////////DIVIDIR BLINKS A UN USUARIO Y EL OTRO
		);
	);
	65.wait;
	x.free;
	~resonz00.set(\gate, 0);
	2.wait;
	~resonz01.set(\gate, 0);
	10.wait;
	s.stop.record;
	"FIN".postln;
});
)

Tdef(\Abismo01).play

(
SynthDef(\resonz00, {| senal, paneo, out, env, gate = 1, salida, num01 = 50, num02 = 1600|
	senal = Resonz.ar(WhiteNoise.ar(1), 2000, XLine.kr(0.001, 1, 55));
	env = EnvGen.ar(Env.adsr(1, 5, 1, 1, 1, -4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida,paneo,level:1));
}).add;
)

~resonz00 = Synth(\resonz00);
~resonz01 = Synth(\resonz01);


(
SynthDef(\resonz01, {| senal, paneo, out, env, gate = 1, salida, num01 = 50, num02 = 1600|
	senal = Resonz.ar(WhiteNoise.ar(1), XLine.kr(1000,8000, 55), 0.05);
	env = EnvGen.ar(Env.adsr(10, 5, 1, 1, 1, -4), gate, doneAction:2);
	salida = senal*env;
	Out.ar(0, Pan4.ar(salida,paneo,level:0.8));
}).add;
)

~resonz01 = Synth(\resonz01);







